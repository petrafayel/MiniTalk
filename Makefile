NAME1 = server

NAME1_BONUS = server_bonus

NAME2 = client

NAME2_BONUS = client_bonus

CLIENT = client.c

CLIENT_BONUS = client_bonus.c

OBJ_CL = $(CLIENT:.c=.o)

OBJ_CL_BONUS = $(CLIENT_BONUS:.c=.o)

SERVER = server.c

SERVER_BONUS = server_bonus.c

OBJ_SE = $(SERVER:.c=.o)

OBJ_SE_BONUS = $(SERVER_BONUS:.c=.o)

FLAGS = -Wall -Wextra -Werror

CC = cc

RM = rm -rf

.c.o:
	$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

all:	$(NAME1) $(NAME2)

$(NAME1): $(OBJ_SE)
	$(CC) -o $(NAME1) $(OBJ_SE)

$(NAME2): $(OBJ_CL)
	$(CC) -o $(NAME2) $(OBJ_CL)

bonus:	$(OBJ_SE_BONUS) $(OBJ_CL_BONUS)
	$(CC) -o $(NAME1_BONUS) $(OBJ_SE_BONUS)
	$(CC) -o $(NAME2_BONUS) $(OBJ_CL_BONUS)

clean:
	$(RM) $(OBJ_SE) $(OBJ_CL) $(OBJ_SE_BONUS) $(OBJ_CL_BONUS)

fclean: clean
	$(RM) $(NAME1) $(NAME2) $(NAME1_BONUS) $(NAME2_BONUS)

re: fclean all

.PHONY: clean fclean re all
