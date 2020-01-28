/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bfs5.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hmichel <hmichel@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/26 15:54:49 by hmichel      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/28 21:30:00 by hmichel     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"
#include <stdio.h>

static int	ft_used_paths(int *nb_subs, int nb_paths, int limit)
{
    int		path;
    int		count;

    count = 0;
    path = -1;
    while (++path < nb_paths)
		count += (nb_subs[path] >= limit) ? limit : nb_subs[path];
    return (count);
}

static void	ft_tri_shell(t_rank *rank, int size) //a changer
{
	int 	step;
	int		i;
	int		j;
	int		val;
	int		val1;
	int		val0;

	step = 0; 
	while (step < size)
		step = 3 * step + 1;
	while (step != 0)
	{
		step = step / 3;
		i = step - 1;
		while (++i < size)
        {
			val = rank->ranking[2][i];
			val1 = rank->ranking[1][i];
			val0 = rank->ranking[0][i];
			j = i;
			while ((j > (step - 1)) && rank->ranking[2][j - step] > val)
			{
				rank->ranking[2][j] = rank->ranking[2][j - step];
				rank->ranking[1][j] = rank->ranking[1][j - step];
				rank->ranking[0][j] = rank->ranking[0][j - step];
				j = j - step;
			}
			rank->ranking[2][j] = val;
			rank->ranking[1][j] = val1;
			rank->ranking[0][j] = val0;
		}
    }
}

static void	ft_import_coord(t_tripaths tri, t_bfs bfs, t_rank *rank, int limit)
{
	rank->i = -1;
	rank->left = 0;
	while (++rank->i < bfs.nb_paths)
	{
		if (tri.nb_subs[rank->i] <= limit)
		{
			rank->j = -1;
			while (++rank->j < tri.nb_subs[rank->i])
			{
				rank->ranking[0][rank->i * limit + rank->j - rank->left] = rank->i;
				rank->ranking[1][rank->i * limit + rank->j - rank->left] = rank->j;
				rank->ranking[2][rank->i * limit + rank->j - rank->left] = tri.paths[rank->i][rank->j].size;
			}
			rank->left += limit - tri.nb_subs[rank->i];
		}
		else
		{
			rank->k = -1;
			while (++rank->k < limit)
			{
				rank->j = -1;
				rank->size = 2147483647;
				while (++rank->j < tri.nb_subs[rank->i])
				{
					if (tri.paths[rank->i][rank->j].size < rank->size)
					{
						rank->size = tri.paths[rank->i][rank->j].size;
						rank->ranking[0][rank->i * limit + rank->k - rank->left] = rank->i;
						rank->ranking[1][rank->i * limit + rank->k - rank->left] = rank->j;
						rank->ranking[2][rank->i * limit + rank->k - rank->left] = tri.paths[rank->i][rank->j].size;
					}
				}
				tri.paths[rank->ranking[0][rank->i * limit + rank->k - rank->left]][rank->ranking[1][rank->i * limit + rank->k - rank->left]].size = rank->size = 2147483647;
			}
		}
	}
}

int			ft_tri_to_res(t_res *res, t_tripaths tri, t_bfs bfs)
{
	int		used_paths;
	t_rank	rank;
	int		i;

	used_paths = ft_used_paths(tri.nb_subs, bfs.nb_paths, LIMIT_PATHS);
	if (!(rank.ranking[0] = (int *)malloc(sizeof(int) * used_paths))) //path
		return (0);
	if (!(rank.ranking[1] = (int *)malloc(sizeof(int) * used_paths))) //sub
		return (0);
	if (!(rank.ranking[2] = (int *)malloc(sizeof(int) * used_paths))) //size
		return (0);
	ft_import_coord(tri, bfs, &rank, LIMIT_PATHS);
	//ft_putintstr(rank.ranking[0], used_paths);
	//ft_putintstr(rank.ranking[1], used_paths);
	//ft_putintstr(rank.ranking[2], used_paths);
	ft_tri_shell(&rank, used_paths);
	//printf("\n");
	//ft_putintstr(rank.ranking[0], used_paths);
	//ft_putintstr(rank.ranking[1], used_paths);
	//ft_putintstr(rank.ranking[2], used_paths);
	if (!(res->paths = (int **)malloc(sizeof(int *) * used_paths)))
		return (0);
	if (!(res->size_paths = (int *)malloc(sizeof(int) * used_paths)))
		return (0);
	i = -1;
	while (++i < used_paths)
	{
		res->size_paths[i] = rank.ranking[2][i];
		if (!(res->paths[i] = (int *)malloc(sizeof(int) * res->size_paths[i])))
			return (0);
		res->paths[i] = ft_intcpy(res->paths[i], tri.paths[rank.ranking[0][i]][rank.ranking[1][i]].path, res->size_paths[i]);
		//ft_putintstr(res->paths[i], res->size_paths[i]);
	}
	res->used_paths = used_paths;
	return (1);
}

/*
int			ft_init_res(t_bfs bfs, t_res *res, int used_paths)
{
	if (!(res->paths = (int **)malloc(sizeof(int *) * used_paths)))
		return (0);
}*/
