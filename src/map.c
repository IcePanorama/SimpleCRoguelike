#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "map.h"

const int MAP_LENGTH = 80;
const int MAP_WIDTH = 20;

const int MAX_ROOM_LENGTH = 10;
const int MAX_ROOM_WIDTH = 5;
const int MIN_ROOM_DIM = 5;
const float MIN_ROOM_SPACING = 30.0f;

int coord_to_index (int x, int y);
float distance (int x1, int y1, int x2, int y2);

Map *
create_map (void)
{
  Map *new_map = malloc (sizeof (Map));
  if (new_map == NULL)
    {
      puts ("Error allocating new map.");
      exit (EXIT_FAILURE);
    }

  new_map->map_chars = malloc (sizeof (char *) * MAP_WIDTH);
  if (new_map->map_chars == NULL)
    {
      puts ("Error allocating new map.");
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

Room *
create_rooms (Map *map, int num_rooms)
{
  Room *rooms = malloc (sizeof (Room) * num_rooms);
  if (rooms == NULL)
    {
      puts ("Error allocating rooms");
      destroy_map (map);
      exit (EXIT_FAILURE);
    }

  float room_spacing = 0;
  while (room_spacing < MIN_ROOM_SPACING)
    {
      /* Generate rooms */
      for (int i = 0; i < num_rooms; i++)
        {
          rooms[i].center.x = rand () % MAP_WIDTH;
          rooms[i].center.y = rand () % MAP_LENGTH;
        }

      /* Calc avg room dist */
      room_spacing = 0;

      // gonna pretend for the time being that the order doesn't matter
      for (int i = 1; i < num_rooms; i++)
        {
          room_spacing
              += distance (rooms[i].center.x, rooms[i].center.y,
                           rooms[i - 1].center.x, rooms[i - 1].center.y);
        }
      room_spacing /= num_rooms;
      printf ("room spacing = %f\n", room_spacing);
    }

  /* actually add rooms to map_chars */
  for (int i = 0; i < num_rooms; i++)
    {
      map->map_chars[rooms[i].center.x][rooms[i].center.y] = '.';
    }

  return rooms;
}

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
