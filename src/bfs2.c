/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bfs2.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hmichel <hmichel@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/07 15:51:35 by hmichel      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 23:45:26 by seanseau    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"
#include <stdio.h>

int			ft_foundroom(t_bfs *bfs, t_temp_bfs temp, int room)
{
	int		tmp;

	tmp = temp.actual_path;
	while (++room < bfs->size_diago)
	{
		if (bfs->mtx_diago[room][bfs->queue[tmp][temp.i_queue]] == 1)
		{
			if (bfs->mtx_state[room][tmp] == -1)
				return (room);
		}
	}
	return (-1);
}

int			ft_size_queue(t_bfs bfs, int path)
{
	int		nb;

	nb = -1;
	while (bfs.queue[path][++nb] != -1)
		;
	return (nb);
}

void		ft_roomto_queue(t_bfs *bfs, t_temp_bfs temp, int room)
{
	while (bfs->queue[temp.actual_path][temp.size_queue] != -1)
		temp.size_queue++;
	bfs->queue[temp.actual_path][temp.size_queue] = room;
}

void		remove_room_queue(t_bfs *bfs)
{
	int x;
	int path;

	path = 0;
	while (path < bfs->nb_paths)
	{
		x = 0;
		while (x < bfs->nb_paths)
		{
			bfs->queue[path][x] = bfs->queue[path][x + 1];
			x++;
		}
		path++;
	}
}

void		ft_del_rooms(t_bfs *bfs, t_temp_bfs temp)
{
	int		i;
	int		y;

	i = temp.size_queue - 1;
	y = -1;
	while (bfs->queue[temp.actual_path][++i] != -1)
		;
	if (i < 2 * temp.size_queue - 1)
	{
		while (++y < temp.size_queue)
		{
			bfs->queue[temp.actual_path][y] = bfs->queue[temp.actual_path]
				[temp.size_queue + y];
			bfs->queue[temp.actual_path][temp.size_queue + y] = -1;
		}
	}
	else
	{
		while (++y < temp.size_queue)
		{
			bfs->queue[temp.actual_path][y] = bfs->queue[temp.actual_path]
				[i + y - temp.size_queue];
			bfs->queue[temp.actual_path][i + y - temp.size_queue] = -1;
		}
	}
}
