// Textures
typedef enum {
    TEXTURE_LOADING = 0,
    TEXTURE_FALLBACK
} TextureIndexes;

class TextureManager{
    public:
        vector<Texture2D> Textures;  // Vector to store all textures
        bool LoadedTextures = false, LoadedImages = false; // To check if loading threads are finished

        void LoadTextures(){
            ConsoleWrite("[ RUNNING ] Loading all textures...");
            // Loading loading icon
            Image LoadingImage = LoadImage("DATA/textures/misc/_loading.png");
            ImageResize(&LoadingImage, 256, 256);
            Texture2D LoadingTex = LoadTextureFromImage(LoadingImage);
            UnloadImage(LoadingImage);
            Textures.push_back(LoadingTex);

            // start image loading thread
            load_imgs = thread(&TextureManager::LoadImages, this);
            load_imgs.detach(); // detach so main thread still runs
        }

        void convertImgToTex(){
            for(Image Img : Images){
                Textures.push_back(LoadTextureFromImage(Img));
            }
            LoadedTextures = true;
            // Unload after conversion
            load_imgs = thread(&TextureManager::UnloadImages, this);
            load_imgs.detach(); // detach so main thread still runs

            ConsoleWrite("[ TEXMAN - FINISHED ] Converted all images to textures");
        }

        // Unloading functions
        void UnloadImages(){
            for(Image Img : Images){
                UnloadImage(Img);
            }
            LoadedImages = false;
            ConsoleWrite("[ TEXMAN - FINISHED ] Unloaded all images\n");
        }
        void UnloadTextures(){
            for(Texture2D Tex : Textures){
                UnloadTexture(Tex);
            }
            LoadedTextures = false;
            ConsoleWrite("[ TEXMAN - FINISHED ] Unloaded all textures\n");
        }

    private:
        vector<Image> Images; // Vector to store all images
        thread load_texs, load_imgs; // loading/unloading threads

        void PushImg(const char* path, int width, int height) {
            Image textureImage = LoadImage(path);       // Load image from path
            ImageResize(&textureImage, width, height);  // Resize image with given params
            Images.push_back(textureImage);             // Append tex to Images vector
        }        

        void LoadImages(){
            ConsoleWrite("[ TEXMAN - RUNNING ] Loading images...");
            // --- Load textures here : ---
            PushImg("DATA/textures/misc/_fallback.png", 256, 256);

            // write success to console
            ConsoleWrite("[ TEXMAN - FINISHED ] Loaded all images\n");
            LoadedImages = true;
        }
};TextureManager TexMan;

// Shaders
typedef enum {
    SHADER_BLUR = 0,
    SHADER_PIXELIZER
} ShaderIndexes;

class ShaderManager{
    public:
        vector<Shader> Shaders;  // Vector to store all models
        bool LoadedShaders = false;

        void LoadShaders(){
            ConsoleWrite("[ RUNNING ] Loading all shaders...");
            // start shader loading
            // first is Vertex seconds is Fragment shaders
            // Shaders.push_back(LoadShader(0, TextFormat("DATA/shaders/glsl%i/blur.fs", GLSL_VERSION))); // example
            Shaders.push_back(LoadShader(0, TextFormat("DATA/shaders/glsl%i/blur.fs", GLSL_VERSION)));
            Shaders.push_back(LoadShader(0, TextFormat("DATA/shaders/glsl%i/pixelizer.fs", GLSL_VERSION)));

            LoadedShaders = true;
        }

        void UnloadShaders(){
            ConsoleWrite("[ RUNNING ] Unloading all shaders...");
            // start shader unloading thread
            load_shaders = thread(&ShaderManager::unload_shaders_via_thread, this);
            load_shaders.detach(); // detach so main thread still runs
        }

    private:
        thread load_shaders;

        void unload_shaders_via_thread(){
            for(Shader shdr : Shaders){
                UnloadShader(shdr);
            }
            LoadedShaders = false;
        }
};ShaderManager ShaderMan;
