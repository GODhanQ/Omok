#include <iostream>
#include <iomanip>
#include <cstring>
#include <algorithm>
#define NOMINMAX
#include <windows.h>
#include "MyStack.h"
using namespace std;

int Checker[20][20]{}, HContinousBoard[20][20]{};
int CountBlackStone{}, CountWhiteStone{}, BContinousMax{}, WContinousMax{}, TContinousMax{};
string map[20][20]{}, player[2]{ " ○"," ●" };   // 1. black, 2. white
string MARKER{ "@" };
// Windows 콘솔 색상 정의
const WORD COLOR_DEFAULT = 0x07;                // 흰색 배경에 회색 글꼴
const WORD COLOR_YELLOW = 0x0E;                 // 검은색 배경에 밝은 노란색 글꼴
const WORD COLOR_RED = 0x0C;                    // 검은색 배경에 밝은 빨간색 글꼴
const WORD COLOR_GREEN = 0x0A;                  // 검은색 배경에 밝은 주황색 글꼴
const WORD COLOR_TEAL = 0x0B;                   // 검은색 배경에 밝은 청록색 글꼴

void Initialize();
void ShowBoard();
int PlaceBStone();
int PlaceWStone();
int CheckBoard();
int Horizonal_Checker();
int Vertical_Checker();
int LHDiagonal_Checker();
int LLDiagonal_Checker();

// 콘솔 텍스트 색상 설정 함수
void setConsoleColor(WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

int main()
{
    Initialize();

    int PlayerTurn{ 0 };

    while (true) {
        system("cls");
        ShowBoard();

        cout << "흑돌 : " << player[0] << ", 백돌 : " << player[1] << endl;
        cout << "입력은 (세로축, 가로축) 입니다.\n";
        cout << "입력에 0이 입력되면 프로그램이 종료됩니다.\n";

        if (0 == PlayerTurn) {
            PlayerTurn = PlaceBStone();
            if (PlayerTurn == -1) break;
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
            if (PlayerTurn == -1) break;
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

void Initialize()
{
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            map[i][j] = "+";
        }
    }
    return;
}
void ShowBoard()
{
    cout << "   |";
    for (int j = 1; j < 20; ++j) 
        cout << setw(2) << j << setw(2) << " |";
    cout << endl;

    for (int i = 1; i < 20; ++i) {
        cout << setw(2) << i << setw(2) << "|";
        for (int j = 1; j < 20; ++j) {
            if (map[i][j] == player[0] || map[i][j] == player[1]) {
                if (HContinousBoard[i][j] == TContinousMax) {
                    setConsoleColor(COLOR_GREEN);
                    cout << setw(2) << map[i][j];
                    setConsoleColor(COLOR_DEFAULT);
                    cout << setw(2) << "|";
                    continue;
                }
                setConsoleColor(COLOR_YELLOW);
                cout << setw(2) << map[i][j];
                setConsoleColor(COLOR_DEFAULT);
            }
            else if (map[i][j] == MARKER) {
                setConsoleColor(COLOR_RED);
                cout << setw(2) << map[i][j];
                setConsoleColor(COLOR_DEFAULT);
            }
            else cout << setw(2) << map[i][j];
            cout << setw(2) << "|";
        }
        cout << endl << "  ";
        for (int j = 1; j < 40; ++j) cout << "ㅡ";
        cout << endl;
    }
    cout << endl;
}

int PlaceBStone()
{
    int x, y;
    bool flag{ false };

    while (true) {
        cout << "흑돌 차례 : ";
        if (!(cin >> x >> y)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "잘못된 입력입니다. 다시 입력하세요.\n";
            continue;
        }
        if (x > 19 || x < 0 || y > 19 || y < 0) {
            cout << "입력 범위가 잘못 되었습니다. 다시 입력하세요.\n";
            continue;
        }
        if (x == 0 || y == 0) return -1;
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                if (map[x][y] != "+") {
                    flag = true;
                    break;
                }
            }
        }
        if (true == flag) {
            cout << "돌이 이미 놓여져 있습니다.\n";
            flag = false;
            continue;
        }
        break;
    }
    map[x][y] = player[0];
    CountBlackStone++;

    return 1;
}
int PlaceWStone()
{
    int x, y;
    bool flag{ false };

    while (true) {
        cout << "백돌 차례 : ";
        if (!(cin >> x >> y)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "잘못된 입력입니다. 다시 입력하세요.\n";
            continue;
        }
        if (x > 19 || x < 0 || y > 19 || y < 0) {
            cout << "입력 범위가 잘못 되었습니다. 다시 입력하세요.\n";
            continue;
        }
        if (x == 0 || y == 0) return -1;
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                if (map[x][y] != "+") {
                    flag = true;
                    break;
                }
            }
        }
        if (true == flag) {
            cout << "돌이 이미 놓여져 있습니다.\n";
            flag = false;
            continue;
        }
        break;
    }
    map[x][y] = player[1];
    CountWhiteStone++;

    return 1;
}

int CheckBoard()
{
    system("cls");
    int Status{};
    //1. 가로
    Status = Horizonal_Checker();
    if (Status == 1)
        return 1;
    else if (Status == 2)
        return 2;

    //2. 좌상우하
    Status = LHDiagonal_Checker();
    if (Status == 1)
        return 1;
    else if (Status == 2)
        return 2;

    //3. 세로
    Status = Vertical_Checker();
    if (Status == 1)
        return 1;
    else if (Status == 2)
        return 2;

    //4. 좌하우상
    Status = LLDiagonal_Checker();
    if (Status == 1)
        return 1;
    else if (Status == 2)
        return 2;

    return 0;
}

