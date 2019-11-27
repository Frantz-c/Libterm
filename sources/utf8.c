/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utf8.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/26 10:52:26 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/27 20:13:26 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

unsigned int	secure_get_utf8_char_size(const unsigned char *str, uint32_t len)
{
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

unsigned int	get_utf8_char_width(const char *s)
{
   if ((const unsigned char)*s < 0xE0u)
		return (1);
	return (2);
}

unsigned int	get_utf8_char_size(const char *s)
{
   if ((const unsigned char)*s < 0xC0u)
		return (1);
	else if ((const unsigned char)*s < 0xE0u)
		return (2);
	else if ((const unsigned char)*s < 0xF0u)
		return (3);
	return (4);
}

/*
**	works only with valid UTF-8 strings.
*/
unsigned int    strlen_utf8(const char *s)
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
unsigned int    get_utf8_string_width(const char *s)
{
    unsigned int    n;
    unsigned int    add;

    n = 0;
    while (*s)
    {
        n += get_utf8_char_width(s);
		s += get_utf8_char_size(s);
    }
    return (n);
}

/*
**	works only with valid UTF-8 strings.
*/
unsigned int    get_utf8_string_width2(const char *s, unsigned int bytes)
{
    unsigned int    n;
    unsigned int    add;

    n = 0;
    while (*s && bytes)
    {
		add = get_utf8_char_width(s);
        if (bytes - add > bytes)
            break ;
        bytes = (bytes - add);
        n += (add == 1) ? add : 2;
        s += add;
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
