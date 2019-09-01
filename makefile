#Makefile start
CC=gcc

 
CFLAGS_WARN = -Wall -g
 
DEFINE =
INCLUDE = -I.
 
SOURCES = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SOURCES))
 
TARGET  = main.exe
 
All:$(OBJS)
	$(CC) -g -o $(TARGET) $(OBJS)	
 
%.o:%.c
	$(CC) -c $(CFLAGS_WARN) $(DEFINE) $(INCLUDE) $< -o $@	
clean:	
	
#end Makefile
