CC = g++
CFLAGS = -Wall -Werror -I./include # specifies the compiler flags to use. In this case, we are setting -Wall and -Werror to enable all warnings and treat warnings as errors, respectively, and -I./include to specify the path to the header file.

SRCS = src/UtilFunction.cpp src/ConvertTool.cpp src/Graph.cpp src/DisjointSet.cpp  src/MainFunction.cpp main.cpp # lists the source files that need to be compiled.
OBJS = $(SRCS:.cpp=.o) # lists the object files that will be generated from the source files.

EXECUTABLE = satelliteNetworkMRCT.exe

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@
	rm -f $(OBJS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXECUTABLE)
