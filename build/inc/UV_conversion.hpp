// #include "custom.h"
// #include "raylib.h" // uncomment if there are include errors

float ScreenHeight, ScreenWidth;
// Temp variables :
float ScreenX,ScreenY;  // create temp ScreenX, ScreenY variables
float u,v;              // create temp u, v variables

// float screen width/height
float GetScreenW(){ return float(GetScreenWidth()); }
float GetScreenH(){ return float(GetScreenHeight()); }

// --- single var conversion --- :
// convert screen coord x to U coordinate and back
float ScreenToU(int ScreenX) {
    float u = static_cast<float>(ScreenX) / static_cast<float>(ScreenWidth);
    return u;
}
float UToScreen(float u) {
    float ScreenX = static_cast<int>(u * ScreenWidth);
    return ScreenX;
}
// convert screen coord y to V coordinate and back
float ScreenToV(int ScreenY) {
    float v = static_cast<float>(ScreenY) / static_cast<float>(ScreenHeight);
    return v;
}
float VToScreen(float v) {
    float ScreenY = static_cast<int>(v * ScreenHeight);
    return ScreenY;
}
// float screen U/V
float GetScreenU(){ return ScreenToU(GetScreenW()); }
float GetScreenV(){ return ScreenToV(GetScreenH()); }
// --- vector conversion --- :
// convert Vector2 (ScreenX, ScreenY) to Vector2 (U, V) and back
Vector2 ScreenToUV(int ScreenX, int ScreenY, int screenWidth = ScreenWidth, int screenHeight = ScreenHeight) {
    Vector2 UVs = { u, v };
    UVs.x = static_cast<float>(ScreenX) / static_cast<float>(screenWidth);
    UVs.y = static_cast<float>(ScreenY) / static_cast<float>(screenHeight);
    return UVs;
}
Vector2 UVToScreen(float u, float v, int screenWidth = ScreenWidth, int screenHeight = ScreenHeight) {
    Vector2 ScreenCoords = { ScreenX, ScreenY };
    ScreenCoords.x = static_cast<int>(u * screenWidth);
    ScreenCoords.y = static_cast<int>(v * screenHeight);
    return ScreenCoords;
}

// responsively positioned Rectangle x,y coords from UV coords
Rectangle RecWithUV(float u, float v, float width, float height) {
    float x, y; // recs x, y

    // Calculate screen coordinates from UV coordinates
    x = UToScreen(u);
    y = VToScreen(v);

    return Rectangle{ x, y, static_cast<float>(width), static_cast<float>(height) };
}
// responsively positioned and sized Rectangle x,y,width,height coords from UV coords
Rectangle ResponsiveRecWithUV(float u, float v, float width, float height) {
    float x, y , w, h; // recs x, y, width and height

    // Calculate screen coordinates from UV coordinates
    x = UToScreen(u);
    y = VToScreen(v);
    w = UToScreen(u + width);
    h = VToScreen(v + height);

    return Rectangle{ x, y, w, h };
} 