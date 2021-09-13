#ifndef INCLUDE_ASTAR_H_
#define INCLUDE_ASTAR_H_
/*
    F:路径评分 = g+h
    G:走一格格子的花销
    H:当前格子到目标格子的估算花销
    上下左右走一格花销为10，斜着走一格花销为14，以方便计算
    即格子宽高为10 对角线为14
 */
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
  int get_f(Point *point) { return (point->g + get_h(point)); };
  int get_h(Point *point) {
    return (abs(_endPoint->y - point->y) + abs(_endPoint->x - point->x)) * 10;
    // return sqrt((_endPoint->y - point->y) * (_endPoint->y - point->y) +
    //             (_endPoint->x - point->x) * (_endPoint->x - point->x)) *
    //        10;
  };
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
