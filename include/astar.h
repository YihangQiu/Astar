#ifndef INCLUDE_ASTAR_H_
#define INCLUDE_ASTAR_H_

#include "point.h"
#include <algorithm>
#include <math.h>
#include <stdio.h>
#include <vector>
using std::vector;

const int D1 = 100;
const int D2 = 140;

class AStar {
private:
  vector<Point *> _openList;      //开放列表
  vector<Point *> _closeList;     //关闭列表
  vector<Point *> _neighbourList; //周边节点
  Point *_endPoint;
  Point *_curPoint;
  vector<vector<Point *>> _allPoints;

public:
  AStar() : _endPoint(nullptr), _curPoint(nullptr){};
  ~AStar() {
    _openList.clear();
    _closeList.clear();
    _neighbourList.clear();
    _allPoints.clear();
  };
  int get_h_manhattan(Point *point) {
    return (abs(_endPoint->y - point->y) + abs(_endPoint->x - point->x)) * D1;
  }
  int get_h_euclidean(Point *point) {
    return sqrt((_endPoint->y - point->y) * (_endPoint->y - point->y) +
                (_endPoint->x - point->x) * (_endPoint->x - point->x)) *
           D1;
  }
  int get_h_octagonal(Point *point) {
    return D1 * (abs(_endPoint->x - point->x) + abs(_endPoint->y - point->y)) +
           (D2 - 2 * D1) * std::min(abs(_endPoint->x - point->x),
                                    abs(_endPoint->y - point->y));
  }
  int get_f_manhattan(Point *point) {
    return (point->g + get_h_manhattan(point));
  }
  int get_f_euclidean(Point *point) {
    return (point->g + get_h_euclidean(point));
  }
  int get_f_octagonal(Point *point) {
    return (point->g + get_h_octagonal(point));
  }

  void computeNeighboringValue(vector<Point *> &neVec,
                               vector<Point *> &_openList);

  Point *findWay_test(Point *beginPoint, Point *endPoint,
                      vector<vector<Point *>> &allPoints, Display &display);
  vector<Point *> getNeighboringPoint_test(Point *point, Display &display);
  void getNeighboringPointLeftDown_test(Point *point, Display &display);
  void getNeighboringPointLeftUp_test(Point *point, Display &display);
  void getNeighboringPointRightUp_test(Point *point, Display &display);
  void getNeighboringPointRightDown_test(Point *point, Display &display);
  void getNeighboringPointRight_test(Point *point, Display &display);
  void getNeighboringPointLeft_test(Point *point, Display &display);
  void getNeighboringPointUp_test(Point *point, Display &display);
  void getNeighboringPointDown_test(Point *point, Display &display);
};

#endif // INCLUDE_ASTAR_H_
