/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnard <abonnard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:15:47 by abonnard          #+#    #+#             */
/*   Updated: 2025/02/14 16:58:55 by abonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	create_pipe(int *pipe_fd)
{
	if (pipe(pipe_fd) < 0)
	{
		pipex_perror(NULL, PIPE_ERR);
		exit(1);
	}
}

void	close_pipe(int fd)
{
	close(fd);
}

void	wait_for_child(pid_t pid)
{
	waitpid(pid, NULL, 0);
}

void	dup_fds(int fd1, int fd2)
{
	if (dup2(fd1, fd2) < 0)
	{
		pipex_perror(NULL, DUP_ERR);
		exit(1);
	}
}

void	close_all_pipes(int *pipes, int count)
{
	if (count <= 0)
		return ;
	close_pipe(pipes[count - 1]);
	close_all_pipes(pipes, count - 1);
}
