
EXECUTABLE = scheduler
SOURCES = init.c main.c t_list.c
OBJECTS = $(addprefix ,$(patsubst %.c,%.o,$(SOURCES)))
WWW_FLAGS = -Wall -Wextra -Werror

all: $(OBJECTS)
	@gcc -g -I. *.o -o $(EXECUTABLE)

%.o: %.c
	gcc -g -c $(WWW_FLAGS) $< -o $@

clean:
	@rm -f *.o

fclean: clean
	@rm -f $(EXECUTABLE)
	@rm -fr *.dSYM

re: fclean all
