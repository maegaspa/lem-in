#include "../include/lemin.h"
#include <stdio.h>

int		*malloc_int_tab(int size)
{
	int	*tab;
	int x;

	x = 0;
	if (!(tab = (int *)malloc(sizeof(int) * size)))
		return (0);
	while (x != size)
	{
		tab[x] = -1;
		x++;
	}
	return (tab);
}

void	remove_node(t_bfs *bfs)
{
	int x;

	x = 0;
	while (x != bfs->q_size)
	{
		bfs->queue[x] = bfs->queue[x + 1];
		x++;
	}
	bfs->q_size--;
}

void	add_node(t_bfs *bfs, int node)
{
	bfs->queue[bfs->q_size] = node;
	bfs->q_size++;
}

void	init_bfs(t_map *map, t_bfs *bfs, int start_node)
{
	bfs->visited = malloc_int_tab(map->inf.size_name);
	bfs->distance = malloc_int_tab(map->inf.size_name);
	bfs->queue = malloc_int_tab(map->inf.size_name);
	bfs->q_size = 0;
	bfs->visited[start_node] = 1;
	bfs->distance[start_node] = 0;
	add_node(bfs, start_node);
	bfs->tab_next = malloc_int_tab(map->inf.size_name);
	bfs->tab_next_size = 0;
	bfs->paths = paths_malloc(map);
	bfs->saved_path = malloc_int_tab(map->inf.size_name);
	bfs->paths[0][0] = map->inf.end;
	bfs->tab_next[0] = map->inf.end;

}

int		**change_matrix(int **matrix, t_map *map, t_bfs *bfs)
{
	int		x;
	int		y;

	x = 0;
	while (x < map->inf.size_name)
	{
		y = 0;
		while (y < map->inf.size_name)
		{
			if (matrix[x][y] == 1)
			{
				if (bfs->distance[y] == 0)
					bfs->distance[y] = 1;
				matrix[x][y] = bfs->distance[y];
			}
			y++;
		}
		x++;
	}
	return (matrix);
}

void	begin_bfs(t_map *map, int start_node)
{
	t_bfs	bfs;
	t_path  path;
	int		x;

//	int		**path_tab;



	init_bfs(map, &bfs, start_node);
	while (bfs.queue[0] != map->inf.end)
	{
		x = 0;
		while (x != map->inf.size_name)
		{
			if (map->matrix[bfs.queue[0]][x] == 1 && bfs.visited[x] == -1 &&
					bfs.distance[x] <= bfs.distance[bfs.queue[0]] + 1)
			{
				bfs.visited[x] = 1;
				bfs.distance[x] = bfs.distance[bfs.queue[0]] + 1;
				add_node(&bfs, x);
			}
			x++;
		}
		//printf("\n");
		remove_node(&bfs);
	}
//	print_tab_int(map->matrix, map->inf.size_name, map->inf.size_name);
	map->matrix = change_matrix(map->matrix, map, &bfs);
	//printf("\n");
	reverse_pathfinding(map, &bfs, &path);
}