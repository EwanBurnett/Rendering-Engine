#include "Input.h"

using namespace Keys;

Engine::Keyboard::Keyboard()
{
    m_LastInput.reset();
    m_ThisInput.reset();
    m_KeyContext.reset();

    SetHoldDelay(0.5f);
}

void Engine::Keyboard::OnKeyPressed(int key)
{
    if (key > MAX_KEY_CODE) {
        return;
    }
    //TODO: Fix F10 key input

    m_LastInput = m_ThisInput;
    m_ThisInput.set(key, true);
}

void Engine::Keyboard::OnKeyReleased(int key)
{
    if (key > MAX_KEY_CODE) {
        return;
    }

    m_LastInput = m_ThisInput;
    m_ThisInput.reset(key);
}

bool Engine::Keyboard::KeyDown(int key) {

    //If the key is out of range, then just return false.
    if (key > MAX_KEY_CODE) {
        return false;
    }

    //If the key wasn't pressed during the last frame, but is this frame
    if (m_LastInput.test(key) == false && m_ThisInput.test(key) == true) {
        return true;
    }
    return false;
}

bool Engine::Keyboard::KeyHeld(int key) {
    //If the key is out of range, then just return false.
    if (key > MAX_KEY_CODE) {
        return false;
    }

    ////Accumulate the amount of time the key has been held for
    //static float accumulator = 0;

    if (m_LastInput.test(key) == true && m_ThisInput.test(key) == true) {
        ////Return true if the key has been held for long enough
        //if (accumulator <= m_KeyHoldDelay) {
        //    return true;
        //}
        //accumulator += dt; 
        //TODO: Implement Delta Time + accumulation
        return true;
    }

    return false;

}

bool Engine::Keyboard::KeyReleased(int key) {

    //If the key is out of range, then just return false.
    if (key > MAX_KEY_CODE) {
        return false;
    }

    //If the key was pressed during the last frame, but isn't pressed this frame
    if (m_LastInput.test(key) == true && m_ThisInput.test(key) == false) {
        return true;
    }
    return false;
}

void Engine::Keyboard::SetHoldDelay(float delay) {
    if (delay > 0) {
        m_KeyHoldDelay = delay;
    }
}

std::bitset<MAX_KEY_CODE> Engine::Keyboard::GetKeyboardState()
{
    return m_ThisInput;
}
