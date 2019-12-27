/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lemin.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hmichel <hmichel@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 13:30:44 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/19 18:02:57 by seanseau    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/includes/ft_printf.h"

typedef struct s_name
{
	char 	*name;
	int		index;
	int 	co_y;
	int			co_x;
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
	unsigned int	len;
	unsigned int	k;
	int 		start_name;
	int			start_link;
}				t_cpt;

typedef struct s_path
{
    int			*n_path;
    int			state;
    int			next_room;
    int			next_room2;
}				t_path;

typedef struct 	s_map
{
	char		**map_name;
	char		**map_link;
	int 		**map_co;
	int			**matrix;
	t_info		inf;
	t_cpt		cpt;
	t_matrix	mat;
	t_link		*tmp_link;
	t_name		*tmp_name;
	t_path  	path;
}				t_map;

typedef struct 	s_prealgo
{
	int			start;
	int			end;
	//int			path_name; //numero du chemin
	int			nb_path; //numbre de chemin au depart
	//int			act_index; //index de la salle actuel
	int			size_diago; //taille matrix diago
	int			**mtx_diago; //matrix diago
	int			**mtx_state; //matrix signe salle
}				t_prealgo;

typedef	struct	s_tempalgo
{
	int			nb_links;
	int			i;
	int			next_index;
	int			act_index; 
	int			path_name; 
	int			actual_link;
	int			step;
}				t_tempalgo;

typedef struct	s_tempclean
{
	int			i;
	int			step;
	int			path_count;
	int			*order;
	int			act_index;
	int			nb_node;

}				t_tempclean;

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
}				t_bfs;

typedef struct	s_temp_bfs
{
	int			actual_path;
	int			i_queue;
}				t_temp_bfs;

typedef struct	s_res
{
	int			*size_paths;
	int			**paths;
}				t_res;

t_bfs	ft_bfs(t_map map);
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
int			check_ant_line(t_map *map, char *line);
int			check_link_line(t_link **link, t_map *map, char *line, char **split);
int			check_name_line(t_name **name, t_map *map, char *line, char **split);
void		check_start_end(t_map *map, char **line);
void	init_matrix(t_map *map);
void	check_all_link_and_name(t_map *map, int i);
int 	free_and_return(char ***split, int i);
int 	set_tab_link(t_link *tmp_link, t_map *map);
int 	set_tab_name_and_co(t_name *tmp_name, t_map *map);
int		name_cmp(char *s1, char *s2);
int		main(void);

/*
**	bfs hmichel
*/
//int			ft_nbpaths_max(t_map map);
//int			ft_set_prealgo(t_map map, t_prealgo *pa);
//void		*ft_allpaths(t_map map, t_prealgo *pa);
//int			ft_bfs(t_map map);
#endif
