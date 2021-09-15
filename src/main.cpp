#include "astar.h"
#include "display.h"
#include "gridmap.h"
#include "point.h"

int main() {

  resource::Display *display = new resource::Display();
  GridMap *gridmap = new GridMap();
  AStar *star = new AStar();

  display->parseMapFile();
  display->printInitMap();
  gridmap->createGridMap(*display);
  Point *point_test = star->findWay_test(gridmap->get_start_point_test(0, 0),
                                         gridmap->get_end_point_test(3, 7),
                                         gridmap->map_test, *display);
  gridmap->printResultMap(point_test, *display);

  delete display;
  delete gridmap;
  delete star;
}
