#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "map.h"

int
main (void)
{
  srand (time (0));
  Map *map = create_map ();

  map->num_rooms = 5;
  map->rooms = create_rooms (map, map->num_rooms);

  print_map (map);

  destroy_map (map);

  return 0;
}
