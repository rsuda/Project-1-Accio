CXX=g++
CXXOPTIMIZE= -O2
CXXFLAGS= -g -Wall -pthread -std=c++11 $(CXXOPTIMIZE)
USERID=123456789
CLASSES=

all: client

client: $(CLASSES)
        $(CXX) -o $@ $^ $(CXXFLAGS) $@.cpp

clean:
        rm -rf *.o *~ *.gch *.swp *.dSYM client *.tar.gz

dist: tarball
tarball: clean
        tar -cvzf /tmp/$(USERID).tar.gz --exclude=./.vagrant . && mv /tmp/$(USERID).tar.gz .