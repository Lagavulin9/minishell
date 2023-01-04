/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 21:33:57 by jinholee          #+#    #+#             */
/*   Updated: 2023/01/04 18:06:02 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_block(t_exec_block *block)
{
	size_t			i;
	t_redirecion	*elem;

	i = 0;
	fprintf(stderr,"==========================\n");
	fprintf(stderr,"cmd: %s\nargs:", block->command);
	while (block->args[i])
		fprintf(stderr,"%s, ", block->args[i++]);
	fprintf(stderr,"\n");
	elem = block->redirection;
	while (elem)
	{
		fprintf(stderr,"file: %s, type: %d\n", \
			elem->file_name, elem->type);
		elem = elem->next;
	}
	fprintf(stderr,"==========================\n");
}

t_exec_block	*block_new(void)
{
	t_exec_block	*new;

	new = malloc(sizeof(t_exec_block));
	if (new)
	{
		new->command = 0;
		new->args = 0;
		new->redirection = 0;
		new->next = 0;
	}
	return (new);
}

void	block_add(t_exec_block	**head, t_exec_block *new)
{
	t_exec_block	*block;
	size_t			idx;

	if (!*head)
	{
		*head = new;
		new->idx = 0;
	}
	else
	{
		idx = 0;
		block = *head;
		while (block->next)
		{
			block = block->next;
			idx++;
		}
		block->next = new;
		new->idx = idx + 1;
	}
}

void	free_block(t_exec_block *blocks)
{
	t_exec_block	*block;
	t_exec_block	*block_tmp;
	t_redirecion	*r_cur;
	t_redirecion	*r_tmp;

	block = blocks;
	while (block)
	{
		if (block->command)
			free(block->command);
		free_split(block->args);
		r_cur = block->redirection;
		while (r_cur)
		{
			r_tmp = r_cur->next;
			free(r_cur->file_name);
			free(r_cur);
			r_cur = r_tmp;
		}
		block_tmp = block->next;
		free(block);
		block = block_tmp;
	}
}
