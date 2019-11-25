/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bfs.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: seanseau <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/23 13:25:18 by seanseau     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/25 14:58:09 by seanseau    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

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
				matrix[x][y] = bfs->distance[y];
			y++;
		}
		x++;
	}
	return (matrix);
}

void	begin_bfs(t_map *map, int start_node)
{
	t_bfs	bfs;
	int		x;

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
		remove_node(&bfs);
	}
	map->matrix = change_matrix(map->matrix, map, &bfs);
	reverse_pathfinding(map, &bfs);
}
