#include <stdio.h>
#include <stdlib.h>

#include "map.h"

const int MAP_LENGTH = 80;
const int MAP_WIDTH = 20;

const int MAX_ROOM_LENGTH = 10;
const int MAX_ROOM_WIDTH = 5;
const int MIN_ROOM_DIM = 5;

int coord_to_index (int x, int y);

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
      exit (EXIT_FAILURE);
    }

  /* Just fills the map with blank characters */
  for (int i = 0; i < MAP_WIDTH; i++)
    {
      new_map->map_chars[i] = malloc (sizeof (char) * MAP_LENGTH);
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
  // for testing
  putchar (' ');
  char letter = 'A';
  for (int i = 0; i < MAP_LENGTH; i++)
    {
      printf ("%c", letter++);
      if (letter > 'z')
        {
          letter = 'A';
        }
    }
  putchar ('\n');

  letter = 'A';
  for (int i = 0; i < MAP_WIDTH; i++)
    {
      printf ("%c", letter++);
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

  for (int i = 0; i < num_rooms; i++)
    {
      map->map_chars[0][0] = '.';                          // top left
      map->map_chars[0][MAP_LENGTH - 1] = '.';             // top right
      map->map_chars[MAP_WIDTH - 1][MAP_LENGTH - 1] = '.'; // bot right
      map->map_chars[MAP_WIDTH - 1][0] = '.';              // bot left
    }

  return rooms;
}

int
coord_to_index (int x, int y)
{
  return x * MAP_LENGTH + y;
}
