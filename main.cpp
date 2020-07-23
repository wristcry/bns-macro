#include "windows.h"
#include <iostream>
#include <stdio.h>
#include <thread>
#include <chrono>

const int sleeptime = 284;
const int lmb_sleeptime = 32;
const int f_sleeptime = 51;
const int delay = 150;

static volatile bool toggled = false; // i hope volatile in c++ is the same as volatile in c#...

static HWND hwnd;
static std::thread toggle_thread;

void toggle() {
	while (true) {
		if (!hwnd) continue;
		if (GetAsyncKeyState(VK_NUMPAD8)) {
			if (!toggled) {
				toggled = true;
				printf("[+] On\n");
			}
			else {
				toggled = false;
				printf("[-] Off\n");
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
	}
	std::terminate();
}

int main() {
	if (FindWindow(NULL, L"ayy lmao")) return 0;
	
	SetConsoleTitle(L"ayy lmao");
	
	hwnd = FindWindow(NULL, L"Blade & Soul");
	if (!hwnd) {
		printf("[!] FindWindow failed. Waiting for game to start...\n");
		while (!hwnd) {
			hwnd = FindWindow(NULL, L"Blade & Soul");
			Sleep(1000);
		}
		printf("[+] Game found: %p\n", hwnd);
	}
	else printf("[+] Game found: %p\n", hwnd);

	toggle_thread = std::thread(toggle);
	
	printf("[+] Started\n[+] Keybinds: Num8 - On/Off, MB4 - skill rotation\n");

	while (true) {
		while (toggled) {
			if (GetAsyncKeyState(VK_XBUTTON1)) {
				PostMessage(hwnd, WM_LBUTTONDOWN, MK_LBUTTON, 0);
				std::this_thread::sleep_for(std::chrono::milliseconds(lmb_sleeptime));
				PostMessage(hwnd, WM_LBUTTONUP, MK_LBUTTON, 0);

				std::this_thread::sleep_for(std::chrono::milliseconds(sleeptime));

				PostMessage(hwnd, WM_KEYDOWN, 0x46, 0);
				std::this_thread::sleep_for(std::chrono::milliseconds(f_sleeptime));
				PostMessage(hwnd, WM_KEYUP, 0x46, 0);

				std::this_thread::sleep_for(std::chrono::milliseconds(delay));
			}
			
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	
	toggle_thread.join();
	system("pause");
	return 0;
}