CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -pthread
DEPS = message.h socket.h make_ip.h login_register.h file.h client.h atomic_task.h logued_actions.h
OBJ = socket.o make_ip.o file.o client.o atomic_task.o login_register.o logued_actions.o main.o

%.o: %.cc $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

main: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

.PHONY: clean
clean:
	rm main *.o