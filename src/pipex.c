/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicn <danicn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 18:22:49 by dcruz-na          #+#    #+#             */
/*   Updated: 2022/08/24 00:26:15 by danicn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char **envp)
{
	while (ft_strncmp(*envp, "PATH", 4))
		envp++;
	return (*envp + 5);
}

char	*find_cmd_path(char **path, char *cmd)
{
	char	*cmd_path;
	char	*cmd1;

	while (*path)
	{
		cmd1 = ft_strjoin(*path, "/");
		cmd_path = ft_strjoin(cmd1, cmd);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd1);
		free(cmd_path);
		path++;
	}
	return (NULL);
}

int	main(int argc, char *argv[], char *envp[])
{
	pid_t	parent;
	int		pipex[2];
	int		fdinit;
	int		fdfinal;

	if (argc != 5)
		return (1);
	fdinit = open(argv[1], O_RDONLY);
	fdfinal = open(argv[4], O_WRONLY | O_CREAT, S_IRWXU);
	pipe(pipex);
	parent = fork();
	if (parent < 0) 
	{
		close_parent(pipex, fdinit, fdfinal);
		return (1);
	}
	else if (parent == 0)
	{
		child_process(pipex, envp, &fdinit, argv);
		close_child(pipex, &fdinit, &fdfinal);
	}
	else
	{
		wait(NULL);
		parent_process(pipex, envp, &fdfinal, argv);
		close_parent(pipex, &fdinit, &fdfinal);
	}
	return (0);
}

void	child_process(int *pipex, char**envp, int *fdinit, char **argv)
{
	char	**path;
	char	**arr;
	char	*cmd_path;

	path = ft_split(find_path(envp), ':');
	arr = ft_split(argv[2], ' ');
	cmd_path = find_cmd_path(path, arr[0]);
	if (!cmd_path)
	{
		free_path(path, arr, cmd_path);
		return ;
	}
	free(arr[0]);
	arr[0] = cmd_path;
	dup2(pipex[1], 1);
	close(pipex[0]);
	dup2(*fdinit, 0);
	execve(arr[0], arr, envp);
	free_path(path, arr, cmd_path);
}

void	parent_process(int *pipex, char **envp, int *fdfinal, char **argv)
{
	char	**path;
	char	**arr;
	char	*cmd_path;

	path = ft_split(find_path(envp), ':');
	arr = ft_split(argv[3], ' ');
	cmd_path = find_cmd_path(path, arr[0]);
	if (!cmd_path)
	{
		free_path(path, arr, cmd_path);
		return ;
	}
	free(arr[0]);
	arr[0] = cmd_path;
	dup2(pipex[0], 0);
	close(pipex[1]);
	dup2(*fdfinal, 1);
	execve(arr[0], arr, envp);
	free_path(path, arr, cmd_path);
}
