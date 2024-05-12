
CXX = g++


CXXFLAGS = -Wall -std=c++11

TARGET = test


OBJS = sqlpp11_adapter.o test.o

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

sqlpp11_adapter.o: sqlpp11_adapter.cpp sqlpp11_adapter.h
	$(CXX) $(CXXFLAGS) -c sqlpp11_adapter.cpp

test.o: test.cpp sqlpp11_adapter.h
	$(CXX) $(CXXFLAGS) -c test.cpp

clean:
	rm -f $(TARGET) $(OBJS)
