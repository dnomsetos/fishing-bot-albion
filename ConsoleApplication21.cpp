#include <iostream>
#include <vector>
#include <windows.h>

using namespace std;

int cr = 216;
int cg = 82;
int cb = 31;

void go_to_albion_window()
{
	keybd_event(VK_MENU, 0, 0, 0);
	Sleep(100);
	keybd_event(VK_TAB, 0, 0, 0);
	Sleep(100);
	keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);
	Sleep(100);
	keybd_event(VK_TAB, 0, 0, 0);
	Sleep(100);
	keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);
	Sleep(100);
	keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
	Sleep(100);
	cout << "lets start!\n";
}

void dismount()
{
	keybd_event('A', 0, KEYEVENTF_EXTENDEDKEY, 0);
	Sleep(100);
	keybd_event('A', 0, KEYEVENTF_KEYUP, 0);
	Sleep(100);
}

pair<int, int> find_hook()
{
	long long t = clock() / CLOCKS_PER_SEC;
	HDC dng = GetDC(NULL);

	int x, y;
	x = 960;
	y = 780;
	

	while (GetRValue(GetPixel(dng, x, y)) < 200)
	{
		y++;
		Sleep(30);
		if (clock() / CLOCKS_PER_SEC - t > 10)
			return { -1, -1 };
	}
	cout << "hook is found!\n";
	y += 4;
	Sleep(100);
	while (GetRValue(GetPixel(dng, x, y)) > 240)
	{
		if (clock() / CLOCKS_PER_SEC - t > 60)
			return { -1, -1 };
	}
	cout << "start playing!\n";
	return { x, y };
}

void fishing()
{
	long long t = clock();
	mouse_event(MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE, 32768, 49152, 0, 0);
	Sleep(1000);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 32768, 49152, 0, 0);
	Sleep(500);
	mouse_event(MOUSEEVENTF_LEFTUP, 32768, 49152, 0, 0);
	Sleep(500);
	auto res = find_hook();
	int x = res.first, y = res.second;
	if (x == -1)
		return;
	HDC dng = GetDC(NULL);

	int cx = 1095, cy = 557;
	vector <int> lx = { cx - 200 };
	for (int i = 0; i < 4; ++i)
		lx.push_back(lx[i] + 10);
	vector <int> rx = { cx - 140 };
	for (int i = 0; i < 4; ++i)
		rx.push_back(rx[i] + 10);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 32768, 49152, 0, 0);
	Sleep(500);
	mouse_event(MOUSEEVENTF_LEFTUP, 32768, 49152, 0, 0);
	Sleep(500);
	while ((int)GetRValue(GetPixel(dng, cx, cy)) >= 200)
	{
		if (clock() / CLOCKS_PER_SEC - t > 60)
			return;
		for (int x : lx)
			if ((int)GetGValue(GetPixel(dng, x, cy)) > 150)
				mouse_event(MOUSEEVENTF_LEFTDOWN, 65536 * x / 1920, 65536 * y / 1080, 0, 0);
		for (int x : rx)
			if ((int)GetGValue(GetPixel(dng, x, cy)) > 150)
				mouse_event(MOUSEEVENTF_LEFTUP, 65536 * x / 1920, 65536 * y / 1080, 0, 0);
	}
	mouse_event(MOUSEEVENTF_LEFTUP, 65536 * x / 1920, 65536 * y / 1080, 0, 0);
}

void switch_character()
{
	mouse_event(MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE, 64500, 1400, 0, 0);
	Sleep(50);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 64500, 1400, 0, 0);
	Sleep(50);
	mouse_event(MOUSEEVENTF_LEFTUP, 64500, 1400, 0, 0);
	Sleep(500);
	mouse_event(MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE, 64000, 9000, 0, 0);
	Sleep(50);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 64000, 9000, 0, 0);
	Sleep(50);
	mouse_event(MOUSEEVENTF_LEFTUP, 64000, 9000, 0, 0);
	Sleep(13000);
	mouse_event(MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE, 37000, 46000, 0, 0);
	Sleep(50);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 37000, 46000, 0, 0);
	Sleep(50);
	mouse_event(MOUSEEVENTF_LEFTUP, 37000, 46000, 0, 0);
	Sleep(5000);
	mouse_event(MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE, 10000, 39000, 0, 0);
	Sleep(50);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 10000, 39000, 0, 0);
	Sleep(50);
	mouse_event(MOUSEEVENTF_LEFTUP, 10000, 39000, 0, 0);
	Sleep(50);
	mouse_event(MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE, 40500, 54500, 0, 0);
	Sleep(50);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 40500, 54500, 0, 0);
	Sleep(50);
	mouse_event(MOUSEEVENTF_LEFTUP, 40500, 54500, 0, 0);
	Sleep(10000);
}

int main()
{
	HDC dng = GetDC(NULL);

	go_to_albion_window();
	long long t = clock() / CLOCKS_PER_SEC;
	while (true)
	{
		fishing();
		Sleep(1000);
		if (clock() / CLOCKS_PER_SEC - t > 240)
		{
			switch_character();
			t = clock() / CLOCKS_PER_SEC;
		}
	}
	return 0;
}