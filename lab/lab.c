/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lab.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 13:53:46 by cjulienn          #+#    #+#             */
/*   Updated: 2022/04/22 13:57:02 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdio.h>

int	main(void)
{
	printf("result of %i modulo 2 = %i\n", 0, 0 % 2);
	printf("result of %i modulo 2 = %i\n", 1, 1 % 2);
	printf("result of %i modulo 2 = %i\n", 2, 2 % 2);
	printf("result of %i modulo 2 = %i\n", 3, 3 % 2);
	printf("result of %i modulo 2 = %i\n", 4, 4 % 2);
	return 0;
}
