.PHONY: clean
clean:
	rm -f sfcu

sfcu: clean
	gcc src/main.c -o sfcu
