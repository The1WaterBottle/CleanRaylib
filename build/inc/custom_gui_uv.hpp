/* Description :
    Custom GUI with raylib because raygui breaks on window reload.

    This uses UV coordinates therefor is/can be responsive.
*/

// NullFunc() is here incase you don't want to run a function when drawing a button, usefull for testing
void NullFunc(){}

// custom Vector for 2 colors
typedef struct ColorPair{
    Color Color_One;
    Color Color_Two;
}ColorPair;
// 3 Vec2s for easier triangle drawing
typedef struct Vector2By3{
    Vector2 Vec1, Vec2, Vec3;
}Vector2By3;

// colors for UI
#define ColLightGray CLITERAL(Color){ 195, 195, 195, 255 }  // Light Gray
#define ColDarkGray CLITERAL(Color){ 145, 145, 145, 255 }   // Dark Gray
#define ColLightBlue CLITERAL(Color){ 190, 245, 255, 255 }  // Light Blue
#define ColDarkBlue CLITERAL(Color){ 92, 172, 246, 255 }    // Dark Blue
// other :
#define MAX_INPUT_CHARS 2047

//|-----------------------------------------------------------------------------------------------------------------|
//|                                                basic shapes with UVs                                            |
//|-----------------------------------------------------------------------------------------------------------------|

// normalised (0-1) UV coords to drawn Rectangle
void drawRecWithUV(float x, float y, unsigned int width, unsigned int height, Color Col){
    DrawRectangleRec(RecWithUV(x, y,static_cast<float>(width), static_cast<float>(height)), Col);
}
// normalised (0-1) UV coords to drawn Rectangle (with responsive width and height)
void drawResponsiveRecWithUV(float x, float y, float width, float height, Color Col){
    DrawRectangleRec(ResponsiveRecWithUV(x, y, width, height), Col);
}
// normalised (0-1) UV coords to drawn Rectangle lines
void drawRecLinesWithUV(Rectangle LinesRec, Color Col){
    DrawRectangleLines(UToScreen(LinesRec.x), VToScreen(LinesRec.y), UToScreen(LinesRec.width), VToScreen(LinesRec.height), Col);
}

// normalised (0-1) UV coords to drawn triangle
void drawTriangleWithUV(Vector2By3 Vec2By3 = {Vector2{0, 0}, Vector2{0.01f, 0}, Vector2{0.005f, 0.01f}}, Color Col = DARKGRAY){
    DrawTriangle(UVToScreen(Vec2By3.Vec1.x, Vec2By3.Vec1.y), UVToScreen(Vec2By3.Vec2.x, Vec2By3.Vec2.y), UVToScreen(Vec2By3.Vec3.x, Vec2By3.Vec3.y), Col);
}

//|-----------------------------------------------------------------------------------------------------------------|
//|                                                    GUI with UVs                                                 |
//|-----------------------------------------------------------------------------------------------------------------|
// --- Logic --- :

// check if mouse is over button and change the cursor accordingly
void changeMouseCursor(float x, float  y, float  width, float  height){
    CheckCollisionPointRec(GetMousePosition(), RecWithUV(x, y, width, height)) ? SetMouseCursor(MOUSE_CURSOR_POINTING_HAND) : SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}
ColorPair changeColors(float x, float  y, float  width, float  height){
    if(CheckCollisionPointRec(GetMousePosition(), RecWithUV(x, y, width, height))){
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        return ColorPair { ColLightBlue, ColDarkBlue };
    } else {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        return ColorPair { ColLightGray, ColDarkGray };
    }
}

// --- Drawing --- :

// UV Text : Normalised (0-1) UVs to draw a Text
// Has defaults so it can be called without parameters
void drawTextUV(const char* Text, float x, float y, int fontSize, Color Col = ColDarkGray){
    DrawText(Text, UToScreen(x), VToScreen(y), fontSize, Col);
}

