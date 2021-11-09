//Ewan Burnett 2021
//Keyboard Input Component
#pragma once

#include <bitset>
#include <map>

namespace Keys {
    //Define commonly used keyboard key macros

#define KB_DIR_LEFT     0x25
#define KB_DIR_UP       0x26
#define KB_DIR_RIGHT    0x27
#define KB_DIR_DOWN     0x28

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

        bool KeyDown(int key);
        bool KeyHeld(int key);
        bool KeyReleased(int key);

        std::bitset<MAX_KEY_CODE> GetKeyboardState();
    private:
        //Each byte corresponds to an ASCII value. ( 0 - 7F )
        
        std::bitset<MAX_KEY_CODE> m_LastInput;   //Input from the last frame
        std::bitset<MAX_KEY_CODE> m_ThisInput;   //Input from this frame

        std::bitset<4> m_KeyContext;    //Context Bit Flags:    0 - is CTRL pressed
                                        //                      1 - is SHIFT pressed
                                        //                      2 - is ALT pressed
                                        //                      3 - Unused
        
    };

}

