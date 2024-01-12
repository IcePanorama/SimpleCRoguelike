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
  Room *rooms = malloc (sizeof (Room) * num_rooms);

  for (int i = 0; i < num_rooms; i++)
    {
      rooms[i].center.x = rand () % (MAP_WIDTH);
      rooms[i].center.y = rand () % (MAP_LENGTH);

      if (rooms[i].center.x < 0 || rooms[i].center.x >= MAP_WIDTH
          || rooms[i].center.y < 0 || rooms[i].center.y >= MAP_LENGTH)
        {
          printf ("Error: invalid room dimensions\n");
          destroy_map (map);
          exit (EXIT_FAILURE);
        }

      int index = rooms[i].center.x * MAP_LENGTH + rooms[i].center.y;

      if (index >= 0 && index < MAP_WIDTH * MAP_LENGTH)
        {
          map->map_chars[index] = '.';
        }
      else
        {
          printf ("Error: index out of bounds.\n");
        }
    }

  return rooms;
}
