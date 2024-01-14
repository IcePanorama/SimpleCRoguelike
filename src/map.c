#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "map.h"

const int MAP_LENGTH = 80;
const int MAP_WIDTH = 20;

const int MAX_ROOM_LENGTH = 10;
const int MAX_ROOM_WIDTH = 8;
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

// TODO: Refactor
Room *
create_rooms (Map *map, int num_rooms)
{
  Room *rooms = malloc (sizeof (Room) * num_rooms);
  if (rooms == NULL)
    {
      puts ("Error allocating rooms.");
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
          rooms[i].width
              = rand () % (MAX_ROOM_WIDTH - MIN_ROOM_DIM + 1) + MIN_ROOM_DIM;
          rooms[i].length
              = rand () % (MAX_ROOM_LENGTH - MIN_ROOM_DIM + 1) + MIN_ROOM_DIM;
        }

      /* Calc avg distance between rooms */
      room_spacing = 0;
      // gonna pretend for the time being that the positioning doesn't matter
      for (int i = 1; i < num_rooms; i++)
        {
          room_spacing
              += distance (rooms[i].center.x, rooms[i].center.y,
                           rooms[i - 1].center.x, rooms[i - 1].center.y);
        }
      room_spacing /= num_rooms;
    }

  /* actually add rooms to map_chars */
  for (int i = 0; i < num_rooms; i++)
    {
      printf ("x: %d, y: %d\n", rooms[i].center.x, rooms[i].center.y);
      printf ("width: %d, len: %d\n", rooms[i].width, rooms[i].length);
      for (int x = rooms[i].center.x - (rooms[i].width / 2);
           x < rooms[i].center.x + (rooms[i].width / 2); x++)
        {
          // where the issue is
          if (x < 0 || x > MAP_WIDTH - 1)
            {
              continue;
            }
          for (int y = rooms[i].center.y - (rooms[i].length / 2);
               y < rooms[i].center.y + (rooms[i].length / 2); y++)
            {
              if (y < 0 || y > MAP_LENGTH - 1)
                {
                  continue;
                }
              map->map_chars[x][y] = '.';
            }
        }
      map->map_chars[rooms[i].center.x][rooms[i].center.y] = '@';
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
