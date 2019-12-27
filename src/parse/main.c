/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hmichel <hmichel@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/11 19:33:43 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/19 17:44:47 by seanseau    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/lemin.h"
#include <stdio.h>

int		main(void)
{
	t_name		*name;
	t_link		*link;
	t_map		map;
	int 		ret;
	//t_prealgo	pa;

	//pa = NULL;
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
	clear(&name, &link);
	ret = print_and_return(ret);
	ft_bfs(map);
	printf("ca marche sauf si ya error");
	return (ret);
}
