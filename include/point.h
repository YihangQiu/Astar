#ifndef INCLUDE_POINT_H_
#define INCLUDE_POINT_H_

#include "display.h"
enum class AType { ATYPE_UNKNOWN, ATYPE_CLOSED, ATYPE_OPENED, ATYPE_BARRIER };
enum class ADirection { MANHATTAN, INCLINE };

class Point {
public:
  Point()
      : x(0), y(0), h(0), f(0), g(0), parent(nullptr),
        type(AType::ATYPE_UNKNOWN){};
  ~Point(){};
  int x;
  int y;
  AType type; //类型:障碍、开放列表、关闭列表
  ADirection direction;
  int f; // f = g+h
  int g;
  int h;
  Point *parent;
  bool operator==(const Point &po) {
    if (x == po.x && y == po.y) {
      return true;
    }
    return false;
  }
};

#endif // INCLUDE_POINT_H_
