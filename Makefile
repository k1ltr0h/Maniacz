GPP = g++
FLAGS = -Wall
CPP_FILES = *.cpp
OUT = -o maniacz
ICON = icon.res


all:
	$(GPP) $(FLAGS) $(CPP_FILES) $(OUT) $(ICON)
