#----------------------------------
# Name:				makefile
# Author:			Fabian Dubacher, based on the excellent template from Renaud Pacalet (https://stackoverflow.com/a/53138757)
# Note:				use 'mingw32-make' in MinGW environment!
#----------------------------------

MKDIR   := md
RMDIR   := rd /S /Q
CC      := gcc
BIN     := ./bin
OBJ     := ./obj
SRC     := ./src
SRCS    := $(wildcard $(SRC)/*.c)
OBJS    := $(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(SRCS))
EXE     := $(BIN)/main.exe
CFLAGS  := -Wall
LDLIBS  := -lgdi32 -luser32

.PHONY: all run clean

all: $(EXE)

$(EXE):	$(OBJS) | $(BIN)
	$(CC)$(LDFLAGS) $^ -o $@ $(LDLIBS) -mwindows

$(OBJ)/%.o: $(SRC)/%.c | $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN) $(OBJ):
	$(MKDIR) $@

run: $(EXE)
	$<

clean:
	$(RMDIR) $(OBJ) $(BIN)