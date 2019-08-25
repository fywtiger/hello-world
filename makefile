#Makefile start
CC=gcc
CP=copy
RM=del
 
CFLAGS_WARN = -Wall -g
 
DEFINE =
INCLUDE = -I.
 
SOURCES = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SOURCES))
 
TARGET  = test.exe
 
All:$(OBJS)
	$(CC) -o $(TARGET) $(OBJS)	
 
%.o:%.c
	$(CC) -c $(CFLAGS_WARN) $(DEFINE) $(INCLUDE) $< -o $@	
clean:	
	
#end Makefile