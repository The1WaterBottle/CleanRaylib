#include "app.hpp"

// Main menu
void drawMainMenu(){
    StartBtn = drawButtonUV(StartBtn, "Start", 52, StartAligner, &start_game);
    SettingsBtn = drawButtonUV(SettingsBtn, "Settings", 52, Rectangle{ StartAligner.x, StartAligner.y + ScreenToV(100), StartAligner.width, StartAligner.height }, &open_settings);
    LoadBtn = drawButtonUV(LoadBtn, "Load", 52, Rectangle{ StartAligner.x, StartAligner.y + ScreenToV(200), StartAligner.width, StartAligner.height }, &open_load_menu);
    ExitBtn = drawButtonUV(ExitBtn, "Exit", 52, Rectangle{ StartAligner.x, StartAligner.y + ScreenToV(300), StartAligner.width, StartAligner.height }, &quick_exit);
}

// Settings menu
void drawSettings(){
    Settings_BackBtn = drawButtonUV(Settings_BackBtn, "Back", 38, SettingsAligner, &CloseSettings);
    applyBtn = drawButtonUV(applyBtn, "Apply", 32, (Rectangle){ SettingsAligner.x, SettingsAligner.y + ScreenToV(60), SettingsAligner.width, SettingsAligner.height } , &ApplySettings);

    // --- screen ---
    ScreenTab = drawToggleUV(ScreenTab, "Screen", 50, Rectangle{SettingsAligner.x, SettingsAligner.y + ScreenToV(140), 220, 60}, &NullFunc, &ClsBools_ScreenTab);
    SoundTab  = drawToggleUV(SoundTab, "Sound", 50, Rectangle{SettingsAligner.x, SettingsAligner.y + ScreenToV(220), 220, 60},   &NullFunc, &ClsBools_SoundTab);
    AboutTab  = drawToggleUV(AboutTab, "About", 50, Rectangle{SettingsAligner.x, SettingsAligner.y + ScreenToV(300), 220, 60},   &NullFunc, &ClsBools_AboutTab);

    Rectangle TabRec = { SettingsAligner.x + ScreenToU(248), SettingsAligner.y + ScreenToV(72), ScreenToU(GetScreenW())-(SettingsAligner.x + ScreenToU(270)), ScreenToV(GetScreenH())-(SettingsAligner.y + ScreenToV(80)) };
    drawRecLinesWithUV(TabRec, ColLightGray);

    if(ScreenTab){ // display screen settings
        drawTextUV("Screen settings", SettingsAligner.x + ScreenToU(265), SettingsAligner.y, 60);
        isFullscreen = drawToggleUV(isFullscreen, "Fullscreen", 40, Rectangle{ SettingsAligner.x + ScreenToU(265), SettingsAligner.y + ScreenToV(140), 250, SettingsAligner.height }, &ToggleScreenReInit);
        isMSAA4X     = drawToggleUV(isMSAA4X    , "MSAA 4x",    40, Rectangle{ SettingsAligner.x + ScreenToU(265), SettingsAligner.y + ScreenToV(200), 250, SettingsAligner.height }, &ToggleScreenReInit);
        // isVSync      = drawToggleUV(isVSync    , "VSync",      40, Rectangle{ SettingsAligner.x + ScreenToU(265), SettingsAligner.y + ScreenToV(260), 250, SettingsAligner.height }, &ToggleScreenReInit); 
    } else if (SoundTab){
        drawTextUV("Sound settings", SettingsAligner.x + ScreenToU(265), SettingsAligner.y, 60);
        isMusicMute = drawToggleUV(isMusicMute, "Mute Music", 40, Rectangle{ SettingsAligner.x + ScreenToU(265), SettingsAligner.y + ScreenToV(140), 250, SettingsAligner.height });
        isSoundMute = drawToggleUV(isSoundMute, "Mute Sound", 40, Rectangle{ SettingsAligner.x + ScreenToU(265), SettingsAligner.y + ScreenToV(200), 250, SettingsAligner.height });
    } else if (AboutTab){
        drawTextUV("About", SettingsAligner.x + ScreenToU(265), SettingsAligner.y, 60);
    }
}

