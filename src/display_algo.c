/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   display_algo.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hmichel <hmichel@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/28 21:22:47 by hmichel      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/30 01:37:28 by seanseau    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"
#include <stdio.h>

void			ft_garrot_gorille2(t_dispa dis, t_sort *s, t_res *res)
{
	if (s->new_size_first[dis.occurrence] > res->size_paths[dis.i])
	{
		s->second_path[s->nb_path_second] = s->first_path[dis.occurrence];
		s->new_size_second[s->nb_path_second] = res->size_paths[dis.occurrence];
		ft_bzero(&s->first_path[dis.occurrence],
				res->size_paths[dis.occurrence]);
		s->first_path[dis.occurrence] = res->paths[dis.i];
		s->new_size_first[dis.occurrence] = res->size_paths[dis.i];
		s->nb_path_second++;
	}
	else
	{
		s->second_path[s->nb_path_second] = res->paths[dis.i];
		s->new_size_second[s->nb_path_second] = res->size_paths[dis.i];
		s->nb_path_second++;
	}
}

void			ft_garrot_gorille(t_dispa dis, t_sort *s, t_res *res)
{
	if (dis.error == 1)
	{
		s->first_path[s->nb_path_first] = res->paths[dis.i];
		s->new_size_first[s->nb_path_first] = res->size_paths[dis.i];
		s->nb_path_first++;
	}
	else if (res->size_paths[dis.occurrence] > res->size_paths[dis.i])
	{
		s->second_path[s->nb_path_second] = s->first_path[dis.occurrence];
		s->new_size_second[s->nb_path_second] = res->size_paths[dis.occurrence];
		ft_bzero(&s->first_path[dis.occurrence],
				res->size_paths[dis.occurrence]);
		s->first_path[dis.occurrence] = res->paths[dis.i];
		s->new_size_first[dis.occurrence] = res->size_paths[dis.i];
		s->nb_path_second++;
	}
	else
		ft_garrot_gorille2(dis, s, res);
}

void			get_occurence(t_dispa dis, t_sort *sort, t_res *res)
{
	while (dis.i < res->used_paths)
	{
		dis.count = -1;
		dis.error = 1;
		while (++dis.count < sort->nb_path_first)
		{
			dis.j = 0;
			while (++dis.j < res->size_paths[dis.i] - 1)
			{
				dis.k = -1;
				while (++dis.k < sort->new_size_first[dis.count] - 1)
				{
					if (res->paths[dis.i][dis.j] ==
							sort->first_path[dis.count][dis.k])
					{
						dis.occurrence = dis.count;
						dis.error++;
					}
				}
			}
		}
		ft_garrot_gorille(dis, sort, res);
		dis.i++;
	}
}

int				init_sort(t_sort *sort, t_res *res)
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

static int		clear_path2(t_res *res, t_sort *sort)
{
	t_dispa		dis;

	dis.i = 1;
	dis.occurrence = 0;
	if (init_sort(sort, res) != 1)
		return (-1);
	get_occurence(dis, sort, res);
	return (1);
}

int				nb_ant_int_path(t_map map, t_sort *sort, int ant, int index)
{
	int i;

	i = 0;
	while (i < sort->nb_path_first)
	{
		if (index >= sort->new_size_first[i])
		{
			sort->dispache[i]++;
			ant++;
		}
		if (ant == map.inf.nb_fourmi)
			return (index);
		i++;
	}
	return (nb_ant_int_path(map, sort, ant, index + 1));
}

void			dis_var(t_dispa *dis, t_map map, t_sort *sort)
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

int				init_dis(t_dispa *dis, t_map map, t_sort *sort)
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

int				dispache_ant(t_map map, t_sort *sort, int nb_ligne)
{
	t_dispa		dis;

	if (init_dis(&dis, map, sort) != 1)
		return (-1);
	while (dis.l < nb_ligne)
	{
		dis.i = 0;
		if ((dis.tmp * sort->nb_path_first) <= map.inf.nb_fourmi)
			dis.ant_cross_max = dis.tmp * sort->nb_path_first;
		if (dis.ant_cross + dis.ant_finish == map.inf.nb_fourmi - dis.reste + 1)
		{
			dis.ant_cross_max += dis.reste;
		}
		dis.m = 0;
		while (dis.i < dis.ant_cross_max)
		{
			dis.j = 0;
			dis.n = 0;
			while (dis.j < sort->nb_path_first)
			{
				if (dis.status_partion[dis.j] == sort->dispache[dis.j])
				{
					if (dis.i < map.inf.nb_fourmi && (!(dis.status_ant[dis.i] ==
									map.inf.start)))
						dis.j = dis.status_path[dis.i];
					else
					{
						dis.q = 0;
						dis.p = 0;
						while (dis.q < sort->nb_path_first)
						{
							if (dis.start_path[dis.q] == 0 && dis.j != dis.q &&
									dis.status_partion[dis.q] != sort->dispache[dis.q])
							{
								dis.p = 1;
								dis.j = dis.q;
								break ;
							}
							dis.q++;
						}
						if (dis.p != 1)
						{
							dis.m = 1;
							dis.i++;
							break ;
						}
					}
				}
				dis.k = 0;
				while (dis.k < sort->new_size_first[dis.j])
				{
					if ((dis.i < map.inf.nb_fourmi) && sort->first_path[dis.j][dis.k] == dis.status_ant[dis.i] && sort->first_path[dis.j][dis.k] != map.inf.end)
					{
						if (dis.space == 1)
							dis.space = 0;
						else
							ft_printf(" ");
						if (dis.status_ant[dis.i] == map.inf.start)
						{
							dis.start_path[dis.n] = 1;
							dis.ant_cross++;
							dis.n++;
						}
						if (dis.status_ant[dis.i] == map.inf.start)
							dis.status_partion[dis.j]++;
						dis.status_ant[dis.i] = sort->first_path[dis.j][dis.k + 1];
						dis.status_path[dis.i] = dis.j;
						if (dis.k + 1 < sort->new_size_first[dis.j] && sort->first_path[dis.j][dis.k + 1] == map.inf.end)
						{
							dis.ant_finish++;
							dis.ant_cross--;
						}
						ft_printf("L%d-%s", dis.i + 1, map.map_name[dis.status_ant[dis.i]]);
						break ;
					}
					dis.k++;
				}
				dis.i++;
				dis.j++;
			}
			if (dis.i % sort->nb_path_first == 0)
			{
				if (dis.i == sort->nb_path_first * dis.tmp && dis.tmp <= map.inf.nb_fourmi)
					dis.tmp++;
			}
			if (dis.m == 1)
			{
				break ;
			}
		}
		dis.p = 0;
		while (dis.p < sort->nb_path_first)
		{
			dis.start_path[dis.p] = 0;
			dis.p++;
		}
		printf("\n");
		dis.space = 1;
		dis.l++;
	}
	return (0);
}

int				display_algo(t_map map, t_res *res)
{
	t_sort	sort;
	int 	i;
	int 	nb_line;

	if (clear_path2(res, &sort) != 1)
		return (-1);
	if (!(sort.dispache = malloc(sizeof(int) * sort.nb_path_first)))
		return (-1);
	i = -1;
	while (++i < sort.nb_path_first)
		sort.dispache[i] = 0;
	nb_line = nb_ant_int_path(map, &sort, 0, 0);
	dispache_ant(map, &sort, nb_line);
	printf("Number of lines required: %d | Number of lines done: %d\n",
			map.line_expected, nb_line);
	return (0);
}
