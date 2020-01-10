/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bfs1.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hmichel <hmichel@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/18 16:13:41 by hmichel      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/10 16:25:03 by seanseau    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"
#include <stdio.h>

int				ft_nb_paths(t_map map)
{
	int		i;
	int		nb1;
	int     nb2;

	nb1 = 0;
	nb2 = 0;
	i = -1;
	while (++i < map.mat.size)
		if (map.new_matrix[map.inf.start][i] == 1)
			nb1++;
	i = -1;
	while (++i < map.mat.size)
		if (map.new_matrix[map.inf.end][i] == 1)
			nb2++;
	if (nb1 < nb2)
		return (nb1);
	return (nb2);
}

int             ft_nb_paths_start(t_map map)
{
	int     i;
	int     nb;

	nb = 0;
	i = -1;
	while (++i < map.mat.size)
		if (map.new_matrix[map.inf.start][i] == 1)
			nb++;
	// /printf("nb = %d\n", map.mat.size);
	return (nb);
}

int				ft_setprealgo(t_map map, t_bfs *bfs)
{
	int 	i;
	int		j;

	j = -1;
	i = -1;
	bfs->start_paths = ft_nb_paths_start(map);
	bfs->nb_paths = ft_nb_paths(map);
	if (!(bfs->mtx_diago = (int **)malloc(sizeof(int *) * map.mat.size)))
		return (0);
	while (++i < map.mat.size)
	{
		if (!(bfs->mtx_diago[i] = (int *)malloc(sizeof(int) * map.mat.size)))
			return (0);
		bfs->mtx_diago[i] = ft_intcpy(bfs->mtx_diago[i], map.new_matrix[i], map.mat.size);
	}
	if (!(bfs->mtx_state = (int **)malloc(sizeof(int *) * map.mat.size)))
		return (0);
	while (++j < map.mat.size)
	{
		i = -1;
		if (!(bfs->mtx_state[j] = (int *)malloc(sizeof(int) * (bfs->start_paths))))
			return (0);
		while (++i < bfs->start_paths)
			bfs->mtx_state[j][i] = -1;
	}
	bfs->start = map.inf.start;
	bfs->end = map.inf.end;
	bfs->size_diago = map.mat.size;
	bfs->found_paths = 0;
	if (!(ft_init_queue(bfs)))
		return (0);
	return (1);
}

void            ft_visited(t_bfs *bfs, t_temp_bfs temp, int step)
{
	int node_to_sign;

	temp.i_queue = 0;
	while (bfs->queue[temp.actual_path][temp.i_queue] != -1)
	{
		node_to_sign = bfs->queue[temp.actual_path][temp.i_queue];
		if (bfs->mtx_state[node_to_sign][temp.actual_path] == -1) //sense etre deja fait avec la queue correct
		    bfs->mtx_state[node_to_sign][temp.actual_path] = step;
		if (node_to_sign == bfs->end)
		{
			temp.i_queue = -1;
			while (bfs->queue[temp.actual_path][++temp.i_queue] != -1)
				bfs->queue[temp.actual_path][temp.i_queue] = -1;
			break ;
		}
		temp.i_queue++;
	}
}

void			ft_setprematrix(t_bfs *bfs, t_temp_bfs temp) // a supp
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
	while (path < bfs->start_paths)
	{
		bfs->mtx_state[bfs->start][path] = 0;
		path++;
	}
	remove_room_queue(bfs);
}

int            all_path_done(t_bfs *bfs) //a refaire
{
    int x;

    x = 0;
    while (x < bfs->nb_paths)
    {
        if (bfs->mtx_state[bfs->end][x] == -1)
            return (0);
        x++;
    }
    return(1);
}

void			ft_foundpaths(t_bfs *bfs, int step, t_map *map) // a reprendre
{
	t_temp_bfs  temp;

	temp.actual_path = 0;
	if (step == 2)
		ft_setprematrix(bfs, temp);
    if (all_path_done(bfs) != 1)
	{
		while (temp.actual_path < bfs->start_paths)
		{
			temp.i_queue = 0;
			temp.size_queue = ft_size_queue(*bfs, temp.actual_path);
			while (temp.i_queue < temp.size_queue)
			{
				ft_setqueue(bfs, temp);
				temp.i_queue++;
			}
			ft_del_rooms(bfs, temp);
			ft_visited(bfs, temp, step);
			temp.actual_path++;
		}
//		print_matrix_state(bfs, map);
		//print_queue(bfs, map);
		ft_foundpaths(bfs, ++step, map);
	}
}

t_bfs			ft_bfs(t_map map) // rajouter fonction retrace all_paths
{
	t_bfs		bfs;

	ft_setprealgo(map, &bfs);
	//printf("ET ICI nb_path = %d\n", bfs.nb_paths);
//	print_tab_int(bfs.mtx_diago, map.mat.size, map.mat.size, &map);
	ft_foundpaths(&bfs, 2, &map);
//	print_matrix_state(&bfs, &map);

	dig_deep(&bfs, &map);
	return (bfs);
}

/*
 **	A faire:
 **
 **	
 **
 **
 */