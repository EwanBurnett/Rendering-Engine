#include "AnimatedSpriteComponent.h"

Engine::AnimatedSpriteComponent::AnimatedSpriteComponent(D3D11_Graphics* gfx) : Engine::SpriteComponent(gfx)
{
    
    /*Animation2D* debugAnim = new Animation2D("Hello", { 64, 64, 1024, 64 }, 1.0f / 10.0f);
    debugAnim->AddFrames(15, 16);
    m_CurrentAnim = debugAnim;*/
    m_CurrentAnim = nullptr;
}

void Engine::AnimatedSpriteComponent::AddClip(std::string name, RECT bounds, float frameTime, int startFrame, int numFrames, bool isLooping)
{
    //Create an animation with the parameters
    Animation2D* animCache = new Animation2D(name, bounds, frameTime, isLooping);
    animCache->AddFrames(startFrame, numFrames);

    //Add the animation clip to the sprites animations.
    m_AnimationClips.emplace(name, animCache);
}

void Engine::AnimatedSpriteComponent::SetClip(std::string clipName)
{
    //Try to load the animation clip
    if (m_AnimationClips.find(clipName) == m_AnimationClips.end()) {
        //TODO: Replace with debug layer
        OutputDebugString(L"Error: Animation Clip couldn't be found");
        return;
    }

    Animation2D* clip = m_AnimationClips.at(clipName);

    //Set the current animation to the clip
    if (m_CurrentAnim != clip) {
        clip->Reset();
        m_CurrentAnim = clip;
    }
    
}

void Engine::AnimatedSpriteComponent::Update(float dt)
{
    m_Accumulator += dt;

    //If the accumulated time is greater than the animation's frame time, Attempt to advance the current animation
    if (m_CurrentAnim != nullptr) {
        if (m_Accumulator >= m_CurrentAnim->m_Duration) {
            SetRect(m_CurrentAnim->Advance());
            m_Accumulator = 0;
        }
    }
    
   
}