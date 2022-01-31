/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/26 12:36:42 by cpopa         #+#    #+#                 */
/*   Updated: 2022/01/31 15:54:14 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/types.h>
# include <fcntl.h>
# include <stdio.h>
# include "libft.h"

typedef struct s_data {
	char	**argv;
	char	**paths;
	int		fd_input;
	int		fd_output;
	int		arguments;
	int		nr_cmd;
	int		i;
}				t_data;

void	pipex(t_data *data, char **envp);

/*
** input data
*/

void	input_data(t_data **data, int argc, char **argv, char **envp);
char	*get_path_cmd(char *comand, t_data *data);

/*
** pipex functions
*/

void	execute_start(t_data *data, char **envp, int *fd1);
void	execute_middle(t_data *data, char **envp, int *fd_a, int *fd_b);
void	execute_last(t_data *data, char **envp, int *fd_x);

/*
** error free exit
*/

void	free_double(char ***str);
void	error_exit(char *str);
void	close_fd(int *fd);
void	free_all(t_data **data);

#endif