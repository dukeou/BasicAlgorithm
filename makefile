objs:=$(patsubst %.c, %.o, $(wildcard *.c))
bins:=$(patsubst %.o, %, $(objs))
objs_need_header_file:=$(shell for f in $(patsubst %.o, %.h, $(objs)); do if [ -f $$f ]; then echo $${f%.*}.o; fi done)
CFLAGS+=-DTEST
LIBS+=-pthread

all: $(bins)

$(bins): %: %.o
	$(CC) $(LIBS) $< -o $@

$(objs_need_header_file): %.o: %.h

$(objs): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(objs) $(bins)

.PHONY: all clean
