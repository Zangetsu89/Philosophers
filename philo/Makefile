NAME		:= philo
CFLAGS		:= -Wextra -Wall -Werror
CFLAGS		+= $(if $(FSAN) , -fsanitize=thread -g)
CFLAGS		+= $(if $(DEBUG) , -g)
SRCS		:= $(shell find ./srcs -iname "*.c")
OBJS		:= ${SRCS:.c=.o}
HEADER		:= $(addprefix -I, ./includes)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(HEADER) -o $(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

fsan:
	$(MAKE) FSAN=1

resan: fclean
	$(MAKE) fsan

debug:
	$(MAKE) DEBUG=1

rebug: fclean
	$(MAKE) debug


re: clean all

.PHONY: all, clean, fclean, re
