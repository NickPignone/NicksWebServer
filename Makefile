CC=gcc
CFLAGS=-g -O0 -Wall -std=gnu99
#add headers to DEPS, otherwise make wont detect changes and recompile
#when headers change
DEPS =

# Shell
SRC = NicksNetwork.c 
OBJ = NicksNetwork.o 
EXEC = NicksNetwork

#.PHONY declaration just says that 'all' isn't a file name.
.PHONY: all
all: $(EXEC)

#compile all .o into executable
#%.o == all .o files
#$@ = left side of :
#$< = right side of :
%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS) 

$(EXEC): $(OBJ) $(DEPS)
	$(CC) -o $@ $^ $(CFLAGS) -lpthread

#https://www.gnu.org/software/make/manual/html_node/Cleanup.html#Cleanup
.PHONY: clean
clean:
	find . -maxdepth 1 -type f -perm +111 ! -name "*.sh" -exec rm {} +
	find . -maxdepth 1 -type f -name "*.o" -exec rm {} +

