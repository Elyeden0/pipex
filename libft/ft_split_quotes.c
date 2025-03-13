/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnard <abonnard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:08:17 by abonnard          #+#    #+#             */
/*   Updated: 2025/03/10 12:48:30 by abonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(const char *s, char c)
{
	size_t	count;
	int		in_quotes;

	count = 0;
	in_quotes = 0;
	while (*s)
	{
		if (*s == '"' || *s == '\'')
			in_quotes = !in_quotes;
		if (*s != c && (s[1] == c || s[1] == '\0') && !in_quotes)
			count++;
		s++;
	}
	return (count);
}

static char	*get_next_word(const char **s, char c)
{
	const char	*start;
	char		*word;
	int			in_quotes;

	while (**s == c)
		(*s)++;
	start = *s;
	in_quotes = 0;
	while (**s && (**s != c || in_quotes))
	{
		if (**s == '"' || **s == '\'')
			in_quotes = !in_quotes;
		(*s)++;
	}
	word = ft_substr(start, 0, *s - start);
	return (word);
}

char	**ft_split_quotes(const char *s, char c)
{
	char	**result;
	size_t	words;
	size_t	i;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	result = (char **)malloc((words + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (i < words)
	{
		result[i] = get_next_word(&s, c);
		i++;
	}
	result[i] = NULL;
	return (result);
}
