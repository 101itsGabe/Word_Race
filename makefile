all: Race.x

Race.x: Word_Race.cpp
	g++6 Word_Race.cpp -o Race.x

clean:
	rm *.0 Race.x
