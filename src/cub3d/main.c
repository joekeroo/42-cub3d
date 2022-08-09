#include "cub3d.h"

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc != 2)
	{
		printf("Invalid number of arguments...\n");
		return (1);
	}
	cub3d();
	return (0);
}