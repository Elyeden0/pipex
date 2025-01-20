/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnard <abonnard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:32:10 by abonnard          #+#    #+#             */
/*   Updated: 2025/01/20 14:50:19 by abonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child_process(char **argv, char **envp, t_pipex *pipex)
{
	dup2(pipex->pipe[1], STDOUT_FILENO);
	dup2(pipex->infile, STDIN_FILENO);
	close(pipex->pipe[0]);
	execute_cmd(argv, envp, pipex);
}

void	parent_process(char **argv, char **envp, t_pipex *pipex)
{
	dup2(pipex->pipe[0], STDIN_FILENO);
	dup2(pipex->outfile, STDOUT_FILENO);
	close(pipex->pipe[1]);
	execute_cmd(argv + 2, envp, pipex);
}

void	execute_cmd(char **argv, char **envp, t_pipex *pipex)
{
	pipex->cmd_args = ft_split(argv[2], ' ');
	if (!pipex->cmd_args)
		error_msg("Split failed");
	pipex->cmd = get_cmd(pipex->cmd_paths, pipex->cmd_args[0]);
	if (!pipex->cmd)
	{
		free_child(pipex);
		cmd_not_found(pipex->cmd_args[0]);
		exit(1);
	}
	execve(pipex->cmd, pipex->cmd_args, envp);
}
