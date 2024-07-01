// #include "raylib.h"

Rectangle frameRec;      // current displayed frames rectangle
int currentFrame;        // n of frame we are on
int framesCounter;       // counter 
int framesSpeed;         // speed adjuster
bool timetoreset = true; // animation loop restarter

Rectangle update_animation(Texture Tex, int numOfFrames, int FrameAdjustment = 0) {
    /* 
        This function takes in the texture to modify, the number of frames the texture
        consists of, and a number to subtract from the total width of the texture to 
        make animation play faster using less frames
        (this can be left empty if not needed)
    */
   
    frameRec.y = 0.0f;
    frameRec.x = 0.0f;
    frameRec.width = Tex.width / numOfFrames;
    frameRec.height = Tex.height;

    if(framesCounter <= numOfFrames - FrameAdjustment){
        frameRec.x = (float)framesCounter * (float)frameRec.width;
    } else {
        framesCounter = 0;
    }

    framesCounter++;

    return frameRec; // returns Rectangle for displaying the correct frame of animation
}

