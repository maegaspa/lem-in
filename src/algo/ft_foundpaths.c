/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_foundpaths.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hmichel <hmichel@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/06 05:57:26 by hmichel      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/12 08:19:50 by hmichel     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/lemin.h"
#include <stdio.h>

int				ft_nbpaths_max(t_map map)
{
	int		i;
	int		nb;

	nb = 0;
	i = -1;
	while (++i < map.inf.size_name)
		if (map.matrix[map.inf.start][i] == 1)
			nb++;
	return (nb);
}

int				ft_set_prealgo(t_map map, t_prealgo *pa)
{
	int 	i;
	int		j;

	j = -1;
	i = -1;
	pa->nb_path = ft_nbpaths_max(map);
	if (!(pa->mtx_diago = (int **)malloc(sizeof(int *) * map.inf.size_name)))
		return (0);
	while (++i < map.inf.size_name)
	{
		if (!(pa->mtx_diago[i] = (int *)malloc(sizeof(int) * map.inf.size_name)))
			return (0);
		pa->mtx_diago[i] = ft_intcpy(pa->mtx_diago[i], map.matrix[i], map.inf.size_name);
	}
	if (!(pa->mtx_state = (int **)malloc(sizeof(int *) * map.inf.size_name)))
		return (0);
	while (++j < map.inf.size_name)
	{
		i = -1;
		if (!(pa->mtx_state[j] = (int *)malloc(sizeof(int) * (pa->nb_path))))
			return (0);
		while (++i < pa->nb_path)
			pa->mtx_state[j][i] = 0;
	}
	pa->start = map.inf.start;
	pa->end = map.inf.end;
	pa->size_diago = map.inf.size_name;
	return (1);
}

int				ft_nblinks(t_prealgo pa, int act_index)
{
	int		i;
	int		nb;

	i = -1;
	nb = 0;
	while (++i < pa.size_diago)
		if (pa.mtx_diago[act_index][i] == 1)
			nb++;
	return (nb);
}

int				ft_islink(t_prealgo pa, t_tempalgo temp)
{
	int		i;

	i = -1;
	while (++i < pa.size_diago)
	{
		if (pa.mtx_diago[temp.act_index][i] == 1 && temp.actual_link == 0)
		{
			if ((pa.mtx_state[i][temp.path_name] == 0) || (temp.step < pa.mtx_state[i][temp.path_name]))
				return (i);
		}
		else if (pa.mtx_diago[temp.act_index][i] == 1)
			temp.actual_link--;
	}
	return (-1);
}

void			ft_foundpaths(t_prealgo *pa, t_tempalgo temp) //appeler avec path = 1 initialement
{
	temp.act_index = temp.next_index;
	if (pa->mtx_state[temp.act_index][temp.path_name] == 0 || temp.step < pa->mtx_state[temp.act_index][temp.path_name])
		pa->mtx_state[temp.act_index][temp.path_name] = temp.step;
	temp.step++;
	temp.nb_links = ft_nblinks(*pa, temp.act_index);
	temp.actual_link = 0;
	temp.i = -1;
	//printf("1FP act_index = %d, nb_links = %d, step = %d, temp.i = %d\n", temp.act_index, temp.nb_links, temp.step, temp.i);
	while (++temp.i < temp.nb_links) //temp.act_index != pa->end && ++temp.i < temp.nb_links
	{
		//printf("2FP temp.next_index = %d, temp.act_index = %d, temp.i = %d, temp.path_name = %d, temp.step = %d, temp.nb_links = %d\n", temp.next_index, temp.act_index, temp.i, temp.path_name, temp.step, temp.nb_links);
		//printf("22FP NEXT temp.next_index = %d\n", ft_islink(*pa, temp));
		if ((temp.next_index = ft_islink(*pa, temp)) != -1)
		{
			if (temp.next_index != pa->start)
			{
				printf("3FP temp.next_index = %d, temp.i = %d, temp.path_name = %d, temp.step = %d, temp.nb_links = %d\n", temp.next_index, temp.i, temp.path_name, temp.step, temp.nb_links);
				ft_foundpaths(pa, temp);
			}
		}
		temp.actual_link++;
	}
}

