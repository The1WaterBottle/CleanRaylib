#include "raylib.h" // opengl header
// includes
#include <iostream>     // basic IO unctionality
#include <cstring>      // Included for strncpy
#include <ctime>        // Included for time stamps
#include <filesystem>   // Included for handling file/folder reads/writes/deletes
#include <fstream>      // Also used for files
#include <vector>       // used instead of arrays
#include <thread>       // multithreading support
#include <chrono>       // pausing multithreading for FPS lock
#include <future>       // for async multithreading
#include <mutex>        // for locking/unlocking threads access to data

// #define GLSL_VERSION 100

// debug
using std::cout;
using std::cerr;
using std::endl;
// multithreading
using std::thread;
using std::ref;
using std::mutex;
using std::unique_lock;
using std::lock_guard;
// file handling
using std::fstream;
using std::vector;
using std::string;

// Colors
#define TRANSPARENT_GRAY CLITERAL(Color){70, 70, 70, 80} // Semi-transparent gray

// Debug
template <typename _Thing>
void ConsoleWrite(_Thing log){
    // display a simple log msg
    cout << log << endl;
}
template <typename _Thing>
void ConsoleErr(_Thing err){
    // display an error log msg
    cerr << err << endl;
}

// Small tools
void DrawGrid2D(int slices = 8){
    for(short i = 0;i < slices;i++){
        for(short j = 0;j < slices;j++){
            DrawRectangleLines(128*j, 128*i, 128, 128, GRAY);
        }
    }
}

static char* GetCurrentTime(){
    // get current time 
    std::time_t currentTime = std::time(nullptr);

    // convert it to a string
    static char timeStr[20]; // Current format is max 20 characters long
    std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", std::localtime(&currentTime));

    ConsoleWrite(timeStr);

    return timeStr;
}

const char* CalcPlayTime(unsigned int seconds){
    unsigned int hours = seconds / 3600;
    unsigned int minutes = (seconds % 3600) / 60;
    unsigned int secs = seconds % 60;

    const char* formatted = TextFormat("%02d:%02d:%02d", hours, minutes, secs);
    return formatted;
}

// proram header files
#include "UV_conversion.hpp"
#include "custom_gui_uv.hpp"
#include "filesystem.hpp"
#include "recourse-manager.hpp"
#include "animation.hpp"
// additionel header files
#include "settings.hpp"
#include "loaders.hpp"
#include "debug.hpp"