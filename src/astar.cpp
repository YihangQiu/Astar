#include "astar.h"
#include "point.h"
using std::vector;

//自定义排序函数
bool mySort(const Point *p1, const Point *p2) { return p1->f < p2->f; }

Point *AStar::findWay(Point *beginPoint, Point *endPoint,
                      vector<vector<Point *>> &allPoints) {
  printf("\n(3) Finding the shortest path using AStar Algorithms ... ...\n");
  printf("\n**** The startpoint[%d][%d]  ->  The endpoint[%d][%d] **** \n",
         beginPoint->x, beginPoint->y, endPoint->x, endPoint->y);
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
  beginPoint->f = get_f_octagonal(beginPoint);
  int count = 0;
  do {
    ++count;
    //获取最小值的节点
    _curPoint = _openList[0];
    printf("\nstep[%d]:tmpoint[%d][%d] is selected\n", count, _curPoint->x,
           _curPoint->y);
    _openList.erase(_openList.begin());
    _curPoint->type = AType::ATYPE_CLOSED;
    _closeList.push_back(_curPoint);

    if (*_curPoint == *_endPoint) {
      printf("Find way and end searching.\n");
      return _curPoint;
    }
    //获取相邻的节点
    vector<Point *> neVec = getNeighboringPoint(_curPoint);
    for (int i = 0; i < neVec.size(); ++i) {
      auto tmpoint = neVec[i];
      if (tmpoint->type == AType::ATYPE_CLOSED) {
        continue;
      }
      //不在开放列表里
      if (tmpoint->type != AType::ATYPE_OPENED) {
        tmpoint->parent = _curPoint;
        if (tmpoint->direction == ADirection::MANHATTAN) {
          tmpoint->g = _curPoint->g + 100;
          printf("tmpoint[%d][%d]:\tvalue_G=%d", tmpoint->x, tmpoint->y,
                 tmpoint->g);
        } else if (tmpoint->direction == ADirection::INCLINE) {
          tmpoint->g = _curPoint->g + 140;
          printf("tmpoint[%d][%d]:\tvalue_G=%d", tmpoint->x, tmpoint->y,
                 tmpoint->g);
        }
        tmpoint->h = get_h_octagonal(tmpoint);
        tmpoint->f = get_f_octagonal(tmpoint);
        printf("\tvalue_H=%d\tvalue_F=%d\n", tmpoint->h, tmpoint->f);
        //添加到开放列表里
        _openList.push_back(tmpoint);
        tmpoint->type = AType::ATYPE_OPENED;
      } else {
        //已经在开放列表里
        if (tmpoint->h < _curPoint->h) {
          tmpoint->parent = _curPoint;
          if (tmpoint->direction == ADirection::MANHATTAN) {
            tmpoint->g = _curPoint->g + 100;
          } else if (tmpoint->direction == ADirection::INCLINE) {
            tmpoint->g = _curPoint->g + 140;
          }
          tmpoint->f = get_f_octagonal(tmpoint); //添加的f函数
        }
        printf("tmpoint[%d][%d]:\tvalue_G=%d\tvalue_H=%d\tvalue_F=%d\n",
               tmpoint->x, tmpoint->y, tmpoint->g, tmpoint->h, tmpoint->f);
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
  getNeighboringPointLeftDown(point);
  getNeighboringPointLeftUp(point);
  getNeighboringPointRightUp(point);
  getNeighboringPointRightDown(point);
  getNeighboringPointRight(point);
  getNeighboringPointLeft(point);
  getNeighboringPointUp(point);
  getNeighboringPointDown(point);
  return _neighbourList;
}

void AStar::getNeighboringPointLeftDown(Point *point) {
  if (point->x > 0 && point->y > 0) {
    if (_allPoints[point->x - 1][point->y - 1]->type != AType::ATYPE_BARRIER) {
      _allPoints[point->x - 1][point->y - 1]->direction = ADirection::INCLINE;
      _neighbourList.push_back(_allPoints[point->x - 1][point->y - 1]);
    }
  }
}
void AStar::getNeighboringPointLeftUp(Point *point) {
  if (point->x > 0 && point->y < MAX_Y - 1) {
    if (_allPoints[point->x - 1][point->y + 1]->type != AType::ATYPE_BARRIER) {
      _allPoints[point->x - 1][point->y + 1]->direction = ADirection::INCLINE;
      _neighbourList.push_back(_allPoints[point->x - 1][point->y + 1]);
    }
  }
}
void AStar::getNeighboringPointRightUp(Point *point) {
  if (point->x < MAX_X - 1 && point->y < MAX_Y - 1) {
    if (_allPoints[point->x + 1][point->y + 1]->type != AType::ATYPE_BARRIER) {
      _allPoints[point->x + 1][point->y + 1]->direction = ADirection::INCLINE;
      _neighbourList.push_back(_allPoints[point->x + 1][point->y + 1]);
    }
  }
}
void AStar::getNeighboringPointRightDown(Point *point) {
  if (point->x < MAX_X - 1 && point->y > 0) {
    if (_allPoints[point->x + 1][point->y - 1]->type != AType::ATYPE_BARRIER) {
      _allPoints[point->x + 1][point->y - 1]->direction = ADirection::INCLINE;
      _neighbourList.push_back(_allPoints[point->x + 1][point->y - 1]);
    }
  }
}

void AStar::getNeighboringPointRight(Point *point) {
  if (point->x < MAX_X - 1) {
    if (_allPoints[point->x + 1][point->y]->type != AType::ATYPE_BARRIER) {
      _allPoints[point->x + 1][point->y]->direction = ADirection::MANHATTAN;
      _neighbourList.push_back(_allPoints[point->x + 1][point->y]);
    }
  }
}

void AStar::getNeighboringPointLeft(Point *point) {
  if (point->x > 0) {
    if (_allPoints[point->x - 1][point->y]->type != AType::ATYPE_BARRIER) {
      _allPoints[point->x - 1][point->y]->direction = ADirection::MANHATTAN;
      _neighbourList.push_back(_allPoints[point->x - 1][point->y]);
    }
  }
}

void AStar::getNeighboringPointUp(Point *point) {
  if (point->y < MAX_Y - 1) {
    if (_allPoints[point->x][point->y + 1]->type != AType::ATYPE_BARRIER) {
      _allPoints[point->x][point->y + 1]->direction = ADirection::MANHATTAN;
      _neighbourList.push_back(_allPoints[point->x][point->y + 1]);
    }
  }
}

void AStar::getNeighboringPointDown(Point *point) {
  if (point->y > 0) {
    if (_allPoints[point->x][point->y - 1]->type != AType::ATYPE_BARRIER) {
      _allPoints[point->x][point->y - 1]->direction = ADirection::MANHATTAN;
      _neighbourList.push_back(_allPoints[point->x][point->y - 1]);
    }
  }
}