void drawTextureUV(Texture2D Tex, float x, float y){
    DrawTexture(Tex, UToScreen(x), VToScreen(y), RAYWHITE);
}
void drawTextureProUV(Texture2D Tex, Rectangle source = {0, 0, 256, 256}, Rectangle dest = {0, 0, 256, 256}, Vector2 origin = {128, 128}, float rot = 0.0f){
    DrawTexturePro(Tex, Rectangle{source.x, source.y, source.width, source.height}, Rectangle{UToScreen(dest.x), VToScreen(dest.y), dest.width, dest.height}, origin, rot, RAYWHITE);
}

// Toggleable button : Normalised (0-1) UVs to draw a toggle button 
// Has defaults so it can be called without parameters
bool drawToggleUV(bool &Boolean, const char* Txt = "Toggle", int FontSize = 40, Rectangle StandartRect = {0.01f, 0.01f, 240, 80}, void (*loopFunc)() = &NullFunc, void (*clickFunc)() = &NullFunc){
    // create a temp rec with all UV coords
    Rectangle RecUVs = { StandartRect.x, StandartRect.y, ScreenToU(StandartRect.width), ScreenToV(StandartRect.height) };

    changeMouseCursor(StandartRect.x, StandartRect.y, StandartRect.width, StandartRect.height);
    ColorPair CPair = changeColors(StandartRect.x, StandartRect.y, StandartRect.width, StandartRect.height);

    // draw btn components
    if(Boolean){
        drawRecWithUV(StandartRect.x, StandartRect.y, StandartRect.width, StandartRect.height, ColDarkBlue);
        drawResponsiveRecWithUV(RecUVs.x + ScreenToU(2), RecUVs.y + ScreenToV(2), RecUVs.width-StandartRect.x - ScreenToU(6), RecUVs.height-StandartRect.y-ScreenToV(6), ColLightBlue); 
        DrawText(Txt, UToScreen(StandartRect.x + ScreenToU(8)), VToScreen(StandartRect.y + ScreenToV(8)), FontSize, ColDarkBlue);
        loopFunc();
    } else {
        drawRecWithUV(StandartRect.x, StandartRect.y, StandartRect.width, StandartRect.height, CPair.Color_Two);
        drawResponsiveRecWithUV(RecUVs.x + ScreenToU(2), RecUVs.y + ScreenToV(2), RecUVs.width-StandartRect.x - ScreenToU(6), RecUVs.height-StandartRect.y-ScreenToV(6), CPair.Color_One); 
        DrawText(Txt, UToScreen(StandartRect.x + ScreenToU(8)), VToScreen(StandartRect.y + ScreenToV(8)), FontSize, CPair.Color_Two);
    }

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        if(CheckCollisionPointRec(GetMousePosition(), RecWithUV(StandartRect.x, StandartRect.y, StandartRect.width, StandartRect.height))){
            clickFunc();
            return !Boolean;
        }
    }
    return Boolean;
}

// Standart Button : Normalised (0-1) UVs to draw a button
// Has defaults so it can be called without parameters
bool drawButtonUV(bool Boolean = false, const char* Txt = "Button", int FontSize = 40, Rectangle StandartRect = {0.01f, 0.01f, 240, 80}, void (*clickFunc)() = &NullFunc, Font font = GetFontDefault()){
    // create a temp rec with all UV coords
    Rectangle RecUVs = { StandartRect.x, StandartRect.y, ScreenToU(StandartRect.width), ScreenToV(StandartRect.height) };

    changeMouseCursor(StandartRect.x, StandartRect.y, StandartRect.width, StandartRect.height);
    ColorPair CPair = changeColors(StandartRect.x, StandartRect.y, StandartRect.width, StandartRect.height);
    
    if(Boolean){ // draw btn components
        drawRecWithUV(StandartRect.x, StandartRect.y, StandartRect.width, StandartRect.height, ColDarkBlue);
        drawResponsiveRecWithUV(RecUVs.x + ScreenToU(2), RecUVs.y + ScreenToV(2), RecUVs.width-StandartRect.x - ScreenToU(6), RecUVs.height-StandartRect.y-ScreenToV(6), ColLightBlue); 
        // DrawText(Txt, UToScreen(StandartRect.x + ScreenToU(8)), VToScreen(StandartRect.y + ScreenToV(8)), FontSize, ColDarkBlue);
        DrawTextEx(font, Txt, Vector2{UToScreen(StandartRect.x + ScreenToU(8)), VToScreen(StandartRect.y + ScreenToV(8))}, FontSize, 1.0f, ColDarkBlue);
        Boolean = !Boolean;
    } else {
        drawRecWithUV(StandartRect.x, StandartRect.y, StandartRect.width, StandartRect.height, CPair.Color_Two);
        drawResponsiveRecWithUV(RecUVs.x + ScreenToU(2), RecUVs.y + ScreenToV(2), RecUVs.width-StandartRect.x - ScreenToU(6), RecUVs.height-StandartRect.y-ScreenToV(6), CPair.Color_One); 
        // DrawText(Txt, UToScreen(StandartRect.x + ScreenToU(8)), VToScreen(StandartRect.y + ScreenToV(8)), FontSize, CPair.Color_Two);
        DrawTextEx(font, Txt, Vector2{UToScreen(StandartRect.x + ScreenToU(8)), VToScreen(StandartRect.y + ScreenToV(8))}, FontSize, 1.0f, CPair.Color_Two);
    }

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        if(CheckCollisionPointRec(GetMousePosition(), RecWithUV(StandartRect.x, StandartRect.y, StandartRect.width, StandartRect.height))){
            clickFunc();
            return !Boolean;
        }
    }
    return Boolean;
}

