/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnard <abonnard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:32:10 by abonnard          #+#    #+#             */
/*   Updated: 2025/02/02 15:30:24 by abonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child_process(char **argv, char **envp, t_pipex *pipex)
{
	if (dup2(pipex->pipe[1], STDOUT_FILENO) == -1)
	{
		pipex_perror(NULL, DUP_ERR);
		exit(1);
	}
	if (dup2(pipex->infile, STDIN_FILENO) == -1)
	{
		pipex_perror(NULL, DUP_ERR);
		exit(1);
	}
	close(pipex->pipe[0]);
	execute_cmd(argv + 2, envp, pipex);
}

void	parent_process(char **argv, char **envp, t_pipex *pipex)
{
	if (dup2(pipex->pipe[0], STDIN_FILENO) == -1)
	{
		pipex_perror(NULL, DUP_ERR);
		exit(1);
	}
	if (dup2(pipex->outfile, STDOUT_FILENO) == -1)
	{
		pipex_perror(NULL, DUP_ERR);
		exit(1);
	}
	close(pipex->pipe[1]);
	execute_cmd(argv + 3, envp, pipex);
}

void	execute_cmd(char **argv, char **envp, t_pipex *pipex)
{
	pipex->cmd_args = ft_split(argv[0], ' ');
	if (!pipex->cmd_args)
	{
		pipex_perror(NULL, NO_MEMORY);
		exit(1);
	}
	if (!pipex->cmd_paths || !pipex->cmd_args[0])
	{
		free_child(pipex);
		cmd_not_found(argv[0]);
	}
	pipex->cmd = get_cmd(pipex->cmd_paths, pipex->cmd_args[0]);
	if (!pipex->cmd)
	{
		free_child(pipex);
		cmd_not_found(pipex->cmd_args[0]);
	}
	if (execve(pipex->cmd, pipex->cmd_args, envp) == -1)
	{
		free_child(pipex);
		pipex_perror(pipex->cmd, CMD_FAIL);
		exit(126);
	}
}
