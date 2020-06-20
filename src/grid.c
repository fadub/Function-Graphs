#include "grid.h"
#include "custom_defs.h"
#include <windows.h>
#include <stdio.h>


void drawAxes(HDC hdc, LPRECT pClientRect) {
	HGDIOBJ hOriginalPen;
	HPEN hFatBluePen;
	
	int middleX = pClientRect->right / 2;
	int middleY = pClientRect->bottom / 2;
	
	// used to number the axes
	int xNumberRectLeft = middleX - CORD_UNIT * 9/10;
	int yNumberRectTop = middleY + CORD_UNIT * 1/2;
	int yNumberRectBottom = middleY + CORD_UNIT;
	
	// use fat blue pen
	hFatBluePen = CreatePen(PS_SOLID, 5, RGB(0, 0, 204));
	hOriginalPen = SelectObject(hdc, hFatBluePen);
	
	// draw y-axis
	MoveToEx(hdc, middleX, pClientRect->top, NULL);
	LineTo(hdc, middleX, pClientRect->bottom);
	
	// draw x-axis
	MoveToEx(hdc, pClientRect->left, middleY, NULL);
	LineTo(hdc, pClientRect->right, middleY);
	
	// use original pen again
	SelectObject(hdc, hOriginalPen);
	
	// number the y-axis
	int currentY = middleY;
	int lineNumber = 0;
	while (currentY + CORD_UNIT < pClientRect->bottom) {
		lineNumber--;
		currentY += CORD_UNIT;

		// don't number the first line
		if (lineNumber > -2) {
			continue;
		}
		
		char strLineNumber[10];	//maximum of 9 digits
		sprintf(strLineNumber, "%d", lineNumber);
		LPCTSTR pStrLineNumber = strLineNumber;
		
		RECT numberRect = {xNumberRectLeft, (currentY - CORD_UNIT * 1/2), middleX, currentY};
		DrawText(hdc, pStrLineNumber, -1, &numberRect, 0);
	}
	
	// number the y-axis
	currentY = middleY;
	lineNumber = 0;
	while (currentY - CORD_UNIT > pClientRect->top) {
		lineNumber++;
		currentY -= CORD_UNIT;

		// don't number the first line
		if (lineNumber < 2) {
			continue;
		}
		
		char strLineNumber[10];	//maximum of 9 digits
		sprintf(strLineNumber, "%d", lineNumber);
		LPCTSTR pStrLineNumber = strLineNumber;
		
		RECT numberRect = {xNumberRectLeft, (currentY - CORD_UNIT * 1/2), middleX, currentY};
		DrawText(hdc, pStrLineNumber, -1, &numberRect, 0);
	}
	
	// number the x-axis
	int currentX = middleX;
	lineNumber = 0;
	while (currentX + CORD_UNIT < pClientRect->right) {
		lineNumber++;
		currentX += CORD_UNIT;

		// don't number the first line
		if (lineNumber < 2) {
			continue;
		}
		
		char strLineNumber[10];	//maximum of 9 digits
		sprintf(strLineNumber, "%d", lineNumber);
		LPCTSTR pStrLineNumber = strLineNumber;
		
		RECT numberRect = {(currentX - CORD_UNIT * 9/10), yNumberRectTop, currentX, yNumberRectBottom};
		//FillRect(hdc, &numberRect, GetStockObject(GRAY_BRUSH));
		DrawText(hdc, pStrLineNumber, -1, &numberRect, DT_RIGHT);
	}
	
	// number the x-axis
	currentX = middleX;
	lineNumber = 0;
	while (currentX - CORD_UNIT > pClientRect->left) {
		lineNumber--;
		currentX -= CORD_UNIT;

		// don't number the first line
		if (lineNumber > -2) {
			continue;
		}
		
		char strLineNumber[10];	//maximum of 9 digits
		sprintf(strLineNumber, "%d", lineNumber);
		LPCTSTR pStrLineNumber = strLineNumber;
		
		RECT numberRect = {(currentX - CORD_UNIT * 9/10), yNumberRectTop, currentX, yNumberRectBottom};
		DrawText(hdc, pStrLineNumber, -1, &numberRect, DT_RIGHT);
	}
}


void drawGrid(HDC hdc, LPRECT pClientRect) {	
	int middleX = pClientRect->right / 2;
	int middleY = pClientRect->bottom / 2;
	
	// draw horizontal grid lines below x-axis
	int currentY = middleY;
	int lineNumber = 0;
	while (currentY + CORD_UNIT < pClientRect->bottom) {
		lineNumber--;
		currentY += CORD_UNIT;
		MoveToEx(hdc, pClientRect->left, currentY, NULL);
		LineTo(hdc, pClientRect->right, currentY);
	}
	
	// draw horizontal grid lines above x-axis
	currentY = middleY;
	lineNumber = 0;
	while (currentY - CORD_UNIT > pClientRect->top) {
		lineNumber++;
		currentY -= CORD_UNIT;
		MoveToEx(hdc, pClientRect->left, currentY, NULL);
		LineTo(hdc, pClientRect->right, currentY);
	}
	
	// draw vertical grid lines on the right side of the y-axis
	int currentX = middleX;
	lineNumber = 0;
	while (currentX + CORD_UNIT < pClientRect->right) {
		lineNumber++;
		currentX += CORD_UNIT;
		MoveToEx(hdc, currentX, pClientRect->top, NULL);
		LineTo(hdc, currentX, pClientRect->bottom);
	}
	
	// draw vertical grid lines on the left side of the y-axis
	currentX = middleX;
	lineNumber = 0;
	while (currentX - CORD_UNIT > pClientRect->left) {
		lineNumber--;
		currentX -= CORD_UNIT;
		MoveToEx(hdc, currentX, pClientRect->top, NULL);
		LineTo(hdc, currentX, pClientRect->bottom);
	}
}