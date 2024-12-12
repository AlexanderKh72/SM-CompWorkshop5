#pragma once

enum ACTION {GAMEOVER, EMPTY, USUAL, OPENED};

class Cell {
private:
	int x;
	int y;
	int neighbours;
	bool bomb;
	bool opened;
	bool marked;

public:
	Cell(bool _bomb = false, int _x = 0, int _y = 0, int _neighbours = 0, bool _opened = false, bool _marked = false) :
		bomb(_bomb), x(_x), y(_y), neighbours(_neighbours), opened(_opened), marked(_marked) {}
	Cell(const Cell& c) :
		bomb(c.isBomb()), neighbours(c.value()), opened(c.isOpened()), marked(c.isMarked()) {}
	~Cell() {}


	bool isBomb() const { return bomb; }
	int value() const { return neighbours; }
	bool isOpened() const { return opened;  }
	bool isMarked() const { return marked; }

	void setCoord(int _x, int _y) { x = _x; y = _y; }
	void setBomb(bool _bomb = true) { bomb = _bomb; }
	void setValue(int val) { neighbours = val; }
	void incValue(bool f = true) { if (f) ++neighbours; }
	void open(bool f = true) { opened = f; }
	void mark() { marked = !marked; }

	void reset();

	ACTION sweep();
	void show() const;
};
