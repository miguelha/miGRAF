#include <windows.h>
#include <time.h>

// structs
typedef struct {
    int x, y, width, height;
    COLORREF color;
} migraf_rect;

// static variables
static HWND hwnd = NULL;
static void (*user_update)(float) = NULL;
static void (*user_draw)(void) = NULL;

// define window procedure (handler)
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    switch(uMsg){
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int migraf_init(const char* title, int width, int height){
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = "miGRAFWindowClass";

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, "miGRAFWindowClass", title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, NULL, NULL, GetModuleHandle(NULL), NULL);

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    if(hwnd) return 0; else return 1;
}

void migraf_run(void (*update)(float dt), void (*draw)(void)){
    user_update = update;
    user_draw = draw;

    LARGE_INTEGER freq, prev, cur;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&prev);

    MSG msg = {0};
    int running = 1;

    while(running){
        while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
            if(msg.message == WM_QUIT){
                running = 0;
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        QueryPerformanceCounter(&cur);
        float dt = (float)(cur.QuadPart - prev.QuadPart) / freq.QuadPart;
        prev = cur;

        if(user_update) user_update(dt);
        if(user_draw) user_draw();

        InvalidateRect(hwnd, NULL, FALSE);
        UpdateWindow(hwnd);

        Sleep(16); // temporary solution to lag. limit to ~60 FPS
    }
}

void migraf_end(void){
    if(hwnd){
        DestroyWindow(hwnd);
        hwnd = NULL;
    }

    UnregisterClass("miGRAFWindowClass", GetModuleHandle(NULL));
}

void migraf_draw_rect(int x, int y, int width, int height, COLORREF color){

}

