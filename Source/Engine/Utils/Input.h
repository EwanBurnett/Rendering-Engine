//Ewan Burnett 2021
//Keyboard Input Component
#pragma once

#include <bitset>
#include <map>

namespace Keys {
    //Define commonly used keyboard key macros
#define KB_KEY_BACK     0x08
#define KB_KEY_TAB      0x09

#define KB_KEY_ENTER    0x0D

#define KB_KEY_SHIFT    0x10
#define KB_KEY_CTRL     0x11

#define KB_KEY_ESC      0x1B

#define KB_KEY_SPACE    0x20
#define KB_KEY_PGUP     0x21
#define KB_KEY_PGDN     0x22

#define KB_DIR_LEFT     0x25
#define KB_DIR_UP       0x26
#define KB_DIR_RIGHT    0x27
#define KB_DIR_DOWN     0x28

#define KB_KEY_PRTSCN   0x2C
#define KB_KEY_INS      0x2D
#define KB_KEY_DEL      0x2E

#define KB_KEY_0        0x30
#define KB_KEY_1        0x31
#define KB_KEY_2        0x32
#define KB_KEY_3        0x33
#define KB_KEY_4        0x34
#define KB_KEY_5        0x35
#define KB_KEY_6        0x36
#define KB_KEY_7        0x37
#define KB_KEY_8        0x38
#define KB_KEY_9        0x39

#define KB_KEY_A        0x41
#define KB_KEY_B        0x42
#define KB_KEY_C        0x43
#define KB_KEY_D        0x44
#define KB_KEY_E        0x45
#define KB_KEY_F        0x46
#define KB_KEY_G        0x47
#define KB_KEY_H        0x48
#define KB_KEY_I        0x49
#define KB_KEY_J        0x4a
#define KB_KEY_K        0x4b
#define KB_KEY_L        0x4c
#define KB_KEY_M        0x4d
#define KB_KEY_N        0x4e
#define KB_KEY_O        0x4f
#define KB_KEY_P        0x50
#define KB_KEY_Q        0x51
#define KB_KEY_R        0x52
#define KB_KEY_S        0x53
#define KB_KEY_T        0x54
#define KB_KEY_U        0x55
#define KB_KEY_V        0x56
#define KB_KEY_W        0x57
#define KB_KEY_X        0x58
#define KB_KEY_Y        0x59
#define KB_KEY_Z        0x5a

#define KB_NUM_0        0x60
#define KB_NUM_1        0x61
#define KB_NUM_2        0x62
#define KB_NUM_3        0x63
#define KB_NUM_4        0x64
#define KB_NUM_5        0x65
#define KB_NUM_6        0x66
#define KB_NUM_7        0x67
#define KB_NUM_8        0x68
#define KB_NUM_9        0x69

#define KB_NUM_MUL      0x6A
#define KB_NUM_ADD      0x6B
#define KB_NUM_SUB      0x6D
#define KB_NUM_DEC      0x6E
#define KB_NUM_DIV      0x6F

#define KB_FNC_F1       0x70
#define KB_FNC_F2       0x71
#define KB_FNC_F3       0x72
#define KB_FNC_F4       0x73
#define KB_FNC_F5       0x74
#define KB_FNC_F6       0x75
#define KB_FNC_F7       0x76
#define KB_FNC_F8       0x77
#define KB_FNC_F9       0x78
#define KB_FNC_F10      0x79
#define KB_FNC_F11      0x7a
#define KB_FNC_F12      0x7b

#define KB_MOD_LSHIFT   0xA0
#define KB_MOD_RSHIFT   0xA1
#define KB_MOD_LCONTROL 0xA2
#define KB_MOD_RCONTROL 0xA3
    //...
}

namespace Engine {
#define MAX_KEY_CODE 0xA3
    
    class Keyboard {
    public:
        Keyboard();

        void OnKeyPressed(int key);
        void OnKeyReleased(int key);

        //Returns true if the key has just been pressed
        bool KeyPressed(int key);

        //Returns true if the key is pressed down 
        bool KeyDown(int key);

        //Returns true if the key has just been released
        bool KeyReleased(int key);

        //TODO: Implement Key Held logic (accumulated held time)
        void SetHoldDelay(float delay);

        std::bitset<MAX_KEY_CODE> GetKeyboardState();
        std::bitset<MAX_KEY_CODE> GetLastKeyboardState();

    private:
        float m_KeyHoldDelay;
        float m_DeltaTime;

        //Each byte corresponds to an ASCII value. ( 0 - 7F )
        
        std::bitset<MAX_KEY_CODE> m_LastInput;   //Input from the last frame
        std::bitset<MAX_KEY_CODE> m_ThisInput;   //Input from this frame

        //TODO: Upgrade to use WM_INPUT messages
        std::bitset<4> m_KeyContext;    //Context Bit Flags:    0 - is CTRL pressed
                                        //                      1 - is SHIFT pressed
                                        //                      2 - is ALT pressed
                                        //                      3 - Unused
        
    };

    class Mouse {
    public:
        //TODO: Implement Mouse input
        Mouse();

        void OnMouseMoved(float x, float y);
    private:
        bool m_bHasFocus;

        float m_PosX;
        float m_PosY;

        //The position of the mouse last frame
        float m_LastPosX; 
        float m_LastPosY;

        std::bitset<8> m_Keys;  //Each byte corresponds to a mouse key:
        //0 - Left Mouse Button
        //1 - Right Mouse Button
        //2 - Scroll Wheel Button
        //3 - Scroll Wheel Up
        //4 - Scroll Wheel Down
        //5 - Extra Mouse Button 1
        //6 - Extra Mouse Button 2
        //7 - Unused
        //8 - Unused

    };

}

