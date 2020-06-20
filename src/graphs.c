#include "graphs.h"
#include "custom_defs.h"
#include "toolbox.h"
#include <windows.h>

void drawGraphs(HDC hdc, LPRECT pClientRect,  double (*f[])(double, BOOL*), size_t sizeOfFuncArr, const char *funcNames[], COLORREF colors[]) {	
	int originX = pClientRect->right / 2;
	int originY = pClientRect->bottom / 2;
	
	int numberOfLinesToDraw = originX;
	int numberOfCordUnitsVisible = originX / CORD_UNIT;
	
	// set font
	SelectObject(hdc, createFontForGraphName());
	
	int rectTextTop = 0;
	for(int i = 0; i < sizeOfFuncArr; i++) {		
		// set pen
		SelectObject(hdc, CreatePen(PS_SOLID, 6, colors[i]));
		
		// create positive graph points
		POINT *pPositiveGraphPoints = (POINT*)malloc(sizeof(POINT) * numberOfLinesToDraw);
		
		int positivePointsCount = 0;
		int x = 0;
		int y = 0;
		double xInCordUnits = 0;
		double yInCordUnits = 0;
		for(int j = 0; j <= numberOfCordUnitsVisible; j++) {
			
			for(int k = 1; k <= CONTROL_POINTS_PER_CORD_UNIT; k++) {
				
				int xBefore = x;
				int yBefore = y;
				double xInCordUnits_before = xInCordUnits;
				double yInCordUnits_before = yInCordUnits;
				
				xInCordUnits = (double)j + ((double)k / (double)CONTROL_POINTS_PER_CORD_UNIT);
				
				BOOL isNotDefined = FALSE;
				double result = (*f[i])(xInCordUnits, &isNotDefined);
				if(isNotDefined) continue;
				yInCordUnits = result;

				x = originX +  xInCordUnits * (double)CORD_UNIT;
				y = originY - (yInCordUnits * (double)CORD_UNIT);
				
				/*
				// DEBUG INFORMATION
				char str[100];
				sprintf(str, "x: %d, xBefore: %d, y: %d, yBefore: %d", x, xBefore, y, yBefore);
				OutputDebugStringA(str);
				*/
				
				/*
				// DEBUG INFORMATION
				char str[200];
				sprintf(str, "x-cord: %f, x-cord_before: %f, y-cord: %f, y-cord_before: %f", xInCordUnits, xInCordUnits_before, yInCordUnits, yInCordUnits_before);
				OutputDebugStringA(str);
				*/
				
				
				// draw seperate line if two graphs are needed (e.g. for an asymptote)
				/*if(((xBefore > pClientRect->right || xBefore < pClientRect->left) && (x > pClientRect->right || x < pClientRect->left) && (sign(xInCordUnits) != sign(xInCordUnits_before))) || 
				   ((yBefore > pClientRect->bottom || yBefore < pClientRect->top) && (y > pClientRect->bottom || y < pClientRect->top) && (sign(yInCordUnits) != sign(yInCordUnits_before)))) {*/
				if((sign(xInCordUnits) != sign(xInCordUnits_before)) || (sign(yInCordUnits) != sign(yInCordUnits_before))) {
									
					if(positivePointsCount > 1) {
						Polyline(hdc, pPositiveGraphPoints, positivePointsCount);
					}
					
					positivePointsCount = 0;
					continue;
				}
				
				// don't draw lines out of the client area
				if(((xBefore > pClientRect->right || xBefore < pClientRect->left) && (x > pClientRect->right || x < pClientRect->left)) ||
				   ((yBefore > pClientRect->bottom || yBefore < pClientRect->top) && (y > pClientRect->bottom || y < pClientRect->top))) {
					   continue;
				}
								
				POINT point = {
					x,
					y
				};
				
				/*
				// DEBUG INFORMATION
				char str[100];
				sprintf(str, "cord-x: %f, cord-y: %f, x: %d, y: %d", xInCordUnits, yInCordUnits, point.x, point.y);
				OutputDebugStringA(str);
				*/
				
				
				pPositiveGraphPoints[positivePointsCount] = point;
				positivePointsCount++;
				
			}
			
		}
		
		
		// create negative graph points
		POINT *pNegativeGraphPoints = (POINT*)malloc(sizeof(POINT) * numberOfLinesToDraw);
		
		int negativePointsCount = 0;
		x = 0;
		y = 0;
		xInCordUnits = 0;
		yInCordUnits = 0;
		for(int j = 0; j >= -numberOfCordUnitsVisible; j--) {
			
			for(int k = 1; k <= CONTROL_POINTS_PER_CORD_UNIT; k++) {
				
				int xBefore = x;
				int yBefore = y;
				double xInCordUnits_before = xInCordUnits;
				double yInCordUnits_before = yInCordUnits;
				
				xInCordUnits = (double)j - ((double)k / (double)CONTROL_POINTS_PER_CORD_UNIT);
				
				BOOL isNotDefined = FALSE;
				double result = (*f[i])(xInCordUnits, &isNotDefined);
				if(isNotDefined) continue;
				yInCordUnits = result;
				
				x = originX + xInCordUnits * (double)CORD_UNIT;
				y = originY - yInCordUnits * (double)CORD_UNIT;				
				
				// draw seperate line if two graphs are needed (e.g. for an asymptote)
				/*if(((xBefore > pClientRect->right || xBefore < pClientRect->left) && (x > pClientRect->right || x < pClientRect->left) && (sign(xInCordUnits) != sign(xInCordUnits_before))) || 
				   ((yBefore > pClientRect->bottom || yBefore < pClientRect->top) && (y > pClientRect->bottom || y < pClientRect->top) && (sign(yInCordUnits) != sign(yInCordUnits_before)))) {*/
				if((sign(xInCordUnits) != sign(xInCordUnits_before)) || (sign(yInCordUnits) != sign(yInCordUnits_before))) {
					
					if(negativePointsCount > 1) {
						Polyline(hdc, pNegativeGraphPoints, negativePointsCount);
					}
					
					negativePointsCount = 0;
					continue;			
				}
				
				// don't draw lines out of the client area
				if(((xBefore > pClientRect->right || xBefore < pClientRect->left) && (x > pClientRect->right || x < pClientRect->left)) ||
				   ((yBefore > pClientRect->bottom || yBefore < pClientRect->top) && (y > pClientRect->bottom || y < pClientRect->top))) {
					   continue;
				}
				
				POINT point = {
					x,
					y
				};
				
				/*
				// DEBUG INFORMATION
				char str[100];
				sprintf(str, "cord-x: %f, cord-y: %f, x: %d, y: %d", xInCordUnits, yInCordUnits, point.x, point.y);
				OutputDebugStringA(str);
				*/
								
				pNegativeGraphPoints[negativePointsCount] = point;
				negativePointsCount++;
			}
			
		}
		
		// draw graph
		if (positivePointsCount > 1) {
			Polyline(hdc, pPositiveGraphPoints, positivePointsCount);
		}
		
		if(negativePointsCount > 1) {
			Polyline(hdc, pNegativeGraphPoints, negativePointsCount);
		}
		
		
		RECT rectText = {2, rectTextTop, 3 * CORD_UNIT, rectTextTop + 2 * CORD_UNIT};
		SetTextColor(hdc, colors[i]);
		DrawText(hdc, funcNames[i], sizeof(funcNames[i]), &rectText, 0);
		rectTextTop = rectTextTop + 2 * CORD_UNIT;
		
		// free memory used for points
		free(pPositiveGraphPoints);
		free(pNegativeGraphPoints);
	}
}


