#include <Windows.h>
#pragma comment (lib, "winmm.lib")
LRESULT WINAPI KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
char* path;
int main(int argc, char* argv[])
{
    if (argc == 2) {
        path = argv[1];
        HHOOK hHook = SetWindowsHookExA(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
        MSG msg;
        while (GetMessage(&msg, NULL, 0, 0) != 0);
        UnhookWindowsHookEx(hHook);
    }
}
LRESULT WINAPI KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (wParam == WM_KEYDOWN)
    {
        if (!PlaySound(path, NULL, SND_ASYNC))
        {
            PostQuitMessage(0);
        }
    }
    KBDLLHOOKSTRUCT* kbd = (KBDLLHOOKSTRUCT*)lParam;
    if (kbd->vkCode == VK_ESCAPE) {
        PostQuitMessage(0);
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}