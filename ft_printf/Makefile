DIR_SRCS		= ./srcs/

DIR_INCLUDES	= ./includes/

SRCS		= 	$(DIR_SRCS)ft_printf.c $(DIR_SRCS)annexes.c $(DIR_SRCS)conversion.c \
			$(DIR_SRCS)nbr_flags.c $(DIR_SRCS)flags.c

HEADER		= 	$(DIR_INCLUDES)ft_printf.h

OBJS		= $(SRCS:.c=.o)

INCLUDES	= -I$(HEADER)

NAME		= libftprintf.a

CC			= gcc
LIB			= ar -rcs
RM			= rm -f

CFLAGS		= -Wall -Werror -Wextra

.c.o:	
			$(CC) -c $< -o $(<:.c=.o) $(INCLUDES)

$(NAME):	$(OBJS) ./includes/ft_printf.h
			@make -C ./libft/
			@cp ./libft/libft.a ./$(NAME)
			$(LIB) $(NAME) $(OBJS)

all:		$(NAME)

clean: 		
			$(RM) $(OBJS)
			@make clean -C ./libft/

fclean:		clean
			$(RM) $(NAME)
			@make fclean -C ./libft/

re:			fclean all

.PHONY:		all clean fclean re
