#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "room.h"
#include "util.h"

const int MAP_LENGTH = 80;
const int MAP_WIDTH = 20;

Map *
create_map (void)
{
  Map *new_map = malloc (sizeof (Map));
  if (new_map == NULL)
    {
      puts ("Error allocating new map.");
      exit (EXIT_FAILURE);
    }
  new_map->num_rooms = 0;

  new_map->map_chars = malloc (sizeof (char *) * MAP_WIDTH);
  if (new_map->map_chars == NULL)
    {
      puts ("Error allocating map_chars.");
      free (new_map);
      exit (EXIT_FAILURE);
    }

  /* Just fills the map with blank characters */
  for (int i = 0; i < MAP_WIDTH; i++)
    {
      new_map->map_chars[i] = malloc (sizeof (char) * MAP_LENGTH);
      if (new_map->map_chars[i] == NULL)
        {
          printf ("Error allocating line %d of new map.\n", i);
          for (int j = 0; j < i - 1; j++)
            {
              free (new_map->map_chars[j]);
            }
          free (new_map);
          exit (EXIT_FAILURE);
        }

      for (int j = 0; j < MAP_LENGTH; j++)
        {
          new_map->map_chars[i][j] = ' ';
        }
    }

  return new_map;
}

void
destroy_map (Map *map)
{
  for (int i = 0; i < MAP_WIDTH; i++)
    {
      free (map->map_chars[i]);
    }
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
          putchar (map->map_chars[i][j]);
        }
      putchar ('\n');
    }
}

void
generate_paths (Map *map)
{
  Room room1;
  Room room2;

  room1 = find_first_room (map->rooms, map->num_rooms);
  map->map_chars[room1.center.x][room1.center.y] = 'X';

  room2 = find_first_room_skip_room (map->rooms, map->num_rooms, room1);
  map->map_chars[room2.center.x][room2.center.y] = '?';

  // printf ("x dist: %f\ty dist: %f\n", x_dist, y_dist);
  int y = room1.center.y;
  while (y <= room2.center.y)
    {
      // printf ("y: %d\n", y);
      if (map->map_chars[room1.center.x][y] == ' ')
        {
          map->map_chars[room1.center.x][y] = '#';
        }
      y++;
    }

  int x = room1.center.x;
  while (x != room2.center.x)
    {
      // printf ("x: %d\n", x);
      if (map->map_chars[x][y] == ' ')
        {
          map->map_chars[x][y] = '#';
        }
      if (x < room2.center.x)
        {
          x++;
        }
      else
        {
          x--;
        }
    }
}
