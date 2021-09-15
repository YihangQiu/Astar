#include "display.h"
#include <assert.h>
#include <fstream>
using std::ifstream;

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
  printf("\e[0;32m[SUCCESS]\033[0m display->parseMapFile(): Read external files.\n");
}

void Display::printInitMap() {
  printf("\e[0;32m[SUCCESS]\033[0m display->printInitMap(): Print the status of each node, 1 means passable, 0 means obstacle.\n");
  for (int i = 0; i < max_x; ++i) {
    for (int j = 0; j < max_y; ++j) {
      printf("%c\t", mapdata_test[i][j]);
    }
    printf("\n");
  }
}
