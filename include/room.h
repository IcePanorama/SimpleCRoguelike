#ifndef _ROOM_H_
#define _ROOM_H_

typedef struct Vec2
{
  int x;
  int y;
} Vec2;

typedef struct Room
{
  Vec2 center;
  int length;
  int width;
} Room;

Room *create_rooms (Map *map, int num_rooms);
Room find_first_room (Room *rooms, int num_rooms);
Room find_first_room_skip_room (Room *rooms, int num_rooms, Room skip_room);
Room find_first_room_skip_rooms (Room *rooms, int num_rooms, Room *skip_rooms,
                                 int num_skip_rooms);
Room *sort_rooms (Map *map, Room *old_rooms);

#endif
