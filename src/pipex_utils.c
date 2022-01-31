/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/28 14:47:50 by cpopa         #+#    #+#                 */
/*   Updated: 2022/01/31 14:57:32 by cpopa         ########   odam.nl         */
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

//	printf("i end: %d\n", data->i);
//	system("lsof -c pipex");

	if (dup2(fd_x[0], 0) == -1)
		error_exit("dup2 fd_x[0] failed\n");
	close_fd(fd_x);

	if (dup2(data->fd_output, 1) == -1)
		error_exit("dup2 output failed\n");
	close(data->fd_output);

	cmd = ft_split(data->argv[data->arguments - 2], ' ');
//	printf("cmd end: %s, i: %d\n", cmd[0], data->i);
	path_out = get_path_cmd(*cmd, data);

	if (execve(path_out, cmd, envp) == -1)
		error_exit("failed execve\n");
}

/*
** Middle function
*/

void	execute_middle(t_data *data, char **envp, int *fd_a, int *fd_b)
{
	char	**cmd;
	char	*path;

	if (dup2(fd_a[0], 0) == -1)
		error_exit("dup2(fd_a[0]-exec middle) failed\n");
	if (dup2(fd_b[1], 1) == -1)
		error_exit("dup2(fd_b[1] - exec middle) failed\n");

//	system("lsof -c pipex");

	close_fd(fd_a);
	close_fd(fd_b);
	
	cmd = ft_split(data->argv[data->i + 1], ' ');
//	printf("cmd middle: %s, i: %d\n", cmd[0], data->i);
	path = get_path_cmd(*cmd, data);

	if (execve(path, cmd, envp) == -1)
		error_exit("failed execve 2\n");
}

/*
** Start function
*/

void	execute_start(t_data *data, char **envp, int *fd1)
{
	char	**cmd;
	char	*path_in;

//	printf("i start: %d\n", data->i);

	if (dup2(data->fd_input, 0) == -1)
		error_exit("dup2(fd_input) failed\n");
	if (dup2(fd1[1], 1) == -1)
		error_exit("dup2(fd[1]-exec start) failed\n");

	close_fd(fd1);
	close(data->fd_input);

	cmd = ft_split(data->argv[2], ' ');
//	printf("cmd start: %s, i: %d\n", *cmd, data->i);
	path_in = get_path_cmd(*cmd, data);

	if (execve(path_in, cmd, envp) == -1)
		error_exit("failed execve 1\n");
}
