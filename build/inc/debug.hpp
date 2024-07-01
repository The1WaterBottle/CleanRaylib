// debug settings
bool isDebugMode = false, isConsoleEnabled = false;

void drawConsole(){
    DrawRectangle(GetScreenW()/2-10, 10, GetScreenW()/2, 525, TRANSPARENT_GRAY);
    DrawRectangle(GetScreenW()/2-10, 10, GetScreenW()/2, 50, TRANSPARENT_GRAY);
    DrawText("CONSOLE", GetScreenW()/2+5, 15, 45, DARKGRAY);
}
void handleConsole(){
    if(IsKeyPressed(KEY_F1)) isConsoleEnabled = !isConsoleEnabled;
}

// --- DEBUG STUFF ---
void _debug_mode(){
    if(IsKeyPressed(KEY_F1)) isConsoleEnabled = !isConsoleEnabled;
    
    if(isDebugMode){
        if(IsKeyDown(KEY_F5)){
            TargetFPS++;
            SetTargetFPS(TargetFPS);
        }
        if(IsKeyDown(KEY_F6)){
            TargetFPS--;
            SetTargetFPS(TargetFPS);
        }
        if(IsKeyPressed(KEY_F7)){
            TargetFPS = 60;
            SetTargetFPS(TargetFPS);
        }
    }
}