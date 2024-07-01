/*
    app.hpp holds the logic for menus.hpp
*/

// Main menu
Rectangle StartAligner = { 0.02f, 0.3f, 250.0f, 80.0f };
bool StartBtn = false, SettingsBtn = false, LoadBtn = false, ExitBtn = false;

void start_game(){
    
    InitThreadByID(THREAD_GAME_CONTROLLS);
    TexMan.LoadTextures();
    ScreenIndex = 5;
}
void open_settings(){
    ScreenIndex = 2;
}
void open_load_menu(){
    ScreenIndex = 3;
}

void quick_exit(){
    _MAIN_GAME_LOOP = false;
}

// Settings menu
Rectangle SettingsAligner = { 0.01f, 0.02f, 120.0f, 50.0f };
bool Settings_BackBtn = false, applyBtn = false, SettingsFromGameBool = false, isScreenReInit = false; 
bool ScreenTab = false, SoundTab = false, AboutTab = false;

void SaveSettings(){

}
void LoadSettings(){

}

void CloseSettings(){
    if(SettingsFromGameBool){
        ScreenIndex = 99;
    } else {
        ScreenIndex = 1;
    }    
}
void ApplySettings(){
    SaveSettings();
    if(isScreenReInit){
        CloseWindow();
        InitWindow();
    }
}
void ClsBools_ScreenTab(){
    ScreenTab = true;
    SoundTab = false;
    AboutTab = false;
}
void ClsBools_SoundTab(){
    ScreenTab = false;
    SoundTab = true;
    AboutTab = false;
}
void ClsBools_AboutTab(){
    ScreenTab = false;
    SoundTab = false;
    AboutTab = true;
}

void ToggleScreenReInit(){
    isScreenReInit = true;
}

// Saving menu
char SaveName[255] = "\0";
unsigned short SaveNameLettecCount = 0;

float ScissorOffsetSaveMenu = 0.0f;
bool SaveBackBtn = false, CreateSaveBtn = false;

void CloseSavingMenu(){
    ScreenIndex = 99;
}
void CreateNewSave(){

}

// Load save menu
float ScissorOffsetLoadMenu = 0.0f;
Rectangle LoadAligner = { 0.02f, 0.02f, 130.0f, 50.0f };
bool LoadBackBtn = false, LoadSG = false, DelSG = false, LoadFromGameBool = false;

void CloseLoadingMenu(){
    if(LoadFromGameBool){
        ScreenIndex = 99;
    } else {
        ScreenIndex = 1;
    }
}
void LoadSaveGame(){

}

// Loading screen
float rot = 0.0f;

// Pause menu
Rectangle PauseAligner = { 0.02f, 0.23f, 250, 70 };
bool ResumeBtn = false, SettingsFromGameBtn = false, SaveBtn = false, LoadBtnPause = false, BackToMenuBtn = false, CompleteExitBtn = false;
bool quitNo = false;

void ResumeGame(){
    isGamePaused = false;
}
void SettingsFromGame(){
    SettingsFromGameBool = true;
    ScreenIndex = 2;
}
void SavingMenu(){
    ScreenIndex = 4;
}
void LoadFromGame(){
    LoadFromGameBool = true;
    ScreenIndex = 3;
}
void BackToMenu(){
    StopThreadByID(THREAD_GAME_CONTROLLS);
    ScreenIndex = 1;
}
void exit(){
    _MAIN_GAME_LOOP = false;
}