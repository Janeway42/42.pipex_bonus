/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/26 12:35:21 by cpopa         #+#    #+#                 */
/*   Updated: 2022/01/29 10:53:50 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	
//	system("leaks pipex");
	data = malloc(sizeof(t_data) * 1);
	if (!data)
		return (-1);
	if (argc < 5)
	{
		perror("incorect input\nexample: input.txt cmd1 ... cmdn output.txt");
		return (1);
	}
	input_data(&data, argc, argv, envp);
	pipex(data, envp);
//	free_all(&data);
	return (0);
}
