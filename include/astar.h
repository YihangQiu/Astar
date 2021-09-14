#ifndef INCLUDE_ASTAR_H_
#define INCLUDE_ASTAR_H_

#include "point.h"
#include <algorithm>
#include <math.h>
#include <stdio.h>
#include <vector>
using std::vector;

class AStar {
private:
  vector<Point *> _openList;      //开放列表
  vector<Point *> _closeList;     //关闭列表
  vector<Point *> _neighbourList; //周边节点
  Point *_endPoint;
  Point *_curPoint;
  vector<vector<Point *>> _allPoints;
  int get_h_octagonal(Point *point) {
    int dx = abs(_endPoint->x - point->x);
    int dy = abs(_endPoint->y - point->y);
    int D1 = 100;
    int D2 = 140; // https://zhuanlan.zhihu.com/p/108344917
    return D1 * (dx + dy) + (D2 - 2 * D1) * std::min(dx,dy);
  }
  int get_f_octagonal(Point *point) {
    return (point->g + get_h_octagonal(point));
  }
  int get_h_manhattan(Point *point) {
    return (abs(_endPoint->y - point->y) + abs(_endPoint->x - point->x)) * 100;
  }
  int get_f_manhattan(Point *point) {
    return (point->g + get_h_manhattan(point));
  }
  int get_h_euclidean(Point *point) {
    return sqrt((_endPoint->y - point->y) * (_endPoint->y - point->y) +
                (_endPoint->x - point->x) * (_endPoint->x - point->x)) *
           100;
  }
  int get_f_euclidean(Point *point) {
    return (point->g + get_h_euclidean(point));
  }

  vector<Point *> getNeighboringPoint(Point *point);

public:
  AStar() : _endPoint(nullptr), _curPoint(nullptr){};
  ~AStar() {
    _openList.clear();
    _closeList.clear();
    _neighbourList.clear();
    _allPoints.clear();
  };
  Point *findWay(Point *beginPoint, Point *endPoint,
                 vector<vector<Point *>> &allPoints);
};

#endif // INCLUDE_ASTAR_H_
