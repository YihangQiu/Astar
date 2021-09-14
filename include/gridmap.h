#ifndef INCLUDE_GRIDMAP_H_
#define INCLUDE_GRIDMAP_H_
#include "astar.h"
#include "display.h"
#include "point.h"

class GridMap {
private:
public:
  GridMap() {}
  ~GridMap() {}
  void createGridMap(char mapdata[MAX_X][MAX_Y]);
  vector<vector<Point *>> map;
  Point *get_start_point(int x, int y) { return map[x][y]; }
  Point *get_end_point(int x, int y) { return map[x][y]; }
  //vector<vector<Point *>> get_map() { return map; }
};

#endif // INCLUDE_GRIDMAP_H_
