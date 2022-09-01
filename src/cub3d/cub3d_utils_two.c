#include "cub3d.h"

int	rgb_to_hex(char *red_char, char *green_char, char *blue_char)
{
	int	red;
	int	green;
	int	blue;
	int	color;

	red = ft_atoi(red_char);
	green = ft_atoi(green_char);
	blue = ft_atoi(blue_char);
	color = (red / 16) * pow(16, 5);
	color += (red % 16) * pow(16, 4);
	color += (green / 16) * pow(16, 3);
	color += (green % 16) * pow(16, 2);
	color += (blue / 16) * 16;
	color += (blue % 16);
	return (color);
}
