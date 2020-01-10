/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hmichel <hmichel@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/07 15:49:57 by hmichel      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/10 18:57:39 by seanseau    ###    #+. /#+    ###.fr     */
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

int		pre_path(t_bfs *bfs)
{
	int room;

	room = -1;
	while (++room < bfs->size_diago)
	{
		if (!(bfs->room_lowest = (int *) malloc(sizeof(int) * 1)))
			return (0);
	}
	room = -1;
	while (++room < bfs->size_diago)
		bfs->room_lowest[room] = 500;
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
	if (map->new_matrix[actual_room][bfs->start] > 0)
		return (bfs->start);
	while (room < bfs->size_diago)
	{
		if (map->new_matrix[actual_room][room] > 0 && bfs->mtx_state[room][path] < step)
		{
			//	printf("link between [%s] and [%s]\n", map->new_name[actual_room], map->new_name[room]);
			//	printf("room [%s] on path %d is at step : %d\n", map->new_name[room], path, bfs->mtx_state[room][path]);
			if (bfs->mtx_state[room][path] > 0 && bfs->mtx_state[room][path] < bfs->room_lowest[room])
			{
				step = bfs->mtx_state[room][path];
				bfs->room_lowest[room] = step;
				lowest_room = room;
			}
		}
		room++;
	}
	return (lowest_room);
}


/*void	add_to_path(t_bfs *bfs, int room, int path)
  {

  }*/

void	get_path(t_bfs *bfs, int path, t_map *map)
{
	int room_position;
	int cancel = 0;
	int	counter = 0;


//	int clone_inutile_print;

	room_position = bfs->end;
	printf("path %d:", path);
	//	add_to_path(bfs, bfs->end, path);
	while (room_position != bfs->start)
	{
		if (room_position == bfs->end)
		{
			room_position = get_lowest_link(bfs, room_position, path, map);
			if (room_position != -1)
			{
				printf(" %s", map->new_name[bfs->end]);
			}
			else
			{
				cancel = 1;
				printf("CANCELLED\n");
				room_position = bfs->start;
			}
		}
		else
			room_position = get_lowest_link(bfs, room_position, path, map);
		if (cancel != 1)//found a room
		{
		// add_to_path(bfs, room_position, path);
			printf("\t%s", map->new_name[room_position]);
		}
		counter++;
	}
	if (cancel != 1)
		printf("\t\t||%d||", counter);
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
		while (path < bfs->start_paths)
		{
			get_path(bfs, path, map);
			path++;
		}
	}
}
