/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 12:07:01 by cpopa         #+#    #+#                 */
/*   Updated: 2022/02/01 11:13:45 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	*join_three(char *str1, char *c, char *str2)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 2));
	if (!result)
		return (NULL);
	while (str1[i] != '\0')
	{
		result[i] = str1[i];
		i++;
	}
	result[i] = *c;
	i++;
	while (str2[j] != '\0')
	{
		result[i + j] = str2[j];
		j++;
	}
	result[i + j] = '\0';
	return (result);
}

static int	get_path_position(char **envp, char *str)
{
	int		i;

	i = 0;
	while (*envp)
	{
		if (ft_strncmp(*envp, str, 5) == 0)
			return (i);
		i++;
		envp++;
	}
	return (-1);
}

static char	**get_paths(char **envp)
{
	char	**paths;
	int		position;

	position = get_path_position(envp, "PATH=");
	if (position < 0)
		error_exit("error path location");
	paths = ft_split(envp[position] + 5, ':');
	if (!paths)
		error_exit("error paths");
	return (paths);
}

char	*get_path_cmd(char *comand, t_data *data)
{
	char	**temp;
	char	*the_one;

	temp = data->paths;
	while (*temp)
	{
		the_one = join_three(*temp, "/", comand);
		if (the_one == NULL)
			error_exit("error the one\n");
		if (access(the_one, F_OK) == 0)
			return (the_one);
		free(the_one);
		temp++;
	}
	error_exit("command invalid\n");
	return (0);
}

void	input_data(t_data **data, int argc, char **argv, char **envp)
{
	(*data)->argv = argv;
	(*data)->arguments = argc;
	(*data)->nr_cmd = argc - 3;
	(*data)->fd_input = open(argv[1], O_RDONLY, 0644);
	if ((*data)->fd_input == -1)
		error_exit("fd_input failed\n");
	(*data)->fd_output = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if ((*data)->fd_output == -1)
		error_exit("fd_output failed\n");
	(*data)->i = 2;
	(*data)->paths = get_paths(envp);
}
