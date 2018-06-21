CCACHE_B=../ccache
CC = $(shell command -v $(CCACHE_B) >/dev/null 2>&1 && echo "$(CCACHE_B) gcc" || echo "gcc")
CXX = $(shell command -v $(CCACHE_B) >/dev/null 2>&1 && echo "$(CCACHE_B) g++" || echo "g++")
CFLAG = -Wall -Wno-format -g -O0 -fPIC 
CXXFLAG = -Wall -Wno-format -g -O0 -fPIC -std=c++11  -DHAVE_SYS_TIME_H

ARCH:=$(shell uname -m)

ARCH32:=i686
ARCH64:=x86_64

ifeq ($(ARCH),$(ARCH64))
SYSTEM_LIB_PATH:=/usr/lib64
else
SYSTEM_LIB_PATH:=/usr/lib
endif

LIB3RD_PATH = .
LOSS_PATH = .


VPATH = $(LOSS_PATH)
SUB_DIRS := $(foreach dir, $(VPATH), $(shell find $(dir) -maxdepth 5 -type d))
DIRS := $(SUB_DIRS)

INC := $(INC) \
       -I /usr/include 

LDFLAGS := $(LDFLAGS) -D_LINUX_OS_ \
           -ldl -lrt

CPP_SRCS = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.cpp))
CC_SRCS = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.cc))
C_SRCS = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.c))
S_SRCS = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.s))
OBJS = $(patsubst %.cpp,%.o,$(CPP_SRCS)) $(patsubst %.cc,%.o,$(CC_SRCS)) $(patsubst %.c,%.o,$(C_SRCS)) $(patsubst %.s,%.o,$(S_SRCS)) 

all:  Ls 
Ls: $(OBJS)
	#$(CXX) -shared -Wl,-soname -o libMultiThreadPools.so $(OBJS) -lc -lrt -ldl $(LDFLAGS)
	ar -crv libMultiThreadPools.a $(OBJS)
	ranlib libMultiThreadPools.a

%.o:%.cpp
	$(CXX) $(INC) $(CXXFLAG) -c -o $@ $< 
%.o:%.c
	$(CXX) $(INC) $(CXXFLAG) -c -o $@ $< 
#%.o:%.c
	#$(CC) $(INC) $(CFLAG) -c -o $@ $< 
#%.o:%.s
	#$(CC) $(INC) $(CFLAG) -c -o $@ $< 
clean:
	rm -f $(OBJS)
	rm -f libMultiThreadPools.*
  
