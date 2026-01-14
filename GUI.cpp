//---------------------------------------------------------------------
//---------------------------------------------------------------------
// The Nonlinear Game Engine (NGE) version 1.1
// (c) Mikael Fridenfalk
// All rights reserved
// The engine is a template for use in the course:
// Real-Time Graphics Programming for Games 1, 7.5 c, 2025
// Uppsala University, Sweden
// Other use requires a written permission from the copyright holder
//---------------------------------------------------------------------
//---------------------------------------------------------------------
#include "GUI.h"
//---------------------------------------------------------------------
//---------------------------------------------------------------------
GUI::GUI(){
    //---------------------------------------------
    Cam_Init();
    //---------------------------------------------
    mTime0 = SDL_GetTicks();
    mTimeInSecs = mTime0/1000;
    //---------------------------------------------
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
GUI::~GUI(){
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void GUI::InitAttributes(){
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE,    8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,  8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,   8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,  8);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);//24-bit Depth Buffer
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,1);//MSAA
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,4);//MSAA
    SDL_GL_SetSwapInterval(1);//Enable Vsync
    //----------------------------------
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void GUI::CreateSurface(){
    InitAttributes();//Context Attr
    //----------------------------------If High-DPI mode is off
    //SDL_DisplayMode dispMode;
    //SDL_GetCurrentDisplayMode(0, &dispMode);
    //sW = dispMode.w; sH = dispMode.h;
    //----------------------------------Create window
    mScreen = SDL_CreateWindow("GFX",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               sW, sH,
                               SDL_WINDOW_OPENGL);
#ifdef __APPLE__
    SDL_SetWindowFullscreen(mScreen,SDL_WINDOW_FULLSCREEN);
#endif
    SDL_GL_CreateContext(mScreen);
    //----------------------------------
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void GUI::SetCamera(int cIdx){//Augmented
    //---------------------------------------
    //---------------------------------------
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double np = mMode == PLAY_MODE ? mNearPlane : mNearPlaneDesign;
    double fp = mMode == PLAY_MODE ? mFarPlane : mFarPlaneDesign;
    gluPerspective(mFOV, double(sW)/double(sH), np, fp);
    //---------------------------------------
    //---------------------------------------
    if (cIdx == 1) Cam();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if (cIdx == 2) Cam();
    //---------------------------------------
    //---------------------------------------
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void GUI::InitGFX(){
    //---------------------------------------
    //---------------------------------------
    CreateSurface();
    //---------------------------------------
    //---------------------------------------
    gluQuadricTexture(mQuadratic, GL_TRUE);
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    //---------------------------------------
    //---------------------------------------
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //---------------------------------------
    glColorMaterial (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    //---------------------------------------
    //glShadeModel(GL_SMOOTH);
    glShadeModel(GL_FLAT);
    //---------------------------------------
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    //---------------------------------------
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    //---------------------------------------
    //---------------------------------------
    
    //---------------------------------------
    //---------------------------------------
    //GLfloat c[] = {0.f,0.3f,0.5f,1.f};
    //GLfloat c[] = {.2f,.4f,.6f,1.f};
    //GLfloat c[] = {.8f,.8f,1.f,1.f};
    //GLfloat c[] = {1.f,1.f,1.f,1.f};
    GLfloat c[] = {0.f,0.f,.2f,1.f};
    glClearColor(c[0],c[1],c[2],c[3]);
    //---------------------------------------
    //---------------------------------------

    //---------------------------------------
    //---------------------------------------
    //GL_EXP, GL_EXP2, GL_LINEAR
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_DENSITY, .1f);
    //---------------------------------------
    //GL_FASTEST, GL_NICEST, GL_DONT_CARE
    glHint(GL_FOG_HINT, GL_FASTEST);
    //---------------------------------------
    glFogf(GL_FOG_START, 1.f);
    glFogf(GL_FOG_END, 50.f);
    glFogfv(GL_FOG_COLOR,c);
    if (mFogON) glEnable(GL_FOG);
    //---------------------------------------
    //---------------------------------------
    
    //---------------------------------------
    //---------------------------------------
    GLfloat ambient[] = {.3f, .3f, .3f, 1.f};
    GLfloat diffuse[] = {.8f, .8f, .8f, 1.f};
    GLfloat position[] = {2.f, 2.f, 2.f, 0.f};
    //---------------------------------------
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    //---------------------------------------
    GLfloat front_mat_shininess[] = {60.f};
    GLfloat front_mat_specular[]  = {.5f, .5f, .2f, 1.f};
    GLfloat front_mat_diffuse[]   = {1.f, .9f, .2f, 1.f};
    //---------------------------------------
    glMaterialfv(GL_FRONT, GL_SHININESS, front_mat_shininess);
    glMaterialfv(GL_FRONT, GL_SPECULAR, front_mat_specular);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, front_mat_diffuse);
    //---------------------------------------
    GLfloat back_mat_shininess[]  = {60.f};
    GLfloat back_mat_specular[]   = {.2f, .2f, .2f, 1.f};
    GLfloat back_mat_diffuse[]    = {.5f, .5f, .28f, 1.f};
    //---------------------------------------
    glMaterialfv(GL_BACK, GL_SHININESS, back_mat_shininess);
    glMaterialfv(GL_BACK, GL_SPECULAR, back_mat_specular);
    glMaterialfv(GL_BACK, GL_DIFFUSE, back_mat_diffuse);
    //---------------------------------------
    //const GLfloat flag[] = {GL_FALSE};
    const GLfloat flag[] = {GL_TRUE};
    glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, flag);
    //---------------------------------------
    //---------------------------------------
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //---------------------------------------
    //---------------------------------------
    glEnable(GL_MULTISAMPLE_ARB);
    //---------------------------------------
    //---------------------------------------
    int idx = 1;
    int A[][3] = {{29,18,19},{40,50,23},{2,50,23}};
    mTexIdxV[0] = A[idx][0];
    mTexIdxV[1] = A[idx][1];
    mTexIdxV[2] = A[idx][2];
    For (i,3){
        char name[32];
        snprintf(name,32,"Tex_%d.png",mTexIdxV[i]);
        Tex_Load(i,name);
    }
    //---------------------------------------
    //---------------------------------------
    Tex_Load(3,"Tex_A1.png");//###
    Tex_Load(4,"Tex_9.jpg");//###
    //---------------------------------------
    //---------------------------------------
    glViewport(0,0,sW,sH);
    //---------------------------------------
    //---------------------------------------
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void GUI::Init(){
    SDL_Init(SDL_INIT_EVERYTHING);
    InitGFX();
    Music_Init();
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void GUI::Tex_Flip(SDL_Surface *s){
    //---------------------------------------
    //---------------------------------------
    //Compared to reading texture from a fast SSD, this method is
    //quick and solves core issues that else may appear in more
    //advanced applications where the texture instead is flipped
    //vertically through texture coords...
    //---------------------------------------
    //---------------------------------------
    SDL_LockSurface(s);
    int NN = s->pitch * s->h;
    UCHAR *p = new UCHAR[NN], *t = new UCHAR[NN];
    SDL_memcpy(t,s->pixels,NN);
    For (i,s->h) SDL_memcpy(&p[i*s->pitch],
                            &t[(s->h-i-1)*s->pitch], s->pitch);
    SDL_memcpy(s->pixels,p,NN); delete [] p; delete [] t;
    SDL_UnlockSurface(s);
    //---------------------------------------
    //---------------------------------------
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
bool GUI::Tex_Load(int texIdx, const char s[128]){
    //---------------------------------------
    //---------------------------------------
    char fileName[256];
    snprintf(fileName,32,"Tex/%s",s);
    SDL_Surface * surface = IMG_Load(fileName);
    if (!surface){
        printf("Error! Texture not found...\n");
        return false;
    }
    Tex_Flip(surface);
    //---------------------------------------
    //---------------------------------------
    int imgFormat = -1;
    GLint nOfColors = surface->format->BytesPerPixel;
    if (nOfColors == 4){
        if (surface->format->Rmask == 0xFF)
            imgFormat = GL_RGBA;
        else imgFormat = GL_BGRA;
    }
    else if (nOfColors == 3){
        if (surface->format->Rmask == 0xFF)
            imgFormat = GL_RGB;
        else imgFormat = GL_BGR;
    }
    else {
        printf("Error! The texture is not a truecolor image...\n");
        return false;
    }
    //---------------------------------------
    //---------------------------------------
    glBindTexture(GL_TEXTURE_2D, texIdx);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    //---------------------------------------
    //---------------------------------------
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //---------------------------------------
    //---------------------------------------
    bool mipmap = true;
    if (mipmap){
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
    }
    else glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //---------------------------------------
    //---------------------------------------
    glTexImage2D(GL_TEXTURE_2D, 0, nOfColors,
                 surface->w, surface->h,
                 0, imgFormat, GL_UNSIGNED_BYTE, surface->pixels);
    //---------------------------------------
    //---------------------------------------
    SDL_FreeSurface(surface);
    //---------------------------------------
    //---------------------------------------
    return true;
    //---------------------------------------
    //---------------------------------------
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
inline void GUI::glTranslatedv(const double v[3]){
    glTranslated(v[0],v[1],v[2]);
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------







//---------------------------------------------------------------------
//---------------------------------------------------------------------
//                              Aux Draw
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void GUI::Draw_Dome(){
    glShadeModel(GL_SMOOTH);
    double R = .999 * mFarPlane, interp, s, x, y, z, v, w;
    int V = 10, W = 10;
    double col[3], col0[3], col1[3];
    double deltaV = 2. * M_PI / double(V), deltaW = M_PI / double(W);
    col0[0] = col0[1] = col0[2] = 1.;
    col1[0] = col1[1] = .15; col1[2] = .78;
    glDisable(GL_LIGHTING);
    glBegin(GL_QUAD_STRIP);
    For (j,W) For (i,V){
        v = double(i) * deltaV;
        For (k,2){
            w = double(j+1-k) * deltaW; s = sin(w);
            x = s * sin(v);//X <=>  y
            y =   - cos(w);//Y <=> -z
            z = s * cos(v);//Z <=>  x
            interp = .5 * (1. + y);
            For (m,3) col[m] = col0[m] + interp * (col1[m] - col0[m]);
            glColor3dv(col);
            glVertex3d(mEye[0]+R*x,mEye[1]+R*y,mEye[2]+R*z);
        }
    }
    glEnd();
    //glEnable(GL_LIGHTING);
    glShadeModel(GL_FLAT);
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void GUI::Draw_TexDome(){
    //---------------------------------------------
    //---------------------------------------------
    glBindTexture(GL_TEXTURE_2D,4);//###
    glDisable(GL_LIGHTING);
    //---------------------------------------------
    //---------------------------------------------
    glEnable(GL_TEXTURE_2D);
    //---------------------------------------------
    //---------------------------------------------
    //glColor3ub(200,100,90);//###
    glColor3ub(255,255,255);
    //---------------------------------------------
    //---------------------------------------------
    double R, p[3];
    if (mMode == DESIGN_MODE){
        R = .9 * mFarPlaneDesign;
        For (i,3) p[i] = mEyeDesign[i];
    }
    else {
        R = .9 * mFarPlane;
        For (i,3) p[i] = mEye[i];
    }
    //---------------------------------------------
    //---------------------------------------------
    glPushMatrix();
    glTranslatedv(p);
    glRotated(90.,1.,0.,0.);
    gluSphere(mQuadratic,R,16,16);
    glPopMatrix();
    //---------------------------------------------
    //---------------------------------------------
    glDisable(GL_TEXTURE_2D);
    //glEnable(GL_LIGHTING);
    //---------------------------------------------
    //---------------------------------------------
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
//                       Draw Transparent Floor
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void GUI::Draw_Floor(){
    //--------------------------------------------
    //--------------------------------------------
    bool draw = mMode == PLAY_MODE || mEyeDesign[1] > 0.;
    //--------------------------------------------
    //--------------------------------------------
    if (!draw) return;
    //--------------------------------------------
    //--------------------------------------------
    double s = 1000., s1 = 0.5*s, y = -1.;
    glDisable(GL_LIGHTING);
    //glEnable(GL_BLEND);
    glColor4ub(0,0,31,255);
    //glColor4ub(0,0,63,204);
    //glColor3ub(0,42,119);
    glBegin(GL_QUADS);
    glNormal3d(0.,1.,0.);
    glVertex3d(-s1,y,-s1); glVertex3d(-s1,y, s1);
    glVertex3d( s1,y, s1); glVertex3d( s1,y,-s1);
    glEnd();
    //glDisable(GL_BLEND);
    //glEnable(GL_LIGHTING);
    //--------------------------------------------
    //--------------------------------------------
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
//                           Draw Floor Grid
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void GUI::Draw_Grid(){
    //-----------------------
    double y = 0.;
    //-----------------------
    glDisable(GL_LIGHTING);
    //-----------------------
    glLineWidth(1);
    glColor3ub(255,255,255);
    int n = 5;
    For (i,2*n+1){
        glBegin(GL_LINES);
        glVertex3d(-n,y,i-n);
        glVertex3d(n,y,i-n);
        glVertex3d(i-n,y,-n);
        glVertex3d(i-n,y,n);
        glEnd();
    }
    //-----------------------
    //glEnable(GL_LIGHTING);
    //-----------------------
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
//                           Draw Coord Sys
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void GUI::Draw_CoordSys(){
    //-----------------------
    if (!mCoordSysON) return;
    //-----------------------
    Draw_Grid();
    //-----------------------
    glEnable(GL_LIGHTING);
    //-----------------------
    glShadeModel(GL_SMOOTH);
    //-----------------------
    int s = 32;
    //-----------------------Origin
    glColor3ub(32,32,32);
    gluSphere(mQuadratic,.02,s,s);
    //-----------------------x-axis
    glColor3ub(255,0,0);
    glPushMatrix();
    glTranslated(1,0,0);
    glRotated(90,0,1,0);
    gluCylinder(mQuadratic,.06,0.,0.,s,1);
    gluCylinder(mQuadratic,.06,0.,.3,s,1);
    glTranslated(0,0,-1);
    gluCylinder(mQuadratic,.01,.01,1.,s,1);
    glPopMatrix();
    //-----------------------y-axis
    glColor3ub(0,255,0);
    glPushMatrix();
    glTranslated(0,1,0);
    glRotated(-90,1,0,0);
    gluCylinder(mQuadratic,.06,0.,0.,s,1);
    gluCylinder(mQuadratic,.06,0.,.3,s,1);
    glTranslated(0,0,-1);
    gluCylinder(mQuadratic,.01,.01,1.,s,1);
    glPopMatrix();
    //-----------------------z-axis
    glColor3ub(0,0,255);
    glPushMatrix();
    glTranslated(0,0,1);
    gluCylinder(mQuadratic,.06,0.,0.,s,1);
    gluCylinder(mQuadratic,.06,0.,.3,s,1);
    glTranslated(0,0,-1);
    gluCylinder(mQuadratic,.01,.01,1.,s,1);
    glPopMatrix();
    //-----------------------
    glShadeModel(GL_FLAT);
    //-----------------------
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
//                               Metrics
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void GUI::Eval_FPS(){
    //--------------------------------------------
    mFrameCounter++;
    //--------------------------------------------
    UINT time1 = SDL_GetTicks();
    UINT timeInSecs = time1/1000;
    if (timeInSecs > mTimeInSecs){
        mTimeInSecs = timeInSecs;
        mFPS = mFrameCounter - mFrameCounter0;
        mFrameCounter0 = mFrameCounter;
    }
    //--------------------------------------------
    mDeltaT_Active = .9 * mDeltaT_Active + .1 * double(time1 - mTime0);
    //--------------------------------------------
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void GUI::Draw_2D_Page1(){
    //--------------------------------------------
    //--------------------------------------------
    Cam2D_SwitchTo2DMode_Begin();
    //--------------------------------------------
    //--------------------------------------------
    int i = 24;
    char s[][16] = {"DESIGN","PLAY"};
    Draw2D_MtxText(i--,"mMode = %s",s[mMode]);
    Draw2D_MtxText(i--,"SDL_GetTicks() = %u ms",SDL_GetTicks());
    Draw2D_MtxText(i--,"mFrameCounter = %u",mFrameCounter);
    Draw2D_MtxText(i--,"mFPS = %u",mFPS);
    Draw2D_MtxText(i--,"mDeltaT_Active = %1.0lf ms",mDeltaT_Active);
    //--------------------------------------------
    Draw2D_MtxText(i--,"mTexIdxV[0] = %d",mTexIdxV[0]);
    Draw2D_MtxText(i--,"mTexIdxV[1] = %d",mTexIdxV[1]);
    Draw2D_MtxText(i--,"mTexIdxV[2] = %d",mTexIdxV[2]);
    //--------------------------------------------
    Draw2D_MtxText(i--,"mPlayerPos: [%3.3lf,%3.3lf,%3.3lf]",
                   mPlayerPos[0],mPlayerPos[1],mPlayerPos[2]);
    Draw2D_MtxText(i--,"mFlyVel: [%3.3lf,%3.3lf,%3.3lf]",
                   mFlyVel[0],mFlyVel[1],mFlyVel[2]);
    Draw2D_MtxText(i--,"mFootholdVel: [%3.3lf,%3.3lf,%3.3lf]",
                   mFootholdVel[0],mFootholdVel[1],mFootholdVel[2]);
    Draw2D_MtxText(i--,"mPlayerLookAtDir: [%3.3lf,%3.3lf,%3.3lf]",
                   mPlayerLookAtDir[0],
                   mPlayerLookAtDir[1],
                   mPlayerLookAtDir[2]);
    int x;
    SDL_GL_GetAttribute(SDL_GL_DEPTH_SIZE, &x);
    Draw2D_MtxText(i--,"Depth Buffer Bits: %d",x);
    Draw2D_MtxText(i--,"mTheta_CamRotationFactor = %3.1lf",mTheta_CamRotationFactor);
    Draw2D_MtxText(i--,"mV_CamRotationFactor = %3.1lf",mV_CamRotationFactor);
    Draw2D_MtxText(i--,"mRadius_Cam = %3.3le m",mRadius_Cam);
    Draw2D_MtxText(i--,"mMouseX = %d",mMouseX);
    Draw2D_MtxText(i--,"mMouseY = %d",mMouseY);
    Draw2D_MtxText(i--,"mMouseMotionX = %d",mMouseMotionX);
    Draw2D_MtxText(i--,"mMouseMotionY = %d",mMouseMotionY);
    Draw2D_MtxText(i--,"mMouseMotionRelX = %d",mMouseMotionRelX);
    Draw2D_MtxText(i--,"mMouseMotionRelY = %d",mMouseMotionRelY);
    Draw2D_MtxText(i--,"mMouseWheel_Accum = %d",mMouseWheel_Accum);
    Draw2D_MtxText(i--,"mEye = [%3.3lf,%3.3lf,%3.3lf]",mEye[0],mEye[1],mEye[2]);
    //--------------------------------------------
    //--------------------------------------------
    Draw_Test2D();
    //--------------------------------------------
    //--------------------------------------------
    Cam2D_SwitchTo2DMode_End();
    //--------------------------------------------
    //--------------------------------------------
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void GUI::Draw_2D_Page2(){
    //--------------------------------------------
    //--------------------------------------------
    Cam2D_SwitchTo2DMode_Begin();
    //--------------------------------------------
    //--------------------------------------------
    int i = 17;
    //--------------------------------------------
    //--------------------------------------------
    Draw2D_MtxText(i--,"Lsys: mTimeWarp0 = %d",mTimeWarp0);
    Draw2D_MtxText(i--,"Lsys: mDrawCounter = %d",Get_DrawCounter());
    Draw2D_MtxText(i--,"Prim: mPrimN = %d",Get_PrimN());
    //--------------------------------------------
    //--------------------------------------------
    Draw2D_MtxText(i--,"mUL0 = [%3.3lf,%3.3lf,%3.3lf]",mUR0[0],mUR0[1],mUR0[2]);
    Draw2D_MtxText(i--,"mUL0 = [%3.3lf,%3.3lf,%3.3lf]",mUL0[0],mUL0[1],mUL0[2]);
    Draw2D_MtxText(i--,"mDL0 = [%3.3lf,%3.3lf,%3.3lf]",mDL0[0],mDL0[1],mDL0[2]);
    Draw2D_MtxText(i--,"mDR0 = [%3.3lf,%3.3lf,%3.3lf]",mDR0[0],mDR0[1],mDR0[2]);
    Draw2D_MtxText(i--,"mUR1 = [%3.3lf,%3.3lf,%3.3lf]",mUR1[0],mUR1[1],mUR1[2]);
    Draw2D_MtxText(i--,"mUL1 = [%3.3lf,%3.3lf,%3.3lf]",mUL1[0],mUL1[1],mUL1[2]);
    Draw2D_MtxText(i--,"mDL1 = [%3.3lf,%3.3lf,%3.3lf]",mDL1[0],mDL1[1],mDL1[2]);
    Draw2D_MtxText(i--,"mDR1 = [%3.3lf,%3.3lf,%3.3lf]",mDR1[0],mDR1[1],mDR1[2]);
    //--------------------------------------------
    //--------------------------------------------
    Draw2D_MtxText(i--,"mN_Right = [%3.3lf,%3.3lf,%3.3lf]",mN_Right[0],mN_Right[1],mN_Right[2]);
    Draw2D_MtxText(i--,"mN_Up    = [%3.3lf,%3.3lf,%3.3lf]",mN_Up[0],mN_Up[1],mN_Up[2]);
    Draw2D_MtxText(i--,"mN_Left  = [%3.3lf,%3.3lf,%3.3lf]",mN_Left[0],mN_Left[1],mN_Left[2]);
    Draw2D_MtxText(i--,"mN_Down  = [%3.3lf,%3.3lf,%3.3lf]",mN_Down[0],mN_Down[1],mN_Down[2]);
    Draw2D_MtxText(i--,"mN_Far   = [%3.3lf,%3.3lf,%3.3lf]",mN_Far[0],mN_Far[1],mN_Far[2]);
    Draw2D_MtxText(i--,"mN_Near  = [%3.3lf,%3.3lf,%3.3lf]",mN_Near[0],mN_Near[1],mN_Near[2]);
    //--------------------------------------------
    //--------------------------------------------
    Draw_Test2D();//###
    //--------------------------------------------
    //--------------------------------------------
    Cam2D_SwitchTo2DMode_End();
    //--------------------------------------------
    //--------------------------------------------
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void GUI::Draw_2D_Page3(){
    //--------------------------------------------
    //--------------------------------------------
    Cam2D_SwitchTo2DMode_Begin();
    //--------------------------------------------
    //--------------------------------------------
    int a = 1;
    //--------------------------------------------
    //--------------------------------------------
    //                     T1
    //--------------------------------------------
    //--------------------------------------------
    if (mLectureIdx == 0){
        switch (mSlideIdx){
            case 0:
                Draw2D_MtxText_XL(3+a,"   GFX PIPELINE"); break;
            case 1:
                Draw2D_MtxText_XL(3+a,"  TRANSPARENCY");
                Draw2D_MtxText_XL(2+a,"  + DEPTH BUFFER"); break;
            case 2:
                Draw2D_MtxText_XL(3+a,"   CUBE+TEXTURE"); break;
            case 3:
                Draw2D_MtxText_XL(3+a,"  WINDOW");
                Draw2D_MtxText_XL(2+a,"  <-> FULLSCREEN"); break;
            case 4:
                Draw2D_MtxText_XL(3+a," CAMERA + LIGHTS"); break;
            case 5:
                Draw2D_MtxText_XL(3+a,"   POINT LIGHTS"); break;
        }
    }
    //--------------------------------------------
    //--------------------------------------------
    //                     T2
    //--------------------------------------------
    //--------------------------------------------
    if (mLectureIdx == 1){
        switch (mSlideIdx){
            case 0:
                Draw2D_MtxText_XL(3+a,"SPHERE & CYLINDER");
                Draw2D_MtxText_XL(2+a,"       + TEXTURE"); break;
            case 1:
                Draw2D_MtxText_XL(3+a,"      SKYBOX"); break;
            case 2:
                Draw2D_MtxText_XL(3+a,"    2D <-> 3D"); break;
            case 3:
                Draw2D_MtxText_XL(3+a,"  IMAGE CAPTURE"); break;
            case 4:
                Draw2D_MtxText_XL(3+a," MINIMAL");
                Draw2D_MtxText_XL(2+a," PLAYER PHYSICS"); break;
            case 5:
                Draw2D_MtxText_XL(3+a," PLAYER <-> DESIGN");
                Draw2D_MtxText_XL(2+a,"    MOUSE CTRL"); break;
        }
    }
    //--------------------------------------------
    //--------------------------------------------
    //                     T3
    //--------------------------------------------
    //--------------------------------------------
    if (mLectureIdx == 2){
        switch (mSlideIdx){
            case 0:
                Draw2D_MtxText_XL(3+a,"  LEVEL of DETAIL"); break;
            case 1:
                Draw2D_MtxText_XL(3+a,"       MSAA"); break;
            case 2:
                Draw2D_MtxText_XL(3+a,"       FOG"); break;
            case 3:
                Draw2D_MtxText_XL(3+a,"    FPS + ECO");
                Draw2D_MtxText_XL(2+a,"    + VSYNC"); break;
            case 4:
                Draw2D_MtxText_XL(3+a,"   BUMP MAPPING"); break;
            case 5:
                Draw2D_MtxText_XL(3+a,"    BILLBOARDS"); break;
        }
    }
    //--------------------------------------------
    //--------------------------------------------
    //                     T4
    //--------------------------------------------
    //--------------------------------------------
    if (mLectureIdx == 3){
        switch (mSlideIdx){
            case 0:
                Draw2D_MtxText_XL(3+a,"  PROCEDURAL");
                Draw2D_MtxText_XL(2+a,"      GENERATION"); break;
            case 1:
                Draw2D_MtxText_XL(3+a,"     L-SYSTEM"); break;
            case 2:
                Draw2D_MtxText_XL(3+a,"    BFS vs DFS");
                Draw2D_MtxText_XL(2+a,"    SEARCH"); break;
            case 3:
                Draw2D_MtxText_XL(3+a,"   STENCIL BUFFER");
                Draw2D_MtxText_XL(2+a,"   + MIRRORS"); break;
            case 4:
                Draw2D_MtxText_XL(3+a,"   TESSALATION"); break;
            case 5:
                Draw2D_MtxText_XL(3+a,"     SPLINES"); break;
        }
    }
    //--------------------------------------------
    //--------------------------------------------
    //                     T5
    //--------------------------------------------
    //--------------------------------------------
    if (mLectureIdx == 4){
        switch (mSlideIdx){
            case 0:
                Draw2D_MtxText_XL(3+a," FRUSTUM CULLING");
                Draw2D_MtxText_XL(2+a," + SPHERICAL BBOX"); break;
            case 1:
                Draw2D_MtxText_XL(3+a,"  FIELD OF VIEW"); break;
            case 2:
                Draw2D_MtxText_XL(3+a," ORTHO PROJECTION"); break;
            case 3:
                Draw2D_MtxText_XL(3+a,"     SHADOWS"); break;
            case 4:
                Draw2D_MtxText_XL(3+a," GPU ARCHITECTURE"); break;
            case 5:
                Draw2D_MtxText_XL(3+a,"    HARDWARE");
                Draw2D_MtxText_XL(2+a,"    RAYTRACING"); break;
        }
    }
    //--------------------------------------------
    //--------------------------------------------
    //                     T6
    //--------------------------------------------
    //--------------------------------------------
    if (mLectureIdx == 5){
        switch (mSlideIdx){
            case 0:
                Draw2D_MtxText_XL(3+a,"     SHADERS"); break;
            case 1:
                Draw2D_MtxText_XL(3+a,"  MOTION & DEPTH");
                Draw2D_MtxText_XL(2+a,"      BLURR"); break;
            case 2:
                Draw2D_MtxText_XL(3+a," FIRE +");
                Draw2D_MtxText_XL(2+a,"  MOVIE TEXTURES"); break;
            case 3:
                Draw2D_MtxText_XL(3+a,"     SHADOWS"); break;
            case 4:
                Draw2D_MtxText_XL(3+a,"      WATER"); break;
            case 5:
                Draw2D_MtxText_XL(3+a," PARTICLE EFFECTS"); break;
        }
    }
    //--------------------------------------------
    //--------------------------------------------
    Cam2D_SwitchTo2DMode_End();
    //--------------------------------------------
    //--------------------------------------------
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------







//---------------------------------------------------------------------
//---------------------------------------------------------------------
//                               Physics
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void GUI::UpdatePlayerDynamics(){
    //----------------------------------------
    //----------------------------------------
    UINT time0 = SDL_GetTicks();
    mDeltaT = .001 * double(time0 - mTime0);
    mTime0 = time0;
    if (mTimeWarpON) mTimeWarp0 = mTime0;
    //----------------------------------------
    double v[3];
    For (i,3){
        v[i] = mFlyVel[i];
        if (mFoothold > .7) v[i] += mFootholdVel[i];
    }
    //----------------------------------------
    For (i,3) mPlayerPos[i] += v[i] * mDeltaT + .5 * mPlayerAccel[i] * mDeltaT * mDeltaT;
    //----------------------------------------
    //----------------------------------------
    For (i,3) mFlyVel[i] += mPlayerAccel[i] * mDeltaT;
    //----------------------------------------
    //----------------------------------------
    mFoothold = -1.;
    //----------------------------------------
    //----------------------------------------
    //              Apply Floor
    //----------------------------------------
    //----------------------------------------
    if (mPlayerPos[1] < mPlayerR){
        For (i,3) mFlyVel[i] = 0.;
        mPlayerPos[1] = mPlayerR;
        mFoothold = 1.;
    }
    //----------------------------------------
    //----------------------------------------
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void GUI::Draw_Player(){
    //----------------------------------------
    //----------------------------------------
    if (!mDrawPlayer || mMode == PLAY_MODE) return;
    //----------------------------------------
    //----------------------------------------
    glPushMatrix();
    glTranslatedv(mPlayerPos);
    glColor3ub(255,0,0);
    gluSphere(mQuadratic,.02,32,32);
    glPopMatrix();
    //----------------------------------------
    //----------------------------------------
    glPushMatrix();
    glTranslatedv(mEye);
    glColor3ub(0,0,255);
    gluSphere(mQuadratic,.02,32,32);
    glColor3ub(255,255,255);
    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex3d(0,0,0);
    glVertex3d(.3*mPlayerLookAtDir[0],
               .3*mPlayerLookAtDir[1],
               .3*mPlayerLookAtDir[2]);
    glEnd();
    glPopMatrix();
    //----------------------------------------
    //----------------------------------------
    glPushMatrix();
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glTranslated(mPlayerPos[0],mPlayerPos[1],mPlayerPos[2]);
    glColor4ub(0,0,255,50);
    gluSphere(mQuadratic,mPlayerR,32,32);
    glDisable(GL_BLEND);
    //glEnable(GL_LIGHTING);
    glPopMatrix();
    //----------------------------------------
    //----------------------------------------
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------







//---------------------------------------------------------------------
//---------------------------------------------------------------------
//                                Draw
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void GUI::Draw(){
    //--------------------------------------------
    //--------------------------------------------
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //--------------------------------------------
    //--------------------------------------------
    SDL_SetRelativeMouseMode(SDL_bool(mMode > DESIGN_MODE));
    //--------------------------------------------
    //--------------------------------------------
    SetCamera(1);
    //--------------------------------------------
    //--------------------------------------------
    UpdatePlayerDynamics();
    //--------------------------------------------
    //--------------------------------------------
    //Prim_A1_1();
    //Prim_A1_2();
    Lsys_Axiom1();
    //--------------------------------------------
    //--------------------------------------------
    if (mMode == PLAY_MODE){
        Frustum_EvalCoords();
        Frustum_EvalPlaneNormals();//###A22
    }
    //--------------------------------------------
    //--------------------------------------------
    
    //--------------------------------------------
    //--------------------------------------------
    SetCamera(2);
    //--------------------------------------------
    //--------------------------------------------
    //Draw_Dome();//###
    //Draw_TexDome();//###
    //Draw_Floor();//###
    //--------------------------------------------
    //--------------------------------------------
    Draw_CoordSys();
    Draw_Player();
    //--------------------------------------------
    //--------------------------------------------
    Draw_Prims();
    //--------------------------------------------
    if (mMode == DESIGN_MODE && mDrawFrustum){
        Frustum_Test();
        Frustum_Draw();
    }
    //--------------------------------------------
    switch (mDisp2D){
        case 1: Draw_2D_Page1(); break;
        case 2: Draw_2D_Page2(); break;
        case 3: Draw_2D_Page3(); break;
    }
    //--------------------------------------------
    //--------------------------------------------
    if (mSaveScreen){
        SaveOpenGLWinTGA(sW,sH);
        mSaveScreen = false;
    }
    //--------------------------------------------
    //--------------------------------------------
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------







//---------------------------------------------------------------------
//---------------------------------------------------------------------
//                              Keyboard
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void GUI::KeyWalk(){
    //--------------------------------------------
    //--------------------------------------------
    if (mWalkingDir == KEY_STILL) return;
    //--------------------------------------------
    //--------------------------------------------
    double n[3], tmp;
    n[0] = mPlayerLookAtDir[0];
    n[1] = 0.;
    n[2] = mPlayerLookAtDir[2];
    Normalize(n);
    //--------------------------------------------
    //--------------------------------------------
    if (mWalkingDir == KEY_BACKWARD){
        n[0] = -n[0]; n[2] = -n[2];}
    else if (mWalkingDir == KEY_LEFT){
        tmp = n[0]; n[0] = n[2]; n[2] = -tmp;}
    else if (mWalkingDir == KEY_RIGHT){
        tmp = n[2]; n[2] = n[0]; n[0] = -tmp;}
    //--------------------------------------------
    //--------------------------------------------
    For (i,2) mFootholdVel[2*i] = n[2*i] * mWalkSpeed;
    //--------------------------------------------
    //--------------------------------------------
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void GUI::KeyWalk(int dir){
    mWalkingDir = dir;
    KeyWalk();
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void GUI::KeyWASD(bool keyDown, int key){
    //--------------------------------------------
    //--------------------------------------------
    bool right    = key == SDLK_d || key == SDLK_RIGHT;
    bool forward  = key == SDLK_w || key == SDLK_UP;
    bool left     = key == SDLK_a || key == SDLK_LEFT;
    bool backward = key == SDLK_s || key == SDLK_DOWN;
    //--------------------------------------------
    //--------------------------------------------
    if (!right && !forward && !left && !backward) return;
    //--------------------------------------------
    //--------------------------------------------
    if (keyDown){
        //----------------------------------------
        if (right){mKeyRight = true; KeyWalk(KEY_RIGHT);}
        //----------------------------------------
        if (forward){mKeyForward = true; KeyWalk(KEY_FORWARD);}
        //----------------------------------------
        if (left){mKeyLeft = true; KeyWalk(KEY_LEFT);}
        //----------------------------------------
        if (backward){mKeyBackward = true; KeyWalk(KEY_BACKWARD);}
        //----------------------------------------
    }
    //--------------------------------------------
    //--------------------------------------------
    else {
        //----------------------------------------
        //----------------------------------------
        if (right){
            mKeyRight = false;
            if (mKeyLeft) KeyWalk(KEY_LEFT);
            else if (mKeyForward) KeyWalk(KEY_FORWARD);
            else if (mKeyBackward) KeyWalk(KEY_BACKWARD);
        }
        else if (left){
            mKeyLeft = false;
            if (mKeyRight) KeyWalk(KEY_RIGHT);
            else if (mKeyForward) KeyWalk(KEY_FORWARD);
            else if (mKeyBackward) KeyWalk(KEY_BACKWARD);
        }
        //----------------------------------------
        //----------------------------------------
        if (forward){
            mKeyForward = false;
            if (mKeyBackward) KeyWalk(KEY_BACKWARD);
            else if (mKeyLeft) KeyWalk(KEY_LEFT);
            else if (mKeyRight) KeyWalk(KEY_RIGHT);
        }
        else if (backward){
            mKeyBackward = false;
            if (mKeyForward) KeyWalk(KEY_FORWARD);
            else if (mKeyLeft) KeyWalk(KEY_LEFT);
            else if (mKeyRight) KeyWalk(KEY_RIGHT);
        }
        //----------------------------------------
        //----------------------------------------
        if (!mKeyRight && !mKeyForward && !mKeyLeft && !mKeyBackward){
            mFootholdVel[0] = mFootholdVel[2] = 0.;
            mWalkingDir = KEY_STILL;
        }
        //----------------------------------------
        //----------------------------------------
    }
    //--------------------------------------------
    //--------------------------------------------
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void GUI::KeyDown(int key){
    //--------------------------------------------
    //--------------------------------------------
    KeyWASD(true,key);
    //--------------------------------------------
    //--------------------------------------------
    Music_KeyDown(key);
    //--------------------------------------------
    //--------------------------------------------
    if (key == SDLK_SPACE && mFoothold > .7){
        mFlyVel[0] = mFootholdVel[0];
        mFlyVel[1] = mJumpInitVel;
        mFlyVel[2] = mFootholdVel[2];
        mFoothold = -1.;
        return;
    }
    //--------------------------------------------
    //--------------------------------------------
    if (key == SDLK_k){
        mTexK = (mTexK + 1) % 3; return;
    }
    if (key == SDLK_PLUS || key == SDLK_MINUS){
        if (key == SDLK_PLUS){
            mTexIdxV[mTexK]++;
            if (mTexIdxV[mTexK] > 60) mTexIdxV[mTexK] = 0;
        }
        else {
            mTexIdxV[mTexK]--;
            if (mTexIdxV[mTexK] < 0) mTexIdxV[mTexK] = 60;
        }
        char s[24];
        snprintf(s,24,"Tex_%d.png",mTexIdxV[mTexK]);
        Tex_Load(mTexK,s);
        return;
    }
    //--------------------------------------------
    //--------------------------------------------
    switch (key){
            //------------------------------------
        case SDLK_0:
            Cam_Init();
            mTimeWarp0 = 0;
            return;
            //------------------------------------
        case SDLK_1:
            mMode = DESIGN_MODE;
            if (mFogON) glDisable(GL_FOG);
            mCoordSysON = true;
            return;
            //------------------------------------
        case SDLK_2:
            mMode = PLAY_MODE;
            if (mFogON) glEnable(GL_FOG);
            mCoordSysON = false;
            return;
            //------------------------------------
        case SDLK_9:
            For (i,3) mLookAtDesign[i] = mPlayerPos[i]; return;
            //------------------------------------
        case SDLK_f: mFrustumCullingON = !mFrustumCullingON; return;
            //------------------------------------
        case SDLK_i: mDisp2D = (mDisp2D+1) % 4; return;
            //------------------------------------
        case SDLK_m: mTimeWarpON = !mTimeWarpON; return;
            //------------------------------------
        case SDLK_p: mDrawFrustum = !mDrawFrustum; return;
            //------------------------------------
        case SDLK_r: mLsys_16_9 = !mLsys_16_9; return;
            //------------------------------------
        case SDLK_t: mSaveScreen = true; return;
            //------------------------------------
    }
    //--------------------------------------------
    //--------------------------------------------
    if (mDisp2D == 3){
        switch (key){
                //------------------------------------
            case SDLK_RIGHT: mSlideIdx = (mSlideIdx+1) % 6; return;
                //------------------------------------
            case SDLK_LEFT: mSlideIdx = (mSlideIdx+5) % 6; return;
                //------------------------------------
            case SDLK_UP: mLectureIdx = (mLectureIdx+5) % 6; return;
                //------------------------------------
            case SDLK_DOWN: mLectureIdx = (mLectureIdx+1) % 6; return;
                //------------------------------------
        }
    }
    //--------------------------------------------
    //--------------------------------------------
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void GUI::KeyUp(int key){
    //--------------------------------------------
    //--------------------------------------------
    KeyWASD(false,key);
    //--------------------------------------------
    //--------------------------------------------
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------







//---------------------------------------------------------------------
//---------------------------------------------------------------------
//                                Mouse
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void GUI::Mouse(UINT button, UINT state, int x, int y){
    //--------------------------------------------
    if (mMode != DESIGN_MODE) return;
    //if (button != SDL_BUTTON_LEFT) return;
    mMouseActiveMotion = state == SDL_PRESSED;
    //--------------------------------------------
    if (state == SDL_PRESSED) mCamControlModeRevolve = true;
    //--------------------------------------------
    if (state == SDL_RELEASED){
        mV_CamRotationFactor += double(x - mMouseX);
        mTheta_CamRotationFactor += double(y - mMouseY);
        if (mMouseX == x && mMouseY == y) Mouse_OGLPos(x,y);
        mCamControlModeRevolve = false;
    }
    //--------------------------------------------
    mMouseMotionX = mMouseX = x; mMouseMotionY = mMouseY = y;
    //--------------------------------------------
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void GUI::MouseMotion(int x, int y, int xrel, int yrel){
    //--------------------------------------------
    if (mMusic_MouseON) Music_MouseMotion(x,y,xrel,yrel);
    //--------------------------------------------
    if (mMode == DESIGN_MODE){
        if (mMouseActiveMotion){
            mMouseMotionX = x; mMouseMotionY = y;
        }
    }
    //--------------------------------------------
    else {
        mMouseMotionRelX += xrel; mMouseMotionRelY += yrel;
        const double a = DEG2RAD * .02;
        mPlayerTheta = (double)mMouseMotionRelX * a;
        mPlayerPhi = mMousePitch_NaturalDir * (double)mMouseMotionRelY * a;
        mPlayerLookAtDir[0] = cos(mPlayerTheta);
        mPlayerLookAtDir[1] = sin(mPlayerPhi);
        mPlayerLookAtDir[2] = sin(mPlayerTheta);
        Normalize(mPlayerLookAtDir);
        KeyWalk();
    }
    //--------------------------------------------
};
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void GUI::MouseWheel(int x, int y){
    if (mMode != DESIGN_MODE) return;
    mMouseWheel_Accum += y;
    double B = -0.004 * mMouseWheel_Factor;
    mRadius_Cam = exp(B * mMouseWheel_Accum);
};
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void GUI::Mouse_OGLPos(int x, int y){
    //--------------------------------------------
    int viewport[4];
    double px, py, pz, modelview[16], proj[16];
    double winX, winY;
    GLfloat winZ;//GLfloat (or double) for correct function
    //--------------------------------------------
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, proj);
    glGetIntegerv(GL_VIEWPORT, viewport);
    //--------------------------------------------
    winX = (double)x; winY = (double)(viewport[3] - y);
    glReadPixels(int(x), int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);//GL_FLOAT for correct function
    gluUnProject(winX, winY, winZ, modelview, proj, viewport, &px, &py, &pz);
    //--------------------------------------------
    if (winZ > .9999f) return;//GLfloat
    double p[] = {px,py,pz};
    For (i,3) mLookAtDesign[i] = p[i];
    //--------------------------------------------
};
//---------------------------------------------------------------------
//---------------------------------------------------------------------







//---------------------------------------------------------------------
//---------------------------------------------------------------------
//                              Cam
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void GUI::Cam_Init(){
    //--------------------------------------------
    //--------------------------------------------
    For (i,3) mLookAtDesign[i] = 0.;
    mCamControlModeRevolve = false;
    mTheta_CamRotationFactor = 180.;
    mV_CamRotationFactor = 1400.;
    mRadius_Cam = 8.;
    //--------------------------------------------
    //--------------------------------------------
    double B = -0.004 * mMouseWheel_Factor;
    mMouseWheel_Accum = int(log(mRadius_Cam)/B);
    //--------------------------------------------
    //--------------------------------------------
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void GUI::Cam_PlayMode(){
    double offset[3] = {0.,.6*(double)mPlayerR,0.};
    For (i,3){
        mEye[i] = mPlayerPos[i] + offset[i];
        mLookAt[i] = mEye[i] + mPlayerLookAtDir[i];
    }
    //-------------------------------------------------------------
    if (mMode == PLAY_MODE){
        gluLookAt(mEye[0], mEye[1], mEye[2],
                  mLookAt[0], mLookAt[1], mLookAt[2],
                  0., 1., 0.);
    }
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void GUI::Cam_DesignMode(){
    //--------------------------------------------
    double R[3], N[3], dx = 0., dy = 0., v, theta;
    double C = -0.1*M_PI/180.;
    double D = - M_PI, E = -1./200.;
    //--------------------------------------------
    if (mCamControlModeRevolve){
        dx = double(mMouseMotionX - mMouseX);
        dy = double(mMouseMotionY - mMouseY);
    }
    //--------------------------------------------
    v = C * (mV_CamRotationFactor + dx);
    theta = D / (1. + exp(E * (mTheta_CamRotationFactor + dy)));
    double s = sin(theta);
    N[0] =   s * sin(v);//X <=>  y
    N[1] = - cos(theta);//Y <=> -z
    N[2] =   s * cos(v);//Z <=>  x
    For (i,3) R[i] = mRadius_Cam * N[i];
    //--------------------------------------------
    if (mMode == PLAY_MODE) For (i,3) mLookAt[i] = mEye[i] - R[i];
    else {
        For (i,3) mEyeDesign[i] = mLookAtDesign[i] + R[i];
        gluLookAt(mEyeDesign[0], mEyeDesign[1], mEyeDesign[2],
                  mLookAtDesign[0], mLookAtDesign[1], mLookAtDesign[2],
                  0., 1., 0.);
    }
    //--------------------------------------------
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void GUI::Cam_Mode(){
    Cam_PlayMode();
    Cam_DesignMode();
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void GUI::Cam(){
    //--------------------------------------------
    //--------------------------------------------
    if (!mLightsFixedToCamera) Cam_Mode();//###
    //--------------------------------------------
    //--------------------------------------------
    //GLfloat pos[] = {1,1,1,1};//Point Light//###
    GLfloat pos[] = {1,1,1,0};//Directional Light
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    //--------------------------------------------
    //--------------------------------------------
    if (mLightsFixedToCamera) Cam_Mode();
    //--------------------------------------------
    //--------------------------------------------
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------







//---------------------------------------------------------------------
//---------------------------------------------------------------------
//                                Close
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void GUI::Close(){
    Music_Close();
    SDL_Quit();
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------







//---------------------------------------------------------------------
//---------------------------------------------------------------------
//                            SDL Main Loop
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void GUI::MainLoop(){
    SDL_Event event;
    bool quit = false;
    int key;
    while (!quit) {
        //-----------------------------------------
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                //---------------------------------
                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                    Mouse(event.button.button,
                          event.button.state,
                          event.button.x,
                          event.button.y);
                    break;
                case SDL_MOUSEMOTION:
                    MouseMotion(event.motion.x,
                                event.motion.y,
                                event.motion.xrel,
                                event.motion.yrel);
                    break;
                case SDL_MOUSEWHEEL:
                    MouseWheel(event.wheel.x,
                               event.wheel.y);
                    break;
                //---------------------------------
                case SDL_KEYDOWN:
                    if (!event.key.repeat){
                        key = event.key.keysym.sym;
                        if (key == SDLK_ESCAPE){quit = true; break;}
                        KeyDown(key);
                    }
                    break;
                case SDL_KEYUP:
                    key = event.key.keysym.sym;
                    KeyUp(key);
                    break;
                //---------------------------------
                case SDL_QUIT: quit = true; break;
                default: break;
                //---------------------------------
            }
        }
        //-----------------------------------------
        Draw();
        SDL_GL_SwapWindow(mScreen);
        Eval_FPS();
        SDL_Delay(3);//###
        //-----------------------------------------
    }
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
