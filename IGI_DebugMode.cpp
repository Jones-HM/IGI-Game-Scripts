// Project I.G.I DebugMode. Enables DebugMode in IGI must be execute in CheatEngine Scripts.
// Written by IGI-ResearchDevs - HM.
// Using GTLibc library.

#include "GTLibc.hpp"
using namespace GTLIBC;

// Game details
#define GAME_NAME "igi"

// Memory addresses
#define DBG_ENABLE 0x005BDC1C
#define DBG_ALLOC 0x00A5EA75
#define DBG_ADDR 0x005C8BF4
#define DBG_PLAYER_INFO 0x0056DF94
#define DBG_FONT 0x0054D958
#define DBG_FONT_BIG "LOCAL:computer/font1.fnt"
#define DBG_FONT_DEBUG "LOCAL:debug.fnt"

int main() {
    GTLibc gtlibc(true);
    DWORD gameBaseAddress;

    // Find the game process
    HANDLE gameHandle = gtlibc.FindGameProcess(GAME_NAME);
    if (gameHandle == NULL) {
        std::cout << "Game process not found." << std::endl;
        return 1;
    }

    gameBaseAddress = gtlibc.GetGameBaseAddress();

    // Enable debug
    gtlibc.WriteAddress(DBG_ALLOC, DBG_ADDR);
    gtlibc.WriteString(DBG_FONT, DBG_FONT_BIG);
    gtlibc.WriteAddress(DBG_FONT + 24, 0x0);

    gtlibc.WriteAddress(DBG_ENABLE, 1);
    gtlibc.WriteAddress(DBG_PLAYER_INFO, 1);

    return 0;
}
