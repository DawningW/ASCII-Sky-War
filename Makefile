cc = gcc
deps = $(wildcard ./*.h)
src = $(wildcard ./*.c)
obj = $(src:%.c=%.o)
lib = -lm -lncurses -lsoundio -lcurl -lcjson

build: $(obj)
	$(cc) $(obj) $(lib) -o build

%.o: %.c $(deps)
	$(cc) -c -I ./include $< -o $@

.PHONY: clean

clean:
	rm -rf $(obj)
