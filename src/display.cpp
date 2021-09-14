#include "display.h"

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

// void Display::modifyResultMap(Point *point, char mapdata[MAX_X][MAX_Y]) {
//   printf("\n----下面是路径点(倒序)-----\n");
//   // while (point) {
//   //   mapdata[point->x][point->y] = '*';
//   //   printf("%d,%d\n", point->x, point->y);
//   //   point = point->parent;
// }
