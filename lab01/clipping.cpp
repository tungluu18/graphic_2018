#include <cstdio>
#include <iostream>
#include <vector>
#include <GL/glut.h>

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 300

using namespace std;

struct Point {
  int x, y;
  Point() {}
  Point(int _x, int _y) : x(_x), y(_y) {}
};

vector <Point> points;

void Init(int argc, char **argv) {
   /** Init Windows **/
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  //glutInitWindowPosition(500, 100);
  glutCreateWindow("Hello world!");

  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  const double w = glutGet( GLUT_WINDOW_WIDTH );
  const double h = glutGet( GLUT_WINDOW_HEIGHT );
  gluOrtho2D(0.0, w, 0.0, h);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void display() {      
  glColor3f(1.0, 1.0, 1.0);
  glPointSize(1.0f);
  glBegin(GL_POINTS);
    for (int i = 0; i < points.size(); ++i) {      
      glVertex2i(points[i].x, points[i].y);
    }
  glEnd();

  glFlush();
}

int main(int argc, char **argv) {
  Init(argc, argv);    
  glutDisplayFunc(display);
  glutMainLoop();

	return 0;
}