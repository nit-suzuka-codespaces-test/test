#
# Makefile
# 実行ファイルはmain
#
# ソースコードを増やしたら、SRCに追加すること
TARGET = main

SRCS   = $(TARGET).cpp MyApp.cpp App.cpp Ball.cpp Block.cpp Blocks.cpp
OBJS   = $(SRCS:%.cpp=%.o)
DEPS   = $(SRCS:%.cpp=%.d)
## for macOS (SFML: brew)
#CXX    = clang++
#CXXFLAGS = -std=c++11 -Wc++11-extensions -g

## for Linux (SfLinux
CXX    = c++
CXXFLAGS = -std=c++11 -g
INCLUDES = -I/usr/local/include
LDFLAGS = -L/usr/local/lib
LIBS     = -lsfml-graphics -lsfml-window -lsfml-system

$(TARGET): $(OBJS)
	$(CXX) -o  $@ $^ $(LDFLAGS) $(LIBS)

.cpp.o:%.d
	$(CXX) $(CXXFLAGS) -c $(INCLUDES) $< 

%.d:%.cpp
	$(CXX) $(CXXFLAGS) -MM $< > $@

-include $(DEPS)

all:$(TARGET)

.PHONY: clean

clean:
	rm -f $(OBJS) $(DEPS) *~ $(TARGET)
