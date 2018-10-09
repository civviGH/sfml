all:
	g++ -c client.cpp
	g++ client.o -o clientapp -lsfml-system -lsfml-network
	g++ -c server.cpp
	g++ server.o -o serverapp -lsfml-system -lsfml-network

clean:
	rm *.o clientapp serverapp
