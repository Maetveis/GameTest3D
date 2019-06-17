CXX := g++
CXXFLAGS := -Wall -O0 -g -std=c++17 -MMD -MP
SRCDIR := src
OBJDIR := build/obj
INCL := include
LIBDIR := lib
LDFLAGS := -g
LDLIBS := -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lassimp

MKDIR := mkdir

ifeq ($(OS),Windows_NT)
	OUT := bin/main.exe
	LDLIBS += -lmingw32 -lopengl32 -lglew32
	#LDFLAGS += -mwindows
else
	OUT := bin/main.run
    INCL :=
    LDLIBS += -lGL -lGLEW
    MKDIR += -p
endif

SRCS := DataStore/GPUAllocator.cpp \
	Game/main.cpp Game/Game.cpp Game/ScaledDeltaTimer.cpp \
	Scene/InGameScene.cpp Scene/SceneManager.cpp \
	Library/GL/UniformBinding.cpp Library/GL/Shader.cpp Library/GL/Init.cpp \
	Library/GL/ShaderStorageBinding.cpp Library/GL/Program.cpp Library/GL/Texture.cpp \
	Library/SDL/Init.cpp Library/SDL/Surface.cpp Library/SDL/Window/WindowInfo.cpp \
 	Library/SDL/Window/GLWindow.cpp \
	Library/Logger/Logger.cpp \
	Render/Material/MaterialParams.cpp Render/Model/Mesh.cpp \
	Render/Model/ModelLoader.cpp Render/Renderer/ObjectRenderer.cpp \
	Render/Scene/FrameParams.cpp Render/Scene/LightParams.cpp \
	Render/Scene/Scene.cpp

OBJNAMES := $(SRCS:.cpp=.o)
OBJS := $(addprefix $(OBJDIR)/,$(OBJNAMES))
BUILD_DIRS := $(patsubst %/,%,$(sort $(dir $(OBJS))))

all : $(OUT)

.PHONY: clean all

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp | $(BUILD_DIRS)
	$(CXX) $< -c $(CXXFLAGS) -o $@

$(OUT) : $(OBJS)
	$(CXX) $^ $(LDFLAGS) $(LDLIBS) -o $(OUT)

$(BUILD_DIRS):
	$(MKDIR) "$@"

clean :
	$(RM) "$(OUT)"
	$(RM) -r "$(OBJDIR)"

-include $(OBJS:.o=.d)
