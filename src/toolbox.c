#include "toolbox.h"
#include <windows.h>
#include <stdlib.h>

int randBetween(int min, int max) {
	return rand() % (max + 1 - min) + min;
}


int sign(double x) {
	if(x >= 0) {
		return 1;
	} else {
		return -1;
	}
}


HFONT createFontForGraphName() {
	return CreateFontA(
	  50,	// font height
	  0,
	  0,
	  0,
	  FW_DONTCARE,
	  FALSE,
	  FALSE,
	  FALSE,
	  DEFAULT_CHARSET,
	  OUT_OUTLINE_PRECIS,
	  CLIP_DEFAULT_PRECIS,
	  CLEARTYPE_QUALITY,
	  VARIABLE_PITCH,
	  TEXT("Arial")
	);
}