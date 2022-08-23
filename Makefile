NAME = pipex
LIBFT = libft/libft.a
SRCS = src/pipex.c src/free.c
OBJS = $(patsubst src/%, obj/%, $(SRCS:.c=.o))
############################
$(NAME): $(OBJS) $(LIBFT)
	gcc $^ -o $@ -Llibft -lft 

$(LIBFT): 
	make all -C libft

all: $(NAME)

obj/%.o: src/%.c
	gcc -c $< -o $@ -Ilibft -Iinclude

clean:
	rm $(OBJS)

fclean: clean
	rm $(NAME)
	make fclean -C libft

re: fclean $(NAME)