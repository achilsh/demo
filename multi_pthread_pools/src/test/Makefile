INC_SVR_COMM = -I.  -I/usr/local/include -I../concurrency
LIB_SVR_COMM = -L/usr/local/lib64 -lpthread  -L../concurrency -lMultiThreadPools

INC_ALL=$(INC_SVR_COMM) 
LIB_ALL=$(LIB_SVR_COMM)

CCACHE_B=../ccache
CXX = $(shell command -v $(CCACHE_B) >/dev/null 2>&1 && echo "$(CCACHE_B) g++" || echo "g++")

BINARY = TestThreadPoolMain TestTimerMain
all:$(BINARY)

.SUFFIXES: .o .cpp

CXXFLAGS= -g -Wall -ggdb3 -std=c++11 -O0

%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c $^ $(INC_ALL)

TestThreadPoolMain:test_threadpool_main.o
	$(CXX) $(CXXFLAGS)  -o $@ $^ $(LIB_ALL)

TestTimerMain:test_timer_main.o
	$(CXX) $(CXXFLAGS)  -o $@ $^ $(LIB_ALL)
clean:
	rm -f *.o *~ $(BINARY)

strip:
	strip $(BINARY)
