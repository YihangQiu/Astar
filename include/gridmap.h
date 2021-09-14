#ifndef INCLUDE_GRIDMAP_H_
#define INCLUDE_GRIDMAP_H_
#include "astar.h"
#include "display.h"
#include "point.h"

class GridMap {
private:
  //vector<vector<Point *>> map_test;

public:
  GridMap() {}
  ~GridMap() {}
  void createGridMap(char mapdata[MAX_X][MAX_Y]);
  vector<vector<Point *>> map;
  vector<vector<Point *>> map_test;
  void createGridMap(Display &display);

  void modifyResultmap(Point *point, Display &display);



  Point *get_start_point(int x, int y) { return map[x][y]; }
  Point *get_end_point(int x, int y) { return map[x][y]; }

  Point *get_start_point_test(int x, int y) { return map_test[x][y]; }
  Point *get_end_point_test(int x, int y) { return map_test[x][y]; }
  vector<vector<Point *>> get_map_test() { return map_test; }
};

#endif // INCLUDE_GRIDMAP_H_
