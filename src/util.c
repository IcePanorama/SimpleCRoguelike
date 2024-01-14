#include <math.h>

#include "map.h"

int
coord_to_index (int x, int y)
{
  return x * MAP_LENGTH + y;
}

float
distance (int x1, int y1, int x2, int y2)
{
  return sqrt ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
