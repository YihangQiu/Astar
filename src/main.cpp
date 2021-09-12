#include "astar.h"
#include "point.h"
#include "stdio.h"

void printMap(char map[MAX_X][MAX_Y], int width, int height) {
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      printf("%c\t", map[i][j]);
    }
    printf("\n");
  }
}

int main(int argc, char *argv[]) {
  printf("----map----\n");
  //初始化地图矩阵 0代表障碍
  char mapdata[MAX_X][MAX_Y] = {
      {'1', '1', '1', '1', '0', '0', '0', '0'},
      {'1', '1', '1', '1', '1', '0', '0', '0'},
      {'0', '0', '1', '0', '0', '1', '1', '1'},
      {'0', '1', '1', '1', '1', '1', '1', '1'},
  };

  printMap(mapdata, MAX_X, MAX_Y);
  
  //创建地图
  vector<vector<GridPoint *>> map;
  for (int i = 0; i < MAX_X; i++) {
    vector<GridPoint *> tmp;
    for (int j = 0; j < MAX_Y; j++) {
      GridPoint *point = new GridPoint();
      point->x = i;
      point->y = j;
      if (mapdata[i][j] == '0') {
        point->type = AType::ATYPE_BARRIER;
      }
      tmp.push_back(point);
    }
    map.push_back(tmp);
  }

  //开始寻路
  Astar *star = new Astar();
  auto point = star->findWay(map[0][0], map[3][7], map);

  if (!point) {
    return 0;
  }

  printf("----下面是路径点(倒序)-----\nx,y\n");

  while (point) {
    mapdata[point->x][point->y] = '*';
    printf("%d,%d\n", point->x, point->y);
    point = point->parent;
  }
  printf("---打印路径---\n");
  printMap(mapdata, MAX_X, MAX_Y);

  //-------------释放内存----------
  delete star;
  for (int i = 0; i < MAX_X; i++) {
    for (int j = 0; j < MAX_Y; j++) {
      delete map[i][j];
      map[i][j] = nullptr;
    }
  }

  return 0;
}
