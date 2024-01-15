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

  Room room = find_first_room (map->rooms, map->num_rooms);
  printf ("-- First room\nx: %d\ty: %d\n", room.center.x, room.center.y);
  map->map_chars[room.center.x][room.center.y] = 'X';

  print_map (map);
  destroy_map (map);

  return 0;
}
