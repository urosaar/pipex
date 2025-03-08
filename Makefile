NAME = pipex

NAME_BONUS = pipex_bonus

CC = gcc
CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

SRCS = mandatory/pipex.c \
       mandatory/pipex_utils.c \
       mandatory/utils.c \
	   mandatory/ft_split.c \
	   mandatory/error.c

OBJS = $(SRCS:.c=.o)

SRCS_BONUS = bonus/ft_split_bonus.c \
             bonus/get_next_line_bonus.c \
			 bonus/pipex_bonus.c \
			 bonus/pipex_bonus_utils.c \
			 bonus/utils_bonus.c \
			 bonus/here_doc_bonus.c \
			 bonus/error_bonus.c

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) mandatory/pipex.h mandatory/libft.h
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)

re: fclean all

bonus: $(OBJS_BONUS) bonus/pipex_bonus.h bonus/libft_bonus.h
	$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME_BONUS)