// Input box : Normalised (0-1) UVs to draw an input box
// Has defaults so it can be called without parameters BUT Text[] 
// should be given a new array, if not then it will overwrite it self
void drawInputBoxUV(unsigned short &letterCount, char *Text = nullptr, int font_size = 52, Rectangle InputRec = {0.01f, 0.01f, 280, 60}, Color TxtColor = ColDarkGray){ 
    // --- Logic : ---
    bool mouseOnTxt = CheckCollisionPointRec(GetMousePosition(), Rectangle{UToScreen(InputRec.x), VToScreen(InputRec.y), InputRec.width, InputRec.height}) ? true : false;
    float TxtOffset = 0;
    unsigned short framesCounter = 0;

    if(mouseOnTxt){
        SetMouseCursor(MOUSE_CURSOR_IBEAM); // Set the window's cursor to the I-Beam
        
        int key = GetCharPressed(); // Get char pressed (unicode character) on the queue
        if(key > 0){ // Check if more characters have been pressed on the same frame
            Text[letterCount] = (char)key;
            Text[letterCount+1] = '\0'; // Add null terminator at the end of the string.
            letterCount++;

            key = GetCharPressed(); // Check next character in the queue
        }

        if (IsKeyPressed(KEY_BACKSPACE)){
            if (letterCount < 0){ 
                letterCount = 0;
                Text[letterCount] = '\0';
            } else {
                letterCount--;
                Text[letterCount] = (char)key;
                Text[letterCount+1] = '\0';
            }
        }
    } else { SetMouseCursor(MOUSE_CURSOR_DEFAULT); }

    // scroll letters if out of bounds
    if(MeasureText(Text, font_size) > InputRec.width-30) TxtOffset = (MeasureText(Text, font_size) - InputRec.width) + 15;
    

    // --- Drawing : ---
    Rectangle RecUVs = { InputRec.x, InputRec.y, ScreenToU(InputRec.width), ScreenToV(InputRec.height) }; // temp Rec with ALL UV coords

    drawRecWithUV(InputRec.x, InputRec.y, InputRec.width, InputRec.height, GRAY); // background rec

    BeginScissorMode(UToScreen(InputRec.x) + 2, VToScreen(InputRec.y) + 2, InputRec.width, InputRec.height); // cut off letters after rec
    
    drawResponsiveRecWithUV(RecUVs.x + ScreenToU(2), RecUVs.y + ScreenToV(2), RecUVs.width-InputRec.x-ScreenToU(6), RecUVs.height-InputRec.y-ScreenToV(6), LIGHTGRAY);
    drawTextUV(Text, RecUVs.x + ScreenToU(5) - ScreenToU(TxtOffset), RecUVs.y + ScreenToV(3), font_size, TxtColor);
    
    // blinking underline
    mouseOnTxt ? framesCounter++ : framesCounter = 0;
    if(mouseOnTxt && letterCount < MAX_INPUT_CHARS){
        if (((framesCounter / 20) % 2) == 0) DrawText("_", (int)InputRec.x + 8 + MeasureText(Text, font_size), ScreenToU(InputRec.y) + ScreenToV(12), 40, TxtColor);
    }
    
    EndScissorMode();
}

