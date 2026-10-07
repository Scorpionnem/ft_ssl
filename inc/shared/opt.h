#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef enum	e_opt_type
{
	OPT_BOOL,
	OPT_INT,
	OPT_FLOAT,
	OPT_STR,
}	t_opt_type;

typedef struct	s_opt
{
	t_opt_type	type;
	union
	{
		bool	bool_val;
		int		int_val;
		float	float_val;
		char	*str_val;
	};
}	t_opt;

static inline t_opt	opt_new(t_opt_type type)
{
	t_opt	f = {};
	f.type = type;
	return (f);
}

typedef struct	s_opt_pair
{
	const char	*id_str;
	t_opt		*opt;
}	t_opt_pair;

typedef struct	s_opt_ctx
{
	t_opt_pair	*options;
	int			options_count;
}	t_opt_ctx;

static inline int	opt_ctx_add_opt(t_opt_ctx *ctx, char *id_str, t_opt *opt, t_opt_type type)
{
	*opt = opt_new(type);
	ctx->options = realloc(ctx->options, (ctx->options_count + 1) * sizeof(t_opt_pair));
	if (!ctx->options)
		return (-1);
	ctx->options[ctx->options_count].id_str = id_str;
	ctx->options[ctx->options_count].opt = opt;
	ctx->options_count++;
	return (0);
}

static inline int	opt_ctx_init(t_opt_ctx *ctx)
{
	memset(ctx, 0, sizeof(t_opt_ctx));
	return (0);
}

static inline int	opt_ctx_delete(t_opt_ctx *ctx)
{
	free(ctx->options);
	return (0);
}

static inline int	_find_opt(t_opt_ctx *ctx, const char *id_str)
{
	int	i = 0;
	while (i < ctx->options_count)
	{
		if (!strcmp(ctx->options[i].id_str, id_str))
			return (i);
		i++;
	}
	return (-1);
}

static inline int	opt_ctx_parse(t_opt_ctx *ctx, char ***av)
{
	int	i = -1;
	int	dump = 0;

	(*av)++;
	while ((*av)[++i])
	{
		char	*arg = (*av)[i];
		int		find = _find_opt(ctx, arg);
		if (find != -1)
		{
			t_opt	*op = ctx->options[find].opt;
			const char	*id = ctx->options[find].id_str;

			switch (op->type)
			{
				case OPT_BOOL:
				{
					op->bool_val = true;
					break ;
				}
				case OPT_STR:
				{
					if (!(*av)[i + 1])
						return (dprintf(2, "%s requires a string argument\n", id), -1);
					op->str_val = (*av)[++i];
					break ;
				}
				case OPT_INT:
				{
					if (!(*av)[i + 1])
						return (dprintf(2, "%s requires an integer argument\n", id), -1);
					op->int_val = atoi((*av)[++i]);
					break ;
				}
				case OPT_FLOAT:
				{
					if (!(*av)[i + 1])
						return (dprintf(2, "%s requires a float argument\n", id), -1);
					op->float_val = atof((*av)[++i]);
					break ;
				}
				default:
					return (dprintf(2, "FATAL: %d invalid opt enum\n", op->type), -1);
			}
		}
		else
			(*av)[dump++] = (*av)[i];
	}
	(*av)[dump] = NULL;
	return (0);
}
