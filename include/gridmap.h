#ifndef INCLUDE_GRIDMAP_H_
#define INCLUDE_GRIDMAP_H_
#include "astar.h"
#include "display.h"
#include "point.h"

namespace data {
class GridMap {
private:
  // vector<vector<Point *>> map_test;

public:
  GridMap() {}
  ~GridMap() {}
  vector<vector<Point *>> map_test;
  void createGridMap(Display &display);
  void printResultMap(Point *point, Display &display);
  Point *get_start_point_test(int x, int y) { return map_test[x][y]; }
  Point *get_end_point_test(int x, int y) { return map_test[x][y]; }
  vector<vector<Point *>> get_map_test() { return map_test; }
};

} // namespace data

#endif // INCLUDE_GRIDMAP_H_
