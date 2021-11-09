#include "Keyboard.h"

using namespace Keys;

Engine::Keyboard::Keyboard()
{
    m_LastInput.reset();
    m_ThisInput.reset();
    m_KeyContext.reset();
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

    if (key > MAX_KEY_CODE) {
        return false;
    }
    //If the key wasn't pressed during the last frame, but is this frame
    if (m_LastInput.test(key) == false && m_ThisInput.test(key) == true) {
        return true;
    }
    return false;
}

std::bitset<MAX_KEY_CODE> Engine::Keyboard::GetKeyboardState()
{
    return m_ThisInput;
}
