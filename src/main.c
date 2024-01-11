#include <stdio.h>
#include <stdlib.h>

#include "map.h"

int
main (void)
{
  Map *map = create_map ();
  print_map (map);
  return 0;
}
