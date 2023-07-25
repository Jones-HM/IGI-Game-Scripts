/*[[Project I.G.I FreeCamera. Enables Free Roam Camera in IGI must be executed in CheatEngine Lua Script.
Controls:
X-Axis = Right/Left
Y-Axis = Up/Down
Z-Axis = Space/Alt
Angle/Roation = Mouse.
Recalibrate View = Backspace.
Start/Exit key = 'END'
Written by IGI-ResearchDevs - HM.--]]*/

#include "GTLibc.hpp"
using namespace GTLIBC;

// Game details
#define GAME_NAME "igi"

// Memory addresses
#define VIEWPORT_TASK 0x00497E94
#define VIEWPORT_ADDR 0x00BCAAE0
#define CAMERA_ADDR 0x00684138
#define VIEWPORT_X 0x00BCAB08
#define VIEWPORT_Y VIEWPORT_X + 8
#define VIEWPORT_Z VIEWPORT_X + 16
#define VIEWPORT_SIZE 9
#define FLOAT_SIZE 4
#define HUMAN_VIEW_BASE 0x0056E210
#define HUMAN_VIEW_OFFSETS {0x08, 0x7CC, 0x14, 0x4F0}

// Function to recalibrate viewport
void RecalibrateViewPort(GTLibc &gtlibc) {
    DWORD humanViewAddress = gtlibc.ReadPointerOffsets<DWORD>(HUMAN_VIEW_BASE, HUMAN_VIEW_OFFSETS);
    gtlibc.WriteFloat(humanViewAddress + 0xF3C, 0.0);
    gtlibc.WriteFloat(humanViewAddress + 0x50C, 3.095987082);
}

int main() {
    GTLibc gtlibc(true);

    // Find the game process
    HANDLE gameHandle = gtlibc.FindGameProcess(GAME_NAME);
    if (gameHandle == NULL) {
        std::cout << "Game process not found." << std::endl;
        return 1;
    }

    // Deattach viewport of camera
    gtlibc.WriteBytes(VIEWPORT_TASK, {0x90, 0x90});

    // Change human 3rd view
    DWORD humanViewAddress = gtlibc.ReadPointerOffsets<DWORD>(HUMAN_VIEW_BASE, HUMAN_VIEW_OFFSETS);
    gtlibc.WriteInteger(humanViewAddress, 3);

    // Main loop for key events
    while (!gtlibc.IsKeyPressed(VK_END)) {
        double vport_x = gtlibc.ReadDouble(VIEWPORT_X);
        double vport_y = gtlibc.ReadDouble(VIEWPORT_Y);
        double vport_z = gtlibc.ReadDouble(VIEWPORT_Z);
        double vport_off = 5.5; // Offset value to move this amount from axis

        // This loop allows us to move, rotate, zoom around freeroam camera
        for (int index = 0; index <= VIEWPORT_SIZE * FLOAT_SIZE; index += FLOAT_SIZE) {
            float camera_prop = gtlibc.ReadFloat(CAMERA_ADDR + index);
            gtlibc.WriteFloat(VIEWPORT_ADDR + index, camera_prop);
        }

        // Key events for X-axis
        if (gtlibc.IsKeyPressed(VK_RIGHT)) {
            gtlibc.WriteDouble(VIEWPORT_X, vport_x - vport_off);
        }
        if (gtlibc.IsKeyPressed(VK_LEFT)) {
            gtlibc.WriteDouble(VIEWPORT_X, vport_x + vport_off);
        }

        // Key events for Y-axis
        if (gtlibc.IsKeyPressed(VK_UP)) {
            gtlibc.WriteDouble(VIEWPORT_Y, vport_y - vport_off);
        }
        if (gtlibc.IsKeyPressed(VK_DOWN)) {
            gtlibc.WriteDouble(VIEWPORT_Y, vport_y + vport_off);
        }

        // Key events for Z-axis
        if (gtlibc.IsKeyPressed(VK_SPACE)) {
            gtlibc.WriteDouble(VIEWPORT_Z, vport_z + vport_off);
        }
        if (gtlibc.IsKeyPressed(VK_MENU)) {
            gtlibc.WriteDouble(VIEWPORT_Z, vport_z - vport_off);
        }

        // Key event for recalibrate view
        if (gtlibc.IsKeyPressed(VK_BACK)) {
            RecalibrateViewPort(gtlibc);
        }
    }

    // Attach viewport of camera
    gtlibc.WriteBytes(VIEWPORT_TASK, {0xF3, 0xA5});

    // Reset human view
    gtlibc.WriteInteger(humanViewAddress, 1);

    return 0;
}