// Load menu
void drawLoadMenu(){
    LoadBackBtn = drawButtonUV(LoadBackBtn, "Back", 38, LoadAligner, &CloseLoadingMenu);

    std::vector<std::string> FolderNames = getFolderNames("saves/"); // get vector with folder names
    BeginScissorMode(UToScreen(0.02f), VToScreen(0.2f), GetScreenW()-UToScreen(0.02f), GetScreenH()); // cut rec for scroll area

    // check for mouse wheel movement
    if(CheckCollisionPointRec(GetMousePosition(), Rectangle{UToScreen(0.02f), VToScreen(0.2f), GetScreenW()-UToScreen(0.02f), GetScreenH()})){
        // Calculate the maximum offset allowed to reach the last element
        float maxOffset = countFolders("saves/") * 242.0f - GetScreenH() + VToScreen(0.2f);

        if(GetMouseWheelMove() > 0){
            if (ScissorOffsetLoadMenu >= 0) {
                ScissorOffsetLoadMenu = 0.0f;
            } else {
                ScissorOffsetLoadMenu += 22.0f;
            }
        }
        else if(GetMouseWheelMove() < 0){
            if (ScissorOffsetLoadMenu <= -maxOffset) {
                ScissorOffsetLoadMenu = -maxOffset;
            } else {
                ScissorOffsetLoadMenu -= 22.0f;
            }
        }
    }

    // draw saves one below the other
    // for (int y = 0; y < countFolders("saves/"); y++) {
    //     LoadSaveFile(FolderNames[y], Time, LoadedPlayTime);
    //     // ConsoleWrite(FolderNames[y]);

    //     float posY = y * (220 + 22) + VToScreen(0.2f); // Y offset
    //     DrawRectangle(UToScreen(0.02f), posY + ScissorOffsetLoadMenu, 830, 220, GRAY); // draw background rec
        
    //     const char* temp = FolderNames[y].c_str(); // convert std::string to const char *
    //     TempSaveDir += FolderNames[y];
    //     drawTextUV(temp, LoadAligner.x + ScreenToU(5), ScreenToV(posY + ScissorOffsetLoadMenu) + ScreenToV(5), 50, Color{210, 210, 210, 255}); // display save name
    //     drawTextUV(Time, LoadAligner.x + ScreenToU(5), ScreenToV(posY + ScissorOffsetLoadMenu) + ScreenToV(60), 16, Color{165, 165, 165, 255}); // display when the save was made
    //     // draw total playtime
    //     drawTextUV("Playtime :", 0.024f, ScreenToV(posY + ScissorOffsetLoadMenu) + ScreenToV(80), 22, Color{180, 180, 180, 255});// Convert int to string
    //     temp = CalculatePlayTime(LoadedPlayTime);
    //     drawTextUV(temp, LoadAligner.x + ScreenToU(113), ScreenToV(posY + ScissorOffsetLoadMenu) + ScreenToV(80), 22, Color{180, 180, 180, 255});

    //     LoadSG = drawToggleUV(LoadSG, "Load", 40, Rectangle{LoadAligner.x + ScreenToU(5), ScreenToV(posY + ScissorOffsetLoadMenu) + ScreenToV(165), 130.0f, 50.0f}, &LoadSaveGame); // load save game
    //     DelSG = drawToggleUV(DelSG, "Delete", 40, Rectangle{LoadAligner.x + ScreenToU(150), ScreenToV(posY + ScissorOffsetLoadMenu) + ScreenToV(165), 145.0f, 50.0f}); // delete save game
    //     if(DelSG){
    //         if(drawConfirmationBox("Delete Save?", 50, Rectangle{ScreenToU(GetScreenW()/2-250), ScreenToV(GetScreenH()/2-175), 500.0f, 350.0f}) == 1) {
    //             DeleteSaveGame();
    //             DelSG = false;
    //         } else if(drawConfirmationBox("Delete Save?", 50, Rectangle{ScreenToU(GetScreenW()/2-250), ScreenToV(GetScreenH()/2-175), 500.0f, 350.0f}) == 2) DelSG = false;
    //     }

    //     TempSaveDir = "saves/";
    // }
    EndScissorMode();
}

