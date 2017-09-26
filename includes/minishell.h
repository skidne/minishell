/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgore <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 16:54:22 by pgore             #+#    #+#             */
/*   Updated: 2017/02/23 21:36:44 by pgore            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <sys/stat.h>
# include <errno.h>
# include <signal.h>
# include <dirent.h>
# include <stdlib.h>
# include <termios.h>
# include "../libft/libft.h"

# define SHNAME "minishell"
# define ENV "env"
# define EXIT "exit"
# define SETENV "setenv"
# define UNSET "unsetenv"
# define CD "cd"
# define ECHOO "echo"
# define BSLASH '\\'
# define QUOTE '\''
# define DQUOTE '\"'
# define DOLLAR '$'
# define SEPAR ';'
# define PUTEND ft_putchar('\n')
# define KDS "\x1B[1m\033[33m"
# define KDS2 "\x1B[1m\033[32m"
# define KMAG "\x1B[0m\033[32m"
# define KWHT "\033[37m"
# define KNRM "\x1B[0m"
# define FUCK_NORME(x, y) (ft_strstr(x, y) || ft_strstr(x, "ECHO"))
# define MSIZE 200
# define NOEXEC 3
# define NOEXIST 2
# define STDIN 0
# define STDERR 2
# define PROMPT ft_putstr(KDS" $ "KWHT);

# define LCONT(list_cell, t_type) ((t_type)((list_cell)->content))
# define LSTR(list_cell) LCONT(list_cell, char*)
# define LTONEXT(list_cell) ((list_cell) = ((list_cell)->next))

typedef struct	s_msh
{
	char		*line;
	char		*nextline;
	char		**strenv;
	t_list		*env;
	char		**arg;
	char		*comm;
	int			ok;
	int			flg;
}				t_msh;

struct termios	g_stored;

void			ft_err_comm(char *name);
void			ft_fatal(char *msg);
void			ft_err_mem();
void			ft_err_perm(char *name);
void			ft_err(char *str, char *name);
void			clear_win(char **av, char **envp);
t_list			*cpy_env(char **envp);
char			**lst_to_str(t_list *lenv);
int				prepare_env(t_msh *k);
int				display_env(t_list *env);
t_list			*redo_env(t_list **env, char *c);
int				check_if_dir(t_msh *k);
char			**go_home(t_list *env);
int				set_env(t_msh *k);
int				ft_count_name(char *arg);
int				found_env(t_list *lst, char *name);
void			delete_env(t_list **env, char *name);
int				unset_env(t_msh *k);
void			specialcheck(t_msh *k);
void			do_commands(t_msh *k);
char			*do_bslash(char *line);
char			*do_quote(char *put, char *line, char q);
char			*for_echo(t_msh *k);
char			*echo_add(t_list *env, char *name);
char			*ft_equaltrim(char *str);
void			add_echo_extra(t_msh *k, char **new, int *i);
void			go_signal(t_list *env);
void			handle_signal(int sign);
void			echo_on(void);
void			echo_off(void);
int				get_input(t_msh *k);
int				is_empty(char *line);
void			separate(char **line, char **next);
void			init_data(t_msh *sh_data);
void			free_all(t_msh *k);
void			free_dbl(char **str);
void			ft_delmem(void **data);
void			del_env_cell(void *str, size_t size);
char			*ft_lstsearch(t_list *lst, char *cont);
char			*go_next(char *path);
char			*found_path(t_list *env, char *arg);
char			*found_path_mid(char **path, char *arg);
int				exit_prog(t_msh *k);
void			put_prompt(t_list *env);
void			look_for_home(t_list *env, char **buff);
void			replace_home(char *home, char **buff);
t_list			*find_list_env(char *arg, t_list *env, size_t *found_len);
char			*env_get_val(char *arg, t_list *env);
int				find_that_env(char *name, char *arg);
int				walk_through(char *line);
void			fuck_you_norme(char *line, char *new, int i, int j);

#endif
