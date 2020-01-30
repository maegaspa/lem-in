/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bfs1.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hmichel <hmichel@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/18 16:13:41 by hmichel      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 23:37:45 by seanseau    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"
#include <stdio.h>

void			ft_nb_paths(t_map map, t_bfs *bfs)
{
	int		i;
	int		nb1;
	int		nb2;

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
	bfs->finish = nb1 * nb2;
	bfs->nb_paths = (nb1 < nb2) ? nb1 : nb2;
	bfs->end_links = (nb1 < nb2) ? nb2 : nb1;
	bfs->start = (nb1 < nb2) ? map.inf.start : map.inf.end;
	bfs->end = (nb1 < nb2) ? map.inf.end : map.inf.start;
}

static int		ft_availablequeue(t_bfs *bfs)
{
	int		i;

	i = -1;
	while (++i < bfs->nb_paths)
		if (bfs->queue[i][0] != -1)
			return (TRUE);
	return (FALSE);
}

void			ft_foundpaths(t_bfs *bfs, int step, t_map *map)
{
	t_temp_bfs	temp;

	temp.actual_path = 0;
	if (step == 2)
		ft_setprematrix(bfs, temp);
	if (bfs->found_paths <= bfs->finish && ft_availablequeue(bfs))
	{
		while (temp.actual_path < bfs->nb_paths)
		{
			temp.i_queue = 0;
			temp.add_queue = 0;
			temp.size_queue = ft_size_queue(*bfs, temp.actual_path);
			while (temp.i_queue < temp.size_queue)
			{
				ft_setqueue(bfs, temp, step);
				temp.i_queue++;
			}
			ft_del_rooms(bfs, temp);
			temp.actual_path++;
		}
		ft_foundpaths(bfs, ++step, map);
	}
}

t_tripaths		ft_bfs(t_map map, t_bfs *bfs, t_tripaths *tri, t_res *res)
{
	tri->count_paths = 0;
	res++;
	if (!ft_setprealgo(map, bfs))
		;
	ft_foundpaths(bfs, 2, &map);
	if (!(tri = ft_takepaths(bfs, res)))
		;
	return (*tri);
}
