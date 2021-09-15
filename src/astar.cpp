#include "astar.h"
#include "point.h"
using std::vector;

bool mySort(const Point *p1, const Point *p2) { return p1->f < p2->f; }

Point *AStar::findWay_test(Point *beginPoint, Point *endPoint,
                           vector<vector<Point *>> &allPoints,
                           Display &display) {
  printf("\e[0;32m[SUCCESS]\033[0m point->findWay(): Finding the shortest path using AStar Algorithms.\n"
         "\e[0;34mThe startpoint:[%d][%d] ---> The endpoint:[%d][%d]\033[0m\n",
         beginPoint->x, beginPoint->y, endPoint->x, endPoint->y);
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
  _openList.push_back(beginPoint);
  beginPoint->type = AType::ATYPE_OPENED;
  beginPoint->f = get_f_octagonal(beginPoint);
  int count = 0;
  do {
    ++count;
    _curPoint = _openList[0];
    printf("\e[0;34mStep %d: point[%d][%d] is selected\033[0m \n", count, _curPoint->x,
           _curPoint->y);
    _openList.erase(_openList.begin());
    _curPoint->type = AType::ATYPE_CLOSED;
    _closeList.push_back(_curPoint);
    if (*_curPoint == *_endPoint) {
      printf("Find way and end searching.\n");
      return _curPoint;
    }
    vector<Point *> neVec = getNeighboringPoint_test(_curPoint, display);
    computeNeighboringValue(neVec, _openList);
    sort(_openList.begin(), _openList.end(), mySort);
  } while (_openList.size() > 0);

  printf("---can not find way---\n");
  return nullptr;
}

vector<Point *> AStar::getNeighboringPoint_test(Point *point,
                                                Display &display) {
  _neighbourList.clear();
  getNeighboringPointRight_test(point, display);
  getNeighboringPointUp_test(point, display);
  getNeighboringPointRightUp_test(point, display);
  getNeighboringPointLeftDown_test(point, display);
  getNeighboringPointLeftUp_test(point, display);
  getNeighboringPointRightDown_test(point, display);
  getNeighboringPointLeft_test(point, display);
  getNeighboringPointDown_test(point, display);
  return _neighbourList;
}

void AStar::getNeighboringPointLeftDown_test(Point *point, Display &display) {
  if (point->x > 0 && point->y > 0) {
    if (_allPoints[point->x - 1][point->y - 1]->type != AType::ATYPE_BARRIER) {
      _allPoints[point->x - 1][point->y - 1]->direction = ADirection::INCLINE;
      _neighbourList.push_back(_allPoints[point->x - 1][point->y - 1]);
    }
  }
}

void AStar::getNeighboringPointLeftUp_test(Point *point, Display &display) {
  if (point->x > 0 && point->y < display.get_y_size() - 1) {
    if (_allPoints[point->x - 1][point->y + 1]->type != AType::ATYPE_BARRIER) {
      _allPoints[point->x - 1][point->y + 1]->direction = ADirection::INCLINE;
      _neighbourList.push_back(_allPoints[point->x - 1][point->y + 1]);
    }
  }
}

void AStar::getNeighboringPointRightUp_test(Point *point, Display &display) {
  if (point->x < display.get_x_size() - 1 &&
      point->y < display.get_y_size() - 1) {
    if (_allPoints[point->x + 1][point->y + 1]->type != AType::ATYPE_BARRIER) {
      _allPoints[point->x + 1][point->y + 1]->direction = ADirection::INCLINE;
      _neighbourList.push_back(_allPoints[point->x + 1][point->y + 1]);
    }
  }
}

void AStar::getNeighboringPointRightDown_test(Point *point, Display &display) {
  if (point->x < display.get_x_size() - 1 && point->y > 0) {
    if (_allPoints[point->x + 1][point->y - 1]->type != AType::ATYPE_BARRIER) {
      _allPoints[point->x + 1][point->y - 1]->direction = ADirection::INCLINE;
      _neighbourList.push_back(_allPoints[point->x + 1][point->y - 1]);
    }
  }
}

void AStar::getNeighboringPointRight_test(Point *point, Display &display) {
  if (point->x < display.get_x_size() - 1) {
    if (_allPoints[point->x + 1][point->y]->type != AType::ATYPE_BARRIER) {
      _allPoints[point->x + 1][point->y]->direction = ADirection::MANHATTAN;
      _neighbourList.push_back(_allPoints[point->x + 1][point->y]);
    }
  }
}

void AStar::getNeighboringPointLeft_test(Point *point, Display &display) {
  if (point->x > 0) {
    if (_allPoints[point->x - 1][point->y]->type != AType::ATYPE_BARRIER) {
      _allPoints[point->x - 1][point->y]->direction = ADirection::MANHATTAN;
      _neighbourList.push_back(_allPoints[point->x - 1][point->y]);
    }
  }
}

void AStar::getNeighboringPointUp_test(Point *point, Display &display) {
  if (point->y < display.get_y_size() - 1) {
    if (_allPoints[point->x][point->y + 1]->type != AType::ATYPE_BARRIER) {
      _allPoints[point->x][point->y + 1]->direction = ADirection::MANHATTAN;
      _neighbourList.push_back(_allPoints[point->x][point->y + 1]);
    }
  }
}

void AStar::getNeighboringPointDown_test(Point *point, Display &display) {
  if (point->y > 0) {
    if (_allPoints[point->x][point->y - 1]->type != AType::ATYPE_BARRIER) {
      _allPoints[point->x][point->y - 1]->direction = ADirection::MANHATTAN;
      _neighbourList.push_back(_allPoints[point->x][point->y - 1]);
    }
  }
}

void AStar::computeNeighboringValue(vector<Point *> &neVec,
                                    vector<Point *> &_openList) {
  for (int i = 0; i < neVec.size(); ++i) {
    auto tmpoint = neVec[i];

    if (tmpoint->type == AType::ATYPE_CLOSED) {
      continue;
    }

    if (tmpoint->type != AType::ATYPE_OPENED) {
      tmpoint->parent = _curPoint;
      if (tmpoint->direction == ADirection::MANHATTAN) {
        tmpoint->g = _curPoint->g + D1;
        printf("point[%d][%d]:\tvalue_G=%d", tmpoint->x, tmpoint->y,
               tmpoint->g);
      } else if (tmpoint->direction == ADirection::INCLINE) {
        tmpoint->g = _curPoint->g + D2;
        printf("point[%d][%d]:\tvalue_G=%d", tmpoint->x, tmpoint->y,
               tmpoint->g);
      }
      tmpoint->h = get_h_octagonal(tmpoint);
      tmpoint->f = get_f_octagonal(tmpoint);
      printf("\tvalue_H=%d\tvalue_F=%d\n", tmpoint->h, tmpoint->f);
      _openList.push_back(tmpoint);
      tmpoint->type = AType::ATYPE_OPENED;
    } else {
      if (tmpoint->h < _curPoint->h) {
        tmpoint->parent = _curPoint;
        if (tmpoint->direction == ADirection::MANHATTAN) {
          tmpoint->g = _curPoint->g + D1;
        } else if (tmpoint->direction == ADirection::INCLINE) {
          tmpoint->g = _curPoint->g + D2;
        }
        tmpoint->f = get_f_octagonal(tmpoint);
      }
      printf("point[%d][%d]:\tvalue_G=%d\tvalue_H=%d\tvalue_F=%d\n",
             tmpoint->x, tmpoint->y, tmpoint->g, tmpoint->h, tmpoint->f);
    }
  }
}
