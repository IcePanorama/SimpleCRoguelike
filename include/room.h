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

#endif
