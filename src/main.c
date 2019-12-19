/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cgarrot <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/11 19:33:43 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/11 19:33:44 by cgarrot     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"
#include <stdio.h>

void 	print_file(t_file_display *f_dis)
{
	t_file_display *tmp_f_dis;

	tmp_f_dis = f_dis;
	while (tmp_f_dis)
	{
		ft_printf("%s\n", tmp_f_dis->line);
		tmp_f_dis = tmp_f_dis->next;
	}
}

int		main(void)
{
	t_file_display	*f_dis;
	t_name	*name;
	t_link	*link;
	t_map	map;
	int 	ret;

	init_value(&map);
	ret = parser(&name, &link, &map, &f_dis);
	if (ret != 1)
		return (print_and_return(ret));
	ret = set_map(&name, &link, &map);
	if (ret != 1)
		return (print_and_return(ret));
	//print_tab(map.map_name);
	//print_tab(map.map_link);
	//print_info_map(&name, &link, &map);
	ret = set_matrix(&map);
	if (ret != 1)
		return (print_and_return(ret));
	//set_matrix(&name, &link, &info);
	delete_cul_de_sac(&map);
	printf("\n");
	//print_tab_int(map.matrix, map.inf.size_name, map.inf.size_name);
	resize_matrix(&map);
	print_file(f_dis);
	clear(&name, &link, &f_dis);
	ret = print_and_return(ret);
	return (ret);
}
