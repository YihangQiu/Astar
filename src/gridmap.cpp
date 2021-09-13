#include "gridmap.h"

 void GridMap::createGridMap(char mapdata[MAX_X][MAX_Y]) {
    for (int i = 0; i < MAX_X; ++i) {
      vector<Point *> tmp;
      for (int j = 0; j < MAX_Y; ++j) {
        Point *point = new Point();
        point->x = i;
        point->y = j;
        if (mapdata[i][j] == '0') {
          point->type = AType::ATYPE_BARRIER;
        }
        tmp.push_back(point);
      }
      map.push_back(tmp);
    }
    printf("\n(2) Initialize the coordinates, type, cost, "
           "and parent pointer of each node. \n");
  }
