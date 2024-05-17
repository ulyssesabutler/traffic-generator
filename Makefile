CC=g++
LIBS=-pthread
EXEC=generator

all: $(EXEC)

$(EXEC): main.o packet.o socket.o hex.o options.o string_utils.o
	$(CC) $(LIBS) -o $@ $^

main.o: main.cpp
	$(CC) -c $^

packet.o: network/packet.cpp
	$(CC) -c $^

socket.o: network/socket.cpp
	$(CC) -c $^

hex.o: util/hex.cpp
	$(CC) -c $^

options.o: util/options.cpp
	$(CC) -c $^

string_utils.o: util/string_utils.cpp
	$(CC) -c $^

.PHONY: clean
clean:
	rm -f $(EXEC) *.o