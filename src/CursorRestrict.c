#include <Windows.h>
#include <stdbool.h>
#include <stdio.h>
//Author:https://github.com/spacemiqote

RECT cursorBounds;
bool boundsEnabled = false;
void SetCursorBounds(int,int,int,int);
void ReleaseCursorBounds(void);
void SetCursorBoundsToWindow(HWND);
void ToggleCursorBounds(void);
void ExitApplication(void);
void c(HINSTANCE hInstance);

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

void ToggleCursorBounds(){
	if (boundsEnabled){
		ReleaseCursorBounds();
	}else{
		HWND foregroundWindow=GetForegroundWindow();
		if(foregroundWindow!=NULL)SetCursorBoundsToWindow(foregroundWindow);
	}
}

void ExitApplication() {
	ReleaseCursorBounds();
	PostQuitMessage(0);
}

LRESULT CALLBACK WindowProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam){
	if (uMsg==WM_INPUT){
		UINT dwSize=0;
		GetRawInputData((HRAWINPUT)lParam,RID_INPUT,NULL,&dwSize,sizeof(RAWINPUTHEADER));
		LPBYTE lpb=(LPBYTE)HeapAlloc(GetProcessHeap(),0,dwSize);
		if(lpb==NULL)return 0;
		if(GetRawInputData((HRAWINPUT)lParam,RID_INPUT,lpb,
		&dwSize,sizeof(RAWINPUTHEADER))!=dwSize){
			HeapFree(GetProcessHeap(),0,lpb);
			return 0;
		}
		RAWINPUT raw;
		CopyMemory(&raw,lpb,sizeof(RAWINPUT));
		HeapFree(GetProcessHeap(),0,lpb);
		if(raw.header.dwType==RIM_TYPEKEYBOARD){
			RAWKEYBOARD rawKeyboard=raw.data.keyboard;
			USHORT vkCode=rawKeyboard.VKey;
			if(rawKeyboard.Message==WM_KEYDOWN){
				if(GetAsyncKeyState(VK_SHIFT)<0){
					if(vkCode==VK_F11)ToggleCursorBounds();
					else if(vkCode==VK_F12)ExitApplication();
				}
			}
		}
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void InstallRawInputHook(HWND hwnd){
	RAWINPUTDEVICE rid[1];
	rid[0].usUsagePage=1;
	rid[0].usUsage=6;
	rid[0].dwFlags=RIDEV_INPUTSINK;
	rid[0].hwndTarget=hwnd;
	if(!RegisterRawInputDevices(rid, 1, sizeof(rid[0])))return;
}

HWND CreateMessageOnlyWindow(HINSTANCE hInstance) {
	WNDCLASS wc={0};
	wc.lpfnWndProc=WindowProc;
	wc.hInstance=hInstance;
	wc.lpszClassName="CursorRestrict";
	if(!RegisterClass(&wc))return NULL;
	HWND hwnd = CreateWindowEx(
		0,
		"CursorRestrict",
		NULL,
		0,
		0,0,0,0,
		HWND_MESSAGE, NULL, hInstance, NULL
	);
	if(!hwnd)return 0;
	return hwnd;
}

void c(HINSTANCE hInstance){
	HWND hwnd=CreateMessageOnlyWindow(hInstance);
	if(!hwnd)return;
	InstallRawInputHook(hwnd);
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}
