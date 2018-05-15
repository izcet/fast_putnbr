/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fast_putnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 21:53:19 by irhett            #+#    #+#             */
/*   Updated: 2018/05/14 22:54:04 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fast_putnbr.h"

static ssize_t	print_number_fast(int fd, unsigned int num, unsigned char base, 
		unsigned char nl, size_t buffer_size)
{
	char	buffer[buffer_size + nl + 1];
	ssize_t	ret;
	size_t	index;

	index = buffer_size + nl + 1;

	buffer[--index] = '\0';
	if (nl)
		buffer[--index] = '\n';

	while (index > 0)
	{
		buffer[--index] = alphabet[num % base];
		num /= base;
	}

	ret = write(fd, buffer, buffer_size + nl);
	return (ret);
}

static size_t	get_num_len(unsigned int num, unsigned char base)
{
	size_t	characters;

	characters = 1;
	while (num >= base)
	{
		num /= base;
		characters++;
	}
	return (characters);
}

ssize_t		fast_putnbr_fd (int fd, unsigned int num, unsigned char base, 
		unsigned char nl)
{
	ssize_t		buffer_size;
	ssize_t		ret;

	if (base > 16 || base < 2) 
		return (-1);
	if (nl)
		nl = 1;

	buffer_size = get_num_len(num, base);
	ret = print_number_fast(fd, num, base, nl, buffer_size);

	return (ret);
}

ssize_t		fast_putnbr(unsigned int num, unsigned char base, unsigned char nl)
{
	return (fast_putnbr_fd(1, num, base, nl));
}

ssize_t		fast_putnbr_easy(unsigned int num)
{
	return (fast_putnbr_fd(1, num, 10, 1));
}
