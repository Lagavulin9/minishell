/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idxinholee <idxinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 21:35:47 by idxinholee          #+#    #+#             */
/*   Updated: 2023/01/08 21:00:31 by idxinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_redirection(t_redirecion **head, char **split, size_t *index)
{
	t_redirecion	*block;
	t_redirecion	*new;
	size_t			idx;

	new = ft_calloc(1, sizeof(t_redirecion));
	if (!*head)
		*head = new;
	else
	{
		block = *head;
		while (block->next)
			block = block->next;
		block->next = new;
	}
	idx = *index;
	if (*split[idx] == '<' || *split[idx] == '>')
	{
		new->type = *split[idx++];
		if (*split[idx] == '<' || *split[idx] == '>')
			new->type += *split[idx++];
		new->file_name = ft_strdup(split[idx]);
	}
	*index = idx;
}

char	**set_redirections(t_exec_block *block, char **split)
{
	char	buffer[BUFFER_SIZE];
	size_t	buffer_index;
	size_t	idx;

	idx = 0;
	buffer_index = 0;
	while (split[idx])
	{
		if (*split[idx] == '<' || *split[idx] == '>')
			add_redirection(&block->redirection, split, &idx);
		else
		{
			ft_memcpy(buffer + buffer_index++, " ", 1);
			ft_memcpy(buffer + buffer_index, split[idx], ft_strlen(split[idx]));
			buffer_index += ft_strlen(split[idx]);
		}
		idx++;
	}
	buffer[buffer_index] = 0;
	free_split(split);
	return (split_with_char(buffer, ' '));
}

// char	**set_arguments(char **split)
// {
// 	char	**args;
// 	char	*output;
// 	size_t	idx;
// 	size_t	idxdx;

// 	idx = 0;
// 	while (split[idx])
// 		idx++;
// 	args = ft_calloc(idx + 1, sizeof(char *));
// 	idx = 0;
// 	idxdx = 0;
// 	while (split[idx])
// 	{
// 		output = quote_handler(split[idx++]);
// 		if (output)
// 			args[idxdx++] = output;
// 	}
// 	return (args);
// }

int	is_quoted(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

char	**lst_to_arr(t_list *lst)
{
	t_list	*elem;
	char	**arr;
	size_t	i;

	arr = ft_malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	i = 0;
	elem = lst;
	while (elem)
	{
		arr[i++] = ft_strdup(elem->copy);
		elem = elem->next;
	}
	arr[i] = 0;
	return (arr);
}

void	add_string_arg_to_list(t_list **args, char *str)
{
	char	**split;
	char	*expanded;
	size_t	idx;

	idx = 0;
	expanded = expand_env(tilde_replace(str));
	split = ft_split(expanded, ' ');
	while (split[idx])
		ft_lstadd_back(args, ft_lstnew(split[idx++]));
	free(expanded);
	free_split(split);
}

char	**set_arguments(char **split)
{
	t_list	*args;
	char	**arr;
	char	*replaced;
	size_t	i;

	args = 0;
	i = 0;
	while (split[i])
	{
		if (!is_quoted(split[i]))
			add_string_arg_to_list(&args, split[i]);
		else
		{
			replaced = quote_handler(split[i]);
			ft_lstadd_back(&args, ft_lstnew(replaced));
			free(replaced);
		}
		i++;
	}
	arr = lst_to_arr(args);
	ft_lstclear(&args, free);
	return (arr);
}
