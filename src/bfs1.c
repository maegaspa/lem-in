/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bfs1.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hmichel <hmichel@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/18 16:13:41 by hmichel      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/24 05:15:21 by hmichel     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"
#include <stdio.h>

void				ft_nb_paths(t_map map, t_bfs *bfs)
{
	int		i;
	int		nb1;
	int     nb2;

	nb1 = 0;
	nb2 = 0;
	i = -1;
	while (++i < map.inf.size_name)
		if (map.matrix[map.inf.start][i] == 1)
			nb1++;
	i = -1;
	while (++i < map.inf.size_name)
		if (map.matrix[map.inf.end][i] == 1)
			nb2++;
	bfs->finish = nb1 * nb2;
	if (nb1 < nb2)
 	{
		bfs->nb_paths = nb1;
		bfs->end_links = nb2;
		bfs->start = map.inf.start;
		bfs->end = map.inf.end;
	}
	else
	{
		bfs->nb_paths = nb2;
		bfs->end_links = nb1;
		bfs->start = map.inf.end;
		bfs->end = map.inf.start;
	}
}

int             ft_nb_paths_start(t_map map)
{
	int     i;
	int     nb;

	nb = 0;
	i = -1;
	while (++i < map.inf.size_name)
		if (map.matrix[map.inf.start][i] == 1)
			nb++;
	// /printf("nb = %d\n", map.inf.size_name);
	return (nb);
}

int				ft_setprealgo(t_map map, t_bfs *bfs)
{
	int 	i;
	int		j;

	j = -1;
	i = -1;
	ft_nb_paths(map, bfs);
	if (!(bfs->mtx_diago = (int **)malloc(sizeof(int *) * map.inf.size_name)))
		return (FAILURE);
	while (++i < map.inf.size_name)
	{
		if (!(bfs->mtx_diago[i] = (int *)malloc(sizeof(int) * map.inf.size_name)))
			return (FAILURE);
		bfs->mtx_diago[i] = ft_intcpy(bfs->mtx_diago[i], map.matrix[i], map.inf.size_name);
	}
	if (!(bfs->mtx_state = (int **)malloc(sizeof(int *) * map.inf.size_name)))
		return (FAILURE);
	while (++j < map.inf.size_name)
	{
		i = -1;
		if (!(bfs->mtx_state[j] = (int *)malloc(sizeof(int) * (bfs->nb_paths))))
			return (FAILURE);
		while (++i < bfs->nb_paths)
			bfs->mtx_state[j][i] = -1;
	}
	bfs->size_diago = map.inf.size_name;
	bfs->found_paths = 0;
	if (!(ft_init_queue(bfs)))
		return (FAILURE);
	return (SUCCESS);
}

void            ft_visited(t_bfs *bfs, t_temp_bfs temp, int step)
{
	int node_to_sign;

	temp.i_queue = 0;
	while (bfs->queue[temp.actual_path][temp.i_queue] != -1)
	{
		node_to_sign = bfs->queue[temp.actual_path][temp.i_queue];
		if (bfs->mtx_state[node_to_sign][temp.actual_path] == -1)
		    bfs->mtx_state[node_to_sign][temp.actual_path] = step;
		if (node_to_sign == bfs->end)
		{
			bfs->found_paths++;
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
	while (path < bfs->nb_paths)
	{
		bfs->mtx_state[bfs->start][path] = 0;
		path++;
	}
	remove_room_queue(bfs);
}
/*
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
*/
static int		ft_availablequeue(t_bfs *bfs)
{
	int		i;

	i = -1;
	while (++i < bfs->nb_paths)
		if (bfs->queue[i][0] != -1)
			return (TRUE);
	return (FALSE);
}

void			ft_foundpaths(t_bfs *bfs, int step, t_map *map) // a reprendre
{
	t_temp_bfs  temp;

	temp.actual_path = 0;
	if (step == 2)
		ft_setprematrix(bfs, temp);
	//print_queue(bfs, map);
	//printf("\n");
	//print_matrix_state(bfs, map);
	//printf("\n");
    if (bfs->found_paths <= bfs->finish && ft_availablequeue(bfs))//if (all_path_done(bfs) != 1)
	{
		while (temp.actual_path < bfs->nb_paths)
		{
			temp.i_queue = 0;
			temp.size_queue = ft_size_queue(*bfs, temp.actual_path);
			while (temp.i_queue < temp.size_queue)
			{
				//print_queue(bfs, map);
				ft_setqueue(bfs, temp);
				temp.i_queue++;
			}
			//print_queue(bfs, map);
			//printf("\n");
			ft_del_rooms(bfs, temp);
			//print_queue(bfs, map);
			//printf("\n");
			ft_visited(bfs, temp, step);
			temp.actual_path++;
		}
		//print_queue(bfs, map);
		ft_foundpaths(bfs, ++step, map);
	}
	//ft_freequeue(bfs);
}

int			ft_bfs(t_map map, t_bfs *bfs, t_tripaths *tri) // rajouter fonction retrace all_paths
{
	//int 		i;
	//int 		j;

	if (!ft_setprealgo(map, bfs))
		return (FAILURE);
	//printf("ET ICI nb_path = %d\n", bfs.nb_paths);
//	print_tab_int(bfs.mtx_diago, map.inf.size_name, map.inf.size_name, &map);
	ft_foundpaths(bfs, 2, &map);
	if (bfs->start == map.inf.start)
		print_matrix_state(bfs, &map);
	else
		print_matrix_state2(bfs, &map);
	if (!ft_takepaths(bfs, tri))
		return (FAILURE);
	//dig_deep(&bfs, &map);
	//ft_init_res(bfs, res, &map);
	printf("OUI\n");
	//dig_deep1(bfs, &map, res);
	//i = -1;
	//while (++i < bfs->nb_paths)
	//{
	//	j = -1;
	//	while (++j < res->size_paths[i] + 1)
	//	{
	//		printf("%d ", res->paths[i][j]);
	//	}
	//	printf("\n");
	//}
	return (1);
}

/*
 **	A faire:
 **
 **	CLEAN SORTIE ERREUR
 **
 **
 */
