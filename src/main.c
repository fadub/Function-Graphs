#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <windowsx.h>
#include "custom_defs.h"
#include "grid.h"
#include "graphs.h"
#include "custom_functions.h"


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void drawContent(HWND hwnd, RECT *clientRect);

LPCTSTR WINDOW_CLASS_NAME = L"CoordWindow";
LPCTSTR WINDOW_TITLE = L"Graphs of functions";
int mouseX = 0;
int coordMarkX = 0;
BOOL displayCoordMark = FALSE;
COLORREF graphColors[SIZE_FUNC_ARR];


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow) {
    // Register the window class.   
    WNDCLASSEX wc;

	wc.cbSize 		 = sizeof(WNDCLASSEX);
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = WINDOW_CLASS_NAME;
    wc.style         = 0;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hIcon         = LoadIcon(NULL, IDI_WINLOGO);
    wc.hCursor       = LoadCursor(NULL, IDC_CROSS);
    wc.hIconSm       = LoadIcon(NULL, IDI_WINLOGO);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, L"Failed to register window class.", L"Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Create the window.
    HWND hwnd = CreateWindowEx(
        WS_EX_LEFT,                     // Optional window styles.
        WINDOW_CLASS_NAME,              // Window class
        WINDOW_TITLE,		    		// Window text
        WS_OVERLAPPEDWINDOW,            // Window style
        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
        );

    if (hwnd == NULL) {
		MessageBox(NULL, L"Failed to create window", L"Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
	
	// initialization
	generateGraphColors(graphColors, SIZE_FUNC_ARR);

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	RECT clientRect;
	
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
		
	case WM_SIZE:
		// get client area
		GetClientRect(hwnd, &clientRect);
		
		// erase old drawings
		InvalidateRect(hwnd, &clientRect, TRUE);
		
		UpdateWindow(hwnd);
        return 0;

    case WM_PAINT: 
		// get client area
		GetClientRect(hwnd, &clientRect);
		
		drawContent(hwnd, &clientRect);
        return 0;
		
	case WM_LBUTTONDOWN:
		displayCoordMark = TRUE;
		mouseX = GET_X_LPARAM(lParam);
		
		// erase old line
		GetClientRect(hwnd, &clientRect);
		InvalidateRect(hwnd, &clientRect, TRUE);
		RedrawWindow(hwnd, NULL, NULL, RDW_INTERNALPAINT);
		
		return 0;
		
	case WM_RBUTTONDOWN:
		displayCoordMark = FALSE;
		
		// erase old line
		GetClientRect(hwnd, &clientRect);
		InvalidateRect(hwnd, &clientRect, TRUE);
		RedrawWindow(hwnd, NULL, NULL, RDW_INTERNALPAINT);
		
		return 0;
		
	/* Show coord mark while moving mouse
	case WM_MOUSEMOVE:
		mouseX = GET_X_LPARAM(lParam);	
		
		// erase old line
		GetClientRect(hwnd, &clientRect);
		if(!isYvalid(&clientRect, mouseX, coordMarkX)) {		
			InvalidateRect(hwnd, &clientRect, TRUE);
			RedrawWindow(hwnd, NULL, NULL, RDW_INTERNALPAINT);
		}
		
		return 0;
	*/
    }
	
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


void drawContent(HWND hwnd, RECT *clientRect) {	
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);
	
	// paint client area white
	FillRect(hdc, clientRect, GetStockObject(WHITE_BRUSH));
	
	drawAxes(hdc, clientRect);
	drawGrid(hdc, clientRect);
	
	drawGraphs(hdc, clientRect, funcArr, SIZE_FUNC_ARR, funcNames, graphColors);
	
	if(displayCoordMark) {
		coordMarkX = markCoord(hdc, clientRect, mouseX, funcArr, SIZE_FUNC_ARR);
	}
	//coordMarkX = markCoord_inCordSteps(hdc, clientRect, mouseX, funcArr, SIZE_FUNC_ARR);
	
	EndPaint(hwnd, &ps);
}