#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void setConsoleColor(WORD color);
void Initialize();
void ShowBoard();
int PlaceBStone();
int PlaceWStone();
int CheckBoard();
int Horizonal_Checker();
int Vertical_Checker();
int LHDiagonal_Checker();
int LLDiagonal_Checker();

#endif