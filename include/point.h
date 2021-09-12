#ifndef INCLUDE_POINT_H_
#define INCLUDE_POINT_H_

enum class AType {
  ATYPE_UNKNOWN,
  ATYPE_CLOSED,
  ATYPE_OPENED,
  ATYPE_BARRIER //障碍
};

//地图最大值
const int MAX_X = 4;
const int MAX_Y = 8;

class GridPoint {
public:
  GridPoint();
  ~GridPoint();
  int x;
  int y;
  AType type; //类型:障碍、开放列表、关闭列表
  int f;      // f = g+h
  int g;
  int h;
  GridPoint *parent;
  bool operator==(const GridPoint &po) {
    if (x == po.x && y == po.y) {
      return true;
    }
    return false;
  }
};

#endif // INCLUDE_POINT_H_
