#pragma once
#include "clCell.h"

enum DIFFICULTY { ELEMENTARY, EASY, MEDIUM, HARD, IMPOSSIBLE };
enum GAMESTATE {VICTORY, FAILURE, PLAYING};

class Field {
private:
	int nrow;
	int ncol;
	int nbomb;
	int nmarked;
	Cell** cells;
	GAMESTATE gs;

	void boundary(int i, int j, int& dx_s, int& dx_e, int& dy_s, int& dy_e);
	void setSizes(DIFFICULTY d);

public:
	Field(int _nrow, int _ncol, int _nbomb);
	Field(DIFFICULTY d = MEDIUM);
	~Field();

	void rebuild(int _nrow, int _ncol, int _nbomb);
	void rebuild(DIFFICULTY d = MEDIUM);

	int getNrow() const { return nrow; }
	int getNcol() const { return ncol; }
	GAMESTATE gamestate() const { return gs; }

	void reset();
	void show() const;
	void showScore() const;
	void showHelp() const;

	void openAll();
	void endgame(bool victory);

	void sweep(int i, int j);
	void mark(int i, int j);

	void check();
};

void play(Field& field);
