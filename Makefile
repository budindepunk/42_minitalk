CLIENT = client
SERVER = server

CC = cc
FLAGS = -Wall -Wextra -Werror
RM = rm -f

all: $(CLIENT) $(SERVER)

$(CLIENT): client.c
	$(CC) $(FLAGS) client.c -o client
$(SERVER): server.c
	$(CC) $(FLAGS) server.c -o server

clean:
	$(RM) $(CLIENT) $(SERVER)
fclean: clean

re: fclean all
