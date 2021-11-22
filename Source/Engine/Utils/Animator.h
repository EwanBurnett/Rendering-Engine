#pragma once

#include "Time.h"
#include <Windows.h>
#include <string>
#include <vector>
#include <SpriteBatch.h>
#include <map>
#include "../Components/SpriteComponent.h"

struct Animation2D {
    std::string m_Name; //The name of the animation clip.
    RECT m_TexSize;     //How big the sprite atlas is, in pixels (Sprite Size X, Sprite Size Y, Width, Height)
    std::vector<RECT> m_Frames;
    int m_CurrentFrame;
    float m_Duration;   //How long to wait before advancing each frame
    bool m_bIsLooping;

    Animation2D(std::string name, RECT texSize, float duration, bool isLooping = true) :
        m_Name(name),
        m_TexSize(texSize),
        m_Frames(),
        m_CurrentFrame(1),
        m_Duration(duration),
        m_bIsLooping(isLooping)
    {}

    //Resets the animation to its default values.
    void Reset() {
        m_CurrentFrame = 1;
    }

    //Adds a number of frames to the animation, from a range.
    //startFrame - The frame to start from
    //numFrames - how many frames to add
    void AddFrames(int startFrame, int numFrames)
    {
        //Cache the sprite size values
        int SpriteSizeX = m_TexSize.left;
        int SpriteSizeY = m_TexSize.top;

        //Cache the atlas size
        int AtlasWidth = m_TexSize.right;
        int AtlasHeight = m_TexSize.bottom;

        //Slice the spritesheet into a grid, based on the sprite and texture sizes
        int SpritesX = AtlasWidth / SpriteSizeX;    //e.g. 64x64 sprites on a 256x512 sheet:
        int SpritesY = AtlasHeight / SpriteSizeY;    //SpritesX = 4, SpritesY = 8


        //Add all the sprites to the animation
        for (int idx = startFrame; idx < startFrame + numFrames; idx++) {

            //If we try to add more sprites than there are in the sheet, break
            if (idx > (SpritesX * SpritesY)) {
                return;
            }

            //Get the correct XY indices
            int idx_X = ((idx + SpritesX) % SpritesX); //- 1;   //Take advantage of typecasting to get the correct index
            int idx_Y = (idx / SpritesX) - (SpritesX % 2);
            //if (idx_X == 0 && idx != 0) {   //Don't compute for the first row
            //    idx_Y = SpritesY - (idx % (SpritesY - 1)) - ((SpritesY % 2));
            //}
           

            //Ensure the index is within the bounds of the sprite atlas
            if (idx_X >= SpritesX) {
                return;
            }
            if (idx_Y >= SpritesY) {
                return;
            }

            RECT output = { idx_X * m_TexSize.left, idx_Y * m_TexSize.top, (idx_X * m_TexSize.left) + m_TexSize.left, (idx_Y * m_TexSize.top) + m_TexSize.top };

            //Add the animation frame to the animation
            m_Frames.push_back(output);
        }
    }

    //Advance the animation by a specified number of frames (1 by default)
    //Return Value - The RECT of the new animation frame
    RECT Advance(int frames = 1) {
        int tgtFrame = m_CurrentFrame + frames;

        int s = m_Frames.size();
        //Don't do anything if the clip is invalid
 
        if (tgtFrame >= s) {
            //If the requested frame would exceed the amount of frames in the animation, check to see if we're looping.
            if (!m_bIsLooping) {
                //If looping is disabled, Return the last frame in the animation
                return(m_Frames.back());
            }
            tgtFrame = 1;
        }

        //Compute the relevant animation frame.
        //tgtFrame = (tgtFrame % m_CurrentFrame);
        RECT frameCache = m_Frames.at(tgtFrame);

        m_CurrentFrame = tgtFrame;

        return(frameCache);
    }


};


//Handles switching between animation clips
class Animator2D {

public:
    Animator2D() {};

    void SetClip(std::string clipName);
    void Update(float dt);
private:
    Animation2D* m_CurrentAnim;

    
    Time m_Time;

    //Engine::SpriteComponent& m_SpriteRef;
    float m_FrameInterval;


};
