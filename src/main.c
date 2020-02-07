/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hmichel <hmichel@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/06 14:30:48 by seanseau     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 22:03:49 by hmichel     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"


void 	print_tab_int(int **tab, int y, int x, t_map *map);//

void		print_file(t_file_display *f_dis)
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

int			start_link_to_end(t_map *map, t_file_display *f_dis)
{
	int		i;

	i = -1;
	if (map->matrix[map->inf.start][map->inf.end] == 1)
	{
		print_file(f_dis);
		while (++i < map->inf.nb_fourmi - 1)
			ft_printf("L%d-%s ", i + 1, map->map_name[map->inf.end]);
		ft_printf("L%d-%s\n", i + 1, map->map_name[map->inf.end]);
		return (1);
	}
	return (0);
}

int			resolution(t_map *map, t_file_display *f_dis)
{
	t_res			res;
	t_bfs			bfs;
	t_tripaths		tri;

	tri.paths = NULL;
	tri.nb_subs = NULL;
	tri.count_paths = 0;
	tri = ft_bfs(*map, &bfs, &tri, &res);
	if (tri.count_paths == 0)
		return (-1);
	if (!ft_tri_to_res(&res, tri, bfs, *map))
		return (print_and_return(map->ret));
	free_tri(&tri, &bfs);
	print_file(f_dis);
	display_algo(*map, &res);
	free_all(&bfs, map, &res);
	return (1);
}

int			main(void)
{
	t_file_display	*f_dis;
	t_name			*name;
	t_link			*link;
	t_map			map;

	init_value(&map);
	if ((map.ret = parser(&name, &link, &map, &f_dis)) <= 0)
		return (print_and_return(map.ret));
	if (!(map.ret = set_map(&name, &link, &map)))
		return (print_and_return(map.ret));
	if ((map.ret = set_matrix(&map)) <= 0)
		return (print_and_return(map.ret));
	if ((start_link_to_end(&map, f_dis) == 1))
		return (0);
	ft_printf("oui\n");
	//print_tab_int(map.matrix, map.inf.size_name, map.inf.size_name, &map);
	if ((map.ret = resolution(&map, f_dis)) <= 0)
		return (print_and_return(map.ret));
	clear(&name, &link, &f_dis);
	return (0);
}
