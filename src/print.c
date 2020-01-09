/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hmichel <hmichel@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/07 15:49:57 by hmichel      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/08 17:43:10 by hmichel     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"
#include <stdio.h>


void			print_queue(t_bfs *bfs, t_map *map)
{
	int x;
	int y;

	x = 0;
	while (x < bfs->start_paths)
	{
		printf("queue path[%d] : ", x);
		y = 0;
		while (y < map->mat.size)
		{
			printf("[%d][%d] = %2d,  ", x, y, bfs->queue[x][y]);
			y++;
		}
		printf("\n");
		x++;
	}
}
/*
void			print_queue(t_bfs *bfs, t_map *map)
{
	int y;

	printf("queue path 1 : \n");
	y = 0;
	while (y < map->mat.size)
	{
		printf("  %2d  ", bfs->queue[1][y]);
		y++;
	}
	printf("\n");
}
*/
void		print_matrix_state(t_bfs *bfs, t_map *map)
{
	int x = 0;
	int y;

	while (x < map->mat.size)
	{
		printf("ROOM[%s] (step): ", map->new_name[x]);
		y = 0;
		while (y < bfs->start_paths)
		{
			printf("[%d]", bfs->mtx_state[x][y]);
			y++;
		}
		printf("\n");
		x++;
	}
}

void	print_path(t_bfs *bfs, t_map *map, int path, int max_length)
{
	int x;

	int step = 0;
	while (step != max_length + 1)
	{
		x = 0;
		while (x < map->mat.size)
		{
			if (bfs->mtx_state[x][path] == step)
				printf("|%s|", map->new_name[x]);
			x++;
		}
		step++;
	}
	printf("|%s|\n", map->new_name[bfs->end]);
}

void	dig_deep(t_bfs *bfs, t_map *map)
{
	int y = 0;
	int x;
	int path_max;
	while (y < bfs->start_paths)
	{
		path_max = 0;
		x = 0;
		while (x < map->mat.size)
		{
			if (x != bfs->end && bfs->mtx_state[x][y] > path_max)
				path_max = bfs->mtx_state[x][y];
			x++;
		}
		printf("path_max de path %d : %d\n", y, path_max);
		print_path(bfs, map, y, path_max);
		y++;
	}
}