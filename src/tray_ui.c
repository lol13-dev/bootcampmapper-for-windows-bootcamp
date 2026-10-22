#include "../include/mapper.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_TRAYICON:
            if (lParam == WM_RBUTTONUP || lParam == WM_LBUTTONUP) {
                POINT pt;
                GetCursorPos(&pt);
                
                HMENU hMenu = CreatePopupMenu();
                InsertMenu(hMenu, -1, MF_BYPOSITION | MF_STRING, ID_TRAY_ABOUT, "Tentang BootcampMapper...");
                InsertMenu(hMenu, -1, MF_BYPOSITION | MF_SEPARATOR, 0, NULL);
                InsertMenu(hMenu, -1, MF_BYPOSITION | MF_STRING, ID_TRAY_EXIT, "Keluar (Exit)");
                
                SetForegroundWindow(hwnd);
                TrackPopupMenu(hMenu, TPM_BOTTOMALIGN | TPM_LEFTALIGN, pt.x, pt.y, 0, hwnd, NULL);
                DestroyMenu(hMenu);
            }
            break;
            
        case WM_COMMAND:
            if (LOWORD(wParam) == ID_TRAY_EXIT) {
                PostQuitMessage(0);
            } else if (LOWORD(wParam) == ID_TRAY_ABOUT) {
                MessageBox(NULL, "BootcampKeyRescue\n\nSoftware Remapping ESC & F1-F12 untuk MacBook A1707.\nPengaktif: Left CTRL.", "Tentang", MB_OK | MB_ICONINFORMATION);
            }
            break;
            
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}