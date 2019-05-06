objs:=$(patsubst %.c, %.o, $(wildcard *.c))
bins:=$(patsubst %.o, %, $(objs))
CFLAGS+=-DTEST

all: $(bins)

$(bins): %: %.o
	$(CC) $< -o $@

$(objs): %.o: %.h

$(objs): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(objs) $(bins)

.PHONY: all clean
