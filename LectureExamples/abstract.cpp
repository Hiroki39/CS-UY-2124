#include <iostream>
using namespace std;

class Shape {  // abstract class
public:
    Shape(int x, int y) : x(x), y(y) {}
    void move(int x, int y) {
        this->x = x;
        this->y = y;
    }
    // virtual void draw() { cout << "Default stufff..."; }

    // Abstract
    virtual void draw() = 0;  // pure virtual

private:
    int x, y;
};

class Triangle : public Shape {
public:
    Triangle(int x, int y) : Shape(x, y) {}
    void draw() { cout << "Triangle Drawing" << endl; }
};

class Circle : public Shape {
public:
    Circle(int x, int y) : Shape(x, y) {}
    void draw() { cout << "Circle Drawing" << endl; }
};

void drawShape(Shape& aShape) { aShape.draw(); }  // should work

int main() {
    // Shape aShape(3, 4); won't compile at any time
    Triangle tri(3, 4);
    tri.draw();
    Circle circ(3, 4);
    circ.draw();

    drawShape(circ);
}
