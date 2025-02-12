/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnard <abonnard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:29:28 by abonnard          #+#    #+#             */
/*   Updated: 2025/02/12 12:29:30 by abonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

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
