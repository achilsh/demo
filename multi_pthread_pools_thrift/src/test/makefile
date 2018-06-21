CCACHE_B=../ccache
CC = $(shell command -v $(CCACHE_B) >/dev/null 2>&1 && echo "$(CCACHE_B) gcc" || echo "gcc")
CXX = $(shell command -v $(CCACHE_B) >/dev/null 2>&1 && echo "$(CCACHE_B) g++" || echo "g++")
CFLAGS = -g -O0 #-Wall
CPPFLAGS =  -D_GNU_SOURCE=1 -D_REENTRANT -fPIC -DNODE_BEAT=10.0  -std=c++11
CXXFLAG = -O0 -Wall -ggdb -m64 -Wl,--export-dynamic  -lrt -std=c++11 -pthread

ifeq ($(unit_test),y)
CPPFLAGS += -DUNIT_TEST
endif

ARCH:=$(shell uname -m)

ARCH32:=i686
ARCH64:=x86_64

ifeq ($(ARCH),$(ARCH64))
SYSTEM_LIB_PATH:=/usr/lib64
else
SYSTEM_LIB_PATH:=/usr/lib
endif
LIB3RD_PATH = 
LOSS_PATH = ../concurrency

STARSHIP_PATH = .

VPATH = $(STARSHIP_PATH)
SUB_DIRS := $(foreach dir, $(VPATH), $(shell find $(dir) -maxdepth 5 -type d))
DIRS := $(SUB_DIRS)


INC := $(INC) \
       -I $(LOSS_PATH)/ \
       -I $(STARSHIP_PATH) 


LDFLAGS := $(LDFLAGS) -D_LINUX_OS_ \
           -L$(LOSS_PATH) \
           -lMultiThreadPools \
           -L$(SYSTEM_LIB_PATH) -lpthread \
           -lz -lc -ldl -lrt

SUB_INCLUDE =  
COMM_PATH = 
CPP_SRCS = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.cpp))
CC_SRCS = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.cc))
C_SRCS = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.c))
COMM_CPP_SRCS = $(foreach dir, $(COMM_PATH), $(wildcard $(dir)/*.cpp))
COMM_CC_SRCS = $(foreach dir, $(COMM_PATH), $(wildcard $(dir)/*.cc))
COMM_C_SRCS = $(foreach dir, $(COMM_PATH), $(wildcard $(dir)/*.c))
OBJS = $(patsubst %.cpp,%.o,$(CPP_SRCS)) $(patsubst %.c,%.o,$(C_SRCS)) $(patsubst %.cc,%.o,$(CC_SRCS))
COMM_OBJS = $(patsubst %.cpp,%.o,$(COMM_CPP_SRCS)) $(patsubst %.c,%.o,$(COMM_C_SRCS)) $(patsubst %.cc,%.o,$(COMM_CC_SRCS))

TARGET = TestMain

all: $(TARGET)

TestMain: $(OBJS)
	$(CXX) $(CXXFLAG) $(UNITTEST) -o $@ $(OBJS) $(LDFLAGS) $(INC)

%.o:%.cpp
	$(CXX) $(INC) $(CPPFLAGS) $(CFLAGS) $(UNITTEST) -c -o $@ $< $(LDFLAGS)
%.o:%.cc
	$(CXX) $(INC) $(CPPFLAGS) $(UNITTEST) -c -o $@ $< $(LDFLAGS)
%.o:%.c
	$(CC) $(INC) $(CFLAGS) $(UNITTEST) -c -o $@ $< $(LDFLAGS)
clean:
	rm -f $(OBJS)
	rm -f $(TARGET)
