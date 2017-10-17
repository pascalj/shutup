src = $(wildcard *.c)
obj = $(src:.c=.o)

LDFLAGS = -framework CoreFoundation -framework IOKit

shutup: $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) shutup

