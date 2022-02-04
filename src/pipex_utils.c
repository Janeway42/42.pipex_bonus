/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/28 14:47:50 by cpopa         #+#    #+#                 */
/*   Updated: 2022/02/04 15:05:50 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*
** End function
*/

void	execute_last(t_data *data, char **envp, int *fd_x)
{
	char	**cmd;
	char	*path_out;

	if (dup2(fd_x[0], 0) == -1)
		error_exit("dup2(fd_x[0]) - execute_last - failed\n");
	close_fd(fd_x);
	if (dup2(data->fd_output, 1) == -1)
		error_exit("dup2(output) - execute_last - failed\n");
	close(data->fd_output);
	cmd = ft_split(data->argv[data->arguments - 2], ' ');
	if (!cmd)
		error_exit("failed split cmd end\n");
	if (access(*cmd, F_OK) == 0)
		path_out = *cmd;
	else
		path_out = get_path_cmd(*cmd, data);
	if (execve(path_out, cmd, envp) == -1)
		error_exit("failed execve last\n");
}

/*
** Middle function
*/

void	execute_middle(t_data *data, char **envp, int *fd_a, int *fd_b)
{
	char	**cmd;
	char	*path;

	if (dup2(fd_a[0], 0) == -1)
		error_exit("dup2(fd_a[0]) - execute_middle - failed\n");
	if (dup2(fd_b[1], 1) == -1)
		error_exit("dup2(fd_b[1]) - execute_middle - failed\n");
	close_fd(fd_a);
	close_fd(fd_b);
	cmd = ft_split(data->argv[data->i + 1], ' ');
	if (!cmd)
		error_exit("failed split cmd middle\n");
	if (access(*cmd, F_OK) == 0)
		path = *cmd;
	else
		path = get_path_cmd(*cmd, data);
	if (execve(path, cmd, envp) == -1)
		error_exit("failed execve middle\n");
}

/*
** Start function
*/

void	execute_start(t_data *data, char **envp, int *fd1)
{
	char	**cmd;
	char	*path_in;

	if (dup2(data->fd_input, 0) == -1)
		error_exit("dup2(fd_input) - execute_start - failed\n");
	if (dup2(fd1[1], 1) == -1)
		error_exit("dup2(fd1[1]) - execute_start - failed\n");
	close_fd(fd1);
	close(data->fd_input);
	cmd = ft_split(data->argv[2], ' ');
	if (!cmd)
		error_exit("failed split cmd start\n");
	if (access(*cmd, F_OK) == 0)
		path_in = *cmd;
	else
		path_in = get_path_cmd(*cmd, data);
	if (execve(path_in, cmd, envp) == -1)
		error_exit("failed execve start\n");
}
