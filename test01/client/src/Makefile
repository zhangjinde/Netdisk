SRCS:=$(wildcard *.c)
OBJS:=$(patsubst %.c,%.o,$(SRCS))
ELF:=client
CC:=gcc
$(ELF):$(OBJS)
	$(CC) -o $@ $^
.PHONY:rebuild clean
rebuild:clean $(OBJS) $(ELF)
clean:
	rm -rf $(OBJS) $(ELF)
