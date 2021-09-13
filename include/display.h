#ifndef INCLUDE_DISPLAY_H_
#define INCLUDE_DISPLAY_H_

#include "point.h"
#include <stdio.h>
//地图最大值
const int MAX_X = 4;
const int MAX_Y = 8;

class Display {
private:
public:
  Display(){};
  ~Display(){};
  void printInitMap(char map[MAX_X][MAX_Y], const int &width,
                    const int &height);
  void printResultMap(char map[MAX_X][MAX_Y], const int &width,
                      const int &height);
};

#endif // INCLUDE_DISPLAY_H_
