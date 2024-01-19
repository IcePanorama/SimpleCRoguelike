#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "room.h"
#include "util.h"

const int MAX_ROOM_LENGTH = 10;
const int MAX_ROOM_WIDTH = 8;
const int MIN_ROOM_DIM = 5;
const float MIN_ROOM_SPACING = 30.0f;

Room generate_room (void);
float calc_avg_room_spacing (Room *rooms, int num_rooms);
void add_rooms_to_map_chars (Map *map, Room *rooms);
int rooms_equal (Room room1, Room room2);

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
  map->num_rooms = num_rooms;

  // FIXME: fix rooms overlapping
  float room_spacing = 0;
  while (room_spacing < MIN_ROOM_SPACING)
    {
      for (int i = 0; i < map->num_rooms; i++)
        {
          rooms[i] = generate_room ();
        }

      room_spacing = calc_avg_room_spacing (rooms, map->num_rooms);
    }

  add_rooms_to_map_chars (map, rooms);

  return rooms;
}

Room
generate_room (void)
{
  Room new_room;

  new_room.center.x = rand () % MAP_WIDTH;
  new_room.center.y = rand () % MAP_LENGTH;
  new_room.width
      = rand () % (MAX_ROOM_WIDTH - MIN_ROOM_DIM + 1) + MIN_ROOM_DIM;
  new_room.length
      = rand () % (MAX_ROOM_LENGTH - MIN_ROOM_DIM + 1) + MIN_ROOM_DIM;

  return new_room;
}

float
calc_avg_room_spacing (Room *rooms, int num_rooms)
{
  float room_spacing = 0;

  // gonna pretend for the time being that the positioning doesn't matter
  for (int i = 1; i < num_rooms; i++)
    {
      room_spacing += distance (rooms[i].center.x, rooms[i].center.y,
                                rooms[i - 1].center.x, rooms[i - 1].center.y);
    }

  return room_spacing /= num_rooms;
}

// idk if I like this func name
void
add_rooms_to_map_chars (Map *map, Room *rooms)
{
  for (int i = 0; i < map->num_rooms; i++)
    {
      for (int x = rooms[i].center.x - (rooms[i].width / 2);
           x < rooms[i].center.x + (rooms[i].width / 2); x++)
        {
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
    }
}

Room
find_first_room (Room *rooms, int num_rooms)
{
  /* finds the room furthest to the left */
  Room first_room;
  int y = MAP_LENGTH;
  for (int i = 0; i < num_rooms; i++)
    {
      if (rooms[i].center.y < y)
        {
          y = rooms[i].center.y;
          first_room = rooms[i];
        }
    }

  return first_room;
}

// idk if I like this func name either
Room
find_first_room_skip_room (Room *rooms, int num_rooms, Room skip_room)
{
  /* finds the room furthest to the left, but skips given room */
  Room first_room;
  int y = MAP_LENGTH;
  for (int i = 0; i < num_rooms; i++)
    {
      if (rooms_equal (rooms[i], skip_room))
        {
          continue;
        }
      if (rooms[i].center.y < y)
        {
          y = rooms[i].center.y;
          first_room = rooms[i];
        }
    }

  return first_room;
}

int
rooms_equal (Room room1, Room room2)
{
  printf ("x1: %d\tx2: %d\ty1: %d\ty2: %d\n", room1.center.x, room2.center.x,
          room1.center.y, room2.center.y);
  return room1.center.x == room2.center.x && room1.center.y == room2.center.y;
}

Room *
sort_rooms (Map *map, Room *old_rooms)
{
  // FIXME: leaking memory here
  Room *sorted_rooms = malloc (sizeof (Room) * map->num_rooms);
  // Room sorted_rooms[map->num_rooms];
  if (sorted_rooms == NULL)
    {
      puts ("Error allocating sorted rooms.");
      destroy_map (map);
      exit (EXIT_FAILURE);
    }

  sorted_rooms[0] = find_first_room (old_rooms, map->num_rooms);
  for (int i = 1; i < map->num_rooms; i++)
    {
      sorted_rooms[i] = find_first_room_skip_rooms (old_rooms, map->num_rooms,
                                                    sorted_rooms, i);
    }

  // free (old_rooms);
  return sorted_rooms;
}

Room
find_first_room_skip_rooms (Room *rooms, int num_rooms, Room *skip_rooms,
                            int num_skip_rooms)
{
  /* finds the room furthest to the left, but skips given rooms */
  bool shouldSkip = false;
  Room first_room;
  int y = MAP_LENGTH;
  for (int i = 0; i < num_rooms; i++)
    {
      for (int j = 0; j < num_skip_rooms; j++)
        {
          shouldSkip = false;
          if (rooms_equal (rooms[i], skip_rooms[j]))
            {
              shouldSkip = true;
              break;
            }
        }

      if (shouldSkip)
        {
          continue;
        }

      if (rooms[i].center.y < y)
        {
          y = rooms[i].center.y;
          first_room = rooms[i];
        }
    }

  return first_room;
}
