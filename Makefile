compile: 
	g++ -g -I include -I ArcAim/headers -o bin/x64/ArcAim ArcAim/src/*.cpp -L lib-makefile/SFML -lopenal32 -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio