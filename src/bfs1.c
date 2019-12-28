/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bfs1.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hmichel <hmichel@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/18 16:13:41 by hmichel      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/28 15:50:16 by seanseau    ###    #+. /#+    ###.fr     */
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
		bfs->mtx_state[node_to_sign][temp.actual_path] = step;
		temp.i_queue++;
	}
}

int				ft_foundroom(t_bfs *bfs, t_temp_bfs temp, int room)
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

void			ft_roomto_queue(t_bfs *bfs, t_temp_bfs temp, int room)
{
	while (bfs->queue[temp.actual_path][temp.i_queue] != -1) //temp en copie donc pas de modif de l'index dans le temp de foundpaths (500IQ)
		temp.i_queue++;
	bfs->queue[temp.actual_path][temp.i_queue] = room;
}

void			ft_delactual_room(t_bfs *bfs, int path, t_temp_bfs temp)
{
	int		i;
	int		save_room;

	i = 0;
	while (bfs->queue[path][i + 1] != -1)
		i++;
	save_room = bfs->queue[path][i];
	bfs->queue[path][i] = -1;
	bfs->queue[path][temp.i_queue] = save_room;
}

void			ft_setqueue(t_bfs *bfs, t_temp_bfs temp)
{
	int		next_room;
	int		path;

	next_room = -1;
	while ((next_room = ft_foundroom(bfs, temp, next_room)) != -1)
		ft_roomto_queue(bfs, temp, next_room);
	path = temp.actual_path;
	ft_delactual_room(bfs, path, temp);
}

void			print_queue(t_bfs *bfs, t_map *map)
{
	int x;
	int y;

	map->inf.start = map->inf.start;
	x = 0;
	while (x < bfs->start_paths)
	{
//		printf("queue path[%d] (rooms): ", x);
		y = 0;
		while (y < bfs->size_diago)
		{
//			printf("[%s]", map->new_name[bfs->queue[x][y]]);
			y++;
		}
//		printf("\n");
		x++;
	}
}

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

void			ft_pre_roomto_queue(t_bfs *bfs, t_temp_bfs temp, int room, int path)
{
	while (bfs->queue[path][temp.i_queue] != -1) //temp en copie donc pas de modif de l'index dans le temp de foundpaths (500IQ)
		temp.i_queue++;
	bfs->queue[path][temp.i_queue] = room;
}

void			ft_setprematrix(t_bfs *bfs, t_temp_bfs temp)
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

void			ft_foundpaths(t_bfs *bfs, int step, t_map *map)
{
	t_temp_bfs  temp;

	temp.actual_path = 0;
	if (step == 2)
		ft_setprematrix(bfs, temp);
//	print_queue(bfs, map);
//	printf("\n");
//	print_matrix_state(bfs, map);
//	printf("\n");

	if (!(bfs->found_paths == bfs->nb_paths) && step < map->mat.size)
	{
		while (temp.actual_path < bfs->start_paths)
		{
			temp.i_queue = 0;
			ft_setqueue(bfs, temp);
			ft_visited(bfs, temp, step);
			temp.actual_path++;
		}
		ft_foundpaths(bfs, ++step, map);
	}
}

void	print_path(t_bfs *bfs, t_map *map, int path, int max_length)
{
	int x;

	int step = 0;
	while (step != max_length + 1)
	{
		x = 0;
		while (x < map->mat.size)
		{
			if (bfs->mtx_state[x][path] == step)
				printf("|%s|", map->new_name[x]);
			x++;
		}
		step++;
	}
	printf("|%s|\n", map->new_name[bfs->end]);
}

void	dig_deep(t_bfs *bfs, t_map *map)
{
	int y = 0;
	int x;
	int path_max;
	while (y < bfs->start_paths)
	{
		path_max = 0;
		x = 0;
		while (x < map->mat.size)
		{
			if (x != bfs->end && bfs->mtx_state[x][y] > path_max)
				path_max = bfs->mtx_state[x][y];
			x++;
		}
		printf("path_max de path %d : %d\n", y, path_max);
		print_path(bfs, map, y, path_max);
		y++;
	}
}

t_bfs	ft_bfs(t_map map)
{
	t_bfs		bfs;

	ft_setprealgo(map, &bfs);
//	print_tab_int(bfs.mtx_diago, map.mat.size, map.mat.size, &map);
	ft_foundpaths(&bfs, 2, &map);
	print_matrix_state(&bfs, &map);

//	dig_deep(&bfs, &map);
	return (bfs);
}

/*
 **	A faire:
 **	-gerer la sortie quand on trouve end (enlever de la queue), faire found_paths++ et faire attention a augmenter found_paths une fois max par chemin
 **	-fonction bfs mettre NULL en sortie pour teste mtx_stat (plan papier), matrice state et a queue a controler
 **	
 **
 */
