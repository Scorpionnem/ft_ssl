#pragma once

#include "shared/opt.h"

typedef struct	s_ctx
{
	struct
	{
		t_opt_ctx	ctx;

		t_opt	help;
		t_opt	encode;
		t_opt	decode;
		t_opt	input;
		t_opt	output;
		t_opt	string;
	}	opt;
}	t_ctx;

int	ctx_init(t_ctx* ctx, char*** av);
int	ctx_delete(t_ctx* ctx);
