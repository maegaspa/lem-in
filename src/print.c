/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hmichel <hmichel@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/07 15:49:57 by hmichel      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/25 01:05:36 by seanseau    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"
#include <stdio.h>

void			ft_printallpaths(t_tripaths tri, t_bfs bfs)
{
	int		paths;
	int		subs;

	paths = -1;
	while (++paths < bfs.nb_paths)
	{
		subs = -1;
		while (++subs < bfs.end_links)
			ft_putintstr(tri.paths[paths][subs].path, tri.paths[paths][subs].size);
	}
}

void			ft_print_paths(t_tripaths tri, t_bfs bfs, t_map *map)
{
	int paths;
	int subs;
	int	nb_subs;
	int i;
	paths = -1;
	while (++paths < bfs.nb_paths)
	{
		printf("path %d :\n", paths);
		subs = -1;
		nb_subs = get_nb_sub_path(&bfs, paths);
		while (++subs < nb_subs)
		{
			i = tri.paths[paths][subs].size - 1;
			while (i > -1)
			{
				printf("%s ", map->map_name[tri.paths[paths][subs].path[i]]);
				i--;
			}
			printf("\n");
		}
		printf("\n\n");
	}
}

void			ft_putintstr(int *tab, int size)
{
	int		i;

	i = -1;
	while (++i < size)
		printf("%d ", tab[i]);
	printf("\n");
}


void			print_queue(t_bfs *bfs, t_map *map)
{
	int x;
	int y;

	x = 0;
	while (x < bfs->nb_paths)
	{
		printf("queue path[%d] : ", x);
		y = 0;
		while (y < map->inf.size_name)
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

	while (x < map->inf.size_name)
	{
		printf("ROOM[%2s] (step): ", map->map_name[x]);
		y = 0;
		while (y < bfs->nb_paths)
		{
			printf("[%2d]", bfs->mtx_state[x][y]);
			y++;
		}
		printf("\n");
		x++;
	}
}

void		print_matrix_state2(t_bfs *bfs, t_map *map)
{
	int x = map->inf.size_name - 1;
	int y;

	while (x > -1)
	{
		printf("ROOM[%2s] (step): ", map->map_name[x]);
		y = 0;
		while (y < bfs->nb_paths)
		{
			printf("[%2d]", bfs->mtx_state[x][y]);
			y++;
		}
		printf("\n");
		x--;
	}
}

int		pre_path(t_bfs *bfs)
{
	int paths;

	paths = -1;
	if (!(bfs->room_lowest = (int *) malloc(sizeof(int) * bfs->nb_paths)))
		return (0);
	while (++paths < bfs->nb_paths)
		bfs->room_lowest[paths] = 500;
	return (1);
}

int		get_lowest_link(t_bfs *bfs, int actual_room, int path, t_map *map)
{
	int room;
	int lowest_room;
	int step;

	lowest_room = -1;
	step = 500;
	room = 0;
	if (map->matrix[actual_room][bfs->start] > 0)
		return (bfs->start);
	while (room < bfs->size_diago)
	{
		if (map->matrix[actual_room][room] > 0 && bfs->mtx_state[room][path] < step)
		{
			//	printf("link between [%s] and [%s]\n", map->new_name[actual_room], map->new_name[room]);
			//	printf("room %s has step : %d\n", map->new_name[room], bfs->mtx_state[room][path]);
			//	printf("room [%s] on path %d is at step : %d\n", map->new_name[room], path, bfs->mtx_state[room][path]);
			//	printf("room_lowest : %d\n", bfs->room_lowest[path]);
			if (bfs->mtx_state[room][path] > 0 && bfs->mtx_state[room][path] < bfs->room_lowest[path])
			{
				step = bfs->mtx_state[room][path];
				bfs->room_lowest[path] = step;
				lowest_room = room;
			}
		}

		room++;
	}
	return (lowest_room);
}

void	get_path(t_bfs *bfs, int path, t_map *map)
{
	int room_position;
	int	counter = 0;


	room_position = bfs->end;
	printf("[path %d]:", path);
	printf(" %s", map->new_name[bfs->end]);
	while (room_position != bfs->start)
	{
		room_position = get_lowest_link(bfs, room_position, path, map);
		printf(" %s", map->new_name[room_position]);
		counter++;
	}
	printf(" ||%d||", counter);
	printf("\n");
}

void	dig_deep(t_bfs *bfs, t_map *map)
{
	int path;

	path = 0;
	if (!(pre_path(bfs)))
		printf("error\n");
	else
	{
		while (path < bfs->nb_paths)
		{
			get_path(bfs, path, map);
			path++;
		}
	}
}
