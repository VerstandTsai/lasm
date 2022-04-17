all: lasm.c
	gcc -o lasm lasm.c
install: lasm.c
	gcc -o lasm lasm.c
	mv lasm /usr/bin/lasm
clean:
	rm -rf lasm
