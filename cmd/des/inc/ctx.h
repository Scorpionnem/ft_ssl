#pragma once

#include "shared/opt.h"

typedef struct	s_ctx
{
	struct
	{
		t_opt_ctx	ctx;

		t_opt	help;
		t_opt	base64;
		t_opt	decrypt;
		t_opt	encrypt;
		t_opt	input;
		t_opt	output;
		t_opt	key;
		t_opt	password;
		t_opt	salt;
		t_opt	init_vec;
	}	opt;

}	t_ctx;

int	ctx_init(t_ctx* ctx, char ***av);
int	ctx_delete(t_ctx* ctx);
