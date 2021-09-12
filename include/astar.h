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
#include <stdio.h>
#include <vector>
using namespace std;

class Astar {
private:
  vector<GridPoint *> _openList;      //开放列表
  vector<GridPoint *> _closeList;     //关闭列表
  vector<GridPoint *> _neighbourList; //周边节点
  GridPoint *_endPoint;
  GridPoint *_curPoint;
  vector<vector<GridPoint *>> _allPoints;
  int getF(GridPoint *point);
  int getH(GridPoint *point);
  vector<GridPoint *> getNeighboringPoint(GridPoint *point);

public:
  Astar();
  ~Astar();
  GridPoint *findWay(GridPoint *beginPoint, GridPoint *endPoint,
                     vector<vector<GridPoint *>> &allPoints);
};

#endif // INCLUDE_ASTAR_H_
