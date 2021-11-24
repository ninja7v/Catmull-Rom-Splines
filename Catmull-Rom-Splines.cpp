// Catmull-Rom splines interpolation coded in C++ by Luc PREVOST 

//////////////
// Libraries
//////////////
#include <GL/glut.h>
#include <iostream>
#include <list>
#include <stdexcept> 
#include <chrono>

////////////
// Classes
////////////
class Point {
public:
   // Parameters
   float x, y, tx = 0, ty = 0;
   // Functions
   Point(float x1 = 0, float y1 = 0) : x(x1), y(y1) {
   }
   Point operator*(float const &a) {
      Point p;
      p.x = x * a;
      p.y = y * a;
      return p;
   }
   Point operator+(Point const &P) {
      Point p;
      p.x = x + P.x;
      p.y = y + P.y;
      return p;
   }
   Point operator-(Point const &P) {
      Point p;
      p.x = x - P.x;
      p.y = y - P.y;
      return p;
   }
   float dot(Point P) {
      return pow(P.x - x, 2) + pow(P.y - y, 2);
   }
   void display() {
      glEnable(GL_POINT_SMOOTH);
      glPointSize(50.0);
      glBegin(GL_POINTS);
      glColor3f(0.5, 0.5, 0.5);
      glVertex2f(x, 1-y);
      glEnd();
      glDisable(GL_POINT_SMOOTH);
   }
   float distance(Point* P) {
      return pow(pow(P->x - x, 2) + pow(P->y - y, 2), 0.5);
   }
   void updateTangent(Point* P1, Point* P2) {
      try {
         float norm = P1->distance(P2);
         if (norm == 0)
            throw std::runtime_error("Attempted to divide by Zero\n");
         tx = (P2->x - P1->x) / norm;
         ty = (P2->y - P1->y) / norm;
      }
      catch (std::runtime_error& e) {
         std::cout << e.what();
      };
   }
};

class Spline {
public:
   // Parameters
   Point *P0, *P1, *P2, *P3;
   static float alpha;
   // Functions
   Spline(Point* B1, Point* start, Point* end, Point* B2) : P0(B1), P1(start), P2(end), P3(B2) {
   }
   Point operator()(float t) {
      // Uniform
      /*float x[4], y[4];
      // In P1
      x[3] = P1->x;
      y[3] = P1->y;
      x[2] = P1->tx;
      y[2] = P1->ty;
      // In P2
      x[1] = 3 * P2->x - 3 * P1->x - P2->tx - 2 * P1->tx;
      y[1] = 3 * P2->y - 3 * P1->y - P2->ty - 2 * P1->ty;
      x[0] = P2->x - x[1] - x[2] - x[3];
      y[0] = P2->y - y[1] - y[2] - y[3];
      Point P = Point();
      for (int i = 0; i < 4; i++) {
         P.x += x[i] * pow(t, 3 - i);
         P.y += y[i] * pow(t, 3 - i);
      }*/
      // Centripedal
      auto GetT = [=](float t, Point* p0, Point* p1) {
         Point p = *p1 - *p0;
         float a = pow(p.x, 2) + pow(p.y, 2); // Dot product
         float b = pow(a, alpha * .5f);
         return (b + t);
      };
      float t0 = 0.0f;
      float t1 = pow(pow(P1->x - P0->x, 2) + pow(P1->y - P0->y, 2), alpha * 0.5) + t0; //GetT(t0, P0, P1);
      float t2 = pow(pow(P2->x - P1->x, 2) + pow(P2->y - P1->y, 2), alpha * 0.5) + t1; //GetT(t1, P1, P2);
      float t3 = pow(pow(P3->x - P2->x, 2) + pow(P3->y - P2->y, 2), alpha * 0.5) + t2; //GetT(t2, P2, P3);
      float T = t1 + t * (t2 - t1);
      Point A1 = *P0 * ((t1 - T) / (t1 - t0)) + *P1 * ((T - t0) / (t1 - t0));
      Point A2 = *P1 * ((t2 - T) / (t2 - t1)) + *P2 * ((T - t1) / (t2 - t1));
      Point A3 = *P2 * ((t3 - T) / (t3 - t2)) + *P3 * ((T - t2) / (t3 - t2));
      Point B1 = A1 * ((t2 - T) / (t2 - t0)) + A2 * ((T - t0) / (t2 - t0));
      Point B2 = A2 * ((t3 - T) / (t3 - t1)) + A3 * ((T - t1) / (t3 - t1));
      Point P = B1 * ((t2 - T) / (t2 - t1)) + B2 * ((T - t1) / (t2 - t1));
      return P;
   }
   void display(bool curveClosed) {
      Point Pip1, Pi = operator()(0);
      float step = 0.02;
      float x0, y0, x1, y1;
      for (float t = step; t <= 1; t += step) {
         Pip1 = operator()(t);
         x0 = Pi.x;
         y0 = 1 - Pi.y;
         x1 = Pip1.x;
         y1 = 1 - Pip1.y;
         Pi = Pip1;
         glLineWidth(10);
         glBegin(GL_LINES);
         glColor3f(0.5, 0.5, 0.5);
         glVertex2f(x0, y0);
         glVertex2f(x1, y1);
         glEnd();
         if (curveClosed) {
            auto t0 = std::chrono::high_resolution_clock::now(), t1 = t0;
            do { t1 = std::chrono::high_resolution_clock::now(); }
            while (std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() < 3);
            glFlush();
         }
      }
   }
};

