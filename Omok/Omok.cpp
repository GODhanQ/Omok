#include <iostream>
#include <iomanip>
#include <cstring>
#define NOMINMAX
#include <windows.h>
using namespace std;

int Checker[20][20]{};
string map[20][20];
string player[2]{ " ○"," ●" };// 1. black, 2. white
int CountBlackStone{}, CountWhiteStone{};
constexpr string MARKER{ "@" };  //win marker
// Windows 콘솔 색상 정의
const WORD COLOR_DEFAULT = 0x07;   // 흰색 배경에 회색 글꼴
const WORD COLOR_YELLOW = 0x0E;    // 검은색 배경에 밝은 노란색 글꼴
const WORD COLOR_RED = 0x0C;       // 검은색 배경에 밝은 빨간색 글꼴

void initialize();
void ShowBoard();
int PBS();
int PWS();
int CheckBoard();
int HC();
int VC();
int LHDiagonal_Checker();
int LLDiagonal_Checker();

// 콘솔 텍스트 색상 설정 함수
void setConsoleColor(WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

int main()
{
    initialize();

    int PlayerTurn{ 0 };

    while (true) {
        system("cls");
        ShowBoard();

        if (0 == PlayerTurn) {
            PlayerTurn = PBS();
            if (PlayerTurn == -1) {
                break;
            }
            if (1 == CheckBoard()) {
                system("cls");
                ShowBoard();
                break;
            }
            PlayerTurn = 1;
        }
        else {
            PlayerTurn = PWS();
            if (PlayerTurn == -1) {
                break;
            }
            if (1 == CheckBoard()) {
                system("cls");
                ShowBoard();
                break;
            }
            PlayerTurn = 0;
        }
    }
    cout << "흑돌의 갯수 : " << CountBlackStone << endl;
    cout << "백돌의 갯수 : " << CountWhiteStone << endl;
}

void initialize()
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
    for (int j = 1; j < 20; ++j) {
        cout << setw(2) << j % 20 << setw(2) << " |";
    }
    cout << endl;
    for (int i = 1; i < 20; ++i) {
        cout << setw(2) << i % 20 << setw(2) << "|";
        for (int j = 1; j < 20; ++j) {
            if (map[i][j] == player[0] || map[i][j] == player[1]) {
                setConsoleColor(COLOR_YELLOW);
                cout << setw(2) << map[i][j];
                setConsoleColor(COLOR_DEFAULT);
            }
            else if (map[i][j] == MARKER) {
                setConsoleColor(COLOR_RED);
                cout << setw(2) << map[i][j];
                setConsoleColor(COLOR_DEFAULT);
            }
            else {
                cout << setw(2) << map[i][j];
            }
            cout << setw(2) << "|";
        }
        cout << endl << "  ";
        for (int j = 1; j < 40; ++j) {
            cout << "ㅡ";
        }
        cout << endl;
    }
    cout << endl;
    /*
    for (int i = 1; i < 20; i++) {
        cout << i << " ";
    }
    cout << endl;
    for (int i = 1; i < 20; i++) {
        cout << i << " ";
        for (int j = 1; j < 20; j++) {
            cout << map[i][j] << ' ';
        }
        cout << '\n';
    }
    return;
    */
}

int PBS()
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
int PWS()
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
    //1. 가로, 2. 좌상우하 대각, 3. 세로, 4.우상좌하 대각;
    int Status{};
    //1. 가로
    cout << "가로 검사\n";
    Status = HC();
    if (Status == 1) {
        cout << "\n흑돌 승리!\n";
        return 1;
    }
    else if (Status == 2) {
        cout << "\n백돌 승리!\n";
        return 1;
    }

    //2. 좌상우하
    //Status = LRDC();
    cout << "좌상우하 대각선 검사\n";
    Status = LHDiagonal_Checker();
    if (Status == 1) {
        cout << "\n흑돌 승리!\n";
        return 1;
    }
    else if (Status == 2) {
        cout << "\n백돌 승리!\n";
        return 1;
    }

    //3. 세로
    cout << "세로 검사\n";
    Status = VC();
    if (Status == 1) {
        cout << "\n흑돌 승리!\n";
        return 1;
    }
    else if (Status == 2) {
        cout << "\n백돌 승리!\n";
        return 1;
    }

    //4. 좌하우상
    Status = LLDiagonal_Checker();
    if (Status == 1) {
        cout << "\n흑돌 승리!\n";
        return 1;
    }
    else if (Status == 2) {
        cout << "\n백돌 승리!\n";
        return 1;
    }
}

