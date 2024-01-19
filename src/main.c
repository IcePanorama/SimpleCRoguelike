#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "map.h"
#include "room.h"

int
main (void)
{
  srand (time (0));
  Map *map = create_map ();

  map->rooms = create_rooms (map, 5);
  generate_paths (map);
  // TODO: redo room drawing so rooms don't overlap
  //  add doors to rooms
  //  connect rooms by connection doors

  print_map (map);
  destroy_map (map);

  return 0;
}
