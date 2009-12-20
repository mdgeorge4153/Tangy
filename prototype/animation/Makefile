#
# GLSL example
#

OGL_OBJECTS     = ogl.o textfile.o
ORGANIC_OBJECTS = organic.o textfile.o
TEXGEN_OBJECTS  = texgen.o
LDFLAGS= -lGL -lGLEW -lglut

all: ogl organic 

ogl: $(OGL_OBJECTS)
	g++ $(OGL_OBJECTS) $(LDFLAGS) -o ogl

organic: $(ORGANIC_OBJECTS)
	g++ $(ORGANIC_OBJECTS) $(LDFLAGS) -o organic

texgen: $(TEXGEN_OBJECTS)
	g++ $(TEXGEN_OBJECTS) $(LDFLAGS) -o texgen

textfile.o: textfile.h textfile.cpp

clean:
	rm -rf $(OGL_OBJECTS) $(ORGANIC_OBJECTS) $(TEXGEN_OBJECTS) ogl organic texgen

.PHONY: clean
