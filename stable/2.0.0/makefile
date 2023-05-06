CPPFILES = $(wildcard *.cpp)
OBJFILES = $(CPPFILES:.cpp=.o)
OUT      = main

#CFLAGS = -Wall -I/opt/homebrew/opt/libomp/include
CFLAGS = -Wall
#LDLIBS = -lstdc++ -lm -L/opt/homebrew/opt/libomp/lib
LDLIBS = -lstdc++ -lm
$(OUT): $(OBJFILES)

.PHONY: clean
clean:
	rm -f $(OBJFILES) $(OUT)
