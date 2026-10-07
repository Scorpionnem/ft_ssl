#include "ctx.h"

int	ctx_init(t_ctx* ctx, char ***av)
{
	memset(ctx, 0, sizeof(t_ctx));

	opt_ctx_init(&ctx->opt.ctx);
	opt_ctx_add_opt(&ctx->opt.ctx, "-h", &ctx->opt.help, OPT_BOOL);
	opt_ctx_add_opt(&ctx->opt.ctx, "--help", &ctx->opt.help, OPT_BOOL);
	opt_ctx_parse(&ctx->opt.ctx, av);
	return (0);
}

int	ctx_delete(t_ctx* ctx)
{
	opt_ctx_delete(&ctx->opt.ctx);
	return (0);
}
