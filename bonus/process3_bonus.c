/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process3_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnard <abonnard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:15:55 by abonnard          #+#    #+#             */
/*   Updated: 2025/02/14 16:57:40 by abonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	create_pipes_recursive(int *pipes, int argc, int index)
{
	if (index >= argc - 4)
		return ;
	create_pipe(pipes + index * 2);
	create_pipes_recursive(pipes, argc, index + 1);
}

void	wait_for_children_recursive(t_pipex *pipex, int argc, int index)
{
	if (index >= argc - 3)
		return ;
	wait_for_child(pipex->pid2);
	wait_for_children_recursive(pipex, argc, index + 1);
}
