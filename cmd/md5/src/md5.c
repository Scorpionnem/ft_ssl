#include "md5.h"

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

static u32 rotl(u32 value, u32 shift)
{
	if ((shift &= 31) == 0)
		return (value);
	return (value << shift) | (value >> (32 - shift));
}

const u32	K[64] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391,
};

const u32	S[64] = {
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21,
};

void	md5(u8 *msg, u64 len, u8 buf[16])
{
	u64	number_blocks = ((len + 8) >> 6) + 1;
	u64	total_length = number_blocks << 6;

	u8	*padding_bytes = calloc((total_length - len), sizeof(u8));
	u64	padding_bytes_size = (total_length - len) * sizeof(u8);
	padding_bytes[0] = (u8)0x80;

	u64 message_length_bits = len << 3;
	for (u32 i = 0; i < 8; ++i )
	{
		padding_bytes[padding_bytes_size - 8 + i] = (u8)message_length_bits;
		message_length_bits >>= 8;
	}

	u32	a0 = 0x67452301;
	u32	b0 = 0xefcdab89;
	u32	c0 = 0x98badcfe;
	u32	d0 = 0x10325476;

	for (u64 c = 0; c < number_blocks; c++)
	{
		u32	buffer[16] = {0};
		u64	index = c << 6;

		for (u64 j = 0; j < 64; index++, ++j)
			buffer[j >> 2] = ((u32)( (index < len) ? msg[index] : padding_bytes[index - len]) << 24) | (buffer[j >> 2] >> 8);

		u32	A = a0;
		u32	B = b0;
		u32	C = c0;
		u32	D = d0;

		for (u32 i = 0; i < 64; i++)
		{
			u32	F = 0;
			u32	G = 0;

			if (i <= 15)
			{
				F = (B & C) | ((~B) & D);
				G = i;
			}
			else if (i <= 31)
			{
				F = (D & B) | ((~D) & C);
				G = (5 * i + 1) % 16;
			}
			else if (i <= 47)
			{
				F = B ^ C ^ D;
				G = (3 * i + 5) % 16;
			}
			else if (i <= 63)
			{
				F = C ^ (B | (~D));
				G = (7 * i) % 16;
			}

			F = F + A + K[i] + buffer[G];
			A = D;
			D = C;
			C = B;
			B = B + rotl(F, S[i]);
		}
		a0 += A;
		b0 += B;
		c0 += C;
		d0 += D;
	}

	u8	hash[16] = {0};
	u64 count = 0;
	for (u64 i = 0; i < 4; ++i)
	{
		u64 n = (i == 0) ? a0 : ((i == 1) ? b0 : ((i == 2) ? c0 : d0));
		for (u64 j = 0; j < 4; ++j)
		{
			hash[count++] = (u8)(n);
			n >>= 8;
		}
	}

	memcpy(buf, hash, 16);
	free(padding_bytes);
}
