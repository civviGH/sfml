all:
	g++ -c server.cpp UpdatePacket.cpp Player.cpp
	g++ server.o -o server.bin UpdatePacket.o Player.o -lsfml-system -lsfml-window -lsfml-graphics -lsfml-network
	g++ -c client.cpp
	g++ client.o -o client.bin UpdatePacket.o Player.o -lsfml-system -lsfml-window -lsfml-graphics -lsfml-network
debug:
	g++ -c -g server.cpp UpdatePacket.cpp Player.cpp
	g++ server.o -o server.bin UpdatePacket.o Player.o -lsfml-system -lsfml-window -lsfml-graphics -lsfml-network
	g++ -c -g client.cpp
	g++ client.o -o client.bin UpdatePacket.o Player.o -lsfml-system -lsfml-window -lsfml-graphics -lsfml-network
clean:
	rm *.o server.bin client.bin
