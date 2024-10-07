void drawLoadingScreen(){
    DrawTexturePro(TexMan.Textures[TEXTURE_LOADING], Rectangle{0, 0, 256, 256},
                    Rectangle{GetScreenW()/2, GetScreenH()/2, 256, 256},
                    Vector2{  128, 128}, rot, RAYWHITE);
    rot += 10.0f;
    drawTextUV("Loading...", ScreenToU(GetScreenW()/2-MeasureText("Loading...", 90)/2), ScreenToV(GetScreenH()/1.32), 90, Color{0, 0, 0, 255}); 

    if(TexMan.LoadedImages){
        TexMan.convertImgToTex();
    }
    if(TexMan.LoadedTextures){
        ScreenIndex = 99;
    }
}

Texture2D _background;
void renderPauseMenu(){
    if(isGamePaused) {
        if(IsKeyPressed(KEY_ESCAPE)){
            isGamePaused = false;
        }
    }
    // draw blurry background    
    BeginShaderMode(ShaderMan.Shaders[SHADER_BLUR]);
        DrawTexture(_background, 0, 0, RAYWHITE);
    EndShaderMode();

    DrawRectangle(0, 0, GetScreenW(), GetScreenH(), TRANSPARENT_GRAY); // Transparent gray background
    drawTextUV("Paused", 0.01f, 0.01f, 60);

    ResumeBtn = drawButtonUV(ResumeBtn, "Resume", 44, Rectangle{ 0.02f, 0.23f, 250, 70 }, &ResumeGame);
    SettingsFromGameBtn = drawButtonUV(SettingsFromGameBtn, "Settings", 40, Rectangle{ PauseAligner.x, PauseAligner.y + ScreenToV(85), PauseAligner.width, PauseAligner.height }, &SettingsFromGame);
    SaveBtn = drawButtonUV(SaveBtn, "Save", 44, Rectangle{ PauseAligner.x, PauseAligner.y + ScreenToV(170), PauseAligner.width, PauseAligner.height }, &SavingMenu);
    LoadBtnPause = drawButtonUV(LoadBtnPause, "Load", 44, Rectangle{ PauseAligner.x, PauseAligner.y + ScreenToV(255), PauseAligner.width, PauseAligner.height }, &LoadFromGame);
    BackToMenuBtn = drawButtonUV(BackToMenuBtn, "Main menu", 44, Rectangle{ PauseAligner.x, PauseAligner.y + ScreenToV(340), PauseAligner.width, PauseAligner.height }, &BackToMenu);
    CompleteExitBtn = drawToggleUV(CompleteExitBtn, "Quit Game", 44, Rectangle{ PauseAligner.x, PauseAligner.y + ScreenToV(425), PauseAligner.width, PauseAligner.height }, &exit);
    if(quitNo){
        quitNo = false;
        CompleteExitBtn = false;
    } 
}

void renderMainGame(Camera2D Cam = {0}){
    //* Begin rendering    
    // BeginMode2D(Cam); // stuff inside BeginMode2D() will move (world, enemies, ...)


    // EndMode2D(); // stuff outside BeginMode2D() will stay in place (UI, ...)
}
