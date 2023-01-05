/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 21:37:55 by jinholee          #+#    #+#             */
/*   Updated: 2023/01/05 13:33:35 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	convert_back(char **split, char c)
{
	char	*str;

	while (*split)
	{
		str = *split++;
		while (*str)
		{
			if (*str == -1)
				*str = c;
			str++;
		}
	}
}

int	is_blank(char *str)
{
	size_t	idx;

	idx = 0;
	while (str[idx])
	{
		if (str[idx] != ' ')
			return (0);
		idx++;
	}
	return (1);
}

char	**split_with_char(char *raw_input, char c)
{
	char	*converted;
	char	**split;
	char	opening;
	size_t	idx;

	converted = ft_strdup(raw_input);
	idx = 0;
	opening = 0;
	while (converted[idx])
	{
		if (opening)
		{
			if (converted[idx] == c)
				converted[idx] = -1;
			else if (converted[idx] == opening)
				opening = 0;
		}
		else if (converted[idx] == '\'' || converted[idx] == '\"')
			opening = converted[idx];
		idx++;
	}
	split = ft_split(converted, c);
	convert_back(split, c);
	free(converted);
	return (split);
}
