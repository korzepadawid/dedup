run:
	gcc -Wall -Wextra -I/opt/homebrew/opt/openssl/include \
	-L/opt/homebrew/opt/openssl/lib -lssl -lcrypto \
	-Wno-deprecated-declarations \
	-std=c2x main.c map.c sha256.c && \
	./a.out $(ARGS) && rm a.out
	