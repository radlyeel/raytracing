PROG = trace
OBJS = trace.o

CXX = g++
CXXFLAGS += -std=c++20 -Wall -Werror

$(PROG): $(OBJS)
	$(CXX) $(OBJS) -o $(PROG)

clean:
	rm -f $(PROG) $(OBJS)

check: $(PROG)
	./$(PROG) > $(PROG).ppm