int markCoordInSteps(HDC hdc, LPRECT pClientRect, int mouseX, double (*f[])(double, BOOL*), size_t sizeOfFuncArr) {
	HPEN hCurrentPen;
	
	// use fat red pen
	hCurrentPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	SelectObject(hdc, hCurrentPen);
	
	int originX = pClientRect->right / 2;
	int originY = pClientRect->bottom / 2;
	
	int xInCordUnits;
	if(mouseX < originX) {
		xInCordUnits = (mouseX - originX) / CORD_UNIT - 1;
	} else {
		xInCordUnits = (mouseX - originX) / CORD_UNIT + 1;
	}
	
	int x = originX + xInCordUnits * CORD_UNIT;
	
	for(int i = 0; i < sizeOfFuncArr; i++) {
		BOOL isNotDefined = FALSE;
		double yInCordUnits = (*f[i])(xInCordUnits, &isNotDefined);
		if(isNotDefined) continue;
		
		int y = originY - (int)(yInCordUnits * (double)CORD_UNIT);
		
		MoveToEx(hdc, x, originY, NULL);
		LineTo(hdc, x, y);	
		
		MoveToEx(hdc, originX, y, NULL);
		LineTo(hdc, x, y);
	}
	
	return x;
}


int markCoord(HDC hdc, LPRECT pClientRect, int mouseX, double (*f[])(double, BOOL*), size_t sizeOfFuncArr) {
	HPEN hCurrentPen;
	
	// use fat red pen
	hCurrentPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	SelectObject(hdc, hCurrentPen);
	
	int originX = pClientRect->right / 2;
	int originY = pClientRect->bottom / 2;
	
	double xInCordUnits = (double)(mouseX - originX) / (double)CORD_UNIT;
	
	for(int i = 0; i < sizeOfFuncArr; i++) {
		BOOL isNotDefined = FALSE;
		double yInCordUnits = (*f[i])(xInCordUnits, &isNotDefined);
		if(isNotDefined) continue;
		
		int y = (int)((double)originY - (yInCordUnits * (double)CORD_UNIT));
		
		MoveToEx(hdc, mouseX, originY, NULL);
		LineTo(hdc, mouseX, y);	
		
		MoveToEx(hdc, originX, y, NULL);
		LineTo(hdc, mouseX, y);
	}
	
	return mouseX;
}


BOOL isYvalid(LPRECT pClientRect, int mouseX, int coordMarkX) {
	int originX = pClientRect->right / 2;
	
	if(mouseX > originX) {
		if((coordMarkX < mouseX) ||
	       (coordMarkX - CORD_UNIT > mouseX)) {
			return FALSE;
		} else {
			return TRUE;
		}
	} else {
		if((coordMarkX > mouseX) ||
	       (coordMarkX + CORD_UNIT < mouseX)) {
			return FALSE;
		} else {
			return TRUE;
		}
	}
}


void generateGraphColors(COLORREF colors[], size_t amount) {
	for(int i = 0; i < amount; i++) {
		/*// make all graphs red
		colors[i] = RGB(210, 0, 0);
		continue;
		/////////////////////////////*/
		
		for(int j = 0; j < sizeof(COLORREF); j++) {
			unsigned char *bColor = (unsigned char*)&colors[i] + j;
			*bColor = (unsigned char)randBetween(0, 100);
		}
	}
}