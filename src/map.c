#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "room.h"
#include "util.h"

const int MAP_LENGTH = 80;
const int MAP_WIDTH = 20;

int draw_hor_path (Map *map, Vec2 start_pos, Vec2 end_pos, int x);
void draw_vert_path (Map *map, Vec2 end_pos, int x, int y);

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

  room2 = find_first_room_skip_room (map->rooms, map->num_rooms, room1);

  int x = room1.center.x;
  int y = draw_hor_path (map, room1.center, room2.center, x);
  // temp to prevent unused type Werror
  printf ("y: %d\n", y);

  draw_vert_path (map, room2.center, x, y);
}

int
draw_hor_path (Map *map, Vec2 start_pos, Vec2 end_pos, int x)
{
  int y = start_pos.y;
  while (y <= end_pos.y)
    {
      if (map->map_chars[x][y] == ' ')
        {
          map->map_chars[x][y] = '#';
        }
      y++;
    }
  return y - 1;
}

void
draw_vert_path (Map *map, Vec2 end_pos, int x, int y)
{
  while (x != end_pos.x)
    {
      if (map->map_chars[x][y] == ' ')
        {
          map->map_chars[x][y] = '#';
        }
      if (x < end_pos.x)
        {
          x++;
        }
      else
        {
          x--;
        }
    }
}
