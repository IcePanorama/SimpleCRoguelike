#ifndef _MAP_H_
#define _MAP_H_

typedef struct Map
{
  char *map_chars;
} Map;

Map *create_map (void);
void destroy_map (Map *map);
void print_map (Map *map);

#endif
