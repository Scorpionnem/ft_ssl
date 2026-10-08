#include "ctx.h"
#include "base64.h"
#include "shared/input.h"

int	encode_mode(t_ctx* ctx)
{
	t_input	in;

	if (ctx->opt.input.str_val)
		input_get(&in, INPUT_FILE, ctx->opt.input.str_val);
	else if (ctx->opt.string.str_val)
		input_get(&in, INPUT_STR, ctx->opt.string.str_val);
	else
		input_get(&in, INPUT_STDIN, NULL);

	int	fd = STDOUT_FILENO;
	if (ctx->opt.output.str_val)
		fd = open(ctx->opt.output.str_val, O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
		return (-1);

	base64_encode(fd, in.bytes, in.size);
	input_free(&in);
	return (0);
}

int	decode_mode(t_ctx* ctx)
{
	t_input	in;

	if (ctx->opt.input.str_val)
		input_get(&in, INPUT_FILE, ctx->opt.input.str_val);
	else if (ctx->opt.string.str_val)
		input_get(&in, INPUT_STR, ctx->opt.string.str_val);
	else
		input_get(&in, INPUT_STDIN, NULL);

	int	fd = STDOUT_FILENO;
	if (ctx->opt.output.str_val)
		fd = open(ctx->opt.output.str_val, O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
		return (-1);

	base64_decode(fd, in.bytes, in.size);
	input_free(&in);
	return (0);
}

int	main(int ac, char** av)
{
	(void)ac;

	t_ctx	ctx;
	ctx_init(&ctx, &av);

	if (ctx.opt.decode.bool_val)
		decode_mode(&ctx);
	else if (ctx.opt.encode.bool_val)
		encode_mode(&ctx);

	ctx_delete(&ctx);
}
