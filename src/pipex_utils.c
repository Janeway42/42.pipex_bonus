/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/28 14:47:50 by cpopa         #+#    #+#                 */
/*   Updated: 2022/02/14 17:52:21 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*
** "	if (ft_strncmp(*cmd, "../", 3) == 0 || ft_strncmp(*cmd, "./", 2) == 0
**		|| ft_strncmp(*cmd, "/", 1) == 0)"
** This looks first if the comand points to a local application instead of bash
** If that is the case then the path = command.
** Otherwise the program checks for the path through the PATH address.
** If there is a local application without "..'/" "./" or "/", get_path_cmd
** checks for that once the check through PATH fails before error_command.
** In case of unset PATH (path is made NULL)
** then get_path_cmd checks for a local application.
*/

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
	if (data->argv[data->arguments - 2][0] == '\0')
		error_command(data->argv[data->arguments - 2], ": command not found\n");
	cmd = ft_split(data->argv[data->arguments - 2], ' ');
	if (!cmd)
		error_exit("failed ft_split cmd end\n");
	if (ft_strncmp(*cmd, "../", 3) == 0 || ft_strncmp(*cmd, "./", 2) == 0
		|| ft_strncmp(*cmd, "/", 1) == 0)
	{
		if (access(*cmd, F_OK) == 0)
		path_out = *cmd;
	}
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
	if (data->argv[data->i + 1][0] == '\0')
		error_command(data->argv[data->i + 1], ": command not found\n");
	cmd = ft_split(data->argv[data->i + 1], ' ');
	if (!cmd)
		error_exit("failed ft_split cmd middle\n");
	if (ft_strncmp(*cmd, "../", 3) == 0 || ft_strncmp(*cmd, "./", 2) == 0
		|| ft_strncmp(*cmd, "/", 1) == 0)
	{
		if (access(*cmd, F_OK) == 0)
		path = *cmd;
	}
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

	printf("control\n");
	if (dup2(data->fd_input, 0) == -1)
		error_exit("dup2(fd_input) - execute_start - failed\n");
	if (dup2(fd1[1], 1) == -1)
		error_exit("dup2(fd1[1]) - execute_start - failed\n");
	close_fd(fd1);
	close(data->fd_input);
	if (data->argv[2][0] == '\0')
		error_command(data->argv[2], ": command not found\n");
	cmd = ft_split(data->argv[2], ' ');
	if (!cmd)
		error_exit("failed ft_split cmd start\n");
	if (ft_strncmp(*cmd, "../", 3) == 0 || ft_strncmp(*cmd, "./", 2) == 0
		|| ft_strncmp(*cmd, "/", 1) == 0)
	{
		if (access(*cmd, F_OK) == 0)
		path_in = *cmd;
	}
	else
		path_in = get_path_cmd(*cmd, data);
	if (execve(path_in, cmd, envp) == -1)
		error_exit("failed execve start\n");
}