void			ft_init_tempalgo1(t_tempalgo *temp, t_prealgo pa)
{
	temp->nb_links = ft_nblinks(pa, pa.start);
	temp->i = -1;
	temp->next_index = 0;
	temp->act_index = pa.start;
	temp->path_name = -1;
	temp->actual_link = -1;
	temp->step = 1;
}

void			*ft_allpaths(t_map map, t_prealgo *pa) //appeler avec path = 1 initialement
{
	t_tempalgo	temp;

	printf("AP debut\n");
	if (!ft_set_prealgo(map, pa))
		return (NULL);
	printf("AP 1, pa->start = %d, pa->end = %d\n", pa->start, pa->end);
	//print_tab_int(pa->mtx_diago, pa->size_diago, pa->size_diago);
	ft_init_tempalgo1(&temp, *pa);
	printf("AP 2, temp.nb_links = %d\n", temp.nb_links);
	while (++temp.actual_link < temp.nb_links)
	{
		temp.path_name++;
		pa->mtx_state[map.inf.start][temp.i] = 1;
		printf("AP 3, temp.act_index = %d, temp.actual_link = %d\n", temp.act_index, temp.actual_link);
		if ((temp.next_index = ft_islink(*pa, temp)) == -1)
			printf("erreur sur next_index\n"); //erreur
		printf("AP 4, temp.next_index = %d, temp.actual_link = %d\n", temp.next_index, temp.actual_link);
		if (temp.next_index != pa->start) //&& temp.next_index != pa->end)
		{
			printf("AP appel FP avec temp.next_index = %d, temp.i = %d, temp.path_name = %d, temp.step = %d, temp.nb_links = %d\n", temp.next_index, temp.i, temp.path_name, temp.step, temp.nb_links);
			ft_foundpaths(pa, temp);
		}
	}
	return (pa);
}

void			ft_init_prealgo(t_prealgo *begin)
{
	begin->start = 0;
	begin->end = 0;
	begin->nb_path = 0;
	begin->size_diago = 0;
	begin->mtx_diago = NULL;
	begin->mtx_state = NULL;
}

int				ft_bfs(t_map map) //faire traitement int** pour garrot
{
	t_prealgo	begin;

	//if (!ft_set_prealgo(map, &begin))
	//	return (0);
	ft_init_prealgo(&begin);
	ft_allpaths(map, &begin);
	print_tab_int(begin.mtx_state, begin.size_diago, ft_nblinks(begin, begin.start));
	return (1);
}












/*
//Si ca passe pas avec vecteur, add cette fonction dans les return
t_prealgo		ft_addstate(t_prealgo begin, t_prealgo pa)
{
	int		i;
	int		j;

	j = -1;
	if (begin == 0)
		return (pa);
	if (pa == 0)
		return (begin);
	while (++j < pa.size_diago)
	{
		i = -1;
		while (++i < pa.nb_path)
			if (pa.mtx_state[j][i] > 0)
				begin.mtx_state[j][i] = pa.mtx_state[j][i];
	}
	return (begin);
}
*/
/*
t_prealgo		ft_foundpaths(t_prealgo pa, int path) //appeler avec path = 1 initialement
{
	int		
	while (ft_islink(pa, path) != -1)
	{
		pa.act_index = ft_islink(pa.act_index, path);
		pa.mtx_state[pa.act_index][pa.path_name] = 1;
		return(ft_addstate(ft_addstate(pa, ft_foundpaths(pa, 1)), ft_foundpaths(pa, path + 1)));
	}
	return (NULL);
}

t_prealgo			ft_allpaths(t_prealgo pa, int path) //appeler avec path = 1 initialement
{
	while (ft_islink(pa.act_index, path) != -1)
	{
		pa.path_name++;
		pa.act_index = ft_islink(pa.start, path);
		pa.mtx_state[pa.start][pa.path_name] = 1;
		return(ft_addstate(ft_addstate(pa, ft_foundpaths(pa, 1)), ft_allpaths(pa, path + 1))); //foundpath signe chemin actuel et allpaths les suivants
	}
	return (NULL);
}

int				ft_bfs(t_map map) //faire traitement int** pour garrot
{
	t_prealgo	begin;

	if (!ft_set_prealgo(map, &begin))
		return (0);
	begin = ft_allpaths(begin, 1);
	return (1);
}*/