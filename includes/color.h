/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <tsomchan@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:06:06 by tsomchan          #+#    #+#             */
/*   Updated: 2024/11/18 16:46:23 by tsomchan         ###   ########.fr       */
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

#  define B_BLACK		"\033[1;30m"
#  define B_RED			"\033[1;31m"
#  define B_GREEN		"\033[1;32m"
#  define B_YELLOW		"\033[1;33m"
#  define B_BLUE		"\033[1;34m"
#  define B_PURPLE		"\033[1;35m"
#  define B_CYAN		"\033[1;36m"
#  define B_WHITE		"\033[1;37m"
#  define NO_COLOR		"\033[0m"

//"\033[1;38;5;$NUMm" where NUM is number 0-255 for more specific color.
//"\033[1;38;2;R;G;Bm" where R, G, & B is number 0-255 for more specific color
//"\033[58;#########] set underline color in format similar to above"

#  define ORANGE		"\033[1;38;5;208m"
#  define LGREEN		"\033[1;38;5;190m"

/* Background Format	---- -
	[2 == white text?
	[3 == italic
	[4 == underlined
						- ---- */

#  define BG_BLACK		"\033[1;40m"
#  define BG_RED		"\033[1;41m"
#  define BG_GREEN		"\033[1;42m"
#  define BG_YELLOW		"\033[1;43m"
#  define BG_BLUE		"\033[1;44m"
#  define BG_PURPLE		"\033[1;45m"
#  define BG_CYAN		"\033[1;46m"
#  define BG_WHITE		"\033[1;47m"
#  define BG_RESET		"\033[49m"

#  define BG_ORANGE		"\033[1;48;5;208m"
#  define BG_LGREEN		"\033[1;48;5;190m"

#  define U_LINE		"\033[4m"

# else

#  define B_BLACK		""
#  define B_RED			""
#  define B_GREEN		""
#  define B_YELLOW		""
#  define B_BLUE		""
#  define B_PURPLE		""
#  define B_CYAN		""
#  define B_WHITE		""
#  define RESET_C		""

#  define ORANGE		""
#  define LGREEN		""

#  define BG_BLACK		""
#  define BG_RED		""
#  define BG_GREEN		""
#  define BG_YELLOW		""
#  define BG_BLUE		""
#  define BG_PURPLE		""
#  define BG_CYAN		""
#  define BG_WHITE		""
#  define BG_RESET		""
#  define BG_ORANGE		""
#  define BG_LGREEN		""
#  define U_LINE		""

# endif /* if COLOR_MODE == 1 */
#endif
