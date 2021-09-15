#include "display.h"
#include <assert.h>
#include <fstream>
using std::ifstream;

void Display::printInitMap(char map[MAX_X][MAX_Y], const int &width,
                           const int &height) {
  printf("\n(1) Print the status of each node, 1 means passable, 0 means "
         "obstacle. \n");
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      printf("%c\t", map[i][j]);
    }
    printf("\n");
  }
}

void Display::printResultMap(char map[MAX_X][MAX_Y], const int &width,
                             const int &height) {
  printf("\n(4) Print the result map. \n");
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      if (map[i][j] == '*') {
        printf("\e[0;31m%c\t\033[0m", map[i][j]);
      } else {
        printf("%c\t", map[i][j]);
      }
    }
    printf("\n");
  }
}

void Display::parseMapFile() {
  ifstream mapfile("../testcase/map.txt");
  assert(mapfile.is_open());
  std::string line;
  vector<char> tmp;
  while (getline(mapfile, line)) {
    for (auto &word : line) {
      tmp.push_back(word);
    }
    mapdata_test.push_back(tmp);
    tmp.clear();
  }
  max_x = mapdata_test.size();
  max_y = mapdata_test[0].size();
  mapfile.close();
}

void Display::printInitMap() {
  printf("\n(1) Print the status of each node, 1 means passable, 0 means "
         "obstacle. \n");
  for (int i = 0; i < max_x; i++) {
    for (int j = 0; j < max_y; j++) {
      printf("%c\t", mapdata_test[i][j]);
    }
    printf("\n");
  }
}

void Display::printResultMap_test() {
  printf("\n(4) Print the result map. \n");
  for (int i = 0; i < get_x_size(); ++i) {
    for (int j = 0; j < get_y_size(); ++j) {
      if (get_mapdata()[i][j] == '*') {
        printf("\e[0;31m%c\t\033[0m", get_mapdata()[i][j]);
      } else {
        printf("%c\t", get_mapdata()[i][j]);
      }
    }
    printf("\n");
  }
}

void Display::printResultMap_test(Point *point) {
  printf("\n(4) Print the result map. \n");
  for (int i = 0; i < get_x_size(); ++i) {
    for (int j = 0; j < get_y_size(); ++j) {
      if (get_mapdata()[i][j] == '*') {
        printf("\e[0;31m%c\t\033[0m", get_mapdata()[i][j]);
      } else {
        printf("%c\t", get_mapdata()[i][j]);
      }
    }
    printf("\n");
  }
}




// void GridMap::modifyResultmap(Point *point, Display &display) {
//   while (point) {
//     display.get_mapdata()[point->x][point->y] = '*';
//     point = point->parent;
//   }
// }
