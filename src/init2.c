/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init2.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: seanseau <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/30 16:44:10 by seanseau     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/30 18:17:33 by seanseau    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"

int		init_sort(t_sort *sort, t_res *res)
{
	if (!(sort->new_size_first = malloc(sizeof(int) * res->used_paths)))
		return (0);
	if (!(sort->new_size_second = malloc(sizeof(int) * res->used_paths)))
		return (0);
	if (!(sort->first_path = malloc(sizeof(int*) * res->used_paths)))
		return (0);
	if (!(sort->second_path = malloc(sizeof(int*) * res->used_paths)))
		return (0);
	sort->nb_path_first = 1;
	sort->nb_path_second = 0;
	sort->first_path[0] = res->paths[0];
	sort->new_size_first[0] = res->size_paths[0];
	return (1);
}

void	dis_var(t_dispa *dis, t_map map, t_sort *sort)
{
	dis->reste = map.inf.nb_fourmi % sort->nb_path_first;
	dis->ant_finish = 0;
	dis->ant_cross_max = sort->nb_path_first;
	dis->l = 0;
	dis->tmp = 1;
	dis->ant_cross = 1;
	dis->m = 0;
	dis->n = 0;
	dis->space = 1;
}

int		init_dis(t_dispa *dis, t_map map, t_sort *sort)
{
	if (!(dis->status_path = malloc(sizeof(int) * map.inf.nb_fourmi)))
		return (0);
	if (!(dis->status_ant = malloc(sizeof(int) * map.inf.nb_fourmi)))
		return (0);
	if (!(dis->start_path = malloc(sizeof(int) * sort->nb_path_first)))
		return (0);
	if (!(dis->status_partion = malloc(sizeof(int) * sort->nb_path_first)))
		return (0);
	dis->i = -1;
	while (++dis->i < map.inf.nb_fourmi)
	{
		dis->status_path[dis->i] = -1;
		dis->status_ant[dis->i] = map.inf.start;
	}
	dis->i = -1;
	while (++dis->i < sort->nb_path_first)
	{
		dis->start_path[dis->i] = 0;
		dis->status_partion[dis->i] = 0;
	}
	dis_var(dis, map, sort);
	return (1);
}

int		init_mtx_state(t_bfs *bfs, t_map map)
{
	int i;
	int j;

	j = -1;
	while (++j < map.inf.size_name)
	{
		if (!(bfs->mtx_state[j] = (int *)malloc(sizeof(int) * (bfs->nb_paths))))
			return (FAILURE);
		i = -1;
		while (++i < bfs->nb_paths)
			bfs->mtx_state[j][i] = -1;
	}
	return (SUCCESS);
}
