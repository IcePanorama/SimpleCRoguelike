#include <stdio.h>
#include <stdlib.h>

#include "map.h"

const int MAP_LENGTH = 80;
const int MAP_WIDTH = 20;

Map *
create_map (void)
{
  Map *new_map = malloc (sizeof (Map));
  new_map->map_chars = malloc (sizeof (char) * MAP_LENGTH * MAP_WIDTH);

  /* Just fills the map with blank characters */
  for (int i = 0; i < MAP_WIDTH; i++)
    {
      for (int j = 0; j < MAP_LENGTH; j++)
        {
          new_map->map_chars[i * MAP_LENGTH + j] = '#'; //' ';
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
          putchar (map->map_chars[i * MAP_LENGTH + j]);
        }
      putchar ('\n');
    }
}

Room *
create_rooms (Map *map, int num_rooms)
{
  printf ("num_rooms: %d\n", num_rooms);

  Room *rooms = malloc (sizeof (Room) * num_rooms);

  rooms[0].center.x = 3;
  rooms[0].center.y = 3;

  if (rooms[0].center.x < 0 || rooms[0].center.x >= MAP_WIDTH
      || rooms[0].center.y < 0 || rooms[0].center.y >= MAP_LENGTH)
    {
      printf ("Error: invalid room dimensions\n");
      destroy_map (map);
      exit (EXIT_FAILURE);
    }

  int index = rooms[0].center.x * MAP_LENGTH + rooms[0].center.y;

  if (index >= 0 && index < MAP_WIDTH * MAP_LENGTH)
    {
      map->map_chars[index] = '.';
    }
  else
    {
      printf ("Error: index out of bounds.\n");
    }

  return rooms;
}
