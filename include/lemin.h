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
} 				t_info;

typedef struct s_cpt
{
	int		error;
	int		i;
	int		j;
	unsigned int	len;
	unsigned int	k;
	int 	start_name;
	int 	start_link;
} 				t_cpt;

typedef struct s_map
{
	char	**map_name;
	char	**map_link;
	int 	**map_co;
	int		**matrix;
	t_info	inf;
	t_cpt	cpt;
	t_link	*tmp_link;
	t_name	*tmp_name;
}				t_map;

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
int 	ft_strcheck(char *s1, char *s2);
int		check_valid_co(int **tab, int len);
void 	print_tab_int(int **tab, int y, int x);
int 	print_and_return(int i);
int			check_ant_line(t_map *map, char *line);
int			check_link_line(t_link **link, t_map *map, char *line, char **split);
int			check_name_line(t_name **name, t_map *map, char *line, char **split);
void		check_start_end(t_map *map, char **line);
int		main(void);

#endif
