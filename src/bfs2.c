/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bfs2.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hmichel <hmichel@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/07 15:51:35 by hmichel      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/07 18:57:35 by hmichel     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"
#include <stdio.h>

int			ft_init_queue(t_bfs *bfs)
{
	int     i;
	int     j;

	i = -1;
	if (!(bfs->queue = (int **)malloc(sizeof(int *) * bfs->start_paths)))
		return (0);
	while (++i < bfs->start_paths)
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
	if (!(bfs->queue[temp.actual_path][temp.i_queue] == bfs->end))
	{
		while (++room < bfs->size_diago)
		{
			if (bfs->mtx_diago[room][bfs->queue[temp.actual_path][temp.i_queue]] == 1)
			{
				if (bfs->mtx_state[room][temp.actual_path] == -1)
					return (room);
			}
		}
	}
	return (-1);
}

void		ft_setqueue(t_bfs *bfs, t_temp_bfs temp)
{
	int		next_room;
	int		path;

	next_room = -1;
	while ((next_room = ft_foundroom(bfs, temp, next_room)) != -1)
		ft_roomto_queue(bfs, temp, next_room);
	path = temp.actual_path;
	ft_delactual_room(bfs, path, temp);
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

void			ft_delactual_room(t_bfs *bfs, int path, t_temp_bfs temp)
{
	int		i;
	int		save_room;

	i = 0;
	while (bfs->queue[temp.actual_path][i + 1] != -1)
		i++;
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

void			ft_roomto_queue(t_bfs *bfs, t_temp_bfs temp, int room)
{
	while (bfs->queue[temp.actual_path][temp.i_queue] != -1) //temp en copie donc pas de modif de l'index dans le temp de foundpaths (500IQ)
		temp.i_queue++;
	if (bfs->queue[temp.actual_path][temp.i_queue - 1] != bfs->end)
	    bfs->queue[temp.actual_path][temp.i_queue] = room;
}