/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 12:07:17 by cpopa         #+#    #+#                 */
/*   Updated: 2022/01/28 16:55:19 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	pipex(t_data *data, char **envp)
{
	int		fd1[2];
	int		fd2[2];
	pid_t	id_child;

	if (pipe(fd1) == -1)
		error_exit("faild pipe\n");
	id_child = fork();
	if (id_child < 0)
		error_exit("failed fork\n");
	if (id_child == 0)
		execute_start(data, envp, fd1);
	
	while (data->i < data->nr_cmd - 1)
	{
		if (data->i % 2 != 0)
		{
			if (pipe(fd2) == -1)
				error_exit("faild pipe\n");

			id_child = fork();
			if (id_child < 0)
				error_exit("failed fork\n");
			if (id_child == 0)
				execute_middle(data, envp, fd1, fd2); // execute_uneven
			close_fd(fd1);
		}
		else if (data->i % 2 == 0)
		{
			if (pipe(fd1) == -1)
				error_exit("faild pipe\n"); 

			id_child = fork();
			if (id_child < 0)
				error_exit("failed fork\n"); 
			if (id_child == 0)
				execute_middle(data, envp, fd2, fd1); // execute even 
			close_fd(fd2);
		}
		data->i++;
	}

	if (data->i == data->nr_cmd - 1)
	{
		id_child = fork();
		if (id_child < 0)
			error_exit("failed fork\n"); // error, free data, exit 
		if (id_child == 0)
		{
			if (data->i % 2 == 0)
				execute_last(data, envp, fd2); // even 
			else if (data->i % 2 != 0)
				execute_last(data, envp, fd1); // uneven 
		}
		if (data->i % 2 == 0)
			close_fd(fd2);
		else if (data->i % 2 != 0)
			close_fd(fd1);
	}
}
