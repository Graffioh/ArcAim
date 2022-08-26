compile: 
	g++ -g -I include -I ArcAim/headers -o Exec/ArcAim ArcAim/src/*.cpp -L lib-makefile/SFML -lopenal32 -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio