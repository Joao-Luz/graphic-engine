LINK := -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl
CFLAGS := -g -std=c++17
INCLUDE_PATHS := -Isrc -Iexternal
CXX := g++

CLIENT = examples/cubes.cpp

CLIOBJECT = $(CLIENT:%.cpp=build/%.o)

TARGET = build/$(basename $(notdir $(CLIENT)))

SRC = src/Camera.cpp \
	  src/Shader.cpp \
	  external/stb_image/stb_image.cpp \
	  external/glad/glad.c \

HEADERS = src/Camera.h \
		  src/Shader.h \
		  external/stb_image/stb_image.h \
		  external/glad/glad.h \

OBJECTS := $(SRC:%.cpp=build/%.o)

all: $(TARGET)

build/src/%.o: src/%.cpp $(HEADERS)
	@mkdir -p build/src/
	$(CXX) $(INCLUDE_PATHS) $(CFLAGS) -c -o $@ $<

build/external/%.o: external/%.cpp $(HEADERS)
	@mkdir -p build/external/
	@mkdir -p build/external/stb_image/
	@mkdir -p build/external/glad/
	$(CXX) $(INCLUDE_PATHS) $(CFLAGS) -c -o $@ $<

$(CLIOBJECT): $(CLIENT) $(HEADERS)
	@mkdir -p build/examples/
	$(CXX) $(INCLUDE_PATHS) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJECTS) $(CLIOBJECT)
	$(CXX) $(INCLUDE_PATHS) $(OBJECTS) $(CLIOBJECT) $(LINK) -o $@

clean:
	-rm -f -r build

debug: $(TARGET)
	@valgrind ./$(TARGET)

run: $(TARGET)
	@./$(TARGET)
