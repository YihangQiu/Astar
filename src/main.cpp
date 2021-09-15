#include "astar.h"
#include "display.h"
#include "gridmap.h"
#include "point.h"
#include "stdio.h"

int main() {

  Display *display = new Display();
  GridMap *gridmap = new GridMap();
  AStar *star = new AStar();

  display->parseMapFile();
  display->printInitMap();
  gridmap->createGridMap(*display);
  Point *point_test = star->findWay_test(gridmap->get_start_point_test(0, 0),
                                         gridmap->get_end_point_test(3, 7),
                                         gridmap->map_test, *display);
  gridmap->modifyResultmap(point_test, *display); // meibiyao ,直接在print修改
  display->printResultMap_test();

  delete display;
  delete gridmap;
  delete star;
}
