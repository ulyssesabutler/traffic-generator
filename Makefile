CC=g++
LIBS=-pthread
EXEC=generator

$(EXEC): main.o packet.o socket.o hex.o
	$(CC) $(LIBS) -o $@ $^

main.o: main.cpp
	$(CC) -c $^

packet.o: network/packet.cpp
	$(CC) -c $^

socket.o: network/socket.cpp
	$(CC) -c $^

hex.o: util/hex.cpp
	$(CC) -c $^

.PHONY: clean
clean:
	rm -f $(EXEC) *.o