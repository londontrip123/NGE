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
//                                Demo
//---------------------------------------------------------------------
//---------------------------------------------------------------------
// This minimal class demonstrates how to play music and sound effects
// by the SDL2 Mixer package
// (1) To start and stop the music file Random.mp3, press 6 on the
// keyboard
// (2) To activate a short laser blast, press 7
// (3) For a minimal interactive music setup, set mMusic_MouseON to
// true in Music.h. Press 8 and move around the mouse cursor 
// in the active OpenGL window to modify the volume for the four
// looping audio channels. The WAV files MainDrums0.wav to
// MainDrums3.wav, play in parallel by synchronized loops. To stop the
// loops, press 8. 
//---------------------------------------------------------------------
//---------------------------------------------------------------------
#include "Music.h"
//---------------------------------------------------------------------
//---------------------------------------------------------------------
Music::Music(){
    //--------------------------------------------
    //--------------------------------------------
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------



//---------------------------------------------------------------------
//---------------------------------------------------------------------
//                          Scalar Transform
//---------------------------------------------------------------------
//---------------------------------------------------------------------
double Music::SmoothStep(double x0, double x1, double x){
    x = (x - x0) / (x1 - x0);
    if (x < 0.) return 0.;
    if (x > 1.) return 1.;
    return x * x * (3.0f - 2.0f * x);
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------



//---------------------------------------------------------------------
//---------------------------------------------------------------------
//                             Init/Close
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Music::Music_Init(){
    //--------------------------------------------
    Mix_Init(MIX_INIT_MP3 | MIX_INIT_MID);
    //--------------------------------------------
    int ret = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
    if (ret == -1) printf("Music_Init: Mix_OpenAudio Error!\n");
    //--------------------------------------------
    mMainTrack = Mix_LoadMUS("Audio/Random.mp3");
    if (mMainTrack == NULL) printf("Music_Init: Random.mp3 Load Error!\n");
    //--------------------------------------------
    mLaser = Mix_LoadWAV("Audio/Laser0.wav");
    if (mLaser == NULL) printf("Music_Init: Laser0.wav Load Error!\n");
    //--------------------------------------------
    char s[64] = "Audio/MainDrumsX.wav";
    //--------------------------------------------
    For (i,4){
        s[15] = '0' + i;
        mMainDrumsV[i] = Mix_LoadWAV(s);
        if (mMainDrumsV[i] == NULL) printf("Music_Init: Load Error!\n");
    }
    //--------------------------------------------
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Music::Music_Close(){
    //--------------------------------------------
    if (mMainTrack != NULL) Mix_FreeMusic(mMainTrack);
    if (mLaser != NULL) Mix_FreeChunk(mLaser);
    For (i,4) if (mMainDrumsV[i] != NULL) Mix_FreeChunk(mMainDrumsV[i]);
    Mix_CloseAudio();
    //--------------------------------------------
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------



//---------------------------------------------------------------------
//---------------------------------------------------------------------
//                                Misc
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Music::Music_KeyDown(int key){
    //--------------------------------------------
    if (key == SDLK_6){
        if (mMusicLoopON) Mix_HaltMusic();
        else {
            int N = -1;//Loop N times. N = -1 => Loop forever
            int ret = Mix_PlayMusic(mMainTrack,N);
            if (ret == -1) printf("Mix_PlayMusic Error\n");
        }
        mMusicLoopON = !mMusicLoopON;
        return;
    }
    //--------------------------------------------
    if (key == SDLK_7){
        int ret = Mix_PlayChannel(4, mLaser, 0);
        if (ret == -1) printf("Mix_PlayChannel Error\n");
        return;
    }
    //--------------------------------------------
    if (key == SDLK_8 && mMusic_MouseON){
        if (mDrumLoopON) Mix_HaltChannel(-1);
        else {
            int ret = -1;
            For (i,4){
                ret = Mix_PlayChannel(i,mMainDrumsV[i],-1);
                if (ret == -1) printf("Mix_PlayChannel Error %d\n",i);
            }
        }
        mDrumLoopON = !mDrumLoopON;
        return;
    }
    //--------------------------------------------
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Music::Music_MouseMotion(int X, int Y, int xrel, int yrel){
    double x = double(X)/double(sW);
    double y = double(Y)/double(sH);
    double xx = 1 - x, yy = 1 - y, r[4];
    r[0] = 1. - SmoothStep(.7,.8,sqrt(xx*xx + y*y));//hihat open 0 UL
    r[1] = 1. - SmoothStep(.7,.8,sqrt(x*x + yy*yy));//hihat closed 1 DL
    r[2] = 1. - SmoothStep(.7,.8,sqrt(x*x + y*y));//clap 2 UR
    r[3] = 1. - SmoothStep(.7,.8,sqrt(xx*xx + yy*yy));//base drum + clap 3 DR
    For (i,4) Mix_Volume(i,(int)round(double(MIX_MAX_VOLUME) * r[i]));
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------

