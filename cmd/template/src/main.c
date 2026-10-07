#include "ctx.h"

int	main(int ac, char **av)
{
	(void)ac;

	t_ctx	ctx;
	ctx_init(&ctx, &av);

	ctx_delete(&ctx);
}
