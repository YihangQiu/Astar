#include "astar.h"
#include "display.h"
#include "gridmap.h"
#include "point.h"
#include "stdio.h"

int main() {

  char mapdata[MAX_X][MAX_Y] = {
      {'1', '1', '1', '1', '0', '0', '0', '0'},
      {'1', '1', '1', '1', '1', '0', '0', '0'},
      {'0', '0', '1', '0', '0', '1', '1', '1'},
      {'0', '1', '1', '1', '1', '1', '1', '1'},
  };
  Display *display = new Display();
  GridMap *gridmap = new GridMap();
  AStar *star = new AStar();

  display->printInitMap(mapdata, MAX_X, MAX_Y);
  gridmap->createGridMap(mapdata);
  Point *point = star->findWay(gridmap->get_start_point(0, 0),
                               gridmap->get_end_point(3, 7), gridmap->map);
  while (point) {
    mapdata[point->x][point->y] = '*';
    point = point->parent;
  }
  display->printResultMap(mapdata, MAX_X, MAX_Y);

  delete display;
  delete gridmap;
  delete star;
}
