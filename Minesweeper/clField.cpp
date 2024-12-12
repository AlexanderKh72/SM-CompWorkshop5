#include <ctime>
#include "clField.h"
#include "R32M.h"
#include "Console.h"

void Field::boundary(int i, int j, int& dx_s, int& dx_e, int& dy_s, int& dy_e) {
	dx_s = -1; dx_e = 1;
	dy_s = -1; dy_e = 1;
	if (i == 0)			dy_s = 0;
	if (i == nrow - 1)	dy_e = 0;
	if (j == 0)			dx_s = 0;
	if (j == ncol - 1)	dx_e = 0;
}

void Field::setSizes(DIFFICULTY d) {
	switch (d) {
	case ELEMENTARY:
		nrow = ncol = 8;
		nbomb = 10;
		break;
	case EASY:
		nrow = ncol = 16;
		nbomb = 40;
		break;
	case MEDIUM:
		nrow = 16;
		ncol = 30;
		nbomb = 99;
		break;
	case HARD:
		nrow = 40;
		ncol = 60;
		nbomb = 400;
		break;
	case IMPOSSIBLE:
		nrow = 40;
		ncol = 60;
		nbomb = 999;
		break;
	}
}

Field::Field(int _nrow, int _ncol, int nbomb) :
	nrow(_nrow), ncol(_ncol), cells(new Cell*[nrow]), nbomb(nbomb), nmarked(0), gs(PLAYING) {
	for (int i = 0; i < nrow; ++i) {
		cells[i] = new Cell[ncol];
		for (int j = 0; j < ncol; ++j)
			cells[i][j].setCoord(j, i);
	}

	reset();
}

Field::Field(DIFFICULTY d) : nbomb(0), nmarked(0), gs(PLAYING), cells(nullptr) {
	double p{ 0 };
	setSizes(d);
	cells = new Cell*[nrow];
	for (int i = 0; i < nrow; ++i) {
		cells[i] = new Cell[ncol];
		for (int j = 0; j < ncol; ++j)
			cells[i][j].setCoord(j, i);
	}
	reset();
}

void Field::rebuild(int _nrow, int _ncol, int _nbomb) {
	ClearConsole();
	for (int i = 0; i < nrow; ++i)
		delete[] cells[i];
	delete[] cells;

	nrow = _nrow; ncol = _ncol;
	nbomb = _nbomb;
	cells = new Cell*[nrow];
	for (int i = 0; i < nrow; ++i) {
		cells[i] = new Cell[ncol];
		for (int j = 0; j < ncol; ++j)
			cells[i][j].setCoord(j, i);
	}
	reset();
}

void Field::rebuild(DIFFICULTY d)
{
	ClearConsole();
	for (int i = 0; i < nrow; ++i)
		delete[] cells[i];
	delete[] cells;
	setSizes(d);

	cells = new Cell * [nrow];
	for (int i = 0; i < nrow; ++i) {
		cells[i] = new Cell[ncol];
		for (int j = 0; j < ncol; ++j)
			cells[i][j].setCoord(j, i);
	}

	reset();
}

void Field::reset() {
	nmarked = 0; 
	gs = PLAYING;
	for (int i = 0; i < nrow; ++i)
		for (int j = 0; j < ncol; ++j) {
			cells[i][j].reset();
		}
	int m = 0, t = 0;
	int N = nrow * ncol;
	while (m < nbomb) {
		if ((N - t) * rnunif() >= nbomb - m) 
			++t;
		else {
			cells[t / ncol][t % ncol].setBomb();
			++t; ++m;
		}
	}

	for (int i = 0; i < nrow; ++i)
		for (int j = 0; j < ncol; ++j) {
			int dx_s, dx_e, dy_s, dy_e;
			boundary(i, j, dx_s, dx_e, dy_s, dy_e);
			cells[i][j].setValue(0);
			for (int dx = dx_s; dx <= dx_e; ++dx)
				for (int dy = dy_s; dy <= dy_e; ++dy)
					cells[i][j].incValue(cells[i + dy][j + dx].isBomb());
		}
	show();
}

void Field::showScore() const {
	ColorPrint(0, nrow + 1, F_L_WHITE, "%3d/%3d", nmarked, nbomb);
}

