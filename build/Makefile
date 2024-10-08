# Specify platform
# Win/Linux/Web/All (Web needs fixing)
PLATFORM = Win# Default windows

# Config Essentials
PROJECT_NAME = Clean
VERSION_NUMBER = v0.0.1
EXTENSION = exe

# Default GLSL_VERSION based on PLATFORM
ifeq ($(PLATFORM), Win)
    GLSL_VERSION := 330
else ifeq ($(PLATFORM), Web)
    GLSL_VERSION := 100
else
    GLSL_VERSION := 330  # Default for other platforms
endif

# Conditional compilation based on PLATFORM variable
ifeq ($(PLATFORM), Linux)
    compile_cpp: compile_cpp_linux
else ifeq ($(PLATFORM), Win)
    compile_cpp: compile_cpp_windows
else ifeq ($(PLATFORM), Web)
    compile_cpp: compile_cpp_web
else ifeq ($(PLATFORM), All)
    compile_cpp: compile_cpp_linux compile_cpp_windows
else
    $(error Unsupported platform specified: $(PLATFORM))
endif

compile_cpp_linux:
	g++ ../main.cpp -o ../$(PROJECT_NAME)_$(VERSION_NUMBER) \
	-Wall -Wno-unused-function \
	-I ./inc/ -L ./lib/Linux/ -Wl,-Bstatic -lraylib -Wl,-Bdynamic -lX11 -lGL -lm -lpthread -lrt -lXrandr -lasound -std=c++17 \
    -DGLSL_VERSION=$(GLSL_VERSION) \
	&& echo ------------------------------------------------------------------------- \
	&& echo Compiled projcet for Linux successfully \

# && ./$(PROJECT_NAME)_$(VERSION_NUMBER)

compile_cpp_windows:
	g++ ../main.cpp -o ../$(PROJECT_NAME)_$(VERSION_NUMBER).$(EXTENSION) \
	-Wall \
	-I ./inc/ -L ./lib/Win -Wl,-Bstatic -lraylib -lopengl32 -lglfw3 -lgdi32 -lwinmm -std=c++17 \
	-Wno-unused-function \
	-DGLSL_VERSION=$(GLSL_VERSION) \
	&& echo ------------------------------------------------------------------------- \
	&& echo Compiled projcet for Windows successfully \

compile_cpp_web:
	emcc ../main.cpp -o ./web/$(PROJECT_NAME)_$(VERSION_NUMBER).html \
	-Wall -Wno-unused-function \
	-I ./inc/ -L ./lib/Web/ \
    -DGLSL_VERSION=$(GLSL_VERSION) \
	-D_DEFAULT_SOURCE -Wno-missing-braces -Wunused-result -Os -I. \
	-I C:/raylib/src -I C:/raylib/src/external -L. \
	-L C:/raylib/src -s USE_GLFW=3 -s ASYNCIFY \
	-s TOTAL_MEMORY=67108864 \
	-s FORCE_FILESYSTEM=1 --preload-file ../DATA/textures \
	--shell-file C:/raylib/src/shell.html \
	C:/raylib/src/web/libraylib.a -DPLATFORM_WEB \
	-s EXPORTED_FUNCTIONS=["_free","_malloc","_main"] -s EXPORTED_RUNTIME_METHODS=ccall \
	&& echo ------------------------------------------------------------------------- \
	&& echo Compiled projcet for Web successfully \

compile_cpp_andoid:
	ANDROID_ARCH           ?= ARM
	ANDROID_API_VERSION     = 28

	JAVA_HOME              ?= C:/open-jdk
	ANDROID_HOME           ?= C:/android-sdk
	ANDROID_NDK            ?= C:/android-ndk
	ANDROID_TOOLCHAIN      ?= $(ANDROID_NDK)/toolchains/llvm/prebuilt/windows-x86_64
	ANDROID_BUILD_TOOLS    ?= $(ANDROID_HOME)/build-tools/29.0.3
	ANDROID_PLATFORM_TOOLS  = $(ANDROID_HOME)/platform-tools