// Saving menu
void drawSaveMenu(){
    SaveBackBtn = drawButtonUV(SaveBackBtn, "Back", 38, (Rectangle){ 0.02f, 0.02f, 130.0f, 50.0f }, &CloseSavingMenu);

    drawInputBoxUV(SaveNameLettecCount, SaveName, 52, Rectangle{ 0.02f, 0.1f, 400, 60 });
    CreateSaveBtn = drawButtonUV(CreateSaveBtn, "Save", 45, (Rectangle){ 0.022f + ScreenToU(400), 0.1f, 150.0f, 60.0f }, &CreateNewSave);

    vector<string> FolderNames = getFolderNames("saves/"); // get vector with folder names
    BeginScissorMode(UToScreen(0.02f), VToScreen(0.2f), GetScreenW()-UToScreen(0.02f), GetScreenH()); // cut rec for scroll area

    // check for mouse wheel movement
    if(CheckCollisionPointRec(GetMousePosition(), Rectangle{UToScreen(0.02f), VToScreen(0.2f), GetScreenW()-UToScreen(0.02f), GetScreenH()})){
        // Calculate the maximum offset allowed to reach the last element
        float maxOffset = countFolders("saves/") * 242.0f - GetScreenH() + VToScreen(0.2f);

        if(GetMouseWheelMove() > 0){
            if (ScissorOffsetSaveMenu >= 0) {
                ScissorOffsetSaveMenu = 0.0f;
            } else {
                ScissorOffsetSaveMenu += 22.0f;
            }
        }
        else if(GetMouseWheelMove() < 0){
            if (ScissorOffsetSaveMenu <= -maxOffset) {
                ScissorOffsetSaveMenu = -maxOffset;
            } else {
                ScissorOffsetSaveMenu -= 22.0f;
            }
        }
    }

    // draw saves one below the other
    // for (int y = 0; y < countFolders("saves/"); y++) {
        // LoadSaveFile(FolderNames[y], Time, LoadedPlayTime);

        // float posY = y * (220 + 22) + VToScreen(0.2f); // Y offset
        // DrawRectangle(UToScreen(0.02f), posY + ScissorOffsetSaveMenu, 830, 220, GRAY); // draw background rec
        
        // const char* temp = FolderNames[y].c_str(); // convert std::string to const char *
        // TempSaveDir += FolderNames[y];
        // drawTextUV(temp, LoadAligner.x + ScreenToU(5), ScreenToV(posY + ScissorOffsetSaveMenu) + ScreenToV(5), 50, Color{210, 210, 210, 255}); // display save name
        // drawTextUV(Time, LoadAligner.x + ScreenToU(5), ScreenToV(posY + ScissorOffsetSaveMenu) + ScreenToV(60), 16, Color{165, 165, 165, 255}); // display when the save was made
        // // draw total playtime
        // drawTextUV("Playtime :", 0.024f, ScreenToV(posY + ScissorOffsetSaveMenu) + ScreenToV(80), 22, Color{180, 180, 180, 255});// Convert int to string
        // temp = CalculatePlayTime(LoadedPlayTime);
        // drawTextUV(temp, LoadAligner.x + ScreenToU(113), ScreenToV(posY + ScissorOffsetSaveMenu) + ScreenToV(80), 22, Color{180, 180, 180, 255});
    // }
    EndScissorMode();
}