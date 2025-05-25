#ifndef MIGRAF_H
#define MIGRAF_H

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

// initialize library
int migraf_init(const char* title, int width, int height);

// start main loop (given update and draw functions)
void migraf_run(void (*update)(float dt), void (*draw)(void));

// close graphics
void migraf_end(void);

// draw rectangle
void migraf_draw_rect(int x, int y, int width, int height, COLORREF color);

#ifdef __cplusplus
}
#endif

#endif