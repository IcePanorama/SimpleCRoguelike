#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "map.h"

int
main (void)
{
  // srand (time (0));
  srand (1);
  Map *map = create_map ();

  // print_map (map);

  map->num_rooms = 1;
  map->rooms = create_rooms (map, map->num_rooms);
  printf ("map->rooms[0].center.x: %d\n", map->rooms[0].center.x);
  printf ("map->rooms[0].center.y: %d\n", map->rooms[0].center.y);

  print_map (map);

  destroy_map (map);

  return 0;
}
