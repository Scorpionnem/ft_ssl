#include "ctx.h"

int	ctx_init(t_ctx* ctx, char ***av)
{
	memset(ctx, 0, sizeof(t_ctx));

	opt_ctx_init(&ctx->opt.ctx);
	opt_ctx_add_opt(&ctx->opt.ctx, "-h", &ctx->opt.help, OPT_BOOL);
	opt_ctx_add_opt(&ctx->opt.ctx, "--help", &ctx->opt.help, OPT_BOOL);

	opt_ctx_add_opt(&ctx->opt.ctx, "-p", &ctx->opt.echo, OPT_BOOL);
	opt_ctx_add_opt(&ctx->opt.ctx, "--echo", &ctx->opt.echo, OPT_BOOL);

	opt_ctx_add_opt(&ctx->opt.ctx, "-q", &ctx->opt.quiet, OPT_BOOL);
	opt_ctx_add_opt(&ctx->opt.ctx, "--quiet", &ctx->opt.quiet, OPT_BOOL);

	opt_ctx_add_opt(&ctx->opt.ctx, "-r", &ctx->opt.reverse, OPT_BOOL);
	opt_ctx_add_opt(&ctx->opt.ctx, "--reverse", &ctx->opt.reverse, OPT_BOOL);

	opt_ctx_add_opt(&ctx->opt.ctx, "-s", &ctx->opt.string, OPT_STR);
	opt_ctx_add_opt(&ctx->opt.ctx, "--string", &ctx->opt.string, OPT_STR);
	opt_ctx_parse(&ctx->opt.ctx, av);
	return (0);
}

int	ctx_delete(t_ctx* ctx)
{
	opt_ctx_delete(&ctx->opt.ctx);
	return (0);
}
