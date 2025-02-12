/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnard <abonnard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:27:30 by abonnard          #+#    #+#             */
/*   Updated: 2025/02/12 12:29:24 by abonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	close_pipes(t_pipex *pipex)
{
    close(pipex->pipe[0]);
    close(pipex->pipe[1]);
}

void	free_parent(t_pipex *pipex)
{
    int	i;

    i = 0;
    close(pipex->infile);
    close(pipex->outfile);
    while (pipex->cmd_paths[i])
    {
        free(pipex->cmd_paths[i]);
        i++;
    }
    free(pipex->cmd_paths);
}

void	free_child(t_pipex *pipex)
{
    int	i;

    i = 0;
    while (pipex->cmd_args[i])
    {
        free(pipex->cmd_args[i]);
        i++;
    }
    free(pipex->cmd_args);
    free(pipex->cmd);
}

