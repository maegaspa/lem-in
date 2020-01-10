/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lemin.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hmichel <hmichel@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 13:30:44 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/10 16:55:31 by seanseau    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/includes/ft_printf.h"

typedef struct s_file_display
{
	char 	*line;
	struct 	s_file_display *next;
}				t_file_display;

typedef struct s_resize_matrice
{
	int 	i;
	int 	j;
	int 	k;
	int 	x;
	int 	y;
	int 	save_y;
	int 	save_x;
	int 	l;
	int 	m;
	int 	n;
	int 	size_reduct;
}				t_resize_matrice;

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
	int 	size;
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
} 				t_cpt;

typedef struct	s_temp_bfs
{
	int			actual_path;
	int			i_queue;
	int			size_queue;
}				t_temp_bfs;

typedef struct	s_bfs
{
	int			start;
	int			end;
	int			start_paths;
	int			nb_paths;
	int			size_diago;
	int			**mtx_diago;
	int			**mtx_state;
	int			found_paths;
	int			**queue;
	int			*room_lowest;
	int			**paths;
}				t_bfs;

typedef struct s_map
{
	char	**map_name;
	char	**new_name;
	char	**map_link;
	int 	**map_co;
	int		**matrix;
	int		**new_matrix;
	t_info	inf;
	t_cpt	cpt;
	t_matrix mat;
	t_link	*tmp_link;
	t_name	*tmp_name;
	t_resize_matrice n_mat;
	t_file_display	*tmp_f_dis;
}				t_map;

t_bfs	ft_bfs(t_map map);
unsigned int	count_word(const char *s, char c);
void	print_info_map(t_name **name, t_link **link, t_map *map);
void	print_tab(char **tab);
void	free_map(char	**map);
t_link			*insert_link(char *val, int i);
t_name			*insert_name(char **val, int i);
t_file_display		*insert_line(char *line);
void	clear(t_name **name, t_link **link, t_file_display **f_dis);
int		list_len(t_name *name, t_link *link, int chose);
void	print_list(t_name *name, t_link *link);
void	init_value(t_map *map);
int		parser(t_name **name, t_link **link, t_map *map, t_file_display	**f_dis);
int   	set_map(t_name **name, t_link **link, t_map *map);
int 	set_matrix(t_map *map);
int		check_str_number(char *str);
int 	ft_strcheck(char *s1, char *s2, int chose);
int		check_valid_co(int **tab, int len);
void 	print_tab_int(int **tab, int y, int x, t_map *map);
int 	print_and_return(int i);
int			check_ant_line(t_map *map, char **line, t_file_display	**f_dis);
int			check_link_line(t_link **link, t_map *map, char *line, char **split);
int			check_name_line(t_name **name, t_map *map, char *line, char **split);
int		check_start_end(t_map *map, char **line, t_file_display	**f_dis);
int 		insert_line_lst(t_map *map, char **line, t_file_display	**f_dis, int *chose);
void	init_matrix(t_map *map);
int		check_all_link_and_name(t_map *map, int i);
int 	free_and_return(char ***split, int i);
int 	set_tab_link(t_link *tmp_link, t_map *map);
int 	set_tab_name_and_co(t_name *tmp_name, t_map *map);
int		name_cmp(char *s1, char *s2);
int 	delete_cul_de_sac(t_map *map);
int 	resize_matrix(t_map *map);
int		main(void);

/*
**	bfs1.c
*/
int			ft_foundroom(t_bfs *bfs, t_temp_bfs temp, int room);
void		ft_delactual_room(t_bfs *bfs, int path, t_temp_bfs temp);

/*
**	bfs2.c
*/
int			ft_init_queue(t_bfs *bfs);
void		ft_setqueue(t_bfs *bfs, t_temp_bfs temp);
void		remove_room_queue(t_bfs *bfs);
void		ft_pre_roomto_queue(t_bfs *bfs, t_temp_bfs temp, int room, int path);
void		ft_roomto_queue(t_bfs *bfs, t_temp_bfs temp, int room);
int			ft_foundroom(t_bfs *bfs, t_temp_bfs temp, int room);
void		ft_delactual_room(t_bfs *bfs, int path, t_temp_bfs temp);
void		ft_del_rooms(t_bfs *bfs, t_temp_bfs temp);
int			ft_size_queue(t_bfs bfs, int path);

/*
**	print.c
*/
void		print_queue(t_bfs *bfs, t_map *map);
void		print_matrix_state(t_bfs *bfs, t_map *map);
void		print_path(t_bfs *bfs, t_map *map, int path, int max_length);
void		dig_deep(t_bfs *bfs, t_map *map);

#endif
