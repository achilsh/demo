INC_SVR_COMM = -I.  -I/usr/local/include
LIB_SVR_COMM = -L/usr/local/lib  -lpthread

INC_ALL=$(INC_SVR_COMM) 
LIB_ALL=$(LIB_SVR_COMM)

BINARY = test_multi_thread

all:$(BINARY)


.SUFFIXES: .o .cpp
CXX = g++
CC = gcc

CXXFLAGS= -g -Wall -ggdb3 -DDEBUG_TEST -D_ReDirect  -std=c++11

%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c $^ $(INC_ALL)

test_multi_thread:main.o test_thread.o cond_mutx.o
	$(CXX) $(CXXFLAGS)  -o $@ $^ $(LIB_ALL)
clean:
	rm -f *.o *~ $(BINARY)

strip:
	strip $(BINARY)
