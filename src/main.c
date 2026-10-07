#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include "shared/better_stdint.h"

#define STR_IN(x) (sizeof(x) / sizeof(char*))
const char*	std_cmds[] = {
};
const char*	md_cmds[] = {
	"md5",
	"sha256"
};
const char*	cph_cmds[] = {
	"base64",
	"des",
	"des-ecb",
	"des-cbc"
};

#define PRINT_CMDS(x) for (u64 i = 0; i < STR_IN(x); i++) dprintf(2, "  %s\n", x[i]);
void	print_error(const char* s)
{
	if (s)
		dprintf(2, "ft_ssl: %s\n", s);

	dprintf(2, "\nUsage: ft_ssl [command]\n");
	dprintf(2, "\nStandard commands:\n");
	PRINT_CMDS(std_cmds);
	dprintf(2, "\nMessage digest commands:\n");
	PRINT_CMDS(md_cmds);
	dprintf(2, "\nCipher commands:\n");
	PRINT_CMDS(cph_cmds);
}
#undef PRINT_CMDS

#define CHECK_CMD(x) for (u64 i = 0; i < STR_IN(x); i++) if (!strcmp(cmd, x[i])) return (1);
int	is_valid_cmd(const char* cmd)
{
	CHECK_CMD(std_cmds);
	CHECK_CMD(md_cmds);
	CHECK_CMD(cph_cmds);
	return (0);
}
#undef CHECK_CMD

int	main(int ac, char** av)
{
	if (ac < 2)
		return (print_error("too few arguments"), 1);
	if (is_valid_cmd(av[1]) == 0)
		return (print_error("invalid command"), 1);

	av++;
	if (execv(av[0], av) == -1)
		return (dprintf(2, "ft_ssl: '%s': %s\n", av[0], strerror(errno)), 1);
	return (0);
}
