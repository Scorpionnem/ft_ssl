#include "ctx.h"
#include "sha256.h"
#include "shared/itoa.h"
#include "shared/input.h"

static char*	remove_newlines(char* s, u64 len)
{
	char*	res = calloc(len + 1, sizeof(char));
	if (res == NULL)
		return (NULL);

	u64	i = 0;
	u64	j = 0;
	while (i < len)
	{
		if (s[i] == '\n')
			i++;
		else
		{
			res[j] = s[i];
			i++;
			j++;
		}
	}
	return (res);
}

static char*	sha256_str(u8* bytes, u64 len)
{
	u8	buf[32] = {};
	sha256(bytes, len, buf);

	static char	res[65] = {};

	memset(res, 0, sizeof(res));
	for (uint32_t i = 0; i < 32; i++)
		ft_itoa_hex(res + i * 2, buf[i]);
	return (res);
}

static int	print_sha256(t_ctx* ctx, char* hash, t_input_type type, char* str_path)
{
	if (ctx->opt.quiet.bool_val)
	{
		printf("%s\n", hash);
		return (0);
	}

	switch (type)
	{
		case INPUT_STR:
		{
			if (!ctx->opt.reverse.bool_val)
				printf("SHA256 (\"%s\") = %s\n", str_path, hash);
			if (ctx->opt.reverse.bool_val)
				printf("%s \"%s\"\n", hash, str_path);
			return (0);
		}
		case INPUT_FILE:
		{
			if (!ctx->opt.reverse.bool_val)
				printf("SHA256 (%s) = %s\n", str_path, hash);
			if (ctx->opt.reverse.bool_val)
				printf("%s %s\n", hash, str_path);
			return (0);
		}
		case INPUT_STDIN:
		{
			if (ctx->opt.echo.bool_val)
			{
				char* no_nl_str = remove_newlines(str_path, strlen(str_path));
				if (no_nl_str == NULL)
					return (-1);

				if (!ctx->opt.reverse.bool_val)
					printf("SHA256 (%s) = %s\n", no_nl_str, hash);
				if (ctx->opt.reverse.bool_val)
					printf("%s %s\n", hash, no_nl_str);
			}
			else
			{
				if (!ctx->opt.reverse.bool_val)
					printf("sha256 (stdin) = %s\n", hash);
				if (ctx->opt.reverse.bool_val)
					printf("%s stdin\n", hash);
			}
			return (0);
		}
	}
	return (0);
}

int	encode(t_ctx* ctx, char **av)
{
	int	res = 0;

	t_input	in;

	while (*av)
	{
		if (input_get(&in, INPUT_FILE, *av) == -1)
		{
			res = -1;
			av++;
			continue ;
		}
		print_sha256(ctx, sha256_str(in.bytes, in.size), in.type, *av);
		input_free(&in);
		av++;
	}
	if (ctx->opt.string.str_val)
	{
		if (input_get(&in, INPUT_STR, ctx->opt.string.str_val) == -1)
			return (-1);
		print_sha256(ctx, sha256_str(in.bytes, in.size), in.type, ctx->opt.string.str_val);
		input_free(&in);
	}
	if (ctx->opt.echo.bool_val || (ctx->take_stdin && !ctx->opt.string.str_val))
	{
		if (input_get(&in, INPUT_STDIN, NULL) == -1)
			return (-1);
		if (print_sha256(ctx, sha256_str(in.bytes, in.size), in.type, (char*)in.bytes) == -1)
			res = -1;
		input_free(&in);
	}

	return (res);
}

int	main(int ac, char **av)
{
	(void)ac;

	t_ctx	ctx;
	ctx_init(&ctx, &av);

	if (!*av)
		ctx.take_stdin = true;

	int res = encode(&ctx, av);

	ctx_delete(&ctx);
	return (res == -1 ? 1 : 0);
}
