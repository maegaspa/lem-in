/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cleanpath.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hmichel <hmichel@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/12 01:51:51 by hmichel      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/12 17:45:37 by hmichel     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/lemin.h"
#include <stdio.h>

int				ft_init_paths(t_prealgo pa, t_res *res)
{
	int		i;

	i = -1;
	if (!(res->paths = (int **)malloc(sieof(int *) * pa.nb_path)))
		return (0);
	while (++i < pa.nb_path)
		if (!(res->paths[i] = (int *)malloc(sieof(int) * pa.mtx_state[pa.end][i] + 1))) //+1 pour rentrer start dans le chemin
			return (0);
	return (1);
	if (!(res->size_paths = (int *)malloc(sizeof(int) * pa.nb_path)))
		return (0);
	i = -1;
	while (++i < pa.nb_path)
		res->size_paths[i] = pa.mtx_state[pa.end][i] + 1;
	i = -1;
	while (++i < pa.nb_path - 1)
	{
		if (res->size_paths[i] > res->size_paths[i + 1])
		{
			res->size_paths[i] += res->size_paths[i + 1];
			res->size_paths[i + 1] = res->size_paths[i] - res->size_paths[i + 1];
			res->size_paths[i] -= res->size_paths[i + 1];
		}
	}
	return (1);
}

/*	
	size = 1;
	j = -1;
	while (++i < pa.nb_path)
		if (pa.mtx_state[pa.end][i] + 1 == size)
			res->size_paths[++j] = pa.mtx_state[pa.end][i] + 1;
*/
void			ft_init_tempclean(t_tempclean *temp, t_prealgo pa)
{
	temp->i = -1;
	temp->path_count = -1;
	temp->step = 0;
}
// mettre nb_links = nb_chemin de meme taille ET index_path = path utilisé pour remplir **paths
int				ft_select_path(t_prealgo pa, t_res res, t_tempalgo *temp)
{
	int		i;
	int		j;

	j = -1;
	if (!(temp->order = (int *)malloc(sizeof(int) * pa.nb_path)))
		return (0);
	while (++j < pa.nb_path)
	{
		i = -1
		while (++i < pa.nb_path)
		{
			if (pa.mtx_state[pa.end][i] == res.size_paths[j])
			{
				temp->order[j] = i;
				pa.mtx_state[pa.end][i] = -1;
			}
		}
	}
	return (1);
}

int				ft_select_node(t_prealgo pa, t_tempclean temp) //renvoie -1 en gestion d'erreur
{
	int		select;
	int		*compare;
	int		y;

	y = 0;
	if (!(compare = (int *)malloc(sizeof(int * temp.nb_node))))
		return (-1);
	temp.i = 0;
	while (++temp.i < pa.size_diago)
	{
		if (pa.mtx_diago[act_index][i] == 1 && pa.mtx_state[i][temp.path_count] == temp.step - 1)
		{
			compare[y] = temp.i;
			y++;
		}
	}
	temp.i = 0;
	while (++temp.i < pa.nb_path)
	{
		y = -1;
		while (++y < temp.nb_node)
			pa.mtx_state[compare[y]][temp.path_count]
	}
	return (select);
}

t_res			ft_cleanpath(t_prealgo pa)
{
	t_res		res;
	t_tempclean	temp;

	if (!ft_init_paths(pa, &res)
		return (NULL);
	ft_init_tempalgo2(&temp, pa)
	if (!ft_select_path(pa, res, &temp))
		return (NULL);
	while (++temp.path_count < pa.nb_path)
	{
		temp.act_index = pa.end;
		temp.step = res.size_paths[temp.path_count] + 1; //longueur chemin
		while (--temp.step >= 0) //tous les steps
		{
			temp.nb_node = 0;
			res.paths[temp.path_count][temp.step] = pa.mtx_state[temp.act_index][temp.over[temp.path_count]];
			temp.i = -1;
			while (++temp.i < pa.size_diago)
				if (pa.mtx_diago[act_index][i] == 1 && pa.mtx_state[i][temp.path_count] == temp.step - 1)
					temp.nb_node++;
			if (( = ft_select_node(pa, temp)) == -1)
				return (NULL);
		}
	}
	free(&temp.order)
	return (res);
}












/*
int			**ft_cleanpath(t_prealgo pa)
{
	int			**paths;
	t_tempalgo	temp;

	ft_init_tempalgo2(&temp, pa);
	while (++temp.path_name < pa.nb_path)
	{
		temp->nb_links = ft_nblinks(pa, pa.end);
		while (++temp.actual_link < temp->nb_links)
		{
			
		}
	}
}*/
