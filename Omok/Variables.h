#pragma once
#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#define NOMINMAX
#include <Windows.h>

extern int HContinousBoard[20][20], VContinousBoard[20][20];
extern int HBContinousMax, HWContinousMax, HTContinousMax, HStoneSum[4][20];
extern int VBContinousMax, VWContinousMax, VTContinousMax, VStoneSum[4][20];
extern int LHDBContinousMax, LHDWContinousMax, LHDTContinousMax, LHDStoneSum[4][38];
extern int LLDBContinousMax, LLDWContinousMax, LLDTContinousMax, LLDStoneSum[4][38];
extern int CountBlackStone, CountWhiteStone, TContinousMax;
extern std::string map[20][20], player[2];   // 1. black, 2. white
extern std::string MARKER;
// Windows 콘솔 색상 정의
const WORD COLOR_DEFAULT = 0x07;                // 흰색 배경에 회색 글꼴
const WORD COLOR_YELLOW = 0x0E;                 // 검은색 배경에 밝은 노란색 글꼴
const WORD COLOR_RED = 0x0C;                    // 검은색 배경에 밝은 빨간색 글꼴
const WORD COLOR_GREEN = 0x0A;                  // 검은색 배경에 밝은 초록색 글꼴
const WORD COLOR_TEAL = 0x0B;                   // 검은색 배경에 밝은 청록색 글꼴

#endif