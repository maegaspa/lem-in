/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cgarrot <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/11 19:33:43 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/25 11:48:00 by seanseau    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"
#include <stdio.h>

int		main(void)
{
	t_name	*name;
	t_link	*link;
	t_map	map;
	int 	ret;

	init_value(&map);
	ret = parser(&name, &link, &map);
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
	clear(&name, &link);
	ret = print_and_return(ret);
	begin_bfs(&map, map.inf.start);
	ret = 0;
//	while (map.map_name[ret])
//	{
//		printf("%d - %s\n", ret, map.map_name[ret]);
//		ret++;
//	}
	printf("ca marche sauf si ya error");
	return (ret);
}
