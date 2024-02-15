/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:01:48 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/13 11:01:58 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <signal.h>
# include "../ft_libft/include/libft.h"

# ifndef MAX_TIMEOUT
#  define MAX_TIMEOUT 1000
# endif

# ifndef END_CHAR
#  define END_CHAR '\0'
# endif

typedef struct s_timeout {
	char	activated;
	int		cycles;
}	t_timeout;

#endif
