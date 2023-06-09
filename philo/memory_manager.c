/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:39:10 by loculy            #+#    #+#             */
/*   Updated: 2023/06/09 13:07:26 by mmorue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ftm_malloc(size_t sz)
{
	void	*mem;
	t_memng	*new;
	t_memng	**mng;

	mem = malloc(sz);
	if (!mem)
		ft_error();
	mng = ft_head_lst();
	new = ft_memnew_manager(mem, 0, 0);
	ft_memadd_back_manager(mng, new);
	return (mem);
}

void	ftm_free(void *mem)
{
	t_memng	*current;
	t_memng	*back;
	t_memng	**mng;

	if (!mem)
		return ;
	mng = ft_head_lst();
	current = *mng;
	back = 0;
	while (current != NULL)
	{
		if ((unsigned long)current->mem == (unsigned long)mem)
		{
			if (back != 0)
				back->next = current->next;
			else
				*mng = current->next;
			free(mem);
			free(current);
			return ;
		}
		back = current;
		current = current->next;
	}
	free(mem);
}

void	ftm_free_all(void)
{
	t_memng	*current;
	t_memng	*tmp;
	t_memng	**mng;

	mng = ft_head_lst();
	current = *mng;
	if (!current)
		return ;
	while (current != NULL)
	{
		tmp = current;
		current = current->next;
		free(tmp->mem);
		free(tmp);
	}
	*mng = NULL;
}