int Horizonal_Checker()
{
    int continuous_counter{ 1 }, MaxTemp{};
    for (int i = 1; i < 20; i++) {
        WContinousMax = 0; BContinousMax = 0;
        for (int j = 1; j < 20; j++) {
            if (map[i][j] == player[0]) {                           //흑돌일때
                continuous_counter = 1;
                for (int k = 1; k < 5; k++) {
                    if (j + k < 20 && map[i][j + k] == player[0]) continuous_counter++;
                    else break;
                }
                if (BContinousMax <= continuous_counter) BContinousMax = continuous_counter;
                if (continuous_counter == BContinousMax) {
                    for (int l = 0; l < BContinousMax; l++)
                        if (BContinousMax >= WContinousMax) HContinousBoard[i][j + l] = BContinousMax;
                }
                if (5 == continuous_counter) {
                    for (int k = 0; k < 5; ++k)
                        map[i][j + k] = MARKER;
                    return 1;
                }
            }

            else if (map[i][j] == player[1]) {                      //백돌일때
                continuous_counter = 1;
                for (int k = 1; k < 5; k++)
                    if (j + k < 20 && map[i][j + k] == player[1]) continuous_counter++;
                    else break;
                }
                if (WContinousMax <= continuous_counter) WContinousMax = continuous_counter;
                if (continuous_counter == WContinousMax) {
                    for (int l = 0; l < WContinousMax; l++) 
                        if (BContinousMax <= WContinousMax) HContinousBoard[i][j + l] = WContinousMax;
                }
                if (5 == continuous_counter) {
                    for (int k = 0; k < 5; ++k) 
                        map[i][j + k] = MARKER;
                    return 2;
                }
            }
        }
    MaxTemp = max(WContinousMax, BContinousMax);
    if (TContinousMax <= MaxTemp) TContinousMax = MaxTemp;

    return 0;
}
int Vertical_Checker()
{
    int continuous_counter{ 1 };
    for (int i = 1; i < 20; i++) {
        for (int j = 1; j < 20; j++) {
            if (map[i][j] == player[0]) {                           //흑돌일때
                continuous_counter = 1;
                for (int k = 1; k < 5; k++) {
                    if (j + k < 20 && map[i][j + k] == player[0]) continuous_counter++;
                    else break;
                }
                if (5 == continuous_counter) {
                    for (int k = 0; k < 5; ++k)
                        map[i + k][j] = MARKER;
                    return 1;
                }
            }
            if (map[i][j] == player[1]) {                           //백돌일때
                continuous_counter = 1;
                for (int k = 1; k < 5; k++) {
                    if (j + k < 20 && map[i][j + k] == player[1]) continuous_counter++;
                    else break;
                }
                if (5 == continuous_counter) {
                    for (int k = 0; k < 5; ++k)
                        map[i + k][j] = MARKER;
                    return 2;
                }
            }
        }
    }

    return 0;
}
int LHDiagonal_Checker()
{
    int continuous_counter{ 1 };
    for (int i = 1; i < 20; i++) {
        for (int j = 1; j < 20; j++) {
            if (map[i][j] == player[0]) {                           //흑돌일때
                continuous_counter = 1;
                for (int k = 1; k < 5; k++) {
                    if (i + k < 20 && j + k < 20 && map[i + k][j + k] == player[0]) continuous_counter++;
                    else break;
                }
                if (5 == continuous_counter) {
                    for (int k = 0; k < 5; ++k)
                        map[i + k][j + k] = MARKER;
                    return 1;
                }
            }
            else if (map[i][j] == player[1]) {                      //백돌일때
                continuous_counter = 1;
                for (int k = 1; k < 5; k++) {
                    if (i + k < 20 && j + k < 20 && map[i + k][j + k] == player[1]) continuous_counter++;
                    else break;
                }
                if (5 == continuous_counter) {
                    for (int k = 0; k < 5; ++k)
                        map[i - k][j - k] = MARKER;
                    return 2;
                }
            }
        }
    }

    return 0;
}
int LLDiagonal_Checker()
{
    int continuous_counter{ 1 };
    for (int i = 1; i < 20; i++) {
        for (int j = 1; j < 20; j++) {
            if (map[i][j] == player[0]) {                           //흑돌일때
                continuous_counter = 1;
                for (int k = 1; k < 5; k++) {
                    if (i + k < 20 && j - k > 0 && map[i + k][j - k] == player[0]) continuous_counter++;
                    else break;
                }
                if (5 == continuous_counter) {
                    for (int k = 0; k < 5; ++k)
                        map[i + k][j - k] = MARKER;
                    return 1;
                }
            }
            else if (map[i][j] == player[1]) {                      //백돌일때
                continuous_counter = 1;
                for (int k = 1; k < 5; k++) {
                    if (i + k < 20 && j - k > 0 && map[i + k][j - k] == player[1]) continuous_counter++;
                    else break;
                }
                if (5 == continuous_counter) {
                    for (int k = 0; k < 5; ++k)
                        map[i + k][j - k] = MARKER;
                    return 2;
                }
            }
        }
    }

    return 0;
}