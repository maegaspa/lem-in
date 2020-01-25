/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bfs4.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hmichel <hmichel@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/20 08:26:29 by hmichel      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/25 01:13:30 by seanseau    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"
#include <stdio.h>
/*
   static int	ft_init_tripaths(t_tripaths *tri, t_bfs *bfs)
   {
   int		i;
   int		j;

   i = -1;
   if (!(tri = (t_tripaths *)malloc(sizeof(t_tripaths))))
   return (FAILURE);
   if (!(tri->paths = (t_path **)malloc(sizeof(t_path *) * bfs->nb_paths)))
   return (FAILURE);
   while (++i < bfs->end_links)
   {
   j = -1;
   if (!(tri->paths[i] = (t_path *)malloc(sizeof(t_path) * bfs->end_links)))
   return (FAILURE);
   while (++j < bfs->end_links)
   {
   tri->paths[i][j].path = NULL;
   tri->paths[i][j].size = 0;
   }
   }
   return (SUCCESS);
   }*/

static int	ft_sub_ends(t_bfs *bfs, t_temp_paths *tp)
{
	int		room;
	int		j;
	int		path;


	if (!(tp->sub_ends = (int **)malloc(sizeof(int *) * bfs->nb_paths)))
		return (FAILURE);
	path = -1;
	while (++path < bfs->nb_paths)
	{
		if (!(tp->sub_ends[path] = (int *)malloc(sizeof(int) * bfs->end_links)))
			return (FAILURE);
		room = -1;
		j = -1;
		while (++room < bfs->size_diago)
		{
			if (bfs->mtx_diago[bfs->end][room] && bfs->mtx_state[room][path] != -1)
				tp->sub_ends[path][++j] = room;
		}
	}
	return (SUCCESS);
}

static int	ft_states_to_paths(t_bfs *bfs, t_tripaths *tri, t_temp_paths tp)
{
	int		step;
	int		prev;
	int		i_state;

	//	printf("bfs->mtx_state[tp.sub_ends[tp.sub_paths]][tp.act_path] = %d et tp.sub_ends[tp.sub_paths] = %d\n", bfs->mtx_state[tp.sub_ends[tp.sub_paths]][tp.act_path], tp.sub_ends[tp.sub_paths]);
	tri->paths[tp.act_path][tp.sub_paths].size = bfs->mtx_state[tp.sub_ends[tp.act_path][tp.sub_paths]][tp.act_path] + 2; //setting subpath length based on step at before-end room
//	printf("Sub path %d of path %d : size : %d || ends with room n.%d\n", tp.sub_paths, tp.act_path, tri->paths[tp.act_path][tp.sub_paths].size, tp.sub_ends[tp.act_path][tp.sub_paths]);
	//	printf("tp.act_path = %d, tp.sub_paths = %d, tri->paths[tp.act_path][tp.sub_paths].size = %d\n", tp.act_path, tp.sub_paths, tri->paths[tp.act_path][tp.sub_paths].size);
	if (!(tri->paths[tp.act_path][tp.sub_paths].path = (int *)malloc(sizeof(int) *
					tri->paths[tp.act_path][tp.sub_paths].size)))
		return (FAILURE);
	step = bfs->mtx_state[tp.sub_ends[tp.act_path][tp.sub_paths]][tp.act_path];
//	printf("step in room n.%d : %d\n", tp.sub_ends[tp.act_path][tp.sub_paths], step);
//	printf("bfs->end : %d\n", bfs->end);
	tri->paths[tp.act_path][tp.sub_paths].path[tri->paths[tp.act_path][tp.sub_paths].size - 1] = bfs->end; //set last room of subpath to bfs->end
	tri->paths[tp.act_path][tp.sub_paths].path[tri->paths[tp.act_path][tp.sub_paths].size - 2] = tp.sub_ends[tp.act_path][tp.sub_paths]; //set before-last room of subpath to pre-ending room on this sub
	prev = tp.sub_ends[tp.act_path][tp.sub_paths]; //prev = pre ending room on this sub
	while (--step)
	{
		i_state = -1;
		while (++i_state < bfs->size_diago)
		{
			if (bfs->mtx_state[i_state][tp.act_path] == step && bfs->mtx_diago[i_state][prev]) //tester swap ordre conditions pour opti un peu
			{
				tri->paths[tp.act_path][tp.sub_paths].path[step] = i_state;
				prev = i_state;
				break ;
			}
		}
	}
	tri->paths[tp.act_path][tp.sub_paths].path[0] = bfs->start;
	return (SUCCESS);
}

int			get_nb_sub_path(t_bfs *bfs, int path_nb)
{
	int room = -1;
	int count = 0;

	while (++room < bfs->size_diago)
	{
		if (bfs->mtx_diago[room][bfs->end] == 1)
		{
			if (bfs->mtx_state[room][path_nb] != -1)
				count++;
		}
	}
	return (count);
}

int			ft_takepaths(t_bfs *bfs, t_tripaths *tri, t_map *map)
{
	t_temp_paths tp;
	int		i;
	int		j;

	int nb_sub_path;


	i = -1;
	if (!(tri = (t_tripaths *)malloc(sizeof(t_tripaths))))
		return (FAILURE);
	if (!(tri->paths = (t_path **)malloc(sizeof(t_path *) * bfs->nb_paths)))
		return (FAILURE);
	while (++i < bfs->end_links)
	{
		j = -1;
		if (!(tri->paths[i] = (t_path *)malloc(sizeof(t_path) * bfs->end_links)))
			return (FAILURE);
		while (++j < bfs->end_links)
		{
			tri->paths[i][j].path = NULL;
			tri->paths[i][j].size = 0;
		}
	}
	//if (!ft_init_tripaths(tri, bfs))
	//	return (FAILURE);
	if (!ft_sub_ends(bfs, &tp))
		return (FAILURE);
//	ft_putintstr(tp.sub_ends, bfs->end_links);
	tp.act_path = -1;
	while (++tp.act_path < bfs->nb_paths)
	{
		nb_sub_path = get_nb_sub_path(bfs, tp.act_path);
		printf("\t\tpath |%d| - nb_sub_path %d\n", tp.act_path, nb_sub_path);
		tp.sub_paths = -1;
		while (++tp.sub_paths < nb_sub_path)
			if (!ft_states_to_paths(bfs, tri, tp))
				return (FAILURE);
	}
//	ft_printallpaths(*tri, *bfs);

	ft_print_paths(*tri, *bfs, map);
	return (SUCCESS);
}
