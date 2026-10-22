#ifndef MAPPER_H
#define MAPPER_H

#include <windows.h>
#include <shellapi.h> // for tray system.

// ID definitions for the tray icon and menu items
#define WM_TRAYICON (WM_APP + 1)
#define ID_TRAY_EXIT 1001
#define ID_TRAY_ABOUT 1002

// Variable global that will be used to store the handle to the tray icon
extern HHOOK hKeyboardHook;

// FUNCTION DECLARATIONS
void SendKeyStroke(WORD virtualKey);
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#endif // end of MAPPER_H