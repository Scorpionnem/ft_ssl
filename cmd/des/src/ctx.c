#include "ctx.h"

int	ctx_init(t_ctx* ctx, char ***av)
{
	memset(ctx, 0, sizeof(t_ctx));

	opt_ctx_init(&ctx->opt.ctx);
	opt_ctx_add_opt(&ctx->opt.ctx, "-h", &ctx->opt.help, OPT_BOOL);
	opt_ctx_add_opt(&ctx->opt.ctx, "--help", &ctx->opt.help, OPT_BOOL);

	opt_ctx_add_opt(&ctx->opt.ctx, "-a", &ctx->opt.base64, OPT_BOOL);
	opt_ctx_add_opt(&ctx->opt.ctx, "--base64", &ctx->opt.base64, OPT_BOOL);

	opt_ctx_add_opt(&ctx->opt.ctx, "-d", &ctx->opt.decrypt, OPT_BOOL);
	opt_ctx_add_opt(&ctx->opt.ctx, "--decrypt", &ctx->opt.decrypt, OPT_BOOL);

	opt_ctx_add_opt(&ctx->opt.ctx, "-e", &ctx->opt.encrypt, OPT_BOOL);
	opt_ctx_add_opt(&ctx->opt.ctx, "--encrypt", &ctx->opt.encrypt, OPT_BOOL);

	opt_ctx_add_opt(&ctx->opt.ctx, "-i", &ctx->opt.input, OPT_STR);
	opt_ctx_add_opt(&ctx->opt.ctx, "--input", &ctx->opt.input, OPT_STR);

	opt_ctx_add_opt(&ctx->opt.ctx, "-o", &ctx->opt.output, OPT_STR);
	opt_ctx_add_opt(&ctx->opt.ctx, "--output", &ctx->opt.output, OPT_STR);

	opt_ctx_add_opt(&ctx->opt.ctx, "-k", &ctx->opt.key, OPT_STR);
	opt_ctx_add_opt(&ctx->opt.ctx, "--key", &ctx->opt.key, OPT_STR);

	opt_ctx_add_opt(&ctx->opt.ctx, "-p", &ctx->opt.password, OPT_STR);
	opt_ctx_add_opt(&ctx->opt.ctx, "--password", &ctx->opt.password, OPT_STR);

	opt_ctx_add_opt(&ctx->opt.ctx, "-s", &ctx->opt.salt, OPT_STR);
	opt_ctx_add_opt(&ctx->opt.ctx, "--salt", &ctx->opt.salt, OPT_STR);

	opt_ctx_add_opt(&ctx->opt.ctx, "-v", &ctx->opt.init_vec, OPT_STR);
	opt_ctx_add_opt(&ctx->opt.ctx, "--vector", &ctx->opt.init_vec, OPT_STR);

	opt_ctx_parse(&ctx->opt.ctx, av);
	return (0);
}

int	ctx_delete(t_ctx* ctx)
{
	opt_ctx_delete(&ctx->opt.ctx);
	return (0);
}
