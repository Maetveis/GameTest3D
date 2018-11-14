CXX := g++
CXXFLAGS := -Wall -O3 -g -std=c++17 -MMD -MP
SRCDIR := src
OBJDIR := build/obj
INCL := include
LIBDIR := lib
LDFLAGS := -g
LDLIBS := -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lassimp

RM := rm
RMDIR := rm -r
MKDIR := mkdir

ifeq ($(OS),Windows_NT)
	OUT := bin/main.exe
	LDLIBS += -lmingw32 -lopengl32 -lglew32
	#LDFLAGS += -mwindows
else
#$(CXX) $< -c $(CXXFLAGS) -I$(INCL) -o $@
#$(CXX) $^ $(LDFLAGS) -L$(LIBDIR) $(LDLIBS) -o $(OUT)
	OUT := bin/main.run
    INCL :=
    LDLIBS += -lGL -lGLEW
    MKDIR += -p
endif

#Render/RenderManager.cpp

SRCS := Main/main.cpp Main/Game.cpp Main/ScaledDeltaTimer.cpp \
	Scene/InGameScene.cpp \
	Model/Mesh3D.cpp Model/WindowInfo.cpp Model/FrameParams.cpp Model/LightParams.cpp Model/MaterialParams.cpp \
	Init/SDLInit.cpp Init/GlewInit.cpp \
	Manager/WindowManager.cpp Manager/SceneManager.cpp Manager/ModelManager.cpp \
	Helper/ShaderProgram.cpp Helper/UniformBuffer.cpp \
	Program/Mesh3DColor.cpp

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
	-$(RM) "$(OUT)"
	-$(RMDIR) "$(OBJDIR)"

-include $(OBJS:.o=.d)
