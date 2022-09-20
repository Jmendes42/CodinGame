#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

typedef struct  s_map
{
    int     h;
    int     w;
    int     start_row;
    int     start_col;
    int     n;
    int     map_y;
    char    **map;

}       t_map;

char    **createMap(char **map, int N, int y, int x)
{
    map = malloc(sizeof(char *) * (y * N));
    for (int i = 0; i < (y * N); i++)
        map[i] = malloc(sizeof(char) * x + 1);
    return (map);
}

void    populate_map(t_map *s_map)
{
    s_map->map_y = 0;
    for (int i = 0; i < s_map->n; i++) 
    {
        for (int j = 0; j < s_map->h; j++, s_map->map_y++) 
        {
            char map_row[s_map->w + 1];
            scanf("%[^\n]", map_row); fgetc(stdin);
            s_map->map[s_map->map_y] = strdup(map_row);
            fprintf(stderr, "%s\n", s_map->map[s_map->map_y]);
        }
    }
}

void    init_map(t_map *s_map) 
{
    scanf("%d%d", &s_map->w, &s_map->h);
    scanf("%d%d", &s_map->start_row, &s_map->start_col);
    scanf("%d", &s_map->n); fgetc(stdin);
    s_map->map = createMap(s_map->map, s_map->n, s_map->h, s_map->w);
    populate_map(s_map);
    fprintf(stderr, "w = %d h = %d n = %d\n", s_map->w, s_map->h, s_map->n);
    fprintf(stderr, "start_row = %d start_col = %d\n", s_map->start_row, s_map->start_col);
}

int     step_count(t_map *s_map)
{
    int     answer = -1;
    int     steps_min = INT_MAX;

    for (int i = 0; i < s_map->n; i++)
    {
        int y = s_map->start_row + (s_map->h * i);
        int x = s_map->start_col;
        int steps = 0;
        while (s_map->map[y][x] != 'T')
        {
            if (s_map->map[y][x] == '>')
                x++;
            else if (s_map->map[y][x] == '<')
                x--;
            else if (s_map->map[y][x] == '^')
                y--;
            else if (s_map->map[y][x] == 'v')
                y++;
            else 
            {
                steps = steps_min;
                break ;
            }
            if (y == s_map->start_row + (s_map->h * i) && x == s_map->start_col)
            {
                steps = steps_min;
                break ;
            }
            steps++;
        }
        if (steps < steps_min)
        {
            steps_min = steps;
            answer = i;
        }
    }
    return (answer);
}

int main()
{
    t_map   s_map;
    int     answer = -1;

    init_map(&s_map);
    fprintf(stderr, "%d\n", s_map.map_y);
    answer = step_count(&s_map);
    if (answer != -1)
        printf("%d\n", answer);
    else 
        printf("TRAP\n");
    return 0;
}
