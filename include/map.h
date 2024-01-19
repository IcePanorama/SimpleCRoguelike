#ifndef _MAP_H_
#define _MAP_H_

extern const int MAP_LENGTH;
extern const int MAP_WIDTH;

typedef struct Map
{
  char **map_chars;
  int num_rooms;
  struct Room *rooms;
} Map;

Map *create_map (void);
void destroy_map (Map *map);
void print_map (Map *map);
void generate_paths (Map *map);

#endif
