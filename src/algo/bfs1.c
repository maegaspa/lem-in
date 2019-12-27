/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bfs1.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hmichel <hmichel@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/18 16:13:41 by hmichel      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/27 18:02:32 by seanseau    ###    #+. /#+    ###.fr     */
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
	bfs->nb_paths = ft_nb_paths(map);
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
			bfs->mtx_state[j][i] = -1;
	}
	bfs->start = map.inf.start;
	bfs->end = map.inf.end;
	bfs->size_diago = map.inf.size_name;
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

int				ft_foundroom(t_bfs *bfs, t_temp_bfs temp, int room, t_map *map)
{
	if (!(bfs->queue[temp.actual_path][temp.i_queue] == bfs->end))
	{
		while (++room < bfs->size_diago)
		{
			printf("%s et %s (queue[temp.actual_path = %d][temp.i_queue = %d]) sont-ils lies ?\n", map->map_name[room], map->map_name[bfs->queue[temp.actual_path][temp.i_queue]], temp.actual_path, temp.i_queue);

			if (bfs->mtx_diago[room][bfs->queue[temp.actual_path][temp.i_queue]] == 1)
			{
				printf("oui\n");
				printf("bfs->mtx_state[room(%s)][actual_path(%d)] : %d\n", map->map_name[room], temp.actual_path, bfs->mtx_state[room][temp.actual_path]);
				if (bfs->mtx_state[room][temp.actual_path] == -1)
				{
					return (room);
				}
				//		printf("mais deja visited\n");
			}
		}
	}
	return (-1);
}

void			ft_roomto_queue(t_bfs *bfs, t_temp_bfs temp, int room, t_map *map)
{
	while (bfs->queue[temp.actual_path][temp.i_queue] != -1) //temp en copie donc pas de modif de l'index dans le temp de foundpaths (500IQ)
		temp.i_queue++;
	printf("on ajoute la room [%s] a la queue %d\n", map->map_name[room], temp.actual_path);
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

void			ft_setqueue(t_bfs *bfs, t_temp_bfs temp, t_map *map)
{
	int     next_room;
	int path;

	printf("ft_setqueue : \n");
	next_room = -1;
	while ((next_room = ft_foundroom(bfs, temp, next_room, map)) != -1)
	{
		printf("found room :%d\n", next_room);
		ft_roomto_queue(bfs, temp, next_room, map);
	}
	path = temp.actual_path;
	ft_delactual_room(bfs, path, temp);
}

void			print_queue(t_bfs *bfs, t_map *map)
{
	int x = 0;
	int y;

	printf("\n");
	while (x < bfs->start_paths)
	{
		printf("queue path[%d] (rooms): ", x);
		y = 0;
		while (y < bfs->size_diago)
		{
			printf("[%s]", map->map_name[bfs->queue[x][y]]);
			y++;
		}
		printf("\n");
		x++;
	}
}

void		print_matrix_state(t_bfs *bfs, t_map *map)
{
	int x = 0;
	int y;

	while (x < map->inf.size_name)
	{
		printf("ROOM[%s] (step): ", map->map_name[x]);
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
	int x = 0;
	int path = 0;

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

void			ft_setprematrix(t_bfs *bfs, t_temp_bfs temp, t_map *map)
{
	int	next_room;
	int path;

	path = 0;
	temp.i_queue = 0;
	next_room = -1;
	while ((next_room = ft_foundroom(bfs, temp, next_room, map)) != -1)
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
		ft_setprematrix(bfs, temp, map);
	print_queue(bfs, map);
	print_matrix_state(bfs, map);
	if (!(bfs->found_paths == bfs->nb_paths) && step < map->inf.size_name)
	{
		printf("step : %d // nb_paths = %d // found_paths : %d\n", step, bfs->nb_paths, bfs->found_paths);
		while (temp.actual_path < bfs->start_paths)
		{
			temp.i_queue = 0;
			ft_setqueue(bfs, temp, map);
			//	print_queue(bfs, map);
			ft_visited(bfs, temp, step);
			//	print_matrix_state(bfs, map);
			temp.actual_path++;
		}
		printf("\n");
		ft_foundpaths(bfs, ++step, map);
	}
}

t_bfs	ft_bfs(t_map map)
{
	t_bfs		bfs;
	//	t_res		res;

	ft_setprealgo(map, &bfs);
	ft_foundpaths(&bfs, 2, &map);
	return (bfs);
}

/*
 **	A faire:
 **	-gerer la sortie quand on trouve end (enlever de la queue), faire found_paths++ et faire attention a augmenter found_paths une fois max par chemin
 **	-fonction bfs mettre NULL en sortie pour teste mtx_stat (plan papier), matrice state et a queue a controler
 **	
 **
 */
