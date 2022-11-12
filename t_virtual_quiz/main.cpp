#include <algorithm>
#include <iostream>
#include <vector>

#include "Circle.h"
#include "Point.h"
#include "Triangle.h"

int getLargestRadius(const std::vector<Shape*>& v) {
  int lr{0};

  for (const auto* s : v) {
    if (auto* c{dynamic_cast<const Circle*>(s)}) {
      lr = std::max(lr, c->getRadius());
    }
  }

  return lr;
}

int main(int argc, char const* argv[]) {
  // question #1
  {
    Circle c{Point{1, 2}, 7};
    std::cout << c << '\n';

    Triangle t{Point{1, 2}, Point{3, 4}, Point{5, 6}};
    std::cout << t << '\n';
  }

  // question #2
  {
    std::vector<Shape*> v{new Circle{Point{1, 2}, 7},
                          new Triangle{Point{1, 2}, Point{3, 4}, Point{5, 6}},
                          new Circle{Point{7, 8}, 3}};

    // print each shape in vector v on its own line here
    for (const auto* s : v) {
      std::cout << *s << std::endl;
    }

    std::cout << "The largest radius is: " << getLargestRadius(v) << std::endl;

    // delete each element in the vector here
    for (const auto* s : v) {
      delete s;
    }
  }

  return 0;
}
