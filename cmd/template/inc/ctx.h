#pragma once

#include "shared/opt.h"

typedef struct	s_ctx
{
	struct
	{
		t_opt_ctx	ctx;

		t_opt	help;
	}	opt;

}	t_ctx;

int	ctx_init(t_ctx* ctx, char ***av);
int	ctx_delete(t_ctx* ctx);
