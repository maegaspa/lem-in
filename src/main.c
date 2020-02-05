/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hmichel <hmichel@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/11 19:33:43 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 15:21:58 by cgarrot     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"
#include <stdio.h>

void	print_file(t_file_display *f_dis)
{
	t_file_display *tmp_f_dis;

	tmp_f_dis = f_dis;
	while (tmp_f_dis)
	{
		ft_printf("%s\n", tmp_f_dis->line);
		tmp_f_dis = tmp_f_dis->next;
	}
	write(1, "\n", 1);
}

int		start_link_to_end(t_map *map, t_file_display *f_dis)
{
	int		i;

	i = -1;
	if (map->matrix[map->inf.start][map->inf.end] == 1)
	{
		print_file(f_dis);
		while (++i < map->inf.nb_fourmi)
			ft_printf("L%d-%s\n", i + 1, map->map_name[map->inf.end]);
	}
	else
		return (0);
	return (1);
}

int		main(void)
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
	if (!(ret = parser(&name, &link, &map, &f_dis)))
		return (print_and_return(ret));
	if (!(ret = set_map(&name, &link, &map)))
		return (print_and_return(ret));
	if (!(ret = set_matrix(&map)))
		return (print_and_return(ret));
	start_link_to_end(&map, f_dis);
	tri.paths = NULL;
	tri.nb_subs = NULL;
	tri.count_paths = 0;
	tri = ft_bfs(map, &bfs, &tri, &res);
	if (!ft_tri_to_res(&res, tri, bfs, map))
		return (print_and_return(ret));
	print_file(f_dis);
	display_algo(map, &res);
	free_all(&bfs, &map, &res);
	clear(&name, &link, &f_dis);
	return (ret);
}
