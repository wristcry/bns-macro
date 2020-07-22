#include "windows.h"
#include <iostream>
#include <stdio.h>
#include <chrono>

const int sleeptime = 284;
const int lmb_sleeptime = 32;
const int f_sleeptime = 51;
const int delay = 130;

static bool toggled = false;

static HWND hwnd;

int main() {
	if (FindWindow(NULL, L"ayy lmao")) {
		printf("[!] Having >1 instances of macro is awful...\n");
		system("pause");
		return 0;
	}
	
	SetConsoleTitle(L"ayy lmao");
	printf("[+] \x22this shit was broken cuz of 30 ms lmao\x22 (c) wristcry\n");
	hwnd = FindWindow(NULL, L"Blade & Soul");
	if (!hwnd) {
		printf("[!] FindWindow failed. If game currently running, then something broken and macro will not work\n[+] Waiting for game to start...\n");
		while (!hwnd) {
			hwnd = FindWindow(NULL, L"Blade & Soul");
			Sleep(1000);
		}
		printf("[+] Game found: %i\n", hwnd);
	}
	else printf("[+] Game found: %i\n", hwnd);

	printf("[+] Started\n[+] Keybinds: Num8 - On/Off, MB4 - skill rotation\n");

	while (true) {
		Sleep(100);
		
		if (GetAsyncKeyState(VK_NUMPAD8)) {
			toggled = true;
			printf("[+] On\n");
			Sleep(150);
		}
		while (toggled) {
			if (GetAsyncKeyState(VK_NUMPAD8)) {
				toggled = false;
				printf("[-] Off\n");
				Sleep(150);
			}
			if (GetAsyncKeyState(VK_XBUTTON1)) {
				PostMessage(hwnd, WM_LBUTTONDOWN, MK_LBUTTON, 0);
				Sleep(lmb_sleeptime);
				PostMessage(hwnd, WM_LBUTTONUP, MK_LBUTTON, 0);

				Sleep(sleeptime);

				PostMessage(hwnd, WM_KEYDOWN, 0x46, 0);
				Sleep(f_sleeptime);
				PostMessage(hwnd, WM_KEYUP, 0x46, 0);

				Sleep(delay);
			}
			
			Sleep(100);
		}
	}
	
	system("pause");
	return 0;
}