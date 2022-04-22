CC := gcc
CFLAGS := -Wall -O3
Libs = -lpthread
Target := operation
Source := $(wildcard src/*.c)
Objs := $(patsubst %.c,%.o,$(Source))
Modules += add sub mul div main
AllObjs := $(addsuffix /src/*.o,$(Modules))

