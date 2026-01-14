//---------------------------------------------------------------------
//---------------------------------------------------------------------
#pragma once
//---------------------------------------------------------------------
//---------------------------------------------------------------------
#include "Music.h"
//---------------------------------------------------------------------
//---------------------------------------------------------------------
class Frustum : protected Music {
protected:
    //-------------------------------------------------------3D Math
    void    Vec_CrossProd(double * out, const double * a, const double * b);
    double  Vec_DotProd(const double * a, const double * b);
    void    Vec_Normalize(double * a);
    //-------------------------------------------------------
    void    Frustum_Screen2Space(double space[3],
                                 int x, int y, bool isFarClip);
    void    Frustum_EvalCoords();
    void    Frustum_EvalPlaneNormals();
    void    Frustum_Draw();
    int     Frustum_CullObj(const double pos[3], double r);
    //-------------------------------------------------------
    void    Draw_Sphere(const double p[3], double r);
    void    Frustum_Test();
    //-------------------------------------------------------
    int     mCullingPlanes;
    double  FrustumEye[3];
    double  mBSpherePos[3], mBSphereR;
    bool    mBSphereVisible;
    double  mBB_Min[3], mBB_Max[3];
    double  mUR[3], mUL[3], mDL[3], mDR[3];
    double  mPU[4], mPD[4], mPR[4], mPL[4], mPNear[4], mPFar[4];
    double  mFP_A[6], mFP_B[6], mFP_C[6], mFP_D[6];
    double  mSmallestL;
    //-------------------------------------------------------
    double  mUR0[3], mUL0[3], mDL0[3], mDR0[3];
    double  mUR1[3], mUL1[3], mDL1[3], mDR1[3];
    //-------------------------------------------------------
    double  mN_Right[3], mN_Up[3], mN_Left[3], mN_Down[3],
            mN_Far[3], mN_Near[3];
    //-------------------------------------------------------
};
//---------------------------------------------------------------------
//---------------------------------------------------------------------
