#include <iostream>
#include <iomanip>
#include <cstring>
#define NOMINMAX
#include <windows.h>
#include "Variables.h"
#include "Functions.h"
#include "MyOmokStack.h"
using namespace std;

int main()
{
    Initialize();

    int PlayerTurn{ 0 };

    while (true) {
        system("cls");
        ShowBoard();

        TContinousMax = max(HTContinousMax, VTContinousMax);
        for (int i = 0; i < 2; ++i) {
            for (int j = 1; j < 20; ++j) {
                if (HStoneSum[i][j] == TContinousMax && 0 == i) {
                    cout << "가로줄에서 가장 긴 연속된 흑돌의 갯수 : " << HTContinousMax << "\n\n";
                    break;
                }
                else if (HStoneSum[i][j] == TContinousMax && 1 == i) {
                    cout << "세로줄에서 가장 긴 연속된 백돌의 갯수 : " << VTContinousMax << "\n\n";
                    break;
                }
            }
        }

        cout << "흑돌 : " << player[0] << ", 백돌 : " << player[1] << endl;
        cout << "입력은 (세로축, 가로축) 입니다.\n";
        cout << "입력에 0이 입력되면 프로그램이 종료됩니다.\n";

        if (0 == PlayerTurn) {
            PlayerTurn = PlaceBStone();
            if (PlayerTurn == -1) {
                system("cls");
                break;
            }
            if (1 == CheckBoard()) {
                setConsoleColor(COLOR_TEAL);
                cout << "\n흑돌 승리!\n";
                setConsoleColor(COLOR_DEFAULT);
                break;
            }
            PlayerTurn = 1;
        }
        else {
            PlayerTurn = PlaceWStone();
            if (PlayerTurn == -1) {
                system("cls");
                break;
            }
            if (2 == CheckBoard()) {
                setConsoleColor(COLOR_TEAL);
                cout << "\n백돌 승리!\n";
                setConsoleColor(COLOR_DEFAULT);
                break;
            }
            PlayerTurn = 0;
        }
    }
    ShowBoard();
    cout << "총 " << CountBlackStone + CountWhiteStone << "착수\n";
    cout << "흑돌의 갯수 : " << CountBlackStone << endl;
    cout << "백돌의 갯수 : " << CountWhiteStone << endl;
}