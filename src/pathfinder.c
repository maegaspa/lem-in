/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pathfinder.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: seanseau <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/25 10:24:52 by seanseau     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/25 16:36:01 by seanseau    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"
#include <stdio.h>

void	remove_nodes_path(t_bfs *bfs)
{
	int x;

	x = 0;
	while (x != bfs->tab_next_size)
	{
		bfs->tab_next[x] = -1;
		x++;
	}
	bfs->tab_next_size = 0;
}

void	print_path(t_bfs *bfs, t_map *map)
{
	int x;
	int y;
	x = 0;

	while (bfs->paths[x][0] != -1)
	{
		y = 0;
		printf("%d\n", bfs->distance[1]);
		printf("%d -> ", x);
		while (bfs->paths[x][y] != -1)
		{
			printf("|%s|", map->map_name[bfs->paths[x][y]]);
			y++;
		}
		printf("\n");
		x++;
	}
	printf("\n");
}

int		**paths_malloc(t_map *map)
{
	int		x;
	int		y;
	int		**paths;

	if (!(paths = (int **)malloc(sizeof(int *) * 2000)))
		return (NULL);
	x = -1;
	while (++x != 200)
	{
		y = -1;
		if (!(paths[x] = (int *)malloc(sizeof(int) * map->inf.size_name)))
			return (NULL);
		while (++y != map->inf.size_name)
			paths[x][y] = -1;
	}
	paths[0][0] = map->inf.end;
	return (paths);
}

int		get_paths_nb(t_bfs *bfs)
{
	int x;

	x = 0;
	while (bfs->paths[x][0] != -1)
		x++;
	return (x);
}

int		get_last_node(t_bfs *bfs, int path_nb)
{
	int x;

	x = 0;
	while (bfs->paths[path_nb][x] != -1)
		x++;
	return (bfs->paths[path_nb][x - 1]);
}

void	save_path_bfs(t_bfs *bfs, int path_nb)
{
	int x;

	x = 0;
	while (bfs->paths[path_nb][x] != -1)
	{
		bfs->saved_path[x] = bfs->paths[path_nb][x];
		x++;
	}
	while (bfs->saved_path[x] != -1)
	{
		bfs->saved_path[x] = -1;
		x++;
	}
}

void	add_to_path(t_bfs *bfs, int path, int node)
{
	int depth;

	depth = 0;
	while (bfs->paths[path][depth] != -1)
		depth++;
	bfs->paths[path][depth] = node;
}

void	duplicate_save(t_bfs *bfs, t_map *map)
{
	int x;
	int y;
	int	y_node;

	y_node = 0;
	x = 0;
	while (bfs->paths[x][0] == map->inf.end)
		x++;
	y = 0;
	while (bfs->saved_path[y] != -1)
	{
		bfs->paths[x][y] = bfs->saved_path[y];
		y++;
	}
	bfs->new_path = x;
}

int		is_not_visited(int node, int *path)
{
	int x;

	x = 0;
	while (path[x] != -1)
	{
		if (path[x] == node)
			return (-1);
		x++;
	}
	return (1);
}

void	pathfinder(t_map *map, t_bfs *bfs, int nb_paths)
{
	int current_path;
	int node;
	int last_node;
	int nb_link;

	current_path = 0;
	//printf("nb_paths : %d\n", nb_paths);
	while (current_path < nb_paths)
	{
		while (get_last_node(bfs, current_path) == map->inf.start)
			current_path++;
		last_node = get_last_node(bfs, current_path);
	//	printf("path[%d] : last node : |%s|\n", current_path, map->map_name[last_node]);
		if (last_node != map->inf.start)
		{
			node = 0;
			nb_link = 0;
			while (node != map->inf.size_name)
			{
				if (map->matrix[last_node][node] > 0 && map->matrix[last_node][node] <= bfs->distance[last_node])
				{
	//				printf("node |%s| from path |%d| is linked with |%s|\n", map->map_name[last_node], current_path, map->map_name[node]);
					if (nb_link == 0 && is_not_visited(node, bfs->paths[current_path]) == 1)
					{
						save_path_bfs(bfs, current_path);
						add_to_path(bfs, current_path, node);
						nb_link++;
					}
					else if (is_not_visited(node, bfs->saved_path) == 1 && nb_link != 0)
					{
	//					printf("path |%d| is already taken -> duplicating\n", current_path);
						duplicate_save(bfs, map);
						add_to_path(bfs, bfs->new_path, node);
						nb_link++;
					}
				}
				node++;
			}
		}
		current_path++;
	}
}

int		all_path_done(t_bfs *bfs, t_map *map)
{
	int x;
	int y;

	x = 0;
	while (bfs->paths[x][0] != -1)
	{
		y = 0;
		while (bfs->paths[x][y] != -1)
			y++;
		if (bfs->paths[x][y - 1] == map->inf.start)
			x++;
		else
			return (-1);
	}
	return (1);
}

void	reverse_pathfinding(t_map *map, t_bfs *bfs)
{
	while (all_path_done(bfs, map) != 1)
		pathfinder(map, bfs, get_paths_nb(bfs));
	print_path(bfs, map);
}
