/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cgarrot <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/11 19:33:37 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/30 18:13:07 by seanseau    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"

void		init_value(t_map *map)
{
	map->cpt.error = -1;
	map->inf.nb_fourmi = -1;
	map->cpt.i = 0;
	map->cpt.j = 0;
	map->inf.start = -1;
	map->inf.end = -1;
	map->cpt.start_name = 1;
	map->cpt.start_link = 1;
	map->cpt.yes_start = 0;
	map->cpt.yes_end = 0;
	map->n_mat.size_reduct = 0;
}

void		init_matrix(t_map *map)
{
	map->mat.i = 0;
	map->mat.tmp_i = 0;
	map->mat.j = 0;
	map->mat.save_x = -1;
	map->mat.save_y = -1;
	map->mat.name1 = NULL;
	map->mat.name2 = NULL;
	map->mat.split = NULL;
	map->mat.start_link_end = 0;
	map->mat.end_link_start = 0;
}

int			ft_init_queue(t_bfs *bfs)
{
	int		i;
	int		j;

	bfs->found_paths = 0;
	if (!(bfs->queue = (int **)malloc(sizeof(int *) * bfs->nb_paths)))
		return (FAILURE);
	i = -1;
	while (++i < bfs->nb_paths)
	{
		j = -1;
		if (!(bfs->queue[i] = (int *)malloc(sizeof(int) * bfs->size_diago)))
			return (FAILURE);
		while (++j < bfs->size_diago)
			bfs->queue[i][j] = -1;
		bfs->queue[i][0] = bfs->start;
	}
	return (SUCCESS);
}

int			ft_init_tripaths(t_tripaths **tri, t_bfs *bfs, t_temp_paths tp)
{
	int		i;
	int		j;

	i = -1;
	if (!(*tri = (t_tripaths *)malloc(sizeof(t_tripaths))))
		return (FAILURE);
	if (!((*tri)->nb_subs = (int *)malloc(sizeof(int) * bfs->nb_paths)))
		return (FAILURE);
	if (!((*tri)->paths = (t_path **)malloc(sizeof(t_path *) * bfs->nb_paths)))
		return (FAILURE);
	while (++i < bfs->nb_paths)
	{
		j = -1;
		if (!((*tri)->paths[i] = (t_path *)malloc(sizeof(t_path) *
						get_nb_sub_path(bfs, tp, *tri, i))))
			return (FAILURE);
		while (++j < (*tri)->nb_subs[i])
		{
			(*tri)->paths[i][j].path = NULL;
			(*tri)->paths[i][j].size = 0;
		}
	}
	(*tri)->count_paths = 0;
	return (SUCCESS);
}

int			insert_line_lst(t_map *m, char **line, t_file_display **dis, int *c)
{
	if (*c == 0)
	{
		if (!(*dis = insert_line(*line)))
			return (-1);
		m->tmp_f_dis = *dis;
		*c = 1;
	}
	else if (*c == 1)
	{
		if (!(m->tmp_f_dis->next = insert_line(*line)))
			return (-1);
		m->tmp_f_dis = m->tmp_f_dis->next;
	}
	return (1);
}
