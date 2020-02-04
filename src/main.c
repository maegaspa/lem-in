/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hmichel <hmichel@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/11 19:33:43 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/04 14:22:17 by hmichel     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"
#include <stdio.h>

void    free_struct(t_tripaths *tri, t_bfs *bfs)
{
    int i;
    int j;
    int k;

    i = -1;
    j = -1;
    while (++i < bfs->nb_paths)
    {
       while (++j < tri->nb_subs[i])
       {
            k = -1;
            while (k < tri->paths[i][k].size)
                free(tri->paths[i][j].path);
            free(tri->paths[j]->path);
       }
        //free(tri->paths[i]);
    }
    free(tri->nb_subs);
    free(tri->paths);
    //free(tri);
}

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

int 	start_link_to_end(t_map	*map, t_file_display *f_dis)
{
	int 	i;
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
	t_name	*name;
	t_link	*link;
	t_map	map;
	t_res	res;
	t_bfs	bfs;
	t_tripaths tri;
	int 	ret;
//	int j;
//	int		i = -1;

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
	printf("1\n");
	if (start_link_to_end(&map, f_dis))
		return (0);
	//print_tab_int(map.matrix, map.inf.size_name, map.inf.size_name);
	//resize_matrix(&map);
//	print_file(f_dis);
	ret = print_and_return(ret);
	tri.paths = NULL;
	tri.nb_subs = NULL;
	tri.count_paths = 0;
	tri = ft_bfs(map, &bfs, &tri, &res);
	printf("2\n");
	//printf("count_paths = %d\n", tri.count_paths);
	//ft_printallpaths(tri, bfs);
	//ft_printallpaths_name(tri, bfs, &map);
	//printf(" map->line_expected = %d\n",  map.line_expected);
	if (!ft_tri_to_res(&res, tri, bfs, map))
		return (print_and_return(ret));
	printf("3\n");
	//while (++i < res.used_paths)
	//	ft_putintstr(res.paths[i], res.size_paths[i]);
	display_algo(map, &res);
	free_all(&bfs, &map, &res);
	clear(&name, &link, &f_dis);
    //free_struct(&tri, &bfs);
	return (ret);
}
