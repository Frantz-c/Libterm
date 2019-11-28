/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utf8.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/26 10:52:26 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/28 13:38:33 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

uint8_t		secure_get_utf8_char_size(const char *s, uint32_t len)
{
	const uint8_t	*str = (const uint8_t *)s;

	if ((str[0] & 0x80u) == 0) // 0xxxxxxx
		return (1);

	if (len > 1 && (str[0] & 0xe0u) == 0xc0u) // 110xxxxx
	{
		if ((str[1] & 0xc0u) == 0x80u)
			return (2);
		return (0);
	}

	if (len > 2 && (str[0] & 0xf0u) == 0xe0u) // 1110xxxx
	{
		if ((str[0] & 0x0fu) == 0)
		{
			if ((str[1] & 0xe0u) == 0xa0u && (str[2] & 0xc0u) == 0x80u)
				return (3);
			return (0);
		}
		if ((str[0] & 0x0ff) == 0xedu)
		{
			if ((str[1] & 0xe0u) == 0x80u && (str[2] & 0xc0u) == 0x80u)
				return (3);
			return (0);
		}
		if ((str[1] & 0xc0u) == 0x80u && (str[2] & 0xc0u) == 0x80u)
			return (3);
		return (0);
	}

	if (len > 3 && (str[0] & 0xf8u) == 0xf0u) // 11110xxx
	{
		if ((str[0] & 0x07u) == 0) // 11110000
		{
			if ((str[1] & 0xf0u) == 0x90u || (str[1] & 0xe0u) == 0xa0u)
			{
				if ((str[2] & 0xc0u) == 0x80u && (str[3] & 0xc0u) == 0x80u)
					return (4);
				return (0);
			}
			return (0);
		}
		if ((str[0] & 0x07u) < 0x04u)
		{
			if ((str[1] & 0xc0u) == 0x80u && (str[2] & 0xc0u) == 0x80u && (str[3] & 0xc0u) == 0x80u)
				return (4);
			return (0);
		}
		if ((str[0] & 0x07u) == 0x04u)
		{
			if ((str[1] & 0xf0u) == 0x80u && (str[2] & 0xc0u) == 0x80u && (str[3] & 0xc0u) == 0x80u)
				return (4);
		}
	}
	return (0);
}

uint8_t		get_utf8_char_width(const char *s)
{
	const unsigned char	*us = (const unsigned char *)s;

	if (*us < 0xE0u)
		return (1);
	return (2);
}

uint8_t		get_utf8_char_size(const char *s)
{
	const unsigned char	*us = (const unsigned char *)s;

   if (*us < 0xC0u)
		return (1);
	else if (*us < 0xE0u)
		return (2);
	else if (*us < 0xF0u)
		return (3);
	return (4);
}

void		get_utf8_char_info(const char *s, uint8_t *width, uint8_t *size)
{
	const unsigned char	*us = (const unsigned char *)s;

   if (*us < 0xC0u)
		*size = 1;
	else if (*us < 0xE0u)
		*size = 2;
	else if (*us < 0xF0u)
		*size = 3;
	else
		*size = 4;

	*width =  (*us < 0xE0u) ? 1 : 2;
}

uint8_t		get_utf8_prev_char_width(const char *s)
{
	const unsigned char	*us = (const unsigned char *)s - 1;

	while ((*us & 0xC0u) == 0x80u)
		us--;
   if (*us < 0xE0u)
		return (1);
	return (2);
}

uint8_t		get_utf8_prev_char_size(const char *s)
{
	const uint8_t	*us = (const unsigned char *)s - 1;
	uint8_t			size;

	size = 1;
	while ((*us & 0xC0u) == 0x80u)
	{
		us--;
		size++;
	}
	return (size);
}

void		get_utf8_prev_char_info(const char *s, uint8_t *width, uint8_t *size)
{
	const uint8_t	*us = (const unsigned char *)s - 1;

	*size = 1;
	while ((*us & 0xC0u) == 0x80u)
	{
		us--;
		(*size)++;
	}
	*width = (*us < 0xE0u) ? 1 : 2;
}

/*
**	works only with valid UTF-8 strings.
*/
uint32_t    strlen_utf8(const char *s)
{
    unsigned int    n;

    n = 0;
    while (*s)
    {
		s += get_utf8_char_size(s);
        n++;
    }
    return (n);
}

/*
**	works only with valid UTF-8 strings.
*/
uint32_t    get_utf8_string_width(const char *s)
{
    uint32_t    n;
    uint8_t		width;
	uint8_t		size;

    n = 0;
    while (*s)
    {
		get_utf8_char_info(s, &width, &size);
        n += width;
		s += size;
    }
    return (n);
}

/*
**	works only with valid UTF-8 strings.
*/
uint32_t    get_utf8_string_width2(const char *s, uint32_t bytes)
{
    uint32_t    n;
	uint8_t		width;
	uint8_t		size;

    n = 0;
    while (*s && bytes)
    {
		get_utf8_char_info(s, &width, &size);
        if (bytes - size > bytes)
            break ;
        bytes = (bytes - size);
        n += width;
        s += bytes;
    }
    return (n);
}
/*
int    main(void)
{
    char            test[] = "日本語の文章です, où est l'éléphant ?";
    unsigned int    nchar, ncol;

    nchar = strlen_utf8(test);
    ncol = get_utf8_string_width(test);
    printf("\"%s\" -> %u characters, %u cols\n", test, nchar, ncol);
    return (0);
}
*/
