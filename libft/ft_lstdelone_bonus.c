/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnard <abonnard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:19:23 by abonnard          #+#    #+#             */
/*   Updated: 2025/03/12 15:25:42 by abonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdelone_bonus(t_Llist *lst, void (*del)(void*))
{
	if (lst)
	{
		if (del)
			del(lst->content);
		free(lst);
	}
}
