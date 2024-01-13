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
  if (rooms == NULL)
    {
      puts ("Error allocating rooms");
      destroy_map (map);
      exit (EXIT_FAILURE);
    }

  for (int i = 0; i < num_rooms; i++)
    {
      // FIXME: the x and y are opposite of what they should be atm
      rooms[i].center.x = rand () % MAP_WIDTH;
      rooms[i].center.y = rand () % MAP_LENGTH;
      rooms[i].width = rand () % MAX_ROOM_WIDTH + MIN_ROOM_DIM;
      rooms[i].length = rand () % MAX_ROOM_LENGTH + MIN_ROOM_DIM;
      printf ("x: %d\ty: %d\n", rooms[i].center.x, rooms[i].center.y);
      printf ("room width: %d\troom len: %d\n", rooms[i].width,
              rooms[i].length);

      if (rooms[i].center.x < 0 || rooms[i].center.x >= MAP_WIDTH
          || rooms[i].center.y < 0 || rooms[i].center.y >= MAP_LENGTH)
        {
          printf ("Error: invalid room dimensions\n");
          destroy_map (map);
          exit (EXIT_FAILURE);
        }

      // int index = coord_to_index (rooms[i].center.x, rooms[i].center.y);
      int center_index = coord_to_index (rooms[i].center.x, rooms[i].center.y);

      int x = center_index - (rooms[i].length / 2);
      while (x < center_index + (rooms[i].length / 2))
        {
          // don't go to the next line
          if (x % MAP_LENGTH == 0)
            {
              break;
            }
          map->map_chars[x] = '.';
          x++;
        }

      /*for (int i = rooms[i].center.x - (rooms[i].length / 2); i >
      rooms[i].center.x + (rooms[i].length / 2); i++)
      {
      }*/

      /*if (index >= 0 && index < MAP_WIDTH * MAP_LENGTH)
        {
          map->map_chars[index] = '.';
        }
      else
        {
          printf ("Error: index out of bounds.\n");
        }*/
    }

  return rooms;
}

int
coord_to_index (int x, int y)
{
  return x * MAP_LENGTH + y;
}
