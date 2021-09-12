#include "point.h"
#include "stdio.h"

GridPoint::GridPoint()
    : x(0), y(0), h(0), f(0), g(0), parent(nullptr),
      type(AType::ATYPE_UNKNOWN) {}
GridPoint::~GridPoint() {}
