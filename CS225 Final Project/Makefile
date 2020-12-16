distance: distance.cpp distance.h
			g++ distance.cpp distance.h -o distance
interface: interface.cpp interface.h distance.cpp distance.h
			g++ interface.cpp interface.h distance.cpp distance.h -o interface
test:
	g++ -std=c++11 demo.cpp dstra.cpp distance.cpp -o test
clean:
			-rm -f distance interface
