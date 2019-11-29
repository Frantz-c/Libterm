/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main2.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <mhouppin@le-101.fr>               +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/29 17:51:45 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/29 19:00:54 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdint.h>
#include <stdio.h>

const char	*unicode_to_utf8(uint32_t c)
{
	static char	utf8[4];
	
	*((uint32_t*)utf8) = 0u;

	if (c < 0x80u)				// 1 byte
		utf8[0] = (c & 0x7fu);
	else if (c < 0x800u)		// 2 bytes
	{
		utf8[0] = (0xC0 | ((c & 0x7E0) >> 6));
		utf8[1] = (0x80 | (c & 0x3F));
	}
	else if (c < 0x10000u)		// 3 bytes
	{
		utf8[0] = (0xE0 | ((c & 0xF000) >> 12));
		utf8[1] = (0x80 | ((c & 0xFC0)) >> 6);
		utf8[2] = (0x80 | (c & 0x3F));
	}
	else						// 4 bytes
	{
		utf8[0] = (0xF0 | ((c & 0x1C0000) >> 18));
		utf8[1] = (0x80 | ((c & 0x3F000) >> 12));
		utf8[2] = (0x80 | ((c & 0xFC0) >> 6));
		utf8[3] = (0x80 | (c & 0x3F));
	}
	return ((const char *)utf8);
}

uint32_t	utf8_to_unicode(const char *utf8)
{
	if ((utf8[0] & 0x80) == 0)
		return ((uint32_t)utf8[0]);
	else if ((utf8[0] & 0xE0) == 0xC0)
		return ((uint32_t)(((utf8[0] & 0x1F) << 6) | (utf8[1] & 0x3F)));
	else if ((utf8[0] & 0xF0) == 0xE0)
		return (uint32_t)(
			((utf8[0] & 0xF) << 12) |
			((utf8[1] & 0x3F) << 6) |
			(utf8[2] & 0x3F)
		);
	else if ((utf8[0] & 0xF8) == 0xF0)
		return (uint32_t)(
			((utf8[0] & 0x7) << 18) |
			((utf8[1] & 0x3F) << 12) |
			((utf8[2] & 0x3F) << 6) |
			(utf8[3] & 0x3F)
		);
	else
		return (0);
}

int		main(int argc, char *argv[])
{
	uint32_t	unicode;

	if (argc == 1)
		return (1);
	sscanf(argv[1], "%x", &unicode);
	printf("0x%x -> %s (0x%x)\n", unicode, unicode_to_utf8(unicode), utf8_to_unicode(unicode_to_utf8(unicode)));
}
