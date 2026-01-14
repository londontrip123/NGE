//---------------------------------------------------------------------
//---------------------------------------------------------------------
#pragma once
//---------------------------------------------------------------------
//---------------------------------------------------------------------
#ifdef _WIN64
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <gl/glu.h>
#elif __APPLE__
#define GL_SILENCE_DEPRECATION
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <OpenGL/glu.h>
#endif
//---------------------------------------------------------------------
//---------------------------------------------------------------------
#include <cmath>
#include <stdio.h>
//---------------------------------------------------------------------
//---------------------------------------------------------------------
#define SOLUTION
//---------------------------------------------------------------------
//---------------------------------------------------------------------
#define For(i,N) for (int (i) = 0; (i) < (N); (i)++)
//---------------------------------------------------------------------
//---------------------------------------------------------------------
#define DEG2RAD M_PI/180
#define RAD2DEG 180/M_PI
//---------------------------------------------------------------------
//---------------------------------------------------------------------
typedef unsigned int UINT;
typedef unsigned char UCHAR;
//---------------------------------------------------------------------
//---------------------------------------------------------------------
typedef int TEX_IDX;
typedef double COLLKP;
//---------------------------------------------------------------------
//---------------------------------------------------------------------
class Common {
protected:
    //------------------------------
    Common();
    //------------------------------
    ~Common();
    //------------------------------
    int    Rand();
    double RandF();
    //------------------------------
public:
    static int sW, sH;
    //------------------------------
protected:
    UINT    mRandSeed = 0;
    //------------------------------
    enum    {DESIGN_MODE, PLAY_MODE};
    int     mMode = DESIGN_MODE;
    //------------------------------
    UINT    mTimeWarp0 = 0;
    bool    mTimeWarpON = false;
    bool    mTimeWarpFreezeModeON = true;
    //------------------------------
    bool    mTexTimeZoomON = true;
    bool    mTexAutoShiftON = false;
    //------------------------------
    double  mFOV = 30.;
    double  mNearPlane = .1;
    double  mFarPlane = 500.;
    //double  mFarPlane = 10.;//### A2.2
    double  mNearPlaneDesign = .1;
    double  mFarPlaneDesign = 2500.;
    bool    mFogON = false;
    bool    mCoordSysON = true;
    //------------------------------
    bool    mDrawPlayer = false;
    bool    mFrustumCullingON = false;
    bool    mDrawFrustum = false;
    //------------------------------
    double  mEye[3];
    double  mLookAt[3];
    double  mEyeDesign[3];
    double  mLookAtDesign[3];
    bool    mLightsFixedToCamera = false;
    //------------------------------
    //double  mPlayerR = .3;//###
    double  mPlayerR = 1.;
    double  mPlayerPos[3] = {1.,mPlayerR,1.};
    double  mFlyVel[3] = {0.,0.,0.};
    double  mFootholdVel[3] = {0.,0.,0.};
    double  mGravity = 20.;
    double  mJumpInitVel = 12.;
    double  mPlayerAccel[3] = {0,-mGravity,0};
    double  mPlayerLookAtDir[3] = {1.,0.,0.};
    double  mFoothold = -1.;
    double  mWalkSpeed = 10.;
    //------------------------------
    bool    mKeyRight = false;
    bool    mKeyForward = false;
    bool    mKeyLeft = false;
    bool    mKeyBackward = false;
    //------------------------------
    enum    {KEY_STILL, KEY_RIGHT, KEY_FORWARD, KEY_LEFT, KEY_BACKWARD};
    //------------------------------
    int     mWalkingDir = KEY_STILL;
    //------------------------------
    SDL_Window * mScreen = NULL;
    //------------------------------
    GLUquadricObj * mQuadratic;
    //------------------------------
};
//---------------------------------------------------------------------
//---------------------------------------------------------------------
