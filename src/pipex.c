/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicn <danicn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 18:22:49 by dcruz-na          #+#    #+#             */
/*   Updated: 2022/09/03 16:31:52 by danicn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char **envp)
{
	while (ft_strncmp(*envp, "PATH", 4))
		envp++;
	return (*envp + 5);
}

char	*find_cmd_path(char **path, char *cmd, char **arr)
{
	char	*cmd_path;
	char	*cmd1;
	char	**path1;

	path1 = path;
	while (*path1)
	{
		cmd1 = ft_strjoin(*path1, "/");
		cmd_path = ft_strjoin(cmd1, cmd);
		free(cmd1);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		path1++;
	}
	return (NULL);
}

int	main(int argc, char *argv[], char *envp[])
{
	pid_t	parent;
	int		pipex[2];
	int		fds[2];

	if (argc != 5)
		return (EXIT_FAILURE);
	fds[0] = open(argv[1], O_RDONLY);
	fds[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	pipe(pipex);
	parent = fork();
	if (parent < 0)
		exit_program(pipex, fds, NULL, NULL);
	else if (parent == 0)
		child_process(pipex, envp, fds, argv);
	else
		parent_process(pipex, envp, fds, argv);
	return (EXIT_SUCCESS);
}

int	child_process(int *pipex, char**envp, int *fds, char **argv)
{
	char	**path;
	char	**arr;
	char	*cmd_path;

	path = ft_split(find_path(envp), ':');
	if (path == NULL)
		exit_program(pipex, fds, NULL, NULL);
	arr = ft_split(argv[2], ' ');
	if (arr == NULL)
		exit_program(pipex, fds, NULL, path);
	cmd_path = find_cmd_path(path, arr[0], arr);
	if (cmd_path == NULL)
		exit_program(pipex, fds, arr, path);
	free(arr[0]);
	arr[0] = cmd_path;
	dup2(pipex[1], 1);
	close(pipex[0]);
	dup2(fds[0], 0);
	if (execve(arr[0], arr, envp) == -1)
		exit_program(pipex, fds, arr, path);
	free_path(path, arr);
	close_child(pipex, &fds[0], &fds[1]);
	return (EXIT_SUCCESS);
}

int	parent_process(int *pipex, char **envp, int *fds, char **argv)
{
	char	**path;
	char	**arr;
	char	*cmd_path;

	path = ft_split(find_path(envp), ':');
	if (path == NULL)
		exit_program(pipex, fds, NULL, NULL);
	arr = ft_split(argv[3], ' ');
	if (arr == NULL)
		exit_program(pipex, fds, NULL, path);
	cmd_path = find_cmd_path(path, arr[0], arr);
	if (cmd_path == NULL)
		exit_program(pipex, fds, arr, path);
	free(arr[0]);
	arr[0] = cmd_path;
	dup2(pipex[0], 0);
	close(pipex[1]);
	dup2(fds[1], 1);
	if (execve(arr[0], arr, envp) == -1)
		exit_program(pipex, fds, arr, path);
	close_parent(pipex, &fds[0], &fds[1]);
	free_path(path, arr);
	return (EXIT_SUCCESS);
}
