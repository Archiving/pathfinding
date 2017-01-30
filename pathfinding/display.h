#include <GL/freeglut.h>
#include <iostream>
#include <fstream>
#include <string>
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/OpenGL.h>
#endif

//Point class
struct point {
	int x = 0;
	int y = 0;
	bool blocked;
	int red = 0;
};

typedef struct point point;

enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE
};

extern point** grid;

#define VWIDTH 1080
#define VHEIGHT 720
#define VERSION 1.0
#define AUTHOR "Andy Ma"

//regular GLUT methods
void display(int argc, char** argv, float size, float gridSize);
void key_callback(unsigned char key, int x, int y);
void render_callback();
void resize(int w, int h);
void menu_callback(int id);
