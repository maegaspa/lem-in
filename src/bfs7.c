/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bfs7.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hmichel <hmichel@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/04 05:21:55 by hmichel      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/04 14:45:26 by hmichel     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"
#include <stdio.h>

static int	actu_disi(int disi, int step)
{
	int		temp;

	temp = step;
	if (disi > 4)
		return (disi);
	if (disi == 4 && step / 16)
		return (disi);
	if (disi == 4 && (step / 16) == 0)
		return (actu_disi(disi + 1, temp));
	step = step % 16;
	if (disi == 3 && step / 8)
		return (disi);
	if (disi == 3 && (step / 8) == 0)
		return (actu_disi(disi + 1, temp));
	step = step % 8;
	if (disi == 2 && step / 4)
		return (disi);
	if (disi == 2 && (step / 4) == 0)
		return (actu_disi(disi + 1, temp));
	step = step % 4;
	if (disi == 1 && step / 2)
		return (disi);
	if (disi == 1 && (step / 2) == 0)
		return (actu_disi(disi + 1, temp));
	step = step % 2;
	if (disi == 0 && step)
		return (disi);
	return (actu_disi(disi + 1, temp));
}

static void clear_path(t_res *res, t_sort *sort, int step)
{
	t_dispa		dis;

	dis.i = actu_disi(0, step) + 1;
	sort->first_path[0] = res->paths[actu_disi(0, step)];
	sort->new_size_first[0] = res->size_paths[actu_disi(0, step)];
	//printf("step = %2d et dis.i =%2d\n", step, dis.i);
	sort->nb_path_first = 1;
	while (dis.i < res->used_paths)
	{
		if (dis.i < 5)
		{
			dis.i = actu_disi(dis.i, step);
			//printf("step = %2d et dis.i =%2d\n", step, dis.i);
		}
		dis.count = -1;
		dis.error = 0;
		while (++dis.count < sort->nb_path_first)
		{
			dis.j = 0;
			while (++dis.j < res->size_paths[dis.i] - 1)
			{
				dis.k = -1;
				while (++dis.k < sort->new_size_first[dis.count] - 1 && !dis.error)
				{
					if (res->paths[dis.i][dis.j] == sort->first_path[dis.count][dis.k])
					{
						dis.error++;
						break ;
					}
				}
			}
		}
		if (!dis.error)
		{
			sort->first_path[sort->nb_path_first] = res->paths[dis.i];
			sort->new_size_first[sort->nb_path_first] = res->size_paths[dis.i];
			sort->nb_path_first++;
		}
		dis.i++;
	}
	//printf("\n");
}

static int 	ft_nb_line(int total_ants, t_sort *sort, int ant, int index)
{
	int i;

	i = 0;
	while (i < sort->nb_path_first)
	{
		if (index >= sort->new_size_first[i])
			ant++;
		if (ant == total_ants)
			return(index);
		i++;
	}
	return(ft_nb_line(total_ants, sort, ant, index + 1));
}

int			ft_tri_big(t_res *res, t_sort *sort, int nb_line, int total_ants)
{
	int			better_step;
	int			better_nb;
	int			cur_nb;
	int			step;

	better_nb = 2147483645;
	step = -1;
	if (!(sort->new_size_first = malloc(sizeof(int) * res->used_paths)))
		return (0);
	if (!(sort->first_path = malloc(sizeof(int*) * res->used_paths)))
		return (0);
	while (++step < 32)
	{
		clear_path(res, sort, step);
		if ((cur_nb = ft_nb_line(total_ants, sort, 0, 0)) <= nb_line)
			return (SUCCESS);
		if (cur_nb < better_nb)
		{
			//printf("cur_nb = %d\n", cur_nb);
			//printf("step = %d\n", step);
			better_step = step;
			better_nb = cur_nb;
		}
	}
	if (better_step != step - 1)
		clear_path(res, sort, better_step);
	return (1);
}