int HC()
{
    //int changus_state{};                                          // 0 : 변화 없음, 1 : 흑돌로 변화, 2 : 백돌로 변화.
    int continuous_counter{ 1 };                                    // 연속된 돌 카운터
    for (int i = 1; i < 20; i++) {
        for (int j = 1; j < 20; j++) {
            if (map[i][j] == player[0]) {                           //흑돌일때
                //changus_state = 1;
                continuous_counter = 1;
                // 좌상우하 방향 체크
                for (int k = 1; k < 5; k++) {
                    if (i + k < 20 && map[i + k][j] == player[0]) {
                        continuous_counter++;
                    }
                    else {
                        break;
                    }
                }
                if (5 == continuous_counter) {                      // 5개 연속 발견시
                    for (int k = 0; k < 5; ++k) {
                        map[i][j - k] = MARKER;
                    }
                    return 1;
                }
            }
            if (map[i][j] == player[1]) {                           //백돌일때
                //changus_state = 2;
                continuous_counter = 1;
                // 좌상우하 방향 체크
                for (int k = 1; k < 5; k++) {
                    if (i + k < 20 && map[i + k][j] == player[1]) {
                        continuous_counter++;
                    }
                    else {
                        break;
                    }
                }
                if (5 == continuous_counter) {
                    for (int k = 0; k < 5; ++k) {
                        map[i - k][j] = MARKER;
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}
int VC()
{
    //int changus_state{};                                          // 0 : 변화 없음, 1 : 흑돌로 변화, 2 : 백돌로 변화.
    int continuous_counter{ 1 };                                    // 연속된 돌 카운터
    for (int i = 1; i < 20; i++) {
        for (int j = 1; j < 20; j++) {
            if (map[i][j] == player[0]) {                           //흑돌일때
                //changus_state = 1;
                continuous_counter = 1;
                // 좌상우하 방향 체크
                for (int k = 1; k < 5; k++) {
                    if (j + k < 20 && map[i][j + k] == player[0]) {
                        continuous_counter++;
                    }
                    else {
                        break;
                    }
                }
                if (5 == continuous_counter) {
                    for (int k = 0; k < 5; ++k) {
                        map[i][j - k] = MARKER;
                    }
                    return 1;
                }
            }
            if (map[i][j] == player[1]) {                           //백돌일때
                //changus_state = 2;
                continuous_counter = 1;
                // 좌상우하 방향 체크
                for (int k = 1; k < 5; k++) {
                    if (j + k < 20 && map[i][j + k] == player[1]) {
                        continuous_counter++;
                    }
                    else {
                        break;
                    }
                }
                if (5 == continuous_counter) {
                    for (int k = 0; k < 5; ++k) {
                        map[i][j - k] = MARKER;
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}
int LHDiagonal_Checker()
{
    //int changus_state{};
    int continuous_counter{ 1 };
    for (int i = 1; i < 20; i++) {
        for (int j = 1; j < 20; j++) {
            if (map[i][j] == player[0]) {                           //흑돌일때
                //changus_state = 1;
                continuous_counter = 1;
                // 좌상우하 방향 체크
                for (int k = 1; k < 5; k++) {
                    if (i + k < 20 && j + k < 20 && map[i + k][j + k] == player[0]) {
                        continuous_counter++;
                    }
                    else {
                        break;
                    }
                }
                if (5 == continuous_counter) {
                    for (int k = 0; k < 5; ++k) {
                        map[i + k][j + k] = MARKER;
                    }
                    return 1;
                }
            }
            else if (map[i][j] == player[1]) {                      //백돌일때
                //changus_state = 2;
                continuous_counter = 1;
                // 좌상우하 방향 체크
                for (int k = 1; k < 5; k++) {
                    if (i + k < 20 && j + k < 20 && map[i + k][j + k] == player[1]) {
                        continuous_counter++;
                    }
                    else {
                        break;
                    }
                }
                if (5 == continuous_counter) {
                    for (int k = 0; k < 5; ++k) {
                        map[i - k][j - k] = MARKER;
                    }
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
            if (map[i][j] == player[0]) {                                    //흑돌일때
                continuous_counter = 1;
                // 좌하우상 방향 체크
                for (int k = 1; k < 5; k++) {
                    if (i + k < 20 && j - k > 0 && map[i + k][j - k] == player[0]) {
                        continuous_counter++;
                    }
                    else {
                        break;
                    }
                }
                if (5 == continuous_counter) {
                    for (int k = 0; k < 5; ++k) {
                        map[i + k][j - k] = MARKER;
                    }
                    return 1;
                }
            }
            else if (map[i][j] == player[1]) {                                //백돌일때
                continuous_counter = 1;
                // 좌하우상 방향 체크
                for (int k = 1; k < 5; k++) {
                    if (i + k < 20 && j - k > 0 && map[i + k][j - k] == player[1]) {
                        continuous_counter++;
                    }
                    else {
                        break;
                    }
                }
                if (5 == continuous_counter) {
                    for (int k = 0; k < 5; ++k) {
                        map[i + k][j - k] = MARKER;
                    }
                    return 2;
                }
            }
        }
    }
    return 0;
}