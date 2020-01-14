/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bfs3.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hmichel <hmichel@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 02:54:34 by hmichel      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/14 08:23:40 by hmichel     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"
#include <stdio.h>

int				ft_init_res(t_bfs *bfs, t_res *res, t_map *map)
{
	int i;
	int k;
	int	j;
	int l;

	i = -1;
	if (!(res->size_paths = (int*)malloc(sizeof(int) * bfs->nb_paths)))
		return (0);
	if (!(res->paths = (int **)malloc(sizeof(int *) * bfs->nb_paths)))
		return (0);
	if (!(res->rank_size = (int*)malloc(sizeof(int) * bfs->nb_paths)))
		return (0);
	if (bfs->start == map->inf.start)
		k = bfs->start;
	else
		k = bfs->end;
	while (++i < bfs->nb_paths)
	{
		res->size_paths[i] = bfs->mtx_state[k][i];
		res->rank_size[i] = i;
	}
	l = -1;
	if (bfs->nb_paths > 2)
	{
		while (++l < bfs->nb_paths)
		{
			j = -1;
			while (++j < bfs->nb_paths)
				if ((j + 1 < bfs->nb_paths) && res->size_paths[j] > res->size_paths[j + 1])
				{
					ft_swap(&(res->size_paths[j]), &(res->size_paths[j + 1]));
					ft_swap(&(res->rank_size[j]), &(res->rank_size[j + 1]));
				}
		}
	}
	l = -1;
	while (++l < bfs->nb_paths)
		printf("%d ", res->rank_size[l]);
	i = -1;
	while (++i < bfs->nb_paths)
		if (!(res->paths[i] = (int *)malloc(sizeof(int) * res->size_paths[i] + 1)))
			return (0);
	return (0);
}

int		pre_path1(t_bfs *bfs)
{
	int paths;

	paths = -1;
	if (!(bfs->room_lowest = (int *) malloc(sizeof(int) * bfs->nb_paths)))
		return (0);
	while (++paths < bfs->nb_paths)
		bfs->room_lowest[paths] = 500;
	return (1);
}

int		get_lowest_link1(t_bfs *bfs, int actual_room, int path, t_map *map)
{
	int room;
	int lowest_room;
	int step;

	lowest_room = -1;
	step = 500;
	room = 0;
	if (map->new_matrix[actual_room][bfs->start] > 0)
		return (bfs->start);
	while (room < bfs->size_diago)
	{
		if (map->new_matrix[actual_room][room] > 0 && bfs->mtx_state[room][path] < step)
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

void	get_path1(t_bfs *bfs, int path, t_map *map, t_res *res)
{
	int room_position;
	int	counter = 0;
	int i;
	int 	tmp;

	room_position = bfs->end;
	printf("[path %d]:", path);
	printf(" %s", map->new_name[bfs->end]);
	while (room_position != bfs->start)
	{
		room_position = get_lowest_link1(bfs, room_position, path, map);
		i = -1;
		while (++i < bfs->nb_paths)
		{
			if (path == res->rank_size[i])
				tmp = i;
		}
		if (counter == 0)
		{
			res->paths[tmp][counter] = map->inf.start;
			counter++;
		}
		res->paths[tmp][counter] = room_position;
		//printf(" %d", res->paths[path][counter]);
		printf(" %s", map->new_name[room_position]);
		counter++;
	}
	printf(" ||%d||", counter);
	printf("\n");
}

void	dig_deep1(t_bfs *bfs, t_map *map, t_res *res)
{
	int path;

	path = 0;
	if (!(pre_path1(bfs)))
		printf("error\n");
	else
	{
		while (path < bfs->nb_paths)
		{
			get_path1(bfs, path, map, res);
			path++;
		}
	}
}