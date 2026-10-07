#include "ctx.h"

int	ctx_init(t_ctx* ctx, char*** av)
{
	memset(ctx, 0, sizeof(t_ctx));

	opt_ctx_init(&ctx->opt.ctx);
	opt_ctx_add_opt(&ctx->opt.ctx, "-h", &ctx->opt.help, OPT_BOOL);
	opt_ctx_add_opt(&ctx->opt.ctx, "--help", &ctx->opt.help, OPT_BOOL);

	opt_ctx_add_opt(&ctx->opt.ctx, "-d", &ctx->opt.decode, OPT_BOOL);
	opt_ctx_add_opt(&ctx->opt.ctx, "--decode", &ctx->opt.decode, OPT_BOOL);

	opt_ctx_add_opt(&ctx->opt.ctx, "-e", &ctx->opt.encode, OPT_BOOL);
	opt_ctx_add_opt(&ctx->opt.ctx, "--encode", &ctx->opt.encode, OPT_BOOL);
	ctx->opt.encode.bool_val = true;

	opt_ctx_add_opt(&ctx->opt.ctx, "-i", &ctx->opt.input, OPT_STR);
	opt_ctx_add_opt(&ctx->opt.ctx, "--input", &ctx->opt.input, OPT_STR);

	opt_ctx_add_opt(&ctx->opt.ctx, "-s", &ctx->opt.string, OPT_STR);
	opt_ctx_add_opt(&ctx->opt.ctx, "--string", &ctx->opt.string, OPT_STR);

	opt_ctx_add_opt(&ctx->opt.ctx, "-o", &ctx->opt.output, OPT_STR);
	opt_ctx_add_opt(&ctx->opt.ctx, "--output", &ctx->opt.output, OPT_STR);
	opt_ctx_parse(&ctx->opt.ctx, av);
	return (0);
}

int	ctx_delete(t_ctx* ctx)
{
	opt_ctx_delete(&ctx->opt.ctx);
	return (0);
}
