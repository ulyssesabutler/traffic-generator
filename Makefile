CC=g++
LIBS=-pthread
EXEC=generator

$(EXEC): main.cpp
	$(CC) $(LIBS) -o $@ $^

.PHONY: clean
clean:
	rm -f $(EXEC)