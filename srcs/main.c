/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <tsomchan@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:41:13 by tsomchan          #+#    #+#             */
/*   Updated: 2024/11/18 17:14:44 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(void)
{
	printf("COLOR_MODE = %d\n", COLOR_MODE);
	if (COLOR_MODE == 0)
		printf(B_YELLOW "print in main\n" NO_COLOR);
	else if (COLOR_MODE == 1)
		printf("print in colorless\n");
	else
		printf("print\n");
	return (0);
}
