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

int		main(void)
{
	t_name	*name;
	t_link	*link;
	t_map	map;
	int 	ret;

	printf("La Menace d'Hugrebou\n");
	init_value(&map);
	printf("L'Attaque d'Hugrebou\n");
	ret = parser(&name, &link, &map);
	if (ret != 1)
		return (print_and_return(ret));
	printf("La Revanche d'Hugrebou\n");
	ret = set_map(&name, &link, &map);
	if (ret != 1)
		return (print_and_return(ret));
	printf("Un nouvel Hugrebou\n");
	//print_tab(map.map_name);
	//print_tab(map.map_link);
	//print_info_map(&name, &link, &map);
	ret = set_matrix(&map);
	if (ret != 1)
		return (print_and_return(ret));
	printf("Hugrebou contre-attaque\n");
	//set_matrix(&name, &link, &info);
	delete_cul_de_sac(&map);
	printf("Le Retour d'Hugrebou\n");
	printf("\n");
	printf(" Le Réveil d'Hugrebou\n");
	//print_tab_int(map.matrix, map.inf.size_name, map.inf.size_name);
	resize_matrix(&map);
	printf("Le Dernier Hugrebou\n");
	clear(&name, &link);
	printf("L'Ascension d'Hugrebou\n");
	ret = print_and_return(ret);
	printf("ca marche sauf si CALIN arrete de fumer Hugrebou");
	return (ret);
}
