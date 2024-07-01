#include "build/inc/engine.hpp"
// Project specific header files
#include "build/app/variables.hpp"
#include "build/app/threaded.hpp"
#include "build/app/menus.hpp"
#include "build/app/game.hpp"

int main(void){
    InitWindow();
    InitAudio();

    // GameClock
    InitThreadByID(THREAD_GAME_TIMER);

    while (_MAIN_GAME_LOOP) // Main-game-loop
    {
        _debug_mode();
        
        if(WindowShouldClose()) _MAIN_GAME_LOOP = false;
        if(IsWindowResized()) { // update screen width and height
            ScreenWidth = GetScreenW();
            ScreenHeight = GetScreenH();
        }

        // begin drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (ScreenIndex){
            case 1: //* Main Menu
                drawMainMenu();
                break;
            case 2: //* Settings Menu
                drawSettings();
                break;
            case 3: //* Load Menu 
                drawLoadMenu();
                break;
            case 4: //* Save menu
                drawSaveMenu();
                break;
            case 5: //* Loading screen
                drawLoadingScreen();
                break;
            case 99: //* Main Game/Puase menu
                renderMainGame();
                if(isGamePaused){
                    renderPauseMenu();
                }
                break;

            default: // Tiny error handling
                ConsoleWrite("\n[ WARNING ] Something went wrong but no worries!\n");
                ScreenIndex = 1;
                break;
        }

        // display console regardless of screen
        if(isConsoleEnabled){
            DrawRectangle(GetScreenW()/2-10, 10, GetScreenW()/2, 525, TRANSPARENT_GRAY);
            DrawRectangle(GetScreenW()/2-10, 10, GetScreenW()/2, 50, TRANSPARENT_GRAY);
            DrawText("CONSOLE", GetScreenW()/2+5, 15, 45, DARKGRAY);
        }

		EndDrawing();
    }

    // Unload textures, stop threads, close window and OpenGL context then exit program
    if(TexMan.LoadedTextures){
        TexMan.UnloadTextures();
    }
    StopThreads();
    CloseWindow();
    return 0;
}