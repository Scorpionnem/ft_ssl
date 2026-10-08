#pragma once

#include "shared/better_stdint.h"

#define LOWER_HEX		"0123456789abcdef"
static inline void	_ft_itoa_hex_rec(char *buf, u32 n, u32 level, u32 *i)
{
	if (n <= 15)
	{
		if (level == 0)
		{
			buf[*i] = '0';
			(*i)++;
		}
		buf[*i] = LOWER_HEX[n % 16];
		(*i)++;
		return ;
	}
	_ft_itoa_hex_rec(buf, n / 16, level + 1, i);
	_ft_itoa_hex_rec(buf, n % 16, level + 1, i);
}
#undef LOWER_HEX
static inline void	ft_itoa_hex(char *buf, u32 n)
{
	u32	i = 0;

	_ft_itoa_hex_rec(buf, n, 0, &i);
}
