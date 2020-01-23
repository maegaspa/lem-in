/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bfs4.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hmichel <hmichel@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/20 08:26:29 by hmichel      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/23 10:21:46 by hmichel     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"
#include <stdio.h>

static int	ft_init_tripaths(t_tripaths *tri, t_bfs *bfs)
{
	int		i;

	i = -1;
	if  (!(tri = (t_tripaths *)malloc(sizeof(t_tripaths))))
		return (FAILURE);
	if  (!(tri->paths = (t_path **)malloc(sizeof(t_path *) * bfs->nb_paths)))
		return (FAILURE);
	while (++i < bfs->end_links)
		if  (!(tri->paths[i] = (t_path *)malloc(sizeof(t_path) * bfs->end_links)))
			return (FAILURE);
	return (SUCCESS);
}

static int	ft_sub_ends(t_bfs *bfs, t_temp_paths *tp)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!(tp->sub_ends = (int *)malloc(sizeof(int) * bfs->end_links)))
		return (FAILURE);
	while (++i < bfs->size_diago)
	{
		if (bfs->mtx_diago[bfs->end][i])
			tp->sub_ends[++j] = i;
	}
	return (SUCCESS);
}

static int	ft_states_to_paths(t_bfs *bfs, t_tripaths *tri, t_temp_paths tp)
{
	int		step;
	int		prev;
	int		i_state;

	tri->paths[tp.act_path][tp.sub_paths].size = bfs->mtx_state[tp.act_path][tp.sub_ends[tp.sub_paths]] + 2;
	if (!(tri->paths[tp.act_path][tp.sub_paths].path = (int *)malloc(sizeof(int) *
		tri->paths[tp.act_path][tp.sub_paths].size)))
		return (FAILURE);
	step = bfs->mtx_state[tp.act_path][tp.sub_ends[tp.sub_paths]];
	tri->paths[tp.act_path][tp.sub_paths].path[tri->paths[tp.act_path][tp.sub_paths].size - 1] = bfs->end;
	tri->paths[tp.act_path][tp.sub_paths].path[tri->paths[tp.act_path][tp.sub_paths].size - 2] = tp.sub_ends[tp.sub_paths];
	prev = tp.sub_ends[tp.sub_paths];
	while (--step)
	{
		i_state = -1;
		while (++i_state < bfs->size_diago)
		{
			if (bfs->mtx_state[tp.act_path][i_state] == step && bfs->mtx_diago[i_state][prev]) //tester swap ordre conditions pour opti un peu
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

int			ft_takepaths(t_bfs *bfs, t_tripaths *tri)
{
	t_temp_paths tp;

	if (!ft_init_tripaths(tri, bfs))
		return (FAILURE);
	if (!ft_sub_ends(bfs, &tp))
		return (FAILURE);
	ft_putintstr(tp.sub_ends, bfs->end_links);
	tp.act_path = -1;
	while (++tp.act_path < bfs->nb_paths)
	{
		tp.sub_paths = -1;
		while (++tp.sub_paths < bfs->end_links)
			if (!ft_states_to_paths(bfs, tri, tp))
				return (FAILURE);
	}
	return (SUCCESS);
}