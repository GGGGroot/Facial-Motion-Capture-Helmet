CXX = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS = -lwiringPi -lpthread -lrt -lm -lcrypt -lws2811
TARGET = ws2812_example

$(TARGET): test1.o
	$(CXX) $^ $(LDFLAGS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f *.o $(TARGET)
