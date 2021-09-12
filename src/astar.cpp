//  上下左右走一格花销为10，斜着走一格花销为14，以方便计算
//  即格子宽高为10 对角线为14
#include "astar.h"
#include "point.h"
//自定义排序函数
bool mySort(const GridPoint *p1, const GridPoint *p2) { return p1->f < p2->f; }

#pragma mark------CAstar-------

Astar::Astar() : _endPoint(nullptr), _curPoint(nullptr) {}

Astar::~Astar() {
  _openList.clear();
  _closeList.clear();
  _neighbourList.clear();
  _allPoints.clear();
}

GridPoint *Astar::findWay(GridPoint *beginPoint, GridPoint *endPoint,
                          vector<vector<GridPoint *>> &allPoints) {
  //传递地图
  _allPoints = allPoints;

  _endPoint = endPoint;

  if (_endPoint->type == AType::ATYPE_BARRIER) {
    printf("终点是障碍\n");
    return nullptr;
  }
  if (*_endPoint == *beginPoint) {
    printf("起始点相同\n");
    return nullptr;
  }

  _openList.push_back(beginPoint);
  beginPoint->type = AType::ATYPE_OPENED;
  beginPoint->f = getF(beginPoint);
  //---------
  do {
    //获取最小值的节点
    _curPoint = _openList[0];
    _openList.erase(_openList.begin());
    _curPoint->type = AType::ATYPE_CLOSED;
    _closeList.push_back(_curPoint);

    if (*_curPoint == *_endPoint) {
      printf("have find way\n");
      return _curPoint;
    }
    //获取相邻的节点
    vector<GridPoint *> neVec = getNeighboringPoint(_curPoint);
    for (int i = 0; i < neVec.size(); i++) {
      auto tmpoint = neVec[i];
      if (tmpoint->type == AType::ATYPE_CLOSED) {
        continue;
      }
      //是否在开放列表里
      if (tmpoint->type != AType::ATYPE_OPENED) {
        tmpoint->parent = _curPoint;
        tmpoint->g = _curPoint->g + 10;
        //计算H值
        tmpoint->h = getH(tmpoint);
        //添加到开放列表里
        _openList.push_back(tmpoint);
        tmpoint->type = AType::ATYPE_OPENED;
      } else {
        //已经在开放列表里
        if (tmpoint->h < _curPoint->h) {
          tmpoint->parent = _curPoint;
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

int Astar::getF(GridPoint *point) { return (point->g + getH(point)); }
int Astar::getH(GridPoint *point) {
  //曼哈顿城市街区估算法
  return (abs(_endPoint->y - point->y) + abs(_endPoint->x - point->x)) * 10;
}

vector<GridPoint *> Astar::getNeighboringPoint(GridPoint *point) {
  _neighbourList.clear();
  //    cout<<"nei size:"<<_neighbourList.size()<<endl;
  if (point->x < MAX_X - 1) {
    if (_allPoints[point->x + 1][point->y]->type != AType::ATYPE_BARRIER) {
      _neighbourList.push_back(_allPoints[point->x + 1][point->y]);
    }
  }
  if (point->x > 0) {
    if (_allPoints[point->x - 1][point->y]->type != AType::ATYPE_BARRIER) {
      _neighbourList.push_back(_allPoints[point->x - 1][point->y]);
    }
  }
  if (point->y < MAX_Y - 1) {
    if (_allPoints[point->x][point->y + 1]->type != AType::ATYPE_BARRIER) {
      _neighbourList.push_back(_allPoints[point->x][point->y + 1]);
    }
  }
  if (point->y > 0) {
    if (_allPoints[point->x][point->y - 1]->type != AType::ATYPE_BARRIER) {
      _neighbourList.push_back(_allPoints[point->x][point->y - 1]);
    }
  }

  return _neighbourList;
}
