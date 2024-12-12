#include "clCell.h"
#include "Console.h"
#include "R32M.h"

ACTION Cell::sweep() {
	if (opened) return OPENED;
	if (marked) return USUAL;
	opened = true;
	if (bomb) return GAMEOVER; // gameover
	if (neighbours == 0)
		return EMPTY;
	else
		return USUAL;
}

void Cell::show() const {
	MoveCursor(x, y);

	if (opened) {
		if (bomb) {
			if (marked)
				SetColor(B_L_BLUE);
			else
				SetColor(B_L_RED);
			ColorPrint("*");
		}
		else {
			if (marked)
				SetColor(B_L_YELLOW);
			else
				SetColor(F_L_WHITE);
			if (neighbours)
				ColorPrint("%d", neighbours);
			else
				ColorPrint(" ");
		}
	}
	else {
		if (marked)
			ColorPrint(B_D_BLUE, "P");
		else
			ColorPrint(B_L_GREEN, "X");
	}
}

void Cell::reset() {
	opened = false;
	marked = false;
	bomb = false;
}
