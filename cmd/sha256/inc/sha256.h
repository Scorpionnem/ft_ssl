#pragma once

#include "shared/better_stdint.h"

void	sha256(uint8_t *msg, uint64_t len, uint8_t buf[32]);
