/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bfs1.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hmichel <hmichel@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/18 16:13:41 by hmichel      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/19 15:30:57 by hmichel     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/lemin.h"
#include <stdio.h>

int				ft_nb_paths(t_map map)
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
    while (++i < map.inf.size_name)
		if (map.matrix[map.inf.start][i] == 1)
			nb++;
    return (nb);
}

int             ft_init_queue(t_bfs *bfs)
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

int				ft_setprealgo(t_map map, t_bfs *bfs)
{
	int 	i;
	int		j;

	j = -1;
	i = -1;
	bfs->start_paths = ft_nb_paths_start(map);
    bfs->nb_paths = ft_nbpaths_max(map);
	if (!(bfs->mtx_diago = (int **)malloc(sizeof(int *) * map.inf.size_name)))
		return (0);
	while (++i < map.inf.size_name)
	{
		if (!(bfs->mtx_diago[i] = (int *)malloc(sizeof(int) * map.inf.size_name)))
			return (0);
		bfs->mtx_diago[i] = ft_intcpy(bfs->mtx_diago[i], map.matrix[i], map.inf.size_name);
	}
	if (!(bfs->mtx_state = (int **)malloc(sizeof(int *) * map.inf.size_name)))
		return (0);
	while (++j < map.inf.size_name)
	{
		i = -1;
		if (!(bfs->mtx_state[j] = (int *)malloc(sizeof(int) * (bfs->start_paths))))
			return (0);
		while (++i < bfs->start_paths)
			bfs->mtx_state[j][i] = 0;
	}
	bfs->start = map.inf.start;
	bfs->end = map.inf.end;
	bfs->size_diago = map.inf.size_name;
    bfs->founded_paths = 0;
    if (!(ft_init_queue(bfs)))
        return (0);
	return (1);
}   

void            ft_visited(t_bfs *bfs, t_temp_bfs temp, int step)
{
	bfs->mtx_state[bfs->queue[temp.actual_path][++temp.i_queue]][temp.actual_path] = step;
}

int				ft_foundroom(t_bfs *bfs, t_temp_bfs temp, int room)
{
	while (++room < bfs->size_diago)
		if (bfs->mtx_diago[room][bfs->queue[temp.actual_path][temp.i_queue]] == 1
			&& bfs->mtx_state[room][temp.actual_path] == 0)
			return (room);
	return (-1);
}

void			ft_roomto_queue(t_bfs *bfs, t_temp_bfs temp, int room)
{
	int		save_room;
	int		i;

	i = temp.i_queue;
	while (bfs->queue[temp.actual_path][temp.i_queue] != -1) //temp en copie donc pas de modif de l'index dans le temp de foundpaths (500IQ)
		temp.i_queue++;
	bfs->queue[temp.actual_path][temp.i_queue] = room;
}

void			ft_delactual_room(t_bfs *bfs, t_temp_bfs temp)
{
	int		i;
	int		save_room;

	i = 0;
	while (bfs->queue[temp.actual_path][i + 1] != -1)
		i++;
	save_room = bfs->queue[temp.actual_path][i];
	bfs->queue[temp.actual_path][i] = -1;
	bfs->queue[temp.actual_path][temp.i_queue] = save_room;
}

void			ft_setqueue(t_bfs *bfs, t_temp_bfs temp)
{
    int     next_room;

    next_room = -1; //peut-etre useless
	while ((next_room = ft_foundroom(bfs, temp, next_room)) != -1)
    {
		ft_roomto_queue(bfs, temp, next_room);
    }
	ft_delactual_room(bfs, temp);
}

void            ft_foundpaths(t_bfs *bfs, int step)
{
    t_temp_bfs  temp;

    temp.actual_path = 0;
    if (bfs->found_paths == bfs->nb_paths)
        exit;
    while (temp.actual_path < bfs->start_paths)
    {
        temp.i_queue = -1;
        while (bfs->queue[temp.actual_path][++temp.i_queue] != -1)
        {
            ft_visited(bfs, temp, step);
            ft_setqueue(bfs, temp, step);
        }
    }
    ft_foundpaths(bfs, step++);
}

t_res		ft_bfs(t_map map)
{
	t_bfs		bfs;
	t_res		res;

	
}

/*
**	A faire:
**	-gerer la sortie quand on trouve end (enlever de la queue), faire found_paths++ et faire attention a augmenter found_paths une fois max par chemin
**	-fonction bfs mettre NULL en sortie pour teste mtx_stat (plan papier), matrice state et a queue a controler
**	
**
*/