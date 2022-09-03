/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danicn <danicn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 16:18:38 by danicn            #+#    #+#             */
/*   Updated: 2022/09/03 16:18:53 by danicn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include "libft.h"

int		child_process(int *pipex, char**envp, int *fds, char **argv);
int		parent_process(int *pipex, char **envp, int *fds, char **argv);
char	*find_path(char **envp);
char	*find_cmd_path(char **path, char *cmd, char **arr);
void	close_child(int *pipex, int *fd1, int *fd2);
void	close_parent(int *pipex, int *fd1, int *fd2);
void	free_path(char **path, char **arr);
void	exit_program(int *pipex, int *fds, char **arr, char **path);

#endif