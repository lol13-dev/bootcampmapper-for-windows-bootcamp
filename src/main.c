#include "../include/mapper.h"

// Inisialisasi variabel global
HHOOK hKeyboardHook;
NOTIFYICONDATA nid = {0};

// FUNGSI BARU: Mendaftarkan program ke Registry agar otomatis JALAN SAAT BOOTING.
void EnableAutoStartup() {
    HKEY hKey;
    const char* appName = "BootcampKeyRescue";
    char exePath[MAX_PATH];

    // DAPATKAN ALAMAT LENGKAP (path) dari file .exe INI SECARA OTOMATIS.
    GetModuleFileName(NULL, exePath, MAX_PATH);

    // BUKA brankas Registry WIndows khusus untuk program Startup (Run)
    long result = RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_WRITE, &hKey);

    if (result == ERROR_SUCCESS) {
        // TULIS alamat .exe kita ke DALAM REGISTRY.
        RegSetValueEx(hKey, appName, 0, REG_SZ, (unsigned char*)exePath, strlen(exePath) + 1);
        RegCloseKey(hKey);
    }
}

int main() {
    // [+] AKTIFKAN Auto Startup.
    EnableAutoStartup();

    // 1. Buat Jendela Tersembunyi UI
    const char CLASS_NAME[] = "BootcampMapperTray";
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, CLASS_NAME, "BootcampMapper", 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, wc.hInstance, NULL);

    // 2. Konfigurasi Ikon System Tray
    nid.cbSize = sizeof(NOTIFYICONDATA);
    nid.hWnd = hwnd;
    nid.uID = 1;
    nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    nid.uCallbackMessage = WM_TRAYICON;
    nid.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(1)); // Menggunakan ikon dari app.rc
    strcpy(nid.szTip, "BootcampKeyRescue (Aktif)");
    Shell_NotifyIcon(NIM_ADD, &nid);

    // 3. Pasang Keyboard Hook
    hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);

    // 4. Message Loop Utama
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // 5. Pembersihan sebelum keluar
    UnhookWindowsHookEx(hKeyboardHook);
    Shell_NotifyIcon(NIM_DELETE, &nid);
    
    return 0;
}