CC=g++
LDFLAGS=-Wall
LDLIBS=-Lgclib/lib -lgc
CCFLAGS=-Wall -std=c++17 -Igclib/include -Isrc -g

# CCFLAGS += -DPERFORMANCE_TIMERS

TARGET=a.out

all=$(TARGET)

$(TARGET): obj/main.o obj/Application.o obj/ListNode.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

obj/main.o: src/main.cpp
	$(CC) $(CCFLAGS) -o $@ -c $<

obj/%.o: src/%.cpp src/%.h
	$(CC) $(CCFLAGS) -o $@ -c $<

clean:
	rm -f obj/*.o $(TARGET)
