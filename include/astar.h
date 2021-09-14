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
  Point *findWay(Point *beginPoint, Point *endPoint,
                 vector<vector<Point *>> &allPoints);
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
  vector<Point *> getNeighboringPoint(Point *point);
  void getNeighboringPointLeftDown(Point *point);
  void getNeighboringPointLeftUp(Point *point);
  void getNeighboringPointRightUp(Point *point);
  void getNeighboringPointRightDown(Point *point);
  void getNeighboringPointRight(Point *point);
  void getNeighboringPointLeft(Point *point);
  void getNeighboringPointUp(Point *point);
  void getNeighboringPointDown(Point *point);
  void computeNeighboringValue(vector<Point *> &neVec,vector<Point *> &_openList);

};

#endif // INCLUDE_ASTAR_H_
