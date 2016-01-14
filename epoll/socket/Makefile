SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp = .o)
CC = g++
INCLUDES = -I/usr/your_path/include
LIBS = -L/usr/your_path/lib
CCFLAGS = -g -Wall -O0
EXE = server
$(EXE) : $(OBJS)
	$(CC) $(CCFLAGS) $^ -o $@ $(INCLUDES) $(LIBS)
clean:
	rm -f $(EXE)
