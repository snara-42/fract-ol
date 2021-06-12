NAME = fractol

SRCS = srcs/main.c \
	   srcs/util_s.c \
	   srcs/util_n.c \
	   srcs/vec.c

OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

RM = rm -f
CC = gcc
CFLAGS = -Wall -Wextra #-Werror
INCS = -I./ -I$(LMLXPATH)
LFT = 

ifeq ($(shell uname), Darwin)
LMLXPATH = ./minilibx_opengl
LMLX = $(LMLXPATH)/libmlx.a
CFLAGS += -O3 
LIBS = $(LFT) -L$(LMLXPATH) -lmlx -framework OpenGL -framework AppKit
else
LMLXPATH = ./minilibx-linux
LMLX = $(LMLXPATH)/libmlx.a
LIBS = $(LFT) -L$(LMLXPATH) -lmlx -I/usr/local/include -L/usr/local/lib -lX11 -lXext -lm -lbsd
endif

ifeq ($(MAKECMDGOALS),debug)
CFLAGS += -g -fsanitize=address
endif

.c.o:
	$(CC) $(CFLAGS) $(INCS) -MMD -MP -MF $(<:.c=.d) -c $< -o $(<:.c=.o)

all:	$(NAME)
-include $(DEPS)
$(NAME):	$(OBJS) $(LFT) $(LMLX)
	$(CC) $(CFLAGS) $(INC) $^ $(LIBS) -o $@

mlx:	$(LMLX)
$(LMLX):
	make -C $(LMLXPATH)

clean:
	$(RM) $(OBJS) $(DEPS)
fclean: clean
	$(RM) $(NAME) a.out
	make -C $(LMLXPATH) clean
re:	fclean all

noodle:
	@clear
	@echo ""
	@echo ""
	@echo ""
	@echo ""
	@echo ""
	@echo ""
	@echo "	           (    )     (      )"
	@echo "	              (    )    ("
	@echo ""
	@echo "               ___...---=(=)=(===================="
	@echo '         ..-""          )=)=(=)==================='
	@echo "        |-._          ( ( (  ( ( (         _.-|"
	@echo '        |   `""----.................----""`   |'
	@echo "        |                                     |"
	@echo "        |                                     |"
	@echo "         \                                   /"
	@echo "          \                                 /"
	@echo "           \                               /"
	@echo "            \                             /"
	@echo "             \                           /"
	@echo '    _..---""` \                         /`""---.._'
	@echo " .-'           \                       /          '-."
	@echo ":               '-.__             __.-'              :"
	@echo ':                  ) ""---...---"" (                :'
	@echo "\'._                '"--...___...--"'              _.'"
	@echo '   \""--..__                             __..--"" /'
	@echo "     '._     """----.....______.....----"""          _.'"
	@echo '         ""--..,,_____            _____,,..--""'''
	@echo '                      """------"""'
	@sleep 0.5
	@clear
	@echo ""
	@echo ""
	@echo ""
	@echo ""
	@echo "	           (    )     (      )"
	@echo "	              (    )    ("
	@echo ""
	@echo "                        =(=)=(===================="
	@echo "                        ==)=(=)==================="
	@echo "               ___...----())))(---....___"
	@echo '         ..-""          ) (((( )         ""-..'
	@echo "        |-._          ( ( (  ( ( (         _.-|"
	@echo '        |   `""----.................----""`   |'
	@echo "        |                                     |"
	@echo "        |                                     |"
	@echo "         \                                   /"
	@echo "          \                                 /"
	@echo "           \                               /"
	@echo "            \                             /"
	@echo "             \                           /"
	@echo '    _..---""` \                         /`""---.._'
	@echo " .-'           \                       /          '-."
	@echo ":               '-.__             __.-'              :"
	@echo ':                  ) ""---...---"" (                :'
	@echo "\'._                '"--...___...--"'              _.'"
	@echo '   \""--..__                             __..--"" /'
	@echo "     '._     """----.....______.....----"""          _.'"
	@echo '         ""--..,,_____            _____,,..--""'''
	@echo '                      """------"""'
	@sleep 0.5
	@clear
	@echo ""
	@echo "	           (    )     (      )"
	@echo "	              (    )    ("
	@echo "                        =(=)=(===================="
	@echo "                        ==)=(=)==================="
	@echo "                         ())))("
	@echo "                         )(((()"
	@echo "                         ())))("
	@echo "                         )(((()"
	@echo "               ___...----())))(---....___"
	@echo '         ..-""          ) (((( )         ""-..'
	@echo "        |-._          ( ( (  ( ( (         _.-|"
	@echo '        |   `""----.................----""`   |'
	@echo "        |                                     |"
	@echo "        |                                     |"
	@echo "         \                                   /"
	@echo "          \                                 /"
	@echo "           \                               /"
	@echo "            \                             /"
	@echo "             \                           /"
	@echo '    _..---""` \                         /`""---.._'
	@echo " .-'           \                       /          '-."
	@echo ":               '-.__             __.-'              :"
	@echo ':                  ) ""---...---"" (                :'
	@echo "\'._                '"--...___...--"'              _.'"
	@echo '   \""--..__                             __..--"" /'
	@echo "     '._     """----.....______.....----"""          _.'"
	@echo '         ""--..,,_____            _____,,..--""'''
	@echo '                      """------"""'
	@sleep 0.5


.PHONY: all clean fclean tclean re bonus test noodle
