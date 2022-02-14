/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/26 12:35:21 by cpopa         #+#    #+#                 */
/*   Updated: 2022/02/14 17:25:44 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	int		i;
	int		status;

	i = 0;
	if (argc < 5)
	{
		perror("incorect input\nexample: input.txt cmd1 ... cmdn output.txt");
		return (1);
	}
	data = malloc(sizeof(t_data) * 1);
	if (!data)
	{
		perror("failed data malloc\n");
		return (1);
	}
	input_data(&data, argc, argv, envp);
	pipex(data, envp);
	while (i < argc - 3)
	{
		wait(&status);
		i++;
	}
	free_all(&data);
	return (0);
}
