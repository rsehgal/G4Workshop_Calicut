#include <iostream>
using namespace std;
class Rectangle {

  double fLength;
  double fBreadth;

public:
  Rectangle() {
    fLength = 0;
    fBreadth = 0;
  }

  Rectangle(double l, double b) {
    fLength = l;
    fBreadth = b;
  }

  double GetLength() { return fLength; }
  double GetBreadth() { return fBreadth; }
  double GetArea() { return fLength * fBreadth; }
};

int main() {
  // Rectangle r;
  Rectangle *r = new Rectangle();
  cout << "Length : " << r->GetLength() << " : Breadth : " << r->GetBreadth() << " : AREA : " << r->GetArea() << endl;

  // Rectangle s(5,4);
  Rectangle *s = new Rectangle(5, 4);
  cout << "Length : " << s->GetLength() << " : Breadth : " << s->GetBreadth() << " : AREA : " << s->GetArea() << endl;

  return 0;
}
