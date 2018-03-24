edurisc: $(wildcard src/*.c)
	$(CC) $? -o bin/$@
