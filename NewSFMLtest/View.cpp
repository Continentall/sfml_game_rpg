#include "View.h"

View view;
View getplayercoordinateforview(float x, float y) {
	float tempX = x; float tempY = y;
	int winx = GetSystemMetrics(SM_CXSCREEN); //���������� ������ �� X
	int winy = GetSystemMetrics(SM_CYSCREEN); //���������� ������ �� Y
	view.setCenter(tempX, tempY);
	return view;
}