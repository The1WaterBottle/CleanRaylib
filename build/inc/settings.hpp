// App settings
bool _MAIN_GAME_LOOP = true;
unsigned char ScreenIndex = 1;
bool isGamePaused  = false;

// Screen settings
bool ScreenResL = false, ScreenResR = false, ScreenResApply = false;
unsigned short selectedScreenRes = 5;
Vector2 screenReses[9] = { Vector2{1280, 720}, Vector2{1920, 1080}, Vector2{2560, 1440},
                           Vector2{3840, 2160}, Vector2{7680, 4320}, Vector2{1600, 900},
                           Vector2{1360, 768}, Vector2{1366, 768}, Vector2{2560, 180},};
const char* ScreenResolutions[9] = { "1280x720",  "1920x1080", "2560x1440", 
                                     "3840x2160", "7680x4320", "1600x900",
                                     "1360x768",  "1366x768",  "2560x1080"};
unsigned short TargetFPS = 60;
bool isFullscreen = false, isMSAA4X = false, isVSync = false;
bool SelectedScreenResInc = false, SelectedScreenResDec = false;

// Sound settings
bool isMusicMute = false, isSoundMute = false;
unsigned short MasterVol = 0, MusicVol = 0, SoundVol = 0;


// --- FUNCS ---
void SaveSettings() {
    // Open a file in binary write mode
    ofstream outFile("DATA/saves/settings.txt", std::ios::binary);

    if (!outFile.is_open()) {
        ConsoleErr("[ SETTINGS - ERROR ] Failed to open file for writing.");
        return;
    }

    // Save the variables to the file
    // Screen
    outFile << selectedScreenRes << endl; 
    outFile << isFullscreen << endl;
    // outFile << isVSync << endl;
    outFile << TargetFPS << endl;
    outFile << isMSAA4X << endl;
    // Sound
    outFile << MasterVol << endl;
    outFile << MusicVol  << endl;
    outFile << SoundVol  << endl;

    if (!outFile) {
        ConsoleErr("[ SETTINGS - ERROR ] writing to file.");
    } else {
        ConsoleWrite("[ SETTINGS - INFO ] Settings saved successfully.");
    }

    // Close the file
    outFile.close();
}

void LoadSettings() {
    // Open a file in binary read mode
    ifstream inFile("DATA/saves/settings.txt", std::ios::binary);

    if (!inFile.is_open()) {
        ConsoleErr("[ SETTINGS - ERROR ] Failed to open file for reading.");
    }

    // Read the variables from the file
    // Screen
    inFile >> selectedScreenRes; 
    inFile >> isFullscreen;
    // outFile >> isVSync;
    inFile >> TargetFPS;
    inFile >> isMSAA4X;
    // Sound
    inFile >> MasterVol;
    inFile >> MusicVol ;
    inFile >> SoundVol ;

    if (!inFile) {
        ConsoleErr("[ SETTINGS - ERROR ] Can't read from file.");
    } else {
        ConsoleWrite("[ SETTINGS - INFO ] Settings loaded successfully.");

        // Optionally, print the loaded settings to verify
        cout << "selectedScreenRes: " << selectedScreenRes << endl;
        cout << "isFullscreen: " << (isFullscreen ? "true" : "false") << endl;
        cout << "isMSAA4X: " << (isMSAA4X ? "true" : "false") << endl;
        // cout << "isVSync: " << (isVSync ? "true" : "false") << endl;
        cout << "TargetFPS: " << TargetFPS << endl;
        cout << "MasterVol: " << MasterVol << endl;
        cout << "MusicVol: " << MusicVol << endl;
        cout << "SoundVol: " << SoundVol << "\n" << endl;
    }

    // Close the file
    inFile.close();
}