//////////////////////
// Global parameters
//////////////////////
std::list<Point*> Points;
std::list<Spline*> Curve;
std::list<std::list<Spline*>> Curves;
float Spline::alpha = 0.5;

//////////////
// Functions
//////////////
void display(void) {
   // Reset
   glClear(GL_COLOR_BUFFER_BIT);
   // Points
   for (Point* p : Points)
      p->display();
   // Curves finished
   for (std::list<Spline*> C : Curves)
      for (Spline* s : C)
         s->display(Points.empty());
   // Curve under construction
   for (Spline* s : Curve)
      s->display(0);
   glFlush();
}

void update(int button, int state, int X, int Y) {
   float x = X / 1000.0;
   float y = Y / 700.0;
   switch (button) {
   case GLUT_LEFT_BUTTON:
      if (state == GLUT_UP) {
         Point* P = new Point(x, y);
         std::list<Point*>::iterator it0, it1;
         switch (Points.size()) {
         case 0:
            Points.push_back(P);
            std::cout << "Point " << Points.size() << " = (" << x << ", " << y << ") added" << std::endl;
            break;
         case 1:
            if (P->distance(Points.front()) < 0.1)
               delete P;
            else {
               Points.push_back(P);
               std::cout << "Point " << Points.size() << " = (" << x << ", " << y << ") added" << std::endl;
            }
            break;
         default:
            if (Points.size() != Curve.size()) {
               if (P->distance(Points.front()) < 0.1) {
                  if (prev(prev(Points.end())) != Points.begin()) {
                     delete P;
                     it1 = prev(Points.end());
                     Points.back()->updateTangent(*--it1, Points.front());
                     it0 = Points.begin();
                     Points.front()->updateTangent(Points.back(), *++it0);
                     it0 = prev(Points.end());
                     it1 = prev(Points.end());
                     Spline* S = new Spline(*--(--it0), *--it1, Points.back(), Points.front());
                     std::cout << "test" << std::endl;
                     Curve.push_back(S);
                     std::cout << "Spline (" << Points.size() - 1 << ") -> (" << Points.size() << ") added" << std::endl;
                     it0 = prev(Points.end());
                     it1 = Points.begin();
                     Spline* Send = new Spline(*--it0, Points.back(), Points.front(), *++it1);
                     Curve.push_back(Send);
                     std::cout << "Spline (" << Points.size() << ") -> (" << 1 << ") added" << std::endl;
                     it0 = Points.begin();
                     it1 = Points.begin();
                     Spline* Sbegin = new Spline(Points.back(), Points.front(), *++it0, *++(++it1));
                     Curve.push_front(Sbegin);
                     std::cout << "Spline (" << 1 << ") -> (" << 2 << ") added" << std::endl;
                     std::cout << "Curve closed" << std::endl;
                     Curves.push_back(Curve);
                     Curve.clear();
                     Points.clear();
                  }
                  else {
                     delete P;
                  }
               }
               else {
                  it0 = prev(Points.end());
                  Points.back()->updateTangent(*--it0, P);
                  if (it0 != Points.begin()) {
                     it1 = prev(Points.end());
                     Spline* S = new Spline(*--it0, *--it1, Points.back(), P);
                     Curve.push_back(S);
                     std::cout << "Spline (" << Points.size() - 1 << ") -> (" << Points.size() << ") added" << std::endl;
                  }
                  Points.push_back(P);
                  std::cout << "Point " << Points.size() << " = (" << x << ", " << y << ") added" << std::endl;
               }
            }
            break;
         };
      } break;
   case GLUT_RIGHT_BUTTON:
      if (state == GLUT_UP) {
         Points.clear();
         Curve.clear();
         std::list<Point*>::iterator it;
      } break;
   case GLUT_MIDDLE_BUTTON:
      if (state == GLUT_UP) {
         display();
      } break;
   }
}

void init() {
   // Set background color as white
   glClearColor(1.0f, 1.0f, 1.0f, 0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
   // To set the background color active
   glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 1);
}

//////////////////
// Main function
//////////////////
int main(int argc, char* argv[]) {
   // Initialise GLUT with command-line parameters. 
   glutInit(&argc, argv);
   // Set Display Mode
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   // Set window size
   glutInitWindowSize(1000, 700);
   // Set window position
   glutInitWindowPosition(200, 200);
   // Create the window
   glutCreateWindow("Catmull-Rom Splines");
   // Initialise GLUT
   init();
   // Display callback
   glutDisplayFunc(display);
   // Mouse callback
   glutMouseFunc(update);
   // Enter the GLUT event loop
   glutMainLoop();
   return 0;
}
