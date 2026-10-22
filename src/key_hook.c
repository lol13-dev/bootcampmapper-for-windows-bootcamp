#include "../include/mapper.h"
#include <stdio.h>

BOOL isModifierPressed = FALSE; // Hanya dipakai di dalam file ini

void SendKeystroke(WORD virtualKey) {
    INPUT input[2] = {0};
    input[0].type = INPUT_KEYBOARD;
    input[0].ki.wVk = virtualKey;
    
    input[1].type = INPUT_KEYBOARD;
    input[1].ki.wVk = virtualKey;
    input[1].ki.dwFlags = KEYEVENTF_KEYUP;
        
    SendInput(2, input, sizeof(INPUT));
}

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT *p = (KBDLLHOOKSTRUCT *)lParam;

        // sudah digantkikan RMENU akibat key lain bertabrakan
        if (p->vkCode == VK_RMENU) {
            if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
                isModifierPressed = TRUE;
            } else if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP) {
                isModifierPressed = FALSE;
            }
        }

        if (isModifierPressed && (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)) {
            WORD targetKey = 0;
            switch (p->vkCode) {
                case VK_OEM_3:      targetKey = VK_ESCAPE; break; 
                case 0x31:          targetKey = VK_F1; break;     
                case 0x32:          targetKey = VK_F2; break;     
                case 0x33:          targetKey = VK_F3; break;     
                case 0x34:          targetKey = VK_F4; break;     
                case 0x35:          targetKey = VK_F5; break;     
                case 0x36:          targetKey = VK_F6; break;     
                case 0x37:          targetKey = VK_MEDIA_PREV_TRACK; break;
                case 0x38:          targetKey = VK_MEDIA_PLAY_PAUSE; break;
                case 0x39:          targetKey = VK_MEDIA_NEXT_TRACK; break;
                case 0x30:          targetKey = VK_VOLUME_MUTE; break;  
                case VK_OEM_MINUS:  targetKey = VK_VOLUME_DOWN; break;  
                case VK_OEM_PLUS:   targetKey = VK_VOLUME_UP; break;    
            }

            if (targetKey != 0) {
                SendKeystroke(targetKey);
                return 1;
            }
        }
    }
    return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
}