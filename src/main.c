/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hmichel <hmichel@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/11 19:33:43 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/30 00:59:14 by seanseau    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"
#include <stdio.h>

void		print_file(t_file_display *f_dis)
{
	t_file_display *tmp_f_dis;

	tmp_f_dis = f_dis;
	while (tmp_f_dis)
	{
		ft_printf("%s\n", tmp_f_dis->line);
		tmp_f_dis = tmp_f_dis->next;
	}
}

int			ft_one_shot(t_map *map)
{
	int fourmi;

	fourmi = 0;
	if (map->matrix[map->inf.start][map->inf.end] > 0)
	{
		while (++fourmi < map->inf.nb_fourmi)
			ft_printf("L%d-%s ", fourmi, map->map_name[map->inf.end]);
		ft_printf("L%d-%s", fourmi, map->map_name[map->inf.end]);
		return (2);
	}
	return (1);
}

int			main(void)
{
	t_file_display	*f_dis;
	t_name			*name;
	t_link			*link;
	t_map			map;
	t_res			res;
	t_bfs			bfs;
	t_tripaths		tri;
	int				ret;

	init_value(&map);
	ret = parser(&name, &link, &map, &f_dis);
	if (ret != 1)
		return (print_and_return(ret));
	ret = set_map(&name, &link, &map);
	if (ret != 1)
		return (print_and_return(ret));
	ret = set_matrix(&map);
	if (ret != 1)
		return (print_and_return(ret));
	ret = ft_one_shot(&map);
	if (ret != 1)
		return (print_and_return(ret));
	printf("\n");
	ret = print_and_return(ret);
	tri.paths = NULL;
	tri.nb_subs = NULL;
	tri.count_paths = 0;
	tri = ft_bfs(map, &bfs, &tri, &res);
	if (!ft_tri_to_res(&res, tri, bfs, map))
		return (print_and_return(ret));
	display_algo(map, &res);
	return (ret);
}
