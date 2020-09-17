#include "libft.h"

int			ft_strcmp(const char *src1, const char *src2)
{
	while (*src1 && *src2)
	{
		if (*src1 != *src2)
			break ;
		src1++;
		src2++;
	}
	return ((unsigned char)*src1 - (unsigned char)*src2);
}
