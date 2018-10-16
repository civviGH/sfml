all:
	g++ -c server.cpp UpdatePacket.cpp Player.cpp
	g++ server.o -o server UpdatePacket.o Player.o -lsfml-system -lsfml-window -lsfml-graphics -lsfml-network
	g++ -c client.cpp
	g++ client.o -o client UpdatePacket.o Player.o -lsfml-system -lsfml-window -lsfml-graphics -lsfml-network

clean:
	rm *.o server client
