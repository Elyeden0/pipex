NAME = libft.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra

SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
       ft_isdigit.c ft_islower.c ft_isprint.c ft_itoa.c \
       ft_strncmp.c ft_lstclear_bonus.c ft_lstdelone_bonus.c \
       ft_lstiter_bonus.c ft_lstlast_bonus.c ft_strcmp.c \
       ft_lstsize_bonus.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c \
       ft_memset.c ft_printf.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
       ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c \
       ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c \
       ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c \
       ft_toupper.c printf_tools.c printf_tools2.c ft_atol.c ft_error.c \
       get_next_line_bonus.c get_next_line_utils_bonus.c ft_split_quotes.c \

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs -o $(NAME) $(OBJS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
