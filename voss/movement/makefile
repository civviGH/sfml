all:
	g++ -c main.cpp
	g++ main.o -o sfmlapp -lsfml-system -lsfml-window -lsfml-graphics -lsfml-network
	g++ -c client.cpp
	g++ client.o -o clientapp -lsfml-system -lsfml-window -lsfml-graphics -lsfml-network

clean:
	rm *.o sfmlapp clientapp
