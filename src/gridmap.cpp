#include "gridmap.h"

void GridMap::createGridMap(Display &display) {
  for (int i = 0; i < display.get_x_size(); ++i) {
    vector<Point *> tmp;
    for (int j = 0; j < display.get_y_size(); ++j) {
      Point *point = new Point();
      point->x = i;
      point->y = j;
      if (display.get_mapdata()[i][j] == '0') {
        point->type = AType::ATYPE_BARRIER;
      }
      tmp.push_back(point);
    }
    map_test.push_back(tmp);
  }
  printf("\n(2) Initialize the coordinates, type, cost, "
         "and parent pointer of each node. \n");
}

void GridMap::modifyResultmap(Point *point, Display &display) {
  while (point) {
    display.get_mapdata()[point->x][point->y] = '*';
    point = point->parent;
  }
}
