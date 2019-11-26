/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   is_utf8_char.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <mhouppin@le-101.fr>               +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/22 17:53:30 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/22 17:54:59 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

unsigned int		is_utf8_char(char *_str)
{
	unsigned char	*str = (unsigned char *)_str;

	if ((str[0] & 0x80u) == 0) // 0xxxxxxx
		return (1);

	if ((str[0] & 0xE0u) == 0xC0u) // 110xxxxx
	{
		if ((str[1] & 0xC0u) == 0x80u)
			return (2);
		return (0);
	}

	if ((str[0] & 0xF0u) == 0xE0u) // 1110xxxx
	{
		if ((str[0] & 0x0Fu) == 0)
		{
			if ((str[1] & 0xE0u) == 0xA0u && (str[2] & 0xC0u) == 0x80u)
				return (3);
			return (0);
		}
		if ((str[0] & 0x0FF) == 0xEDu)
		{
			if ((str[1] & 0xE0u) == 0x80u && (str[2] & 0xC0u) == 0x80u)
				return (3);
			return (0);
		}
		if ((str[1] & 0xC0u) == 0x80u && (str[2] & 0xC0u) == 0x80u)
			return (3);
		return (0);
	}

	if ((str[0] & 0xF8u) == 0xF0u) // 11110xxx
	{
		if ((str[0] & 0x07u) == 0) // 11110000
		{
			if ((str[1] & 0xF0u) == 0x90u || (str[1] & 0xE0u) == 0xA0u)
			{
				if ((str[2] & 0xC0u) == 0x80u && (str[3] & 0xC0u) == 0x80u)
					return (4);
				return (0);
			}
			return (0);
		}
		if ((str[0] & 0x07u) < 0x04u)
		{
			if ((str[1] & 0xC0u) == 0x80u && (str[2] & 0xC0u) == 0x80u && (str[3] & 0xC0u) == 0x80u)
				return (4);
			return (0);
		}
		if ((str[0] & 0x07u) == 0x04u)
		{
			if ((str[1] & 0xF0u) == 0x80u && (str[2] & 0xC0u) == 0x80u && (str[3] & 0xC0u) == 0x80u)
				return (4);
		}
	}
	return (0);
}
