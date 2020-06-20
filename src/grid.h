#ifndef GRID_H
#define GRID_H

#include <windows.h>
#include <stdio.h>

void drawAxes(HDC hdc, LPRECT pClientRect);
void drawGrid(HDC hdc, LPRECT pClientRect);

#endif // GRID_H