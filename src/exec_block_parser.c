/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_block_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 10:44:34 by jinholee          #+#    #+#             */
/*   Updated: 2023/01/08 18:06:58 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exec_block	*str_to_block(char *str)
{
	t_exec_block	*exec;
	t_redirecion	*elem;
	char			*replaced;
	char			**splited;

	exec = new_block();
	replaced = str_replace(str, "<", " < ");
	replaced = str_replace(replaced, ">", " > ");
	splited = set_redirections(exec, split_with_char(replaced, ' '));
	exec->args = set_arguments(splited);
	if (exec->args[0])
		exec->command = ft_strdup(exec->args[0]);
	elem = exec->redirection;
	while (elem)
	{
		if (elem->type == HERE_DOC)
			here_doc_handler(elem);
		elem = elem->next;
	}
	free(replaced);
	free(splited);
	return (exec);
}

t_exec_block	*exec_block_parser(char *raw_input)
{
	char			**splited;
	size_t			idx;
	t_exec_block	*exec_blocks;

	idx = 0;
	exec_blocks = 0;
	splited = split_with_char(raw_input, '|');
	while (splited[idx])
		add_block(&exec_blocks, str_to_block(splited[idx++]));
	free(splited);
	return (exec_blocks);
}
