//  上下左右走一格花销为10，斜着走一格花销为14，以方便计算
//  即格子宽高为10 对角线为14
#include "astar.h"
#include "point.h"
using std::vector;

//自定义排序函数
bool mySort(const Point *p1, const Point *p2) { return p1->f < p2->f; }

Point *AStar::findWay(Point *beginPoint, Point *endPoint,
                      vector<vector<Point *>> &allPoints) {
  printf("\n(3) Finding the shortest path using AStar Algorithms ... ...\n");
  //传递地图
  _allPoints = allPoints;
  _endPoint = endPoint;

  if (_endPoint->type == AType::ATYPE_BARRIER) {
    printf("The end is an obstacle.\n");
    return nullptr;
  }
  if (*_endPoint == *beginPoint) {
    printf("The start and end points are the same.\n");
    return nullptr;
  }
  //对起始点的处理
  _openList.push_back(beginPoint);
  beginPoint->type = AType::ATYPE_OPENED;
  beginPoint->f = get_f(beginPoint);
  do {
    //获取最小值的节点
    _curPoint = _openList[0];
    _openList.erase(_openList.begin());
    _curPoint->type = AType::ATYPE_CLOSED;
    _closeList.push_back(_curPoint);

    if (*_curPoint == *_endPoint) {
      return _curPoint;
    }
    //获取相邻的节点
    vector<Point *> neVec = getNeighboringPoint(_curPoint);
    for (int i = 0; i < neVec.size(); ++i) {
      auto tmpoint = neVec[i];
      if (tmpoint->type == AType::ATYPE_CLOSED) {
        continue;
      }
      //是否在开放列表里
      if (tmpoint->type != AType::ATYPE_OPENED) {
        tmpoint->parent = _curPoint;
        // if (tmpoint->direction == ADirection::MANHATTAN) {
        //   tmpoint->g = _curPoint->g + 10;
        // } else {
        //   tmpoint->g = _curPoint->g + 14;
        // }
        tmpoint->g = _curPoint->g + 10;
        //计算H值
        tmpoint->h = get_h(tmpoint);
        //添加到开放列表里
        _openList.push_back(tmpoint);
        tmpoint->type = AType::ATYPE_OPENED;
      } else {
        //已经在开放列表里
        if (tmpoint->h < _curPoint->h) {
          tmpoint->parent = _curPoint;
          // if (tmpoint->direction == ADirection::MANHATTAN) {
          //   tmpoint->g = _curPoint->g + 10;
          // } else {
          //   tmpoint->g = _curPoint->g + 14;
          // }
          tmpoint->g = _curPoint->g + 10;
        }
      }
    }
    //排序 F值最小的排在前面
    sort(_openList.begin(), _openList.end(), mySort);

  } while (_openList.size() > 0);

  printf("---can not find way---\n");
  return nullptr;
}

vector<Point *> AStar::getNeighboringPoint(Point *point) {
  _neighbourList.clear();
  if (point->x < MAX_X - 1) {
    if (_allPoints[point->x + 1][point->y]->type != AType::ATYPE_BARRIER) {
      //_allPoints[point->x + 1][point->y]->direction = ADirection::MANHATTAN;
      _neighbourList.push_back(_allPoints[point->x + 1][point->y]);
    }
  }
  if (point->x > 0) {
    if (_allPoints[point->x - 1][point->y]->type != AType::ATYPE_BARRIER) {
      //_allPoints[point->x - 1][point->y]->direction = ADirection::MANHATTAN;
      _neighbourList.push_back(_allPoints[point->x - 1][point->y]);
    }
  }
  if (point->y < MAX_Y - 1) {
    if (_allPoints[point->x][point->y + 1]->type != AType::ATYPE_BARRIER) {
      // _allPoints[point->x][point->y + 1]->direction = ADirection::MANHATTAN;
      _neighbourList.push_back(_allPoints[point->x][point->y + 1]);
    }
  }
  if (point->y > 0) {
    if (_allPoints[point->x][point->y - 1]->type != AType::ATYPE_BARRIER) {
      //_allPoints[point->x][point->y - 1]->direction = ADirection::MANHATTAN;
      _neighbourList.push_back(_allPoints[point->x][point->y - 1]);
    }
  }
  // if (point->x > 0 && point->y > 0) {
  //   if (_allPoints[point->x - 1][point->y - 1]->type != AType::ATYPE_BARRIER)
  //   {
  //     //_allPoints[point->x - 1][point->y - 1]->direction =
  //     ADirection::INCLINE; _neighbourList.push_back(_allPoints[point->x -
  //     1][point->y - 1]);
  //   }
  // }
  // if (point->x > 0 && point->y < MAX_Y - 1) {
  //   if (_allPoints[point->x - 1][point->y + 1]->type != AType::ATYPE_BARRIER)
  //   {
  //     //_allPoints[point->x - 1][point->y + 1]->direction =
  //     ADirection::INCLINE; _neighbourList.push_back(_allPoints[point->x -
  //     1][point->y + 1]);
  //   }
  // }
  // if (point->x < MAX_X - 1 && point->y < MAX_Y - 1) {
  //   if (_allPoints[point->x + 1][point->y + 1]->type != AType::ATYPE_BARRIER)
  //   {
  //     //_allPoints[point->x + 1][point->y + 1]->direction =
  //     ADirection::INCLINE; _neighbourList.push_back(_allPoints[point->x +
  //     1][point->y + 1]);
  //   }
  // }
  // if (point->x < MAX_X - 1 && point->y > 0) {
  //   if (_allPoints[point->x + 1][point->y - 1]->type != AType::ATYPE_BARRIER)
  //   {
  //     //_allPoints[point->x + 1][point->y - 1]->direction =
  //     ADirection::INCLINE; _neighbourList.push_back(_allPoints[point->x +
  //     1][point->y - 1]);
  //   }
  // }
  return _neighbourList;
}