// Confirmation box : Normalised (0-1) UVs to draw a confirmation box with yes and no buttons
bool YesBtn = false, NoBtn = false;
short drawConfirmationBox(const char* Txt, int fontSize, Rectangle ConfBoxRec = { 0, 0, 500, 350}, Color TxtColor = ColDarkGray){
    drawRecWithUV(ConfBoxRec.x, ConfBoxRec.y, ConfBoxRec.width, ConfBoxRec.height, GRAY); // background rec
    drawResponsiveRecWithUV(ConfBoxRec.x + ScreenToU(4), ConfBoxRec.y + ScreenToV(4), ScreenToU(ConfBoxRec.width-12)-ConfBoxRec.x, ScreenToV(ConfBoxRec.height-12)-ConfBoxRec.y, LIGHTGRAY); 
    drawTextUV(Txt, ConfBoxRec.x + ScreenToU(ConfBoxRec.width)/2 - ScreenToU(MeasureText(Txt, fontSize)/2), ConfBoxRec.y + ScreenToV(50), fontSize, TxtColor);
    YesBtn = drawButtonUV(YesBtn, "Yes", 42, Rectangle{ConfBoxRec.x+ScreenToU(50), ConfBoxRec.y+ScreenToV(240), 140, 60});
    NoBtn  = drawButtonUV(NoBtn , "No" , 42, Rectangle{ConfBoxRec.x+ScreenToU(300), ConfBoxRec.y+ScreenToV(240), 140, 60});
    if(YesBtn) return 1;
    else if(NoBtn) return 2;
    else return 0;
}

// Dialogue box : Normalised (0-1) UVs to draw a dialogue box with the charackters image, text and name
Texture2D fallbackTexture = LoadTexture("textures/misc/fallbackTexture.jpg");
void drawDialogueBox(const char* Txt = "Placeholder", int fontSize = 40, Texture2D Tex = fallbackTexture, bool isTexRight = false, Rectangle DialogueBoxRec = { ScreenToU(GetScreenW()/2-525), ScreenToV(GetScreenH()-150), 1050, 140}, Color TxtColor = ColDarkGray){
    if(isTexRight){ // draw portrait texture on the right or the left
        drawTextureUV(Tex, DialogueBoxRec.x+ScreenToU(DialogueBoxRec.width-261), DialogueBoxRec.y-ScreenToV(224)); // draw texture first so it appears in the back
    } else {
        drawTextureUV(Tex, DialogueBoxRec.x+ScreenToU(5), DialogueBoxRec.y-ScreenToV(224)); // draw texture first so it appears in the back
    }

    // draw pieces of the dialogue box
    drawRecWithUV(DialogueBoxRec.x, DialogueBoxRec.y, DialogueBoxRec.width, DialogueBoxRec.height, GRAY); // background rec
    drawResponsiveRecWithUV(DialogueBoxRec.x + ScreenToU(4), DialogueBoxRec.y + ScreenToV(4), ScreenToU(DialogueBoxRec.width-12)-DialogueBoxRec.x, ScreenToV(DialogueBoxRec.height-12)-DialogueBoxRec.y, LIGHTGRAY); 

    drawTextUV(Txt, DialogueBoxRec.x+ScreenToU(15), DialogueBoxRec.y+ScreenToV(15), 45);

    // draw a little triangle int the bottom right when the text finished appearing
    bool isReadyForNextLine = true;
    if(isReadyForNextLine){
        drawTriangleWithUV(Vector2By3{{ScreenToU(DialogueBoxRec.width+80),    ScreenToV(GetScreenH()-6 +5)},
                                      {ScreenToU(DialogueBoxRec.width+80+20), ScreenToV(GetScreenH()-12-9)},
                                      {ScreenToU(DialogueBoxRec.width+80-20), ScreenToV(GetScreenH()-12-9)}}, DARKGRAY);
    }
}
