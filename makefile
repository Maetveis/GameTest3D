CXX := clang++
CXXFLAGS := -Wall -O0 -g -std=c++17 -MMD -MP
SRCDIR := src
OBJDIR := build/obj
INCL := src
LIBDIR := lib
LDFLAGS := -g
LDLIBS := -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lassimp

MKDIR := mkdir

ifeq ($(OS),Windows_NT)
	CXX := g++
	OUT := bin/main.exe
	LDLIBS += -lmingw32 -lopengl32 -lglew32
	INCL += include
	#LDFLAGS += -mwindows
else
	OUT := bin/main.run
    LDLIBS += -lGL -lGLEW
    MKDIR += -p
endif

INCL_CMDS := $(addprefix -I,$(INCL))

-include src/sources.mk

OBJNAMES := $(SRCS:.cpp=.o)
OBJS := $(addprefix $(OBJDIR)/,$(OBJNAMES))
BUILD_DIRS := $(patsubst %/,%,$(sort $(dir $(OBJS))))

all : $(OUT)

.PHONY: clean all

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp | $(BUILD_DIRS)
	$(CXX) $< -c $(CXXFLAGS) $(INCL_CMDS) -o $@

$(OUT) : $(OBJS)
	$(CXX) $^ $(LDFLAGS) $(LDLIBS) -o $(OUT)

$(BUILD_DIRS):
	$(MKDIR) "$@"

clean :
	$(RM) "$(OUT)"
	$(RM) -r "$(OBJDIR)"

-include $(OBJS:.o=.d)
