/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:38:44 by tsomchan          #+#    #+#             */
/*   Updated: 2024/12/07 17:58:18 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printf_and_exit(t_data *data, int ret, char *text)
{
	printf("%s", text);
	if (data)
		free_data(data);
	exit(ret);
}
