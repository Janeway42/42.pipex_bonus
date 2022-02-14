/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 12:07:17 by cpopa         #+#    #+#                 */
/*   Updated: 2022/02/14 17:26:53 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	first_command(t_data *data, char **envp, int *fd)
{
	pid_t	id_child;

	id_child = fork();
	if (id_child < 0)
		error_exit("failed fork\n");
	if (id_child == 0)
		execute_start(data, envp, fd);
	close(data->fd_input);
}

static void	middle_command(t_data *data, char **envp, int *fd_a, int *fd_b)
{
	pid_t	id_child;

	id_child = fork();
	if (id_child < 0)
		error_exit("failed fork\n");
	if (id_child == 0)
		execute_middle(data, envp, fd_a, fd_b);
	close_fd(fd_a);
}

static void	last_command(t_data *data, char **envp, int *fd_a, int *fd_b)
{
	pid_t	id_child;

	id_child = fork();
	if (id_child < 0)
		error_exit("failed fork\n");
	if (id_child == 0)
	{
		if (data->i % 2 == 0)
			execute_last(data, envp, fd_a);
		else if (data->i % 2 != 0)
			execute_last(data, envp, fd_b);
	}
	if (data->i % 2 == 0)
		close_fd(fd_a);
	else if (data->i % 2 != 0)
		close_fd(fd_b);
	close(data->fd_output);
}

void	pipex(t_data *data, char **envp)
{
	int		fd1[2];
	int		fd2[2];

	if (pipe(fd1) == -1)
		error_exit("faild pipe\n");
	first_command(data, envp, fd1);
	while (data->i < data->nr_cmd)
	{
		if (data->i % 2 == 0)
		{
			if (pipe(fd2) == -1)
				error_exit("faild pipe\n");
			middle_command(data, envp, fd1, fd2);
		}
		else if (data->i % 2 != 0)
		{
			if (pipe(fd1) == -1)
				error_exit("faild pipe\n");
			middle_command(data, envp, fd2, fd1);
		}
		data->i++;
	}
	last_command(data, envp, fd1, fd2);
}
