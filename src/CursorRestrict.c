#include <Windows.h>
#include <stdbool.h>
#include <stdio.h>
// Author: https://github.com/spacemiqote

HHOOK keyboardHook;
RECT cursorBounds;
bool boundsEnabled = false;

void SetCursorBounds(int left, int top, int right, int bottom);
void ReleaseCursorBounds(void);
void SetCursorBoundsToWindow(HWND hwnd);
void ToggleCursorBounds(void);
void ExitApplication(void);
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
void InstallKeyboardHook(void);
void UninstallKeyboardHook(void);
void c(void);

void SetCursorBounds(int left, int top, int right, int bottom) {
    cursorBounds.left = left;
    cursorBounds.top = top;
    cursorBounds.right = right;
    cursorBounds.bottom = bottom;
    ClipCursor(&cursorBounds);
}

void ReleaseCursorBounds() {
    ClipCursor(NULL);
    boundsEnabled = false;
}

void SetCursorBoundsToWindow(HWND hwnd) {
    RECT clientRect;
    GetClientRect(hwnd, &clientRect);
    MapWindowPoints(hwnd, NULL, (LPPOINT)&clientRect, 2);
    SetCursorBounds(clientRect.left, clientRect.top, clientRect.right, clientRect.bottom);
    boundsEnabled = true;
}

void UninstallKeyboardHook() {
    if (keyboardHook != NULL) {
        UnhookWindowsHookEx(keyboardHook);
        keyboardHook = NULL;
    }
}

void ToggleCursorBounds() {
    if (boundsEnabled) {
        ReleaseCursorBounds();
    } else {
        HWND foregroundWindow = GetForegroundWindow();
        if (foregroundWindow != NULL) {
            SetCursorBoundsToWindow(foregroundWindow);
        }
    }
}

void ExitApplication() {
    ReleaseCursorBounds();
    UninstallKeyboardHook();
    PostQuitMessage(0);
}

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION && (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)) {
        KBDLLHOOKSTRUCT* pKeyboard = (KBDLLHOOKSTRUCT*)lParam;
        if (pKeyboard->vkCode == VK_F12 && (GetAsyncKeyState(VK_MENU) & 0x8000)) {
            ToggleCursorBounds();
        } else if (pKeyboard->vkCode == VK_F11 && (GetAsyncKeyState(VK_MENU) & 0x8000)) {
            ExitApplication();
        }
    }
    return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}

void InstallKeyboardHook() {
    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);
}

void c() {
    InstallKeyboardHook();

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UninstallKeyboardHook();
}
