CC = clang++
SRCS = $(wildcard src/*.cpp)
OBJS = $(patsubst src/%.cpp, obj/%.o, $(SRCS))
BIN = bin/budget.exe

all : $(BIN)

$(BIN) : $(OBJS)
	$(CC) $(OBJS) -o $@
	.\\bin/budget.exe

obj/%.o : src/%.cpp
	$(CC) -c $< -o $@

clean :
	del /Q obj\\* bin\\*