#pragma once

#include "shared/better_stdint.h"

void	base64_encode(int fd, u8* input, u64 len);
void	base64_decode(int fd, u8* input, u64 len);
