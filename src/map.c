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

  /* Just fills the map with the # character */
  // TODO: replace with ' ' char
  for (int i = 0; i < MAP_WIDTH; i++)
    {
      for (int j = 0; j < MAP_LENGTH; j++)
        {
          new_map->map_chars[i * MAP_WIDTH + j] = '#';
        }
    }

  return new_map;
}

void
destroy_map (Map *map)
{
  free (map->map_chars);
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
