INC_SVR_COMM = -I.  -I/usr/local/include
LIB_SVR_COMM = -L/usr/local/lib  -lpthread

INC_ALL=$(INC_SVR_COMM) 
LIB_ALL=$(LIB_SVR_COMM)

BINARY = test_expand  test_dyn

all:$(BINARY)


.SUFFIXES: .o .cpp
CXX = g++
CC = gcc

CXXFLAGS= -g -Wall -ggdb3 -DDEBUG_TEST -D_ReDirect 

%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c $^ $(INC_ALL)

test_expand:t_expand_main.o
	$(CXX) $(CXXFLAGS)  -o $@ $^ $(LIB_ALL)
test_dyn:t_static_dyn_main.o
	$(CXX) $(CXXFLAGS)  -o $@ $^ $(LIB_ALL)
clean:
	rm -f *.o *~ $(BINARY)

strip:
	strip $(BINARY)
