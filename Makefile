NAME	= ft_ls

SRCS_DIR = ./srcs/
OBJS_DIR = ./objs/

SRCS	= $(SRCS_DIR)main.c $(SRCS_DIR)parsing.c

CC	= gcc
CFLAGS	= -Wall -Werror -Wextra -I ./include/


OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
DEPS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.d))


RM = rm -rf

all: $(NAME)
	@make $(NAME) -q && echo "Good job mate !"

$(OBJS_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


		
$(NAME): 	$(OBJS)
		@make -C ./ft_printf/
		@cp ./ft_printf/libftprintf.a .
		$(CC) $(CCFLAGS) $^ -o $@ -I ./include libftprintf.a

clean: 		
	$(RM) $(OBJS_DIR)
	@make clean -C ./ft_printf/

fclean:	clean
	$(RM) $(NAME)
	@make fclean -C ./ft_printf/

re: fclean all

-include $(DEPS)

.PHONY:		all clean fclean re
