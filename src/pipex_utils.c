/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/28 14:47:50 by cpopa         #+#    #+#                 */
/*   Updated: 2022/01/28 15:20:18 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*
** End functions
*/

void	execute_last(t_data *data, char **envp, int *fd_x)
{
//	int		fd_output;
	char	**cmd;
	char	*path_out;

//	fd_output = open(data->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);  // how to append if command asks 
//	if (fd_output == -1)
//		error_free_exit("fd_output failed\n");
	if (dup2(fd_x[0], 0) == -1)
		error_exit("dup2 failed\n");
	if (dup2(data->fd_output, 1) == -1)
		error_exit("dup2 failed\n");
	close_fd(fd_x);
	close(data->fd_output);

	cmd = ft_split(data->argv[data->i], ' ');
	path_out = get_path_cmd(*cmd, data);

	if (execve(path_out, cmd, envp) == -1)
		error_exit("failed execve\n");
}

/*
** Middle functions
*/

void	execute_middle(t_data *data, char **envp, int *fd_a, int *fd_b)
{
	char	**cmd;
	char	*path;

	if (dup2(fd_a[0], 0) == -1)
		error_exit("dup2(fd[1]-exec2) failed\n");
	if (dup2(fd_b[1], 1) == -1)
		error_exit("dup2(fd_output) failed\n");
	close_fd(fd_a);
	close_fd(fd_b);
	
	cmd = ft_split(data->argv[data->i], ' ');
	path = get_path_cmd(*cmd, data);

	if (execve(path, cmd, envp) == -1)
		error_exit("failed execve 2\n");
}

/*
** Start function
*/

void	execute_start(t_data *data, char **envp, int *fd1)
{
//	int		fd_input;
	char	**cmd;
	char	*path_in;

//	fd_input = open(data->input, O_RDONLY, 0644);
//	if (fd_input == -1)
//		error_exit("fd_input failed\n", &data);
	if (dup2(data->fd_input, 0) == -1)
		error_exit("dup2(fd_input) failed\n");
	if (dup2(fd1[1], 1) == -1)
		error_exit("dup2(fd[1]-exec1) failed\n");
	close_fd(fd1);
	close(data->fd_input);

	cmd = ft_split(data->argv[2], ' ');
	path_in = get_path_cmd(*cmd, data);

	if (execve(path_in, cmd, envp) == -1)
		error_exit("failed execve 1\n");
}
