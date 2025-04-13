#include <iostream>
#include <iomanip>
#include <cstring>
#include <algorithm>
#define NOMINMAX
#include <windows.h>
#include "MyStack.h"
using namespace std;

int HContinousBoard[20][20]{}, VContinousBoard[20][20]{};
int HBContinousMax{}, HWContinousMax{}, HTContinousMax{}, HStoneSum[4][20]{};
int VBContinousMax{}, VWContinousMax{}, VTContinousMax{}, VStoneSum[4][20]{};
int LHDBContinousMax{}, LHDWContinousMax{}, LHDTContinousMax{}, LHDStoneSum[4][38]{};
int LLDBContinousMax{}, LLDWContinousMax{}, LLDTContinousMax{}, LLDStoneSum[4][38]{};
int CountBlackStone{}, CountWhiteStone{}, TContinousMax{};
string map[20][20]{}, player[2]{ " ○"," ●" };   // 1. black, 2. white
string MARKER{ "@" };
// Windows 콘솔 색상 정의
const WORD COLOR_DEFAULT = 0x07;                // 흰색 배경에 회색 글꼴
const WORD COLOR_YELLOW = 0x0E;                 // 검은색 배경에 밝은 노란색 글꼴
const WORD COLOR_RED = 0x0C;                    // 검은색 배경에 밝은 빨간색 글꼴
const WORD COLOR_GREEN = 0x0A;                  // 검은색 배경에 밝은 초록색 글꼴
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
static void setConsoleColor(WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

int main()
{
    Initialize();

    int PlayerTurn{ 0 };

    while (true) {
        //system("cls");
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
    cout << right << setw(108) << "**가로줄에 대해 최대 연속된 돌의 갯수 v  v\n";
    cout << right << setw(98) << "**가로줄에 대해 흑,백돌의 합 v  v\n";
    cout << "   |";
    for (int j = 1; j < 20; ++j)
        cout << setw(2) << j << setw(2) << " |";
    cout << setw(2) << " 흑 백 흑 백";
    cout << endl;

    for (int i = 1; i < 20; ++i) {
        cout << setw(2) << i << setw(2) << "|";
        for (int j = 1; j < 20; ++j) {
            if (map[i][j] == player[0] || map[i][j] == player[1]) {
                if (HContinousBoard[i][j] == HTContinousMax) {
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
        // 각 가로 줄에 대해 몇개의 돌이 놓여져 있는지 출력
        cout << setw(3) << HStoneSum[0][i] << setw(3) << HStoneSum[1][i];
        // 각 가로 줄에 대해 최대 몇개의 연속된 돌이 놓여져 있는지 출력
        cout << setw(3) << HStoneSum[2][i] << setw(3) << HStoneSum[3][i];
        
        cout << endl << "  ";
        for (int j = 1; j < 40; ++j) cout << "ㅡ";
        cout << endl;
    }
    // 각 세로 줄에 대해 몇개의 돌이 놓여져 있는지 출력
    for (int i = 0; i < 4; ++i) {
        if (i % 2 == 0) cout << "흑 :";
        else cout << "백 :";
        for (int j = 1; j < 20; ++j) {
            cout << setw(2) << VStoneSum[i][j] << setw(2) << " |";
        }
        cout << endl;
    }
    // 좌상우하 대각선에 대해 최대 몇개의 연속된 돌이 놓여져 있는지 출력
    cout << "\n좌상우하 대각선에 대해 최대 몇개의 연속된 돌 (19, 1) ~ (1, 19)\n";
    for (int i = 2; i < 4; ++i) {
        if (i % 2 == 0) cout << "흑 :";
        else cout << "백 :";
        for (int j = 1; j < 38; ++j) {
            cout << LHDStoneSum[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    // 좌하우상 대각선에 대해 최대 몇개의 연속된 돌이 놓여져 있는지 출력
    cout << "좌하우상 대각선에 대해 최대 몇개의 연속된 돌 (1, 1) ~ (19, 19)\n";
    for (int i = 2; i < 4; ++i) {
        if (i % 2 == 0) cout << "흑 :";
        else cout << "백 :";
        for (int j = 1; j < 38; ++j) {
            cout << LLDStoneSum[i][j] << " ";
        }
        cout << endl;
    }
    cout << "\n\n";
}

int PlaceBStone()
{
    int x, y;

    while (true) {
        cout << "흑돌 차례 : ";
        if (!(cin >> x >> y)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "잘못된 입력입니다. 다시 입력하세요.\n";
            continue;
        }
        if (x == 0 || y == 0) return -1;
        if (x > 19 || x < 0 || y > 19 || y < 0) {
            cout << "입력 범위가 잘못 되었습니다. 다시 입력하세요.\n";
            continue;
        }
        if (map[x][y] != "+") {
            cout << "돌이 이미 놓여져 있습니다.\n";
            continue;
        }
        break;
    }
    map[x][y] = player[0];
    CountBlackStone++;
    VStoneSum[0][y]++;
    HStoneSum[0][x]++;

    return 1;
}
int PlaceWStone()
{
    int x, y;

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
        if (map[x][y] != "+") {
            cout << "돌이 이미 놓여져 있습니다.\n";
            continue;
        }
        break;
    }
    map[x][y] = player[1];
    CountWhiteStone++;
    VStoneSum[1][y]++;
    HStoneSum[1][x]++;

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
    bool Dis[2]{ false };
    for (int i = 1; i < 20; i++) {
        Dis[0] = false; Dis[1] = false;
        HWContinousMax = 0; HBContinousMax = 0;
        for (int j = 1; j < 20; j++) {
            if (map[i][j] == player[0]) {                           //흑돌일때
                continuous_counter = 1;
                for (int k = 1; k < 5; k++) {
                    if (j + k < 20 && map[i][j + k] == player[0]) continuous_counter++;
                    else break;
                }
                HBContinousMax = max(continuous_counter, HBContinousMax);
                if (continuous_counter == HBContinousMax) {
                    for (int l = 0; l < HBContinousMax; l++)
                        if (HBContinousMax >= HWContinousMax) HContinousBoard[i][j + l] = HBContinousMax;
                }
                if (5 == continuous_counter) {
                    for (int k = 0; k < 5; ++k)
                        map[i][j + k] = MARKER;
                    return 1;
                }

                if (HBContinousMax > HWContinousMax) {
                    Dis[0] = true; Dis[1] = false;
                }
                else if (HBContinousMax < HWContinousMax) {
                    Dis[0] = false; Dis[1] = true;
                }
                else {
                    Dis[0] = false; Dis[1] = false;
                }
            }

            else if (map[i][j] == player[1]) {                      //백돌일때
                continuous_counter = 1;
                for (int k = 1; k < 5; k++) {
                    if (j + k < 20 && map[i][j + k] == player[1]) continuous_counter++;
                    else break;
                }
                HWContinousMax = max(continuous_counter, HWContinousMax);
                if (continuous_counter == HWContinousMax) {
                    for (int l = 0; l < HWContinousMax; l++)
                        if (HBContinousMax <= HWContinousMax) HContinousBoard[i][j + l] = HWContinousMax;
                }
                if (5 == continuous_counter) {
                    for (int k = 0; k < 5; ++k)
                        map[i][j + k] = MARKER;
                    return 2;
                }

                if (HBContinousMax > HWContinousMax) {
                    Dis[0] = true; Dis[1] = false;
                }
                else if (HBContinousMax < HWContinousMax) {
                    Dis[0] = false; Dis[1] = true;
                }
                else {
                    Dis[0] = false; Dis[1] = false;
                }
            }
        }

        if (Dis[0] == true) {
            HStoneSum[2][i] = HBContinousMax;
            HStoneSum[3][i] = -1;
        }
        else if (Dis[1] == true) {
            HStoneSum[3][i] = HWContinousMax;
            HStoneSum[2][i] = -1;
        }
        else {
            HStoneSum[2][i] = HBContinousMax;
            HStoneSum[3][i] = HWContinousMax;
        }

        MaxTemp = max(HWContinousMax, HBContinousMax);
        HTContinousMax = max(HTContinousMax, MaxTemp);
    }

    return 0;
}
int Vertical_Checker()
{
    int continuous_counter{ 1 }, MaxTemp{};
    bool Dis[2]{ false };
    for (int i = 1; i < 20; i++) {
        Dis[0] = false; Dis[1] = false;
        VWContinousMax = 0; VBContinousMax = 0;
        for (int j = 1; j < 20; j++) {
            if (map[j][i] == player[0]) {                           //흑돌일때
                continuous_counter = 1;
                for (int k = 1; k < 5; k++) {
                    if (j + k < 20 && map[j + k][i] == player[0]) continuous_counter++;
                    else break;
                }
                VBContinousMax = max(VBContinousMax, continuous_counter);
                if (5 == continuous_counter) {
                    for (int k = 0; k < 5; ++k)
                        map[j + k][i] = MARKER;
                    return 1;
                }

                if (VBContinousMax > VWContinousMax) {
                    Dis[0] = true; Dis[1] = false;
                }
                else if (VBContinousMax < VWContinousMax) {
                    Dis[0] = false; Dis[1] = true;
                }
                else {
                    Dis[0] = false; Dis[1] = false;
                }
            }
            else if (map[j][i] == player[1]) {                           //백돌일때
                continuous_counter = 1;
                for (int k = 1; k < 5; k++) {
                    if (j + k < 20 && map[j + k][i] == player[1]) continuous_counter++;
                    else break;
                }
                VWContinousMax = max(VWContinousMax, continuous_counter);
                if (5 == continuous_counter) {
                    for (int k = 0; k < 5; ++k)
                        map[j + k][i] = MARKER;
                    return 2;
                }

                if (VBContinousMax > VWContinousMax) {
                    Dis[0] = true; Dis[1] = false;
                }
                else if (VBContinousMax < VWContinousMax) {
                    Dis[0] = false; Dis[1] = true;
                }
                else {
                    Dis[0] = false; Dis[1] = false;
                }
            }
        }

        if (Dis[0] == true) {
            VStoneSum[2][i] = VBContinousMax;
            VStoneSum[3][i] = -1;
        }
        else if (Dis[1] == true) {
            VStoneSum[3][i] = VWContinousMax;
            VStoneSum[2][i] = -1;
        }
        else {
            VStoneSum[2][i] = VBContinousMax;
            VStoneSum[3][i] = VWContinousMax;
        }

        MaxTemp = max(VWContinousMax, VBContinousMax);
        VTContinousMax = max(VTContinousMax, MaxTemp);
    }

    return 0;
}
int LHDiagonal_Checker()
{
    int continuous_counter{ 1 }, MaxTemp{}, DiagonalCount{ 1 };
    bool Dis[2]{ false };
    for (int i = 19; i > 0; --i) {
        Dis[0] = false; Dis[1] = false;
        LHDBContinousMax = 0; LHDWContinousMax = 0;
        for (int j = i; j < 20; ++j) {
            if (map[19][j] == player[0]) {                           //흑돌일때
                continuous_counter = 1;
                LHDBContinousMax = max(continuous_counter, LHDBContinousMax);
                for (int k = 1; k < 20; ++k) {
                    if (i + k > 20 && j + k > 20) break;
                    if (i + k < 20 && j + k < 20 && map[i + k][j + k] == player[0]) {
                        continuous_counter++;
                        LHDBContinousMax = max(continuous_counter, LHDBContinousMax);
                        if (5 == continuous_counter) {
                            for (int k = 0; k < 5; ++k)
                                map[i + k][j + k] = MARKER;
                            return 1;
                        }
                    }
                    else {
                        continuous_counter = 1;
                        continue;
                    }
                }
                if (LHDBContinousMax > LHDWContinousMax) {
                    Dis[0] = true; Dis[1] = false;
                }
                else if (LHDBContinousMax < LHDWContinousMax) {
                    Dis[0] = false; Dis[1] = true;
                }
                else {
                    Dis[0] = false; Dis[1] = false;
                }
            }
            else if (map[19][j] == player[1]) {                      //백돌일때
                continuous_counter = 1;
                LHDBContinousMax = max(continuous_counter, LHDBContinousMax);
                for (int k = 1; k < 20; ++k) {
                    if (i + k > 20 && j + k > 20) break;
                    if (i + k < 20 && j + k < 20 && map[i + k][j + k] == player[1]) {
                        continuous_counter++;
                        LHDWContinousMax = max(continuous_counter, LHDWContinousMax);
                        if (5 == continuous_counter) {
                            for (int k = 0; k < 5; ++k)
                                map[i + k][j + k] = MARKER;
                            return 1;
                        }
                    }
                    else {
                        continuous_counter = 1;
                        continue;
                    }
                }
                if (LHDBContinousMax > LHDWContinousMax) {
                    Dis[0] = true; Dis[1] = false;
                }
                else if (LHDBContinousMax < LHDWContinousMax) {
                    Dis[0] = false; Dis[1] = true;
                }
                else {
                    Dis[0] = false; Dis[1] = false;
                }
            }
        }
        if (Dis[0] == true) {
            LHDStoneSum[2][DiagonalCount] = LHDBContinousMax;
            LHDStoneSum[3][DiagonalCount] = -1;
        }
        else if (Dis[1] == true) {
            LHDStoneSum[3][DiagonalCount] = LHDWContinousMax;
            LHDStoneSum[2][DiagonalCount] = -1;
        }
        else {
            LHDStoneSum[2][DiagonalCount] = LHDBContinousMax;
            LHDStoneSum[3][DiagonalCount] = LHDWContinousMax;
        }
        DiagonalCount++;
    }

    for (int i = 2; i < 19; ++i) {
        Dis[0] = false; Dis[1] = false;
        LHDBContinousMax = 0; LHDWContinousMax = 0;
        for (int j = 1; j < 20; ++j) {
            if (map[i][j] == player[0]) {                           //흑돌일때
                continuous_counter = 1;
                LHDBContinousMax = max(continuous_counter, LHDBContinousMax);
                for (int k = 1; k < 20; ++k) {
                    if (i + k > 20 && j + k > 20) break;
                    if (i + k < 20 && j + k < 20 && map[i + k][j + k] == player[0]) {
                        continuous_counter++;
                        LHDBContinousMax = max(continuous_counter, LHDBContinousMax);
                        if (5 == continuous_counter) {
                            for (int k = 0; k < 5; ++k)
                                map[i + k][j + k] = MARKER;
                            return 1;
                        }
                    }
                    else {
                        continuous_counter = 1;
                        continue;
                    }
                }

                if (LHDBContinousMax > LHDWContinousMax) {
                    Dis[0] = true; Dis[1] = false;
                }
                else if (LHDBContinousMax < LHDWContinousMax) {
                    Dis[0] = false; Dis[1] = true;
                }
                else {
                    Dis[0] = false; Dis[1] = false;
                }
            }
            else if (map[i][j] == player[1]) {                      //백돌일때
                continuous_counter = 1;
                LHDBContinousMax = max(continuous_counter, LHDBContinousMax);
                for (int k = 1; k < 20; ++k) {
                    if (i + k > 20 && j + k > 20) break;
                    if (i + k < 20 && j + k < 20 && map[i + k][j + k] == player[0]) {
                        continuous_counter++;
                        LHDWContinousMax = max(continuous_counter, LHDWContinousMax);
                        if (5 == continuous_counter) {
                            for (int k = 0; k < 5; ++k)
                                map[i + k][j + k] = MARKER;
                            return 1;
                        }
                    }
                    else {
                        continuous_counter = 1;
                        continue;
                    }
                }
                if (LHDBContinousMax > LHDWContinousMax) {
                    Dis[0] = true; Dis[1] = false;
                }
                else if (LHDBContinousMax < LHDWContinousMax) {
                    Dis[0] = false; Dis[1] = true;
                }
                else {
                    Dis[0] = false; Dis[1] = false;
                }
            }
        }

        if (Dis[0] == true) {
            LHDStoneSum[2][DiagonalCount] = LHDBContinousMax;
            LHDStoneSum[3][DiagonalCount] = -1;
        }
        else if (Dis[1] == true) {
            LHDStoneSum[3][DiagonalCount] = LHDWContinousMax;
            LHDStoneSum[2][DiagonalCount] = -1;
        }
        else {
            LHDStoneSum[2][DiagonalCount] = LHDBContinousMax;
            LHDStoneSum[3][DiagonalCount] = LHDWContinousMax;
        }
        DiagonalCount++;
    }
    return 0;
}
int LLDiagonal_Checker()
{
    int continuous_counter{ 1 }, MaxTemp{}, DiagonalCount{ 1 };
    bool Dis[2]{ false };
    for (int i = 1; i < 20; ++i) {
        Dis[0] = false; Dis[1] = false;
        LLDBContinousMax = 0; LLDWContinousMax = 0;
        for (int j = i; j > 0; --j) {
            if (map[1][j] == player[0]) {                           //흑돌일때
                continuous_counter = 1;
                LHDBContinousMax = max(continuous_counter, LHDBContinousMax);
                for (int k = 1; k < 5; ++k) {
                    if (i + k > 20 && j - k < 0) break;
                    if (i + k < 20 && j - k > 0 && map[i + k][j - k] == player[0]) {
                        continuous_counter++;
                        if (5 == continuous_counter) {
                            LLDWContinousMax = max(continuous_counter, LLDWContinousMax);
                            for (int k = 0; k < 5; ++k)
                                map[i + k][j - k] = MARKER;
                            return 1;
                        }
                    }
                    else {
                        continuous_counter = 1;
                        continue;
                    }
                }
                if (LLDBContinousMax > LLDWContinousMax) {
                    Dis[0] = true; Dis[1] = false;
                }
                else if (LLDBContinousMax < LLDWContinousMax) {
                    Dis[0] = false; Dis[1] = true;
                }
                else {
                    Dis[0] = false; Dis[1] = false;
                }
            }
            else if (map[1][j] == player[1]) {                      //백돌일때
                continuous_counter = 1;
                LHDBContinousMax = max(continuous_counter, LHDBContinousMax);
                for (int k = 1; k < 5; ++k) {
                    if (i + k > 20 && j - k < 0) break;
                    if (i + k < 20 && j - k > 0 && map[i + k][j - k] == player[0]) {
                        continuous_counter++;
                        LLDWContinousMax = max(continuous_counter, LLDWContinousMax);
                        if (5 == continuous_counter) {
                            for (int k = 0; k < 5; ++k)
                                map[i + k][j - k] = MARKER;
                            return 1;
                        }
                    }
                    else {
                        continuous_counter = 1;
                        continue;
                    }
                }
            }
            if (LLDBContinousMax > LLDWContinousMax) {
                Dis[0] = true; Dis[1] = false;
            }
            else if (LLDBContinousMax < LLDWContinousMax) {
                Dis[0] = false; Dis[1] = true;
            }
            else {
                Dis[0] = false; Dis[1] = false;
            }
        }

        if (Dis[0] == true) {
            LLDStoneSum[2][DiagonalCount] = LLDBContinousMax;
            LLDStoneSum[3][DiagonalCount] = -1;
        }
        else if (Dis[1] == true) {
            LLDStoneSum[3][DiagonalCount] = LLDWContinousMax;
            LLDStoneSum[2][DiagonalCount] = -1;
        }
        else {
            LLDStoneSum[2][DiagonalCount] = LLDBContinousMax;
            LLDStoneSum[3][DiagonalCount] = LLDWContinousMax;
        }
        DiagonalCount++;
    }

    for (int i = 2; i < 20; ++i) {
        Dis[0] = false; Dis[1] = false;
        LLDBContinousMax = 0; LLDWContinousMax = 0;
        for (int j = i; j > 0; --j) {
            if (map[i][j] == player[0]) {                           //흑돌일때
                continuous_counter = 1;
                LHDBContinousMax = max(continuous_counter, LHDBContinousMax);
                for (int k = 1; k < 5; ++k) {
                    if (i + k > 20 && j - k < 0) break;
                    if (i + k < 20 && j - k > 0 && map[i + k][j - k] == player[0]) {
                        continuous_counter++;
                        LLDWContinousMax = max(continuous_counter, LLDWContinousMax);
                        if (5 == continuous_counter) {
                            for (int k = 0; k < 5; ++k)
                                map[i + k][j - k] = MARKER;
                            return 1;
                        }
                    }
                    else {
                        continuous_counter = 1;
                        continue;
                    }
                }
                if (LLDBContinousMax > LLDWContinousMax) {
                    Dis[0] = true; Dis[1] = false;
                }
                else if (LLDBContinousMax < LLDWContinousMax) {
                    Dis[0] = false; Dis[1] = true;
                }
                else {
                    Dis[0] = false; Dis[1] = false;
                }
            }
            else if (map[i][j] == player[1]) {                      //백돌일때
                continuous_counter = 1;
                LHDBContinousMax = max(continuous_counter, LHDBContinousMax);
                for (int k = 1; k < 5; ++k) {
                    if (i + k > 20 && j - k < 0) break;
                    if (i + k < 20 && j - k > 0 && map[i + k][j - k] == player[0]) {
                        continuous_counter++;
                        LLDWContinousMax = max(continuous_counter, LLDWContinousMax);
                        if (5 == continuous_counter) {
                            for (int k = 0; k < 5; ++k)
                                map[i + k][j - k] = MARKER;
                            return 1;
                        }
                    }
                    else {
                        continuous_counter = 1;
                        continue;
                    }
                }
            }
            if (LLDBContinousMax > LLDWContinousMax) {
                Dis[0] = true; Dis[1] = false;
            }
            else if (LLDBContinousMax < LLDWContinousMax) {
                Dis[0] = false; Dis[1] = true;
            }
            else {
                Dis[0] = false; Dis[1] = false;
            }
        }

        if (Dis[0] == true) {
            LLDStoneSum[2][DiagonalCount] = LLDBContinousMax;
            LLDStoneSum[3][DiagonalCount] = -1;
        }
        else if (Dis[1] == true) {
            LLDStoneSum[3][DiagonalCount] = LLDWContinousMax;
            LLDStoneSum[2][DiagonalCount] = -1;
        }
        else {
            LLDStoneSum[2][DiagonalCount] = LLDBContinousMax;
            LLDStoneSum[3][DiagonalCount] = LLDWContinousMax;
        }
        DiagonalCount++;
    }
    return 0;
}