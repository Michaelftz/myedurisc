edurisc: $(wildcard src/*.c)
	$(CC) $? -g -o bin/$@
