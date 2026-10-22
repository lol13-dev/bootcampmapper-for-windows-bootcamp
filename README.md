# 💀 BootcampKeyRescue (BootcampMapper)

> **"Touch Bar mati di Windows Bootcamp? Skill issue dari Apple, tapi kita tetep ngoding."** 🗿🔥

[![C](https://img.shields.io/badge/Language-C11-blue.svg)](https://en.cppreference.com/w/c)
[![Platform](https://img.shields.io/badge/Platform-Windows%2010%20Bootcamp-informational.svg)](https://support.apple.com/boot-camp)
[![Architecture](https://img.shields.io/badge/Architecture-Win32%20API-orange.svg)](https://learn.microsoft.com/en-us/windows/win32/)

A lightweight, low-level Win32 C background utility made for **MacBook Pro A1707 (2016-2017)** users whose OLED Touch Bar decided to leave the chat on Windows 10 Bootcamp. 

No ESC? No F1-F12? No problem. We map `Left CTRL` + `~` to **ESC**, and `Left CTRL` + `1..=` to **F1-F12 / Media Control**.

---

## 🤡 The Backstory (Touch Bar Dead Arc)

Lu beli MacBook Pro A1707, mau nyoba *Bootcamp Windows 10*, eh Touch Bar-nya malah mati total (black screen of death). Mau pencet `ESC` pas *debugging* kodingan ga bisa, mau ganti volume / kecerahan layarnya pas nonton film juga gabisa.

Daripada bawa ke tukang servis bayar jutaan atau beli keyboard eksternal segede gaban, mending bikin low-level keyboard hook pake **C Win32 API** yang cuma makan RAM **0.5 MB**. *Pure C flex.* 😎

---

## ✨ Features

- ⚡ **Zero Latency**: Di-build pakenya `WH_KEYBOARD_LL` Win32 API Hook. Cepat, hemat resource, dan gak *laggy*.
- 🔑 **Custom Modifier**: Pake `Left CTRL` biar ga bentrok sama shortcut bawaan Windows.
- 🔀 **Smart Remapping**:
  - `Left CTRL` + `~` ➔ **ESC**
  - `Left CTRL` + `1` s/d `6` ➔ **F1** s/d **F6**
  - `Left CTRL` + `7` s/d `9` ➔ **Prev Track**, **Play/Pause**, **Next Track**
  - `Left CTRL` + `0` s/d `=` ➔ **Mute**, **Vol Down**, **Vol Up**
- 🥷 **Stealth & Clean**: Berjalan *pure background*, ada ikon di **System Tray (Taskbar pojok kanan)** buat akses menu klik kanan (*About* & *Exit*). Gak bikin semak desktop!

---

## 📂 Project Architecture

Dikode secara modular (karena kita ga bikin *spaghetti code*):

```text
BootcampMapper/
├── include/
│   └── mapper.h       # Jembatan header & deklarasi fungsi API
├── src/
│   ├── key_hook.c     # Logika intercept keyboard & SendInput()
│   ├── tray_ui.c      # Logika Jendela Tersembunyi & Context Menu System Tray
│   └── main.c         # Entry point, Message Loop, & lifecycle manager
├── .gitignore         # Biar file build ga nyampah di repo
└── README.md          # Dokumen ini!

# Clone reponya dulu
git clone [https://github.com/USERNAME_LU/BootcampMapper.git](https://github.com/USERNAME_LU/BootcampMapper.git)
cd BootcampMapper

# Build langsung ke mode background (GUI System Tray)
gcc src/main.c src/key_hook.c src/tray_ui.c -o BootcampMapper.exe -luser32 -lshell32 -mwindows