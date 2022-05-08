LINK := -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl
CFLAGS := -g -std=c++17
INCLUDE_PATHS := -Iinclude -Ilib
CXX := g++

CLIENT = client/main.cpp

CLIOBJECT = $(CLIENT:%.cpp=build/%.o)

TARGET = build/$(basename $(notdir $(CLIENT)))

SRC = src/Camera.cpp \
	  src/glad.c \
	  src/Shader.cpp \
	  src/stb_image.cpp

HEADERS = include/Camera.h \
		  include/Shader.h \
		  include/stb_image.h

OBJECTS := $(SRC:%.cpp=build/%.o)

all: $(TARGET)

build/src/%.o: src/%.cpp $(HEADERS)
	@mkdir -p build/src/
	$(CXX) $(INCLUDE_PATHS) $(CFLAGS) -c -o $@ $<

build/lib/%.o: lib/%.cpp $(HEADERS)
	@mkdir -p build/lib/
	$(CXX) $(INCLUDE_PATHS) $(CFLAGS) -c -o $@ $<

$(CLIOBJECT): $(CLIENT) $(HEADERS)
	@mkdir -p build/client/
	$(CXX) $(INCLUDE_PATHS) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJECTS) $(CLIOBJECT)
	$(CXX) $(INCLUDE_PATHS) $(OBJECTS) $(CLIOBJECT) $(LINK) -o $@

clean:
	-rm -f -r build

debug: $(TARGET)
	@valgrind ./$(TARGET)

run: $(TARGET)
	@./$(TARGET)
