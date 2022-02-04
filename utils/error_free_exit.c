/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_free_exit.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/26 12:43:02 by cpopa         #+#    #+#                 */
/*   Updated: 2022/02/04 15:36:41 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	error_exit(char *str)
{
	ft_putstr_fd(str, 2);
	write(1, "\n", 1);
	exit(1);
}

void	error_command(char *cmd, char *str)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(str, 2);
	exit(127);
}

void	close_fd(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

void	free_double(char ***str)
{
	char	**temp;

	temp = *str;
	while (*temp)
	{
		free(*temp);
		temp++;
	}
	free(*str);
}

void	free_all(t_data **data)
{
	free_double(&(*data)->paths);
	free(*data);
	*data = NULL;
}
