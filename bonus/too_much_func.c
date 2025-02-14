/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   too_much_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnard <abonnard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:42:54 by abonnard          #+#    #+#             */
/*   Updated: 2025/02/14 16:40:33 by abonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

static void	write_here_doc(char **argv)
{
	char	*line;
	int		tmp_fd;

	tmp_fd = open(".here_doc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp_fd < 0)
	{
		pipex_perror(".here_doc_tmp", NO_FILE);
		exit(1);
	}
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0
			&& line[ft_strlen(argv[2])] == '\n')
		{
			free(line);
			break ;
		}
		write(tmp_fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	close(tmp_fd);
}

void	handle_here_doc(t_pipex *pipex, char **argv, int argc)
{
	write_here_doc(argv);
	pipex->infile = open(".here_doc_tmp", O_RDONLY);
	pipex->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (pipex->infile < 0 || pipex->outfile < 0)
	{
		pipex_perror(".here_doc_tmp", NO_FILE);
		exit(1);
	}
}
