CXX = g++ -fdiagnostics-color=always
CXXFLAGS = -std=c++11 -c -g -fPIC -Wall -Wextra -O2
LDFLAGS = -shared -ldl

.PHONY: all clean
all: mylib.so

test: mylib.so
	LD_PRELOAD=./mylib.so wget https://www.google.com 1>/dev/null && rm index.html*

mylib.so: mylib.cpp mylib.h debugCtrl.h
	$(CXX) $(CXXFLAGS) -o mylib.o mylib.cpp
	$(CXX) -o $@ mylib.o $(LDFLAGS)

clean:
	rm -rf *.o *.so
