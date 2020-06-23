CC=g++
LDFLAGS=-Wall
LDLIBS=-Lgclib/lib -lgc
CCFLAGS=-Wall -std=c++17 -Igclib/include -g

TARGET=a.out

all=$(TARGET)

$(TARGET): list_test.o
	$(CC) $(LDFLAGS) -o $@ $< $(LDLIBS)

list_test.o : list_test.cpp
	$(CC) $(CCFLAGS) -o $@ -c $<
