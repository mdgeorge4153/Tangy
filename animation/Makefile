#
# GLSL example
#

OGL_OBJECTS= ogl.o textfile.o
ORGANIC_OBJECTS= organic.o textfile.o
LDFLAGS= -lGL -lGLEW -lglut

all: ogl organic

ogl: $(OGL_OBJECTS)
	g++ $(OGL_OBJECTS) $(LDFLAGS) -o ogl

organic: $(ORGANIC_OBJECTS)
	g++ $(ORGANIC_OBJECTS) $(LDFLAGS) -o organic

textfile.o: textfile.h textfile.cpp

clean:
	rm -rf $(OGL_OBJECTS) $(ORGANIC_OBJECTS) ogl

.PHONY: clean
