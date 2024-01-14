#ifndef _MAP_H_
#define _MAP_H_

extern const int MAP_LENGTH;

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

typedef struct Map
{
  char **map_chars;
  int num_rooms;
  Room *rooms;
} Map;

Map *create_map (void);
void destroy_map (Map *map);
void print_map (Map *map);
Room *create_rooms (Map *map, int num_rooms);

#endif
