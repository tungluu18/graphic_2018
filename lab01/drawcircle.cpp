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

void drawCircleMidPoint(Point center, int radius) {
  points.clear();
  int x = radius, y = 0;  
  int P = 1 - radius;
  while (x >= y) {
    points.push_back(Point(center.x + x, center.y + y));
    points.push_back(Point(center.x - x, center.y + y));
    points.push_back(Point(center.x - x, center.y - y));
    points.push_back(Point(center.x + x, center.y - y));    
    
    points.push_back(Point(center.x + y, center.y + x));
    points.push_back(Point(center.x - y, center.y + x));
    points.push_back(Point(center.x - y, center.y - x));
    points.push_back(Point(center.x + y, center.y - x));

    ++y;
    if (P <= 0) 
      P = P + 2*y + 1;
    else {
      x--;
      P = P + 2*y - 2*x + 1;
    }        
  }
  //glutPostRedisplay();
}

void drawCircleBresenham(Point center, int radius) {
  points.clear();
  int x = 0, y = radius;
  int d = 3 - 2 * radius;
  while (y > x) {
    points.push_back(Point(center.x + x, center.y + y));
    points.push_back(Point(center.x - x, center.y + y));
    points.push_back(Point(center.x - x, center.y - y));
    points.push_back(Point(center.x + x, center.y - y));    
    
    points.push_back(Point(center.x + y, center.y + x));
    points.push_back(Point(center.x - y, center.y + x));
    points.push_back(Point(center.x - y, center.y - x));
    points.push_back(Point(center.x + y, center.y - x));
    
    if (d > 0) {
      d += 4 * (x - y) + 10;
      y--;
    } else {
      d += 4 * x + 6; 
    }
    x++;
  }
  //glutPostRedisplay();
}

int main(int argc, char **argv) {
  Init(argc, argv);    
  //drawCircleMidPoint(Point(100, 100), 20);
  drawCircleBresenham(Point(100, 100), 100);
  glutDisplayFunc(display);
  glutMainLoop();

	return 0;
}