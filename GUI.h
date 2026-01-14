//---------------------------------------------------------------------
//---------------------------------------------------------------------
#pragma once
//---------------------------------------------------------------------
//---------------------------------------------------------------------
#include "Lsys.h"
#include "GFX2D.h"
//---------------------------------------------------------------------
//---------------------------------------------------------------------
class GUI : protected Lsys, protected GFX2D {
public:
    //-------------------------------------------------------
    GUI(void);
    ~GUI(void);
    //-------------------------------------------------------
private:
    void    InitAttributes();
    void    CreateSurface();
    void    SetCamera(int cIdx);
    //-------------------------------------------------------
    void    Tex_Flip(SDL_Surface *surface);
    bool    Tex_Load(int texIdx, const char t[32]);
    //-------------------------------------------------------
public:
    void    InitGFX();
    void    Init();
    //-------------------------------------------------------
private:
    void    glTranslatedv(const double v[3]);
    //-------------------------------------------------------
    void    Draw_TexRect(int idx, double deltaZ);
    void    Draw_Dome();
    void    Draw_TexDome();
    void    Draw_Floor();
    void    Draw_Grid();
    void    Draw_CoordSys();
    //-------------------------------------------------------
    void    Eval_FPS();
    void    Draw_2D_Page1();
    void    Draw_2D_Page2();
    void    Draw_2D_Page3();
    //-------------------------------------------------------
    void    UpdatePlayerDynamics();
    void    Draw_Player();
    //-------------------------------------------------------
    void    Draw();
    //-------------------------------------------------------
    void    KeyWalk();
    void    KeyWalk(int dir);
    void    KeyWASD(bool keyDown, int key);
    void    KeyDown(int key);
    void    KeyUp(int key);
    //-------------------------------------------------------
    void    Mouse(UINT button, UINT state, int x, int y);
    void    MouseMotion(int x, int y, int xrel, int yrel);
    void    MouseWheel(int x, int y);
    //-------------------------------------------------------
    void    Mouse_OGLPos(int x, int y);
    //-------------------------------------------------------
    void    Cam_Init();
    void    Cam_PlayMode();
    void    Cam_DesignMode();
    void    Cam_Mode();
    void    Cam();
    //-------------------------------------------------------
public:
    void    Close();
    void    MainLoop();
    //-------------------------------------------------------Mouse
private:
    int     mMouseX = 0, mMouseY = 0;
    int     mMouseMotionX = 0, mMouseMotionY = 0;
    //-------------------------------------------------------
    int     mMouseMotionRelX = 0, mMouseMotionRelY = 0;
    double  mPlayerTheta = 0., mPlayerPhi = 0.;
    //-------------------------------------------------------
    int     mMouseButton = 0, mMouseState = 0;
    int     mMouseWheel_Accum = 0;
    bool    mMouseActiveMotion = false;
#ifdef _WIN64
    double  mMouseWheel_Factor = 10.;
#elif __APPLE__
    double  mMouseWheel_Factor = 1.;
#endif
    double  mMousePitch_NaturalDir = -1.;
    //-------------------------------------------------------Camera
    bool    mCamControlModeRevolve;
    double  mTheta_CamRotationFactor;
    double  mV_CamRotationFactor;
    double  mRadius_Cam;
    //-------------------------------------------------------Time
    UINT    mTime0;
    UINT    mTimeInSecs;
    double  mDeltaT = 0.;
    double  mDeltaT_Active = 0;
    //-------------------------------------------------------Frames
    UINT    mFPS = 0;
    UINT    mFrameCounter = 0;
    UINT    mFrameCounter0 = 0;
    //-------------------------------------------------------TexGen
    bool    mSaveScreen = false;
    int     mTexIdxV[3] = {1,2,3};
    int     mTexK = 0;
    //-------------------------------------------------------2D Layer
    int     mDisp2D = 0;//0-3
    int     mLectureIdx = 0;//0-5
    int     mSlideIdx = 0;//0-5
    //-------------------------------------------------------
};
//---------------------------------------------------------------------
//---------------------------------------------------------------------
