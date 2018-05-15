/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fast_putnbr.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 21:54:04 by irhett            #+#    #+#             */
/*   Updated: 2018/05/14 22:48:11 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FAST_PUTNBR_H
# define FAST_PUTNBR_H

#include <unistd.h>
/* no stdio! */
/* no stdlib! */

static char alphabet[16] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    'A', 'B', 'C', 'D', 'E', 'F'
};

/*
   `fd`;    The file descriptor to be written to.

   `num`:	The number to be printed. Unsigned to avoid edge cases.

   `nl`:	Print a newline if `nl` is non-zero.

   `base`:  The base to print the number in. Common ones include 2, 8, 10, 16.
            This will not handle bases above 16 or below 2.
            ** Octal and Hex prefixes will not be included. **

    Return value:
    The number of bytes written, or -1 for error
*/
ssize_t		fast_putnbr_fd(int fd, unsigned int num, unsigned char base,
        unsigned char nl);
/*
   Same as the above, except the file descriptor is always 1.
*/
ssize_t		fast_putnbr(unsigned int num, unsigned char base, unsigned char nl);

/*
   Same as the above, except the `base` is always 10 and a `nl` is always 1
*/
ssize_t     fast_putnbr_easy(unsigned int num);

#endif
