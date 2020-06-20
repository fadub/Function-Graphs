#ifndef GRAPHS_H
#define GRAPHS_H

#include <windows.h>

void drawGraphs(HDC hdc, LPRECT pClientRect, double (*f[])(double, BOOL*), size_t sizeOfFuncArr, const char *funcNames[], COLORREF colors[]);
int markCoordInSteps(HDC hdc, LPRECT pClientRect, int mouseX, double (*f[])(double, BOOL*), size_t sizeOfFuncArr);
int markCoord(HDC hdc, LPRECT pClientRect, int mouseX, double (*f[])(double, BOOL*), size_t sizeOfFuncArr);
BOOL isYvalid(LPRECT pClientRect, int mouseX, int coordMarkX);
void generateGraphColors(COLORREF *colors, size_t amount);

#endif // GRAPHS_H