void Field::showHelp() const {
	ColorPrint(0, nrow + 3, F_L_WHITE, "WASD - move cursor; K - sweep; M - mark");
	ColorPrint(0, nrow + 4, F_L_WHITE, "1-Elementary, 2-Easy, 3-Medium, 4-Hard");
}

void Field::show() const {
	ClearConsole();
	for (int i = 0; i < nrow; ++i)
		for (int j = 0; j < ncol; ++j)
			cells[i][j].show();
	showScore();
	switch (gs) {
	case PLAYING:
		ColorPrint(1, nrow + 2, F_L_WHITE, "You're doing great!");
		break;
	case VICTORY:
		ColorPrint(1, nrow + 2, B_L_GREEN, "VICTORY!!! Play again? (y/n)");
		break;
	case FAILURE:
		ColorPrint(1, nrow + 2, B_L_RED, "GAME OVER. Play again? (y/n)");
		break;
	}
	showHelp();
}

void Field::openAll() {
	for (int i = 0; i < nrow; ++i)
		for (int j = 0; j < ncol; ++j)
			cells[i][j].open();
	show();
}

void Field::sweep(int i, int j) {
	int m{0};
	if (gs != PLAYING) return;
	if (i >= nrow || j >= ncol || i < 0 || j < 0) return;
	switch (cells[i][j].sweep()) {
	case OPENED:
	case EMPTY:
		int dx_s, dx_e, dy_s, dy_e;
		boundary(i, j, dx_s, dx_e, dy_s, dy_e);

		for (int dx = dx_s; dx <= dx_e; ++dx)
			for (int dy = dy_s; dy <= dy_e; ++dy)
				if (cells[i + dy][j + dx].isMarked())
					++m;

		if (m == cells[i][j].value())
		for (int dx = dx_s; dx <= dx_e; ++dx)
			for (int dy = dy_s; dy <= dy_e; ++dy)
				if (!cells[i + dy][j + dx].isOpened())
					sweep(i + dy, j + dx);
		break;
	case USUAL:
		break;
	case GAMEOVER:
		endgame(false);
		break;
	}
	cells[i][j].show();
}

void Field::mark(int i, int j) {
	if (gs != PLAYING) return;
	if (i >= nrow || j >= ncol || i < 0 || j < 0) return;
	if (!cells[i][j].isOpened()) {
		cells[i][j].mark();
		if (cells[i][j].isMarked())
			++nmarked;
		else
			--nmarked;
		if (cells[i][j].isMarked() == cells[i][j].isBomb())
			check();
		cells[i][j].show();
		showScore();
	}
}

void Field::endgame(bool victory) {
	if (victory)
		gs = VICTORY;
	else
		gs = FAILURE;
	openAll();
}

void Field::check() {
	if (gs != PLAYING) return;
	if (nmarked == nbomb) {
		for (int i = 0; i < nrow; ++i)
			for (int j = 0; j < ncol; ++j)
				if (cells[i][j].isMarked() != cells[i][j].isBomb())
					return;
		endgame(true);
	}
}

Field::~Field() {
	for (int i = 0; i < nrow; ++i)
		delete[] cells[i];
	delete[] cells;
}

void play(Field& field) {
	int x{ 0 }, y{ 0 };
	MoveCursor(x, y);
	while (field.gamestate() == PLAYING)
	{
		MoveCursor(x, y);
		int c = _getch();
		switch (c) {
		case 'W':
		case 'w':
			if (y - 1 >= 0) --y;
			break;
		case 'A':
		case 'a':
			if (x - 1 >= 0) --x;
			break;
		case 'S':
		case 's':
			if (y + 1 < field.getNrow()) ++y;
			break;
		case 'D':
		case 'd':
			if (x + 1 < field.getNcol()) ++x;
			break;

		case 'K':
		case 'k':
			field.sweep(y, x);
			break;
		case 'M':
		case 'm':
			field.mark(y, x);
			break;

		case '1':
			field.rebuild(ELEMENTARY);
			break;
		case '2':
			field.rebuild(EASY);
			break;
		case '3':
			field.rebuild(MEDIUM);
			break;
		case '4':
			field.rebuild(HARD);
			break;
		}
	}
}
