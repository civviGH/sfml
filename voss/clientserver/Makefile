all:
	g++ -c server.cpp UpdatePacket.cpp
	g++ server.o -o server -lsfml-system -lsfml-window -lsfml-graphics -lsfml-network UpdatePacket.o
	g++ -c client.cpp
	g++ client.o -o client -lsfml-system -lsfml-window -lsfml-graphics -lsfml-network UpdatePacket.o

clean:
	rm *.o server client
