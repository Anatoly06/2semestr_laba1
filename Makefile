CXX = g++
FLAGS = -Wall -Wextra
TARGET = lab1
SRCS = main.cpp Student.cpp Database.cpp
HDRS = Student.h Database.h

all: $(TARGET)

$(TARGET): $(SRCS) $(HDRS)
	$(CXX) $(FLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)