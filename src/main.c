/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 21:53:52 by irhett            #+#    #+#             */
/*   Updated: 2018/05/14 22:49:08 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fast_putnbr.h"

int		main(int argc, char **argv)
{
	fast_putnbr_easy(42);
	fast_putnbr(42, 2, 1);
	fast_putnbr_fd(2, 12345, 10, 1);
	fast_putnbr(3405691582, 16, 1);
	
	(void)argc;
	(void)argv;
	return (0);
}
