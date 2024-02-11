// File: main.c
// Created: 2021-04-10 23:00:00
// Author: Abhishek Mishra
// File description: main file for the raygui based docker gui.
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

// initial empty ragyui based on one of raygui samples.

int main()
{
    // Initialization
    //---------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 600;
    
    SetConfigFlags(FLAG_WINDOW_UNDECORATED);
    InitWindow(screenWidth, screenHeight, "v-rex-rl: docker gui");

    // General variables
    Vector2 mousePosition = { 0 };
    Vector2 windowPosition = { 500, 200 };
    Vector2 panOffset = mousePosition;
    bool dragWindow = false;
    
    SetWindowPosition(windowPosition.x, windowPosition.y);
    
    bool exitWindow = false;
    
    SetTargetFPS(60);

    // Main game loop
    //--------------------------------------------------------------------------------------
    while (!exitWindow && !WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        mousePosition = GetMousePosition();
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !dragWindow)
        {
            if (CheckCollisionPointRec(mousePosition, (Rectangle){ 0, 0, screenWidth, 20 }))
            {
                dragWindow = true;
                panOffset = mousePosition;
            }
        }

        if (dragWindow)
        {            
            windowPosition.x += (mousePosition.x - panOffset.x);
            windowPosition.y += (mousePosition.y - panOffset.y);

            SetWindowPosition((int)windowPosition.x, (int)windowPosition.y);
            
            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) dragWindow = false;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            exitWindow = GuiWindowBox((Rectangle){ 0, 0, screenWidth, screenHeight }, "#198# V-REX");
            
            DrawText(TextFormat("Mouse Position: [ %.0f, %.0f ]", mousePosition.x, mousePosition.y), 10, 40, 10, DARKGRAY);
            DrawText(TextFormat("Window Position: [ %.0f, %.0f ]", windowPosition.x, windowPosition.y), 10, 60, 10, DARKGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    CloseWindow();

    return 0;
}
