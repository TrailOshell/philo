/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <tsomchan@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:06:06 by tsomchan          #+#    #+#             */
/*   Updated: 2024/11/27 21:04:47 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# if COLOR_MODE == 0

/* Text Format			---- -
	[0 == non-bold
	[1 == bold
	[2 == darken
	[3 == italic
	[4 == underline
	[7 == swap fg and bg col?
	[8 == invis
						- ---- */

#  define NO_CLR	"\033[0m"

#  define BLK		"\033[0;30m"
#  define RED		"\033[0;31m"
#  define GRN		"\033[0;32m"
#  define YLW		"\033[0;33m"
#  define BLU		"\033[0;34m"
#  define PUR		"\033[0;35m"
#  define CYN		"\033[0;36m"
#  define WHT		"\033[0;37m"

#  define B_BLK		"\033[1;30m"
#  define B_RED		"\033[1;31m"
#  define B_GRN		"\033[1;32m"
#  define B_YLW		"\033[1;33m"
#  define B_BLU		"\033[1;34m"
#  define B_PUR		"\033[1;35m"
#  define B_CYN		"\033[1;36m"
#  define B_WHT		"\033[1;37m"

//"\033[1;38;5;$NUMm" where NUM is number 0-255 for more specific color.
//"\033[1;38;2;R;G;Bm" where R, G, & B is number 0-255 for more specific color
//"\033[58;#########] set underline color in format similar to above"

#  define ORANGE		"\033[1;38;5;208m"
#  define LGRN		"\033[1;38;5;190m"

/* Background Format	---- -
	[2 == white text?
	[3 == italic
	[4 == underlined
						- ---- */

#  define BG_BLK		"\033[1;40m"
#  define BG_RED		"\033[1;41m"
#  define BG_GRN		"\033[1;42m"
#  define BG_YLW		"\033[1;43m"
#  define BG_BLU		"\033[1;44m"
#  define BG_PUR		"\033[1;45m"
#  define BG_CYN		"\033[1;46m"
#  define BG_WHT		"\033[1;47m"
#  define BG_RESET		"\033[49m"

#  define BG_ORANGE		"\033[1;48;5;208m"
#  define BG_LGRN		"\033[1;48;5;190m"

#  define U_LINE		"\033[4m"

# else

#  define B_BLK		""
#  define B_RED			""
#  define B_GRN		""
#  define B_YLW		""
#  define B_BLU		""
#  define B_PUR		""
#  define B_CYN		""
#  define B_WHT		""
#  define RESET_C		""

#  define ORANGE		""
#  define LGRN		""

#  define BG_BLK		""
#  define BG_RED		""
#  define BG_GRN		""
#  define BG_YLW		""
#  define BG_BLU		""
#  define BG_PUR		""
#  define BG_CYN		""
#  define BG_WHT		""
#  define BG_RESET		""
#  define BG_ORANGE		""
#  define BG_LGRN		""
#  define U_LINE		""

# endif /* if COLOR_MODE == 1 */
#endif
