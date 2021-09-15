#ifndef INCLUDE_DISPLAY_H_
#define INCLUDE_DISPLAY_H_

#include "point.h"
#include <stdio.h>
#include <vector>
using std::vector;

class Display {
private:
  int max_x = 0;
  int max_y = 0;
  vector<vector<char>> mapdata_test;
  // vector<vector<Point *>> map_test;

public:
  Display(){};
  ~Display(){};

  void parseMapFile();
  int get_x_size() { return max_x; }
  int get_y_size() { return max_y; }
  vector<vector<char>> &get_mapdata() { return mapdata_test; }
  void printInitMap();
  void printResultMap_test();
};

#endif // INCLUDE_DISPLAY_H_
