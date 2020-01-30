/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bfs4.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hmichel <hmichel@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/20 08:26:29 by hmichel      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/30 00:36:09 by seanseau    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"

int			get_nb_sub_path(t_bfs *bfs, t_temp_paths tp, t_tripaths *tri, int p)
{
	int		i;
	int		count;

	count = 0;
	i = -1;
	while (++i < bfs->end_links)
	{
		if (bfs->mtx_state[tp.sub_ends[i]][p] != -1)
			count++;
	}
	tri->nb_subs[p] = count;
	return (count);
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
	tp->act_path = 0;
	tp->sub_paths = 0;
	tp->i_stp = 0;
	return (SUCCESS);
}

void		get_state_to_path(t_bfs *bfs, t_temp_paths *tp, t_tripaths *tri)
{
	int		prev;
	int		step;
	int		i_state;

	i_state = 0;
	prev = tp->sub_ends[tp->sub_paths];
	step = bfs->mtx_state[tp->sub_ends[tp->sub_paths]][tp->act_path];
	while (--step)
	{
		i_state = -1;
		while (++i_state < bfs->size_diago)
		{
			if (bfs->mtx_state[i_state][tp->act_path] == step &&
					bfs->mtx_diago[i_state][prev])
			{
				tri->paths[tp->act_path][tp->i_stp].path[step] = i_state;
				prev = i_state;
				break ;
			}
		}
	}
}

static int	ft_states_to_paths(t_bfs *bfs, t_tripaths *tri, t_temp_paths *tp)
{
	if (bfs->mtx_state[tp->sub_ends[tp->sub_paths]][tp->act_path] == -1)
		return (SUCCESS);
	tri->paths[tp->act_path][tp->i_stp].size = bfs->mtx_state[tp->sub_ends
		[tp->sub_paths]][tp->act_path] + 2;
	if (!(tri->paths[tp->act_path][tp->i_stp].path = (int *)malloc(sizeof(int)
					* tri->paths[tp->act_path][tp->i_stp].size)))
		return (FAILURE);
	tri->paths[tp->act_path][tp->i_stp].path[tri->paths[tp->act_path]
		[tp->i_stp].size - 1] = bfs->end;
	tri->paths[tp->act_path][tp->i_stp].path[tri->paths[tp->act_path]
		[tp->i_stp].size - 2] = tp->sub_ends[tp->sub_paths];
	get_state_to_path(bfs, tp, tri);
	tri->paths[tp->act_path][tp->i_stp].path[0] = bfs->start;
	tp->i_stp++;
	tri->count_paths++;
	return (SUCCESS);
}

t_tripaths	*ft_takepaths(t_bfs *bfs, t_res *res)
{
	t_temp_paths	tp;
	t_tripaths		*tri;
	int				i;

	i = -1;
	res = NULL;
	if (!ft_sub_ends(bfs, &tp))
		return (NULL);
	if (!ft_init_tripaths(&tri, bfs, tp))
		return (NULL);
	tp.act_path = -1;
	while (++tp.act_path < bfs->nb_paths)
	{
		tp.i_stp = 0;
		tp.sub_paths = -1;
		while (++tp.sub_paths < bfs->end_links)
			if (!ft_states_to_paths(bfs, tri, &tp))
				return (NULL);
	}
	return (tri);
}
