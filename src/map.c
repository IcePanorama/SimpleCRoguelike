#include <stdio.h>
#include <stdlib.h>

#include "map.h"

const int MAP_LENGTH = 80;
const int MAP_WIDTH = 20;

Map *
create_map (void)
{
  Map *new_map = malloc (sizeof (Map));
  new_map->map_chars = malloc (sizeof (char *) * MAP_LENGTH * MAP_WIDTH);

  /* Just fills the map with blank characters */
  for (int i = 0; i < MAP_WIDTH; i++)
    {
      for (int j = 0; j < MAP_LENGTH; j++)
        {
          new_map->map_chars[i * MAP_WIDTH + j] = ' ';
        }
    }

  return new_map;
}

void
destroy_map (Map *map)
{
  free (map->map_chars);
  if (map->rooms != NULL)
    {
      free (map->rooms);
    }
  free (map);
}

void
print_map (Map *map)
{
  for (int i = 0; i < MAP_WIDTH; i++)
    {
      for (int j = 0; j < MAP_LENGTH; j++)
        {
          putchar (map->map_chars[i * MAP_WIDTH + j]);
        }
      putchar ('\n');
    }
}

Room *
create_rooms (Map *map, int num_rooms)
{
  Room *rooms = malloc (sizeof (Room) * num_rooms);

  for (int i = 0; i < num_rooms; i++)
    {
      rooms[i].center.x = rand () % (MAP_WIDTH + 1);
      rooms[i].center.y = rand () % (MAP_LENGTH + 1);
      printf ("i: %d\trooms[i].center.x: %d\trooms[i].center.y: %d\n", i,
              rooms[i].center.x, rooms[i].center.y);
      map->map_chars[rooms[i].center.x * MAP_WIDTH + rooms[i].center.y] = '.';
    }

  return rooms;
}
