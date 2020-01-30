/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   set_pre.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: seanseau <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/29 23:33:46 by seanseau     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/30 01:20:20 by seanseau    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"

int		ft_setprealgo(t_map map, t_bfs *bfs)
{
	int		i;
	int		j;

	ft_nb_paths(map, bfs);
	if (!(bfs->mtx_diago = (int **)malloc(sizeof(int *) * map.inf.size_name)))
		return (FAILURE);
	if (!(bfs->mtx_state = (int **)malloc(sizeof(int *) * map.inf.size_name)))
		return (FAILURE);
	i = -1;
	while (++i < map.inf.size_name)
	{
		if (!(bfs->mtx_diago[i] = (int *)malloc(sizeof(int) * map.inf.size_name)))
			return (FAILURE);
		bfs->mtx_diago[i] = ft_intcpy(bfs->mtx_diago[i], map.matrix[i], map.inf.size_name);
	}
	j = -1;
	while (++j < map.inf.size_name)
	{
		if (!(bfs->mtx_state[j] = (int *)malloc(sizeof(int) * (bfs->nb_paths))))
			return (FAILURE);
		i = -1;
		while (++i < bfs->nb_paths)
			bfs->mtx_state[j][i] = -1;
	}
	bfs->size_diago = map.inf.size_name;
	bfs->found_paths = 0;
	if (!(ft_init_queue(bfs)))
		return (FAILURE);
	return (SUCCESS);
}

void	ft_setprematrix(t_bfs *bfs, t_temp_bfs temp)
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

void	ft_pre_roomto_queue(t_bfs *bfs, t_temp_bfs temp, int room, int path)
{
	while (bfs->queue[path][temp.i_queue] != -1)
		temp.i_queue++;
	bfs->queue[path][temp.i_queue] = room;
}

void	ft_setqueue(t_bfs *bfs, t_temp_bfs temp, int step)
{
	int		next_room;

	next_room = -1;
	while ((next_room = ft_foundroom(bfs, temp, next_room)) != -1)
	{
		if (next_room == bfs->end)
			bfs->found_paths++;
		else
		{
			bfs->mtx_state[next_room][temp.actual_path] = step;
			ft_roomto_queue(bfs, temp, next_room);
		}
	}
}
