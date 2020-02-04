#include "../include/lemin.h"
#include <stdio.h>

void		free_all(t_bfs *bfs, t_map *map, t_res *res)
{
	int i;

	i = -1;
	while (++i < bfs->nb_paths)
		free(bfs->queue[i]);
	i = -1;
	while (++i < map->inf.size_link)
		free(map->map_link[i]);
	i = -1;
	while (++i < res->used_paths)
		free(res->paths[i]);
	i = -1;
	while (++i < map->inf.size_name)
	{
		free(bfs->mtx_diago[i]);
		free(bfs->mtx_state[i]);
		free(map->matrix[i]);
		free(map->map_name[i]);
		free(map->map_co[i]);
	}
	free(res->paths);
	free(res->size_paths);
	free(bfs->mtx_diago);
	free(bfs->mtx_state);
	free(map->matrix);
	free(map->map_co);
	free(map->map_link);
	free(map->map_name);
	free(bfs->queue);
	bfs->mtx_diago = NULL;
	bfs->mtx_state = NULL;
	bfs->queue = NULL;
	map->matrix = NULL;
	res->paths = NULL;
}

//
//void 	free_matrix(t_map *map)
//{
//	int i;
//
//	i = -1;
//	while (map->map_name[++i])
//		ft_strdel(&map->map_name[i]);
//	free(&map->map_name);
//	i = -1;
//	while (map->map_link[++i])
//		ft_strdel(&map->map_link[i]);
//	free(&map->map_link);
//	i = -1;
//	while (++i < map->inf.size_name)
//		free(&map->matrix[i]);
//	free(&map->matrix);
//}