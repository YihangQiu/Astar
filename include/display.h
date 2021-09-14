#ifndef INCLUDE_DISPLAY_H_
#define INCLUDE_DISPLAY_H_

#include "point.h"
#include <stdio.h>
#include <vector>
using std::vector;

//地图最大值
const int MAX_X = 4;
const int MAX_Y = 8;

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

  void printInitMap(char map[MAX_X][MAX_Y], const int &width,
                    const int &height);
  void printResultMap(char map[MAX_X][MAX_Y], const int &width,
                      const int &height);

  void printResultMap_test(Display &display);
};

#endif // INCLUDE_DISPLAY_H_
