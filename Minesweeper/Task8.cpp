// Task8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
#include <cstdio>
#include <windows.h>
#include "Console.h"
#include "clField.h"
#include "R32M.h"

int main()
{
    InitConsole("Minesweeper", 70, 70);
    VisibleCursor(true);
    rninit(67);
    Field field(EASY);
    int c;
    play(field);
    c = _getch();
    while ((c != 'n') && (c != 'N')) {
        if (c == 'y' || c == 'Y') {
            field.reset();
            play(field);
        }
        c = _getch();
    }
    ClearConsole();
    return 0;
}
