void InitWindow(){ // Create window
    LoadSettings();
    ConsoleWrite("[ RUNNING ] Initializing Window...");
    if(isMSAA4X) SetConfigFlags(FLAG_MSAA_4X_HINT);
    if(isVSync) SetConfigFlags(FLAG_VSYNC_HINT);
    if(isFullscreen){
        InitWindow(1280, 720, "Game - v0.0.1");
        ToggleFullscreen();
    } else {
        // SetConfigFlags(FLAG_WINDOW_RESIZABLE);
        InitWindow(screenReses[selectedScreenRes].x, screenReses[selectedScreenRes].y, "Game - v0.0.1");
        SetWindowMinSize(1024, 768);
    }
    SetWindowTitle("Game - v0.0.1");
    SetWindowIcon(LoadImage("DATA/textures/misc/Logo.png")); // Load game icon
    SetExitKey(KEY_DELETE); // press DELETE if game crashes
    SetTargetFPS(TargetFPS);
    // store screen width and height into variables for UV_conversion.hpp
    ScreenWidth = GetScreenW();
    ScreenHeight = GetScreenH();
    ConsoleWrite("[ FINISHED ] Initialized Window\n");
}

void InitAudio(){ // Create audio components
    ConsoleWrite("[ RUNNING ] Initializing Audio...");
	InitAudioDevice();
    SetMasterVolume(MasterVol);
    Music MainMusic = LoadMusicStream("DATA/sounds/music/");
    Sound MainSound = LoadSound("DATA/sounds/sound/");
    SetMusicVolume(MainMusic, MusicVol);
    SetSoundVolume(MainSound, SoundVol);
    ConsoleWrite("[ FINISHED ] Initialized Audio\n");
}

Camera2D InitCamera2D(){
    ConsoleWrite("[ RUNNING ] Initializing Camera 2D");
    Camera2D camera = { 0 };
    camera.rotation = 0.0f;
    camera.target = Vector2{0,0};
    camera.offset = Vector2{ GetScreenW()/2, GetScreenH()/2 };
    camera.zoom = 1.0f;
    ConsoleWrite("[ FINISHED ] Initialized Camera 2D\n");
    return camera;
}

Camera3D InitCamera3D(){
    ConsoleWrite("[ RUNNING ] Initializing Camera 3D");
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 4.0f, 2.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };   // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };       // Camera up vector (rotation towards target)
    camera.fovy = 60.0f;                             // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;          // Camera projection type
    ConsoleWrite("[ FINISHED ] Initialized Camera 3D\n");
    return camera;
    // Don't forget : UpdateCamera(&camera, CAMERA_...);
}