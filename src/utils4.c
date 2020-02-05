/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils4.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cgarrot <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/05 15:06:11 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 15:06:14 by cgarrot     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"

int		ft_used_paths(int *nb_subs, int nb_paths, int limit)
{
	int		path;
	int		count;

	count = 0;
	path = -1;
	while (++path < nb_paths)
		count += (nb_subs[path] >= limit) ? limit : nb_subs[path];
	return (count);
}

int		actu_disi2(int disi, int step, int temp)
{
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

int		actu_disi(int disi, int step)
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
	return (actu_disi2(disi, step, temp));
}

void	get_line_expected(t_map *map, char *line)
{
	if (ft_strstr(line, "#Here is"))
		map->line_expected = ft_atoi_3(line);
	else
		map->line_expected = -1;
}
