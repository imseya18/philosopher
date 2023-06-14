/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_manager_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 00:49:05 by mmorue            #+#    #+#             */
/*   Updated: 2023/06/14 15:56:30 by mmorue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ftm_add_track(void *mem)
{
	t_memng	*new;
	t_memng	**mng;

	if (!mem)
		return ;
	if (ft_is_in_lst(mem) == 1)
		return ;
	mng = ft_head_lst();
	new = ft_memnew_manager(mem, 0, 0);
	ft_memadd_back_manager(mng, new);
}

void	ftm_rm_track(void *mem)
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
			free(current);
			return ;
		}
		back = current;
		current = current->next;
	}
}
