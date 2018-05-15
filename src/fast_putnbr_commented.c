/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fast_putnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 21:53:19 by irhett            #+#    #+#             */
/*   Updated: 2018/05/14 23:13:33 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fast_putnbr.h"

/* THIS VERSION IS NOT INCLUDED IN COMPILATION */

/*
    This is where all the magic _really_ happens.
    We've already calculated the size of the buffer that needs to be printed,
    so now we just prepare the buffer and make 1 syscall to output it.
*/
static ssize_t	print_number_fast(
        int fd,  // where we're printing to
        unsigned int num,  // the number in question
        unsigned char base,  // the base of the number (2, 8, 10, 16, 7? w/e)
		unsigned char nl,  // boolean, print a newline or not
        size_t buffer_size  // the amount of space needed for the buffer itself
        )
{
    // The space needed for the buffer is allocated on the stack on the fly
    // Enough for the number, plus 1 for the newline
    // Plus another 1 for a redundant, probably unnecessary null terminator.
	char	buffer[buffer_size + nl + 1];
	
    // The return value for this function
    ssize_t	ret;
	
    // For loading the buffer
    size_t	index;

    // We actually fill the buffer backwards, so we start at the end
	index = buffer_size + nl + 1;

    // Null terminate
	buffer[--index] = '\0';

    // Put the newline if needed
	if (nl)
		buffer[--index] = '\n';

    // We fill the buffer according to the modulus of the number with the base
    // And select the character based on the table
    // Included in `inc/fast_putnbr.h`
	while (index > 0)
	{
		buffer[--index] = alphabet[num % base];
		num /= base;
	}

    // Bow chicka wow wow
	ret = write(fd, buffer, buffer_size + nl);
	return (ret);
}

/*
    This function gets the size in characters needed to store the buffer.
    For example, 
    42 in binary is "101010" so (42, 2) => 6
    255 in hexadecimal is "FF", so (255, 16) => 2
*/
static size_t	get_num_len(
        unsigned int num,  // the number in question 
        unsigned char base  // yeah
        )
{
    // The number we're calculating
    // How many characters are needed to buffer our infamous number
	size_t	characters;

    // We start at 1 because even '0' is 1 character
	characters = 1;

    // Even base 10 needs 2 characters to write "10"
	while (num >= base)
	{
		num /= base;
		characters++;
	}
	return (characters);
}

/*
    The REAL set up function.
    Because all the main logic is done in the helpers above,
    all this has to do is error-checking and returning to the user.
*/
ssize_t		fast_putnbr_fd (
        int fd, 
        unsigned int num, 
        unsigned char base, 
		unsigned char nl
        )
{
	ssize_t		buffer_size;
	ssize_t		ret;

    // If base is greater than 16, we segfault out of bounds.
    // If base is 0, we divide by zero. Also, impossible base.
    // In base 1 we hit an infinite loop in get_num_len.
    // We could write a true "base 1" number, but 3 => 111, 5 => 11111
	if (base > 16 || base < 2) 
		return (-1);
	
    // We don't want exorbitantly sized buffers, only 1 newline.
    if (nl)
		nl = 1;

    // scoop de woop
	buffer_size = get_num_len(num, base);
	// de print
    ret = print_number_fast(fd, num, base, nl, buffer_size);

	return (ret);
}

/*
    This is just a wrapper.
*/
ssize_t		fast_putnbr(
        unsigned int num, 
        unsigned char base, 
        unsigned char nl
        )
{
	return (fast_putnbr_fd(1, num, base, nl));
}

/*
    Even if they easy, wrap it before you tap it.
*/
ssize_t		fast_putnbr_easy(
        unsigned int num  // should be obvious by now
        )
{
	return (fast_putnbr_fd(1, num, 10, 1));
}
