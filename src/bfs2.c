/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bfs2.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hmichel <hmichel@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/07 15:51:35 by hmichel      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/18 15:48:12 by hmichel     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"
#include <stdio.h>

int			ft_init_queue(t_bfs *bfs)
{
	int     i;
	int     j;

	//printf("\nsize queue = %d * %d\n\n", bfs->start_paths, bfs->size_diago);
	i = -1;
	if (!(bfs->queue = (int **)malloc(sizeof(int *) * bfs->nb_paths)))
		return (0);
	while (++i < bfs->nb_paths)
	{
		j = -1;
		if (!(bfs->queue[i] = (int *)malloc(sizeof(int) * bfs->size_diago)))
			return (0);
		while (++j < bfs->size_diago)
			bfs->queue[i][j] = -1;
		bfs->queue[i][0] = bfs->start;
	}
	return (1);
}

int			ft_foundroom(t_bfs *bfs, t_temp_bfs temp, int room)
{
	while (++room < bfs->size_diago)
	{
		//printf(" %d\n", bfs->queue[temp.actual_path][temp.i_queue]);
		if (bfs->mtx_diago[room][bfs->queue[temp.actual_path][temp.i_queue]] == 1)
		{
			if (bfs->mtx_state[room][temp.actual_path] == -1)
				return (room);
		}
	}
	return (-1);
}

int				ft_size_queue(t_bfs bfs, int path)
{
	int		nb;

	nb = -1;
	while (bfs.queue[path][++nb] != -1)
		;
	return (nb);
}

void			ft_roomto_queue(t_bfs *bfs, t_temp_bfs temp, int room)
{
	while (bfs->queue[temp.actual_path][temp.i_queue] != -1) //temp en copie donc pas de modif de l'index dans le temp de foundpaths (500IQ)
		temp.i_queue++;
	//if (bfs->queue[temp.actual_path][temp.i_queue - 1] != bfs->end)
	bfs->queue[temp.actual_path][temp.i_queue] = room;
}

void			ft_setqueue(t_bfs *bfs, t_temp_bfs temp)
{
	int		next_room;
	int		i;
	int		cancel;

	next_room = -1;
	while ((next_room = ft_foundroom(bfs, temp, next_room)) != -1)
	{
		cancel = 0;
		//printf("appel roomtoqueue next_room = %d\n", next_room);
		if (next_room == bfs->end)
		{
			i = -1;
			while (++i < bfs->nb_paths)
			{
				if (bfs->lock_rooms[i] != -1 && bfs->queue[temp.actual_path][temp.i_queue] == bfs->lock_rooms[i])
					cancel = 1;
				if (bfs->lock_rooms[i] == -1)
				{
					bfs->lock_rooms[i] = bfs->queue[temp.actual_path][temp.i_queue];
				}
			}
		}
		if (!cancel)
			ft_roomto_queue(bfs, temp, next_room);
	}
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

void			ft_del_rooms(t_bfs *bfs, t_temp_bfs temp)
{
	int		i;
	int		y;

	i = -1;
	y = -1;
	while (bfs->queue[temp.actual_path][++i] != -1)
	{
		//printf("i = %d et queue[path][i] = %d\n", i, bfs->queue[temp.actual_path][i]);
		;
	}
	while (++y < temp.size_queue)
	{
		//printf("i + y = %d et y = %d\n", i + y, y);
		bfs->queue[temp.actual_path][y] = bfs->queue[temp.actual_path][i + y - temp.size_queue];
		bfs->queue[temp.actual_path][i + y - temp.size_queue] = -1;
	}
}

void			ft_delactual_room(t_bfs *bfs, int path, t_temp_bfs temp)
{
	int		i;
	int		save_room;

	i = 0;
	while (bfs->queue[temp.actual_path][i + 1] != -1)
		i = i + 1;
	save_room = bfs->queue[temp.actual_path][i];
	bfs->queue[path][i] = -1;
	bfs->queue[temp.actual_path][temp.i_queue] = save_room;
}

void			ft_pre_roomto_queue(t_bfs *bfs, t_temp_bfs temp, int room, int path)
{
	while (bfs->queue[path][temp.i_queue] != -1) //temp en copie donc pas de modif de l'index dans le temp de foundpaths (500IQ)
		temp.i_queue++;
	bfs->queue[path][temp.i_queue] = room;
}

