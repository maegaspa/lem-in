/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lemin.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cgarrot <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 13:30:44 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/11 19:28:17 by cgarrot     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/includes/ft_printf.h"
# include <stdio.h>

typedef struct s_name
{
	char 	*name;
	int		index;
	int 	co_y;
	int 	co_x;
	struct s_name *next;
}				t_name;

typedef struct s_link
{
	char 	*link;
	int		index;
	struct s_link *next;
}				t_link;

typedef struct s_info
{
	int	nb_fourmi;
	int start;
	int end;
	int	size_name;
	int	size_link;
	int ret;
} 				t_info;

typedef struct s_matrix
{
	int 	i;
	int 	j;
	int 	start_link_end;
	int 	end_link_start;
	int 	tmp_i;
	int 	save_y;
	int 	save_x;
	char	*name1;
	char	*name2;
	char 	**split;
}				t_matrix;

typedef struct s_cpt
{
	int		error;
	int		i;
	int		j;
	int 	yes_start;
	int 	yes_end;
	unsigned int	len;
	unsigned int	k;
	int 	start_name;
	int 	start_link;
	int     x;
	int     m;
	int     l;
	int     p;
} 				t_cpt;

typedef struct		s_path
{
    int             nb_first_path;
    int             *new_file_first;
    int             *new_file_second;
    int             nb_path;
	int				length;
	int             occur;
	int             error;
	int             nb_newfirst;
	int             nb_newsecond;
	int             count;
	int             **first_path;
	int             **second_path;
	int             *file;
	struct			s_path *next;
}					t_path;

typedef struct      s_display
{
    int             remain;
    int             ant_finish;
    int             *status_ant;
    int             ant_cross;
    int             ant_num;
    int             path_size;
}                   t_display;

typedef struct		s_bfs
{
	int				*visited;
	int				*distance;
	int				*queue;
	int				q_size;
	int				**paths;
	int				*tab_next;
	int				tab_next_size;
	int				new_path;
	int				*saved_path;
}					t_bfs;
typedef struct s_map
{
	char	**map_name;
	char	**map_link;
	int 	**map_co;
	int		**matrix;
	t_info	inf;
	t_cpt	cpt;
	t_matrix mat;
	t_link	*tmp_link;
	t_name	*tmp_name;
}				t_map;

int 	**clear_path(t_map *map, /*t_display *display,*/ t_path *path, t_bfs *bfs);
int		*malloc_int_tab(int size);
void	begin_bfs(t_map *map, int node);
void	reverse_pathfinding(t_map *map, t_bfs *bfs, t_path *path);
int		**paths_malloc(t_map *map);
unsigned int	count_word(const char *s, char c);
void	print_info_map(t_name **name, t_link **link, t_map *map);
void	print_tab(char **tab);
void	free_map(char	**map);
t_link			*insert_link(char *val, int i);
t_name			*insert_name(char **val, int i);
void	clear(t_name **name, t_link **link);
int		list_len(t_name *name, t_link *link, int chose);
void	print_list(t_name *name, t_link *link);
void	init_value(t_map *map);
int		parser(t_name **name, t_link **link, t_map *map);
int   	set_map(t_name **name, t_link **link, t_map *map);
int 	set_matrix(t_map *map);
int		check_str_number(char *str);
int 	ft_strcheck(char *s1, char *s2, int chose);
int		check_valid_co(int **tab, int len);
void 	print_tab_int(int **tab, int y, int x);
int 	print_and_return(int i);
int	    check_ant_line(t_map *map, char *line);
int		check_link_line(t_link **link, t_map *map, char *line, char **split);
int		check_name_line(t_name **name, t_map *map, char *line, char **split);
int		check_start_end(t_map *map, char **line);
void	init_matrix(t_map *map);
int		check_all_link_and_name(t_map *map, int i);
int 	free_and_return(char ***split, int i);
int 	set_tab_link(t_link *tmp_link, t_map *map);
int 	set_tab_name_and_co(t_name *tmp_name, t_map *map);
int		name_cmp(char *s1, char *s2);
int		main(void);
void	get_min_path(t_map *map, t_bfs *bfs);
void	remove_node(t_bfs *bfs);
void	add_node(t_bfs *bfs, int node);
void	init_bfs(t_map *map, t_bfs *bfs, int start_node);
int		**change_matrix(int **matrix, t_map *map, t_bfs *bfs);
void	begin_bfs(t_map *map, int start_node);

#endif
