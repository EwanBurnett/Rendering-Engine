#pragma once
#include "SpriteComponent.h"
#include "../Utils/Animator.h"
#include <map>

namespace Engine {
    class AnimatedSpriteComponent : public SpriteComponent {
    public:
        AnimatedSpriteComponent(D3D11_Graphics* gfx);
        ~AnimatedSpriteComponent(); 

        void AddClip(std::string name, RECT bounds, float frameTime, int startFrame = 0, int numFrames = 1, bool isLooping = true);

        void SetClip(std::string clipName);
        //Plays the requested animation clip, from frame 0.
        void Play(std::string animation);
        void Pause();
        void Unpause();

        void Update(float dt) override;

    private:
        Animation2D* m_CurrentAnim;
        Animator2D m_Animator;
        float m_Accumulator;
        std::map<std::string, Animation2D*> m_AnimationClips;
    };
} 
