/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bfs1.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hmichel <hmichel@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/18 16:13:41 by hmichel      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 11:29:26 by cgarrot     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"
#include <stdio.h>

void		ft_visited(t_bfs *bfs, t_temp_bfs temp, int step)
{
	int node_to_sign;

	temp.i_queue = 0;
	while (bfs->queue[temp.actual_path][temp.i_queue] != -1)
	{
		node_to_sign = bfs->queue[temp.actual_path][temp.i_queue];
		bfs->mtx_state[node_to_sign][temp.actual_path] = step;
		temp.i_queue++;
	}
}

void		ft_setprematrix(t_bfs *bfs, t_temp_bfs temp)
{
	int	next_room;
	int path;

	path = 0;
	temp.i_queue = 0;
	next_room = -1;
	while ((next_room = ft_foundroom(bfs, temp, next_room)) != -1)
	{
		ft_pre_roomto_queue(bfs, temp, next_room, path);
		bfs->mtx_state[next_room][path] = 1;
		path++;
	}
	path = 0;
	while (path < bfs->nb_paths)
	{
		bfs->mtx_state[bfs->start][path] = 0;
		path++;
	}
	remove_room_queue(bfs);
}

static int	ft_availablequeue(t_bfs *bfs)
{
	int		i;

	i = -1;
	while (++i < bfs->nb_paths)
		if (bfs->queue[i][0] != -1)
			return (TRUE);
	return (FALSE);
}

void		ft_foundpaths(t_bfs *bfs, int step, t_map *map)
{
	t_temp_bfs	temp;

	temp.actual_path = 0;
	if (step == 2)
		ft_setprematrix(bfs, temp);
	if (bfs->found_paths <= bfs->finish && ft_availablequeue(bfs))
	{
		while (temp.actual_path < bfs->nb_paths)
		{
			temp.i_queue = 0;
			temp.add_queue = 0;
			temp.size_queue = ft_size_queue(*bfs, temp.actual_path);
			while (temp.i_queue < temp.size_queue)
			{
				ft_setqueue(bfs, temp, step);
				temp.i_queue++;
			}
			ft_del_rooms(bfs, temp);
			temp.actual_path++;
		}
		ft_foundpaths(bfs, ++step, map);
	}
}

t_tripaths	ft_bfs(t_map map, t_bfs *bfs, t_tripaths *tri, t_res *res)
{
	tri->count_paths = 0;
	res++;
	ft_setprealgo(map, bfs);
	ft_foundpaths(bfs, 2, &map);
	tri = ft_takepaths(bfs, res);
	return (*tri);
}
