#include "base64.h"
#include <stdio.h>
#include <string.h>

#define BASE64 "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"

// supposed to be 64???
#define NEWLINE_COUNT 76

static void	print_c(int fd, char c, u64* count)
{
	dprintf(fd, "%c", c);
	(*count)++;
	if (*count == NEWLINE_COUNT)
	{
		dprintf(fd, "\n");
		*count = 0;
	}
}

void	base64_encode(int fd, u8* input, u64 len)
{
	u64	count = 0;
	for (u64 i = 0; i < len; i += 3)
	{
		u32 a = input[i];
		u32 b = (i + 1 < len) ? input[i + 1] : 0;
		u32 c = (i + 2 < len) ? input[i + 2] : 0;

		u32 triple = (a << 16) | (b << 8) | c;

		print_c(fd, BASE64[(triple >> 18) & 0b00111111], &count);
		print_c(fd, BASE64[(triple >> 12) & 0b00111111], &count);

		if (i + 1 < len)
			print_c(fd, BASE64[(triple >> 6) & 0b00111111], &count);
		else
			print_c(fd, '=', &count);

		if (i + 2 < len)
			print_c(fd, BASE64[triple & 0b00111111], &count);
		else
			print_c(fd, '=', &count);
	}
	print_c(fd, '\n', &count);
}

static int	base64_index(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (c - 'A');
	if (c >= 'a' && c <= 'z')
		return (c - 'a' + 26);
	if (c >= '0' && c <= '9')
		return (c - '0' + 52);
	if (c == '+')
		return (62);
	if (c == '/')
		return (63);
	if (c == '=')
		return (0);
	return (-1);
}

void	base64_decode(int fd, u8* input, u64 len)
{
	u8	block[4];
	int		count = 0;

	for (u64 i = 0; i < len; i++)
	{
		if (!strchr(BASE64, input[i]) && input[i] != '=' && input[i] != '\n')
		{
			dprintf(2, "Invalid base64 (ASCII: %d)\n", input[i]);
			return ;
		}
	}

	for (u64 i = 0; i < len; i++)
	{
		char c = input[i];

		if (c == '\n' || c == '\r' || c == ' ' || c == '\t')
			continue ;

		block[count++] = c;

		if (count == 4)
		{
			int	v0 = base64_index(block[0]);
			int	v1 = base64_index(block[1]);
			int	v2 = base64_index(block[2]);
			int	v3 = base64_index(block[3]);

			u32	triple = (v0 << 18) | (v1 << 12) | (v2 << 6) | v3;

			u8	b1 = (triple >> 16) & 0xFF;
			u8	b2 = (triple >> 8) & 0xFF;
			u8	b3 = triple & 0xFF;

			dprintf(fd, "%c", b1);
			if (block[2] != '=')
				dprintf(fd, "%c", b2);
			if (block[3] != '=')
				dprintf(fd, "%c", b3);

			count = 0;
		}
	}
}
