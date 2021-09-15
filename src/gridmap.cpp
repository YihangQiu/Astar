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
  printf("\e[0;32m[SUCCESS]\033[0m gridmap->createGridMap(): Initialize the "
         "coordinates, type, cost and parent pointer of each node. \n");
}

void GridMap::printResultMap(Point *point, Display &display) {
  while (point) {
    point->type = AType::ATYPE_PATH;
    point = point->parent;
  }
  printf("\e[0;32m[SUCCESS]\033[0m gridmap->printResultmap(): Print the "
         "result map.\n");
  for (int i = 0; i < display.get_x_size(); ++i) {
    for (int j = 0; j < display.get_y_size(); ++j) {
      if (map_test[i][j]->type == AType::ATYPE_PATH) {
        printf("\e[1;31m*\t\033[0m");
      } else {
        printf("%c\t", display.get_mapdata()[i][j]);
      }
    }
    printf("\n");
  }
}
