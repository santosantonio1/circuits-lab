CXXFLAGS=-O3 -lm -std=c++23 -Wall

SRC_DIR=src
SRC_FILES=$(wildcard $(SRC_DIR)/*.cc)

EXE_FILES=$(patsubst $(SRC_DIR)/%.cc, %, $(SRC_FILES))

.PHONY:	all	clean cleanw

all:	$(EXE_FILES)

.FORCE:

%:		$(SRC_DIR)/%.cc
		g++ $(CXXFLAGS) -o $@ $<

clean:
		rm -rf $(EXE_FILES)

cleanw:
		del /f /q $(EXE_FILES) 2>nul

