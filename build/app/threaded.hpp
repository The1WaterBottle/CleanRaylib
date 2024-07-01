typedef enum {
    THREAD_GAME_TIMER = 0,
    THREAD_GAME_CONTROLLS
} ThreadIDs;

// Threaded functions go here...
bool _Thread_GameClock = true;
thread _T1_GameClock; 
void GameClock(unsigned int &AppTimer, unsigned int &LoadingTimer, unsigned int &PlayTime) {
    ConsoleWrite("[ THREAD - INFO ] Thread 1 initialized\n");
    while (_Thread_GameClock) {
        // Program timer
        AppTimer++;

        // Loading screen timer
        if(ScreenIndex == 5){
            LoadingTimer++;
        }

        // Game timer
        if(ScreenIndex == 99 && !isGamePaused){
            PlayTime++;
        }

        //* limit code execution to 1 Second
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

bool _Thread_GameControlls = true;
thread _T2_GameControlls; 
void GameControlls(){
    ConsoleWrite("[ THREAD - INFO ] Thread 2 initialized\n");
    while (_Thread_GameControlls) {
        if(IsKeyPressed(KEY_ESCAPE)) isGamePaused = !isGamePaused;

        if(!isGamePaused)
        {

        }

        std::this_thread::sleep_for(std::chrono::microseconds(16666));
    }
}


// Thread logic
void InitThreadByID(int ID){
    switch (ID){
    case 0:
        _T1_GameClock = thread(GameClock, ref(GameTimer), ref(LoadTimer), ref(PlayTime));
        break;
    case 1:
        _T2_GameControlls = thread(GameControlls);
        break;
    
    default:
        ConsoleWrite(TextFormat("[ WARNING ] No Thread with ID : %i", ID));
        break;
    }
    ConsoleWrite(TextFormat("[ FINISHED ] Successfully started Thread with ID : %i", ID));
}

void StopThreadByID(int ID){
    switch (ID){
    case 0:
        _Thread_GameClock = false;
        _T1_GameClock.join();
        _Thread_GameClock = true;
        break;
    case 1:
        _Thread_GameControlls = false;
        _T2_GameControlls.join();
        _Thread_GameControlls = true;
        break;
    
    default:
        ConsoleWrite("[ WARNINIG ] No Thread with that ID");
        break;
    }
    ConsoleWrite(TextFormat("[ FINISHED ] Successfully stopped Thread ID : %i", ID));
}
void StopThreads(){
    _Thread_GameClock = false;
    _T1_GameClock.join();
    _Thread_GameControlls = false;
    _T2_GameControlls.join();
    ConsoleWrite("[ FINISHED ] 2 Threads stopped");
}