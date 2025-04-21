#include "Variables.h"

int HContinousBoard[20][20]{}, VContinousBoard[20][20]{};
int HBContinousMax{}, HWContinousMax{}, HTContinousMax{}, HStoneSum[4][20]{};
int VBContinousMax{}, VWContinousMax{}, VTContinousMax{}, VStoneSum[4][20]{};
int LHDBContinousMax{}, LHDWContinousMax{}, LHDTContinousMax{}, LHDStoneSum[4][38]{};
int LLDBContinousMax{}, LLDWContinousMax{}, LLDTContinousMax{}, LLDStoneSum[4][38]{};
int CountBlackStone{}, CountWhiteStone{}, TContinousMax{};
std::string map[20][20]{}, player[2]{ " ○"," ●" };   // 1. black, 2. white
std::string MARKER{ "@" };