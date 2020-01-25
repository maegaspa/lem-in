#include "../include/lemin.h"
#include <stdio.h>

/*void 	free_all(t_map *map, t_res *res, t_bfs *bfs)
{

}*/

void 	free_matrix(t_map *map)
{
	int i;

	i = -1;
	while (map->map_name[++i])
		ft_strdel(&map->map_name[i]);
	free(&map->map_name);
	i = -1;
	while (map->map_link[++i])
		ft_strdel(&map->map_link[i]);
	free(&map->map_link);
	i = -1;
	while (++i < map->inf.size_name)
		free(&map->matrix[i]);
	free(&map->matrix);
}