/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   display_algo.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hmichel <hmichel@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/28 21:22:47 by hmichel      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/30 18:09:04 by seanseau    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"

int				partition_eq_dispache(t_dispa *d, t_map map, t_sort *sort)
{
	if (d->i < map.inf.nb_fourmi && (!(d->status_ant[d->i] == map.inf.start)))
		d->j = d->status_path[d->i];
	else
	{
		d->q = 0;
		d->p = 0;
		while (d->q < sort->nb_path_first)
		{
			if (d->start_path[d->q] == 0 && d->j != d->q &&
					d->status_partion[d->q] != sort->dispache[d->q])
			{
				d->p = 1;
				d->j = d->q;
				break ;
			}
			d->q++;
		}
		if (d->p != 1)
		{
			d->m = 1;
			d->i++;
			return (-1);
		}
	}
	return (1);
}

void			display_print2(t_dispa *dis, t_sort *sort, t_map map)
{
	while (dis->k < sort->new_size_first[dis->j])
	{
		if ((dis->i < map.inf.nb_fourmi) && sort->first_path[dis->j][dis->k] ==
	dis->status_ant[dis->i] && sort->first_path[dis->j][dis->k] != map.inf.end)
		{
			print_space(dis);
			if (dis->status_ant[dis->i] == map.inf.start)
			{
				dis->start_path[dis->n] = 1;
				dis->ant_cross++;
				dis->n++;
			}
			if (dis->status_ant[dis->i] == map.inf.start)
				dis->status_partion[dis->j]++;
			dis->status_ant[dis->i] = sort->first_path[dis->j][dis->k + 1];
			dis->status_path[dis->i] = dis->j;
			last_ant_finish(dis, sort, map);
			ft_printf("L%d-%s", dis->i + 1,
					map.map_name[dis->status_ant[dis->i]]);
			break ;
		}
		dis->k++;
	}
}

void			display_print(t_dispa *dis, t_sort *sort, t_map map)
{
	dis->m = 0;
	dis->i = 0;
	while (dis->i < dis->ant_cross_max)
	{
		dis->j = 0;
		dis->n = 0;
		while (dis->j < sort->nb_path_first)
		{
			if (dis->status_partion[dis->j] == sort->dispache[dis->j])
				if (partition_eq_dispache(dis, map, sort) == -1)
					break ;
			dis->k = 0;
			display_print2(dis, sort, map);
			dis->i++;
			dis->j++;
		}
		if (dis->i % sort->nb_path_first == 0)
			if (dis->i == sort->nb_path_first * dis->tmp && dis->tmp <=
					map.inf.nb_fourmi)
				dis->tmp++;
		if (dis->m == 1)
			break ;
	}
}

int				dispache_ant(t_map map, t_sort *sort, int nb_ligne)
{
	t_dispa		dis;

	if (init_dis(&dis, map, sort) != 1)
		return (-1);
	while (dis.l < nb_ligne)
	{
		if ((dis.tmp * sort->nb_path_first) <= map.inf.nb_fourmi)
			dis.ant_cross_max = dis.tmp * sort->nb_path_first;
		if (dis.ant_cross + dis.ant_finish == map.inf.nb_fourmi - dis.reste + 1)
			dis.ant_cross_max += dis.reste;
		display_print(&dis, sort, map);
		dis.p = 0;
		while (dis.p < sort->nb_path_first)
		{
			dis.start_path[dis.p] = 0;
			dis.p++;
		}
		ft_printf("\n");
		dis.space = 1;
		dis.l++;
	}
	free(dis.status_ant);
	free(dis.status_path);
	free(dis.start_path);
	free(dis.status_partion);
	free(sort->new_size_first);
	free(sort->new_size_second);
	return (0);
}

int				display_algo(t_map map, t_res *res)
{
	t_sort	sort;
	int		i;
	int		nb_line;

	if (clear_path2(res, &sort) != 1)
		return (-1);
	if (!(sort.dispache = malloc(sizeof(int) * sort.nb_path_first)))
		return (-1);
	i = -1;
	while (++i < sort.nb_path_first)
		sort.dispache[i] = 0;
	nb_line = nb_ant_int_path(map, &sort, 0, 0);
	dispache_ant(map, &sort, nb_line);
	ft_printf("Number of lines required: %d | Number of lines done: %d\n",
			map.line_expected, nb_line);
	free(sort.dispache);
    free(sort.first_path);
    free(sort.second_path);
	return (0);
}
