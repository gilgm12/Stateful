

TARGET=example
CC=g++

all:
	$(CC) example.cc tools.cc time_state.cc point_state.cc point_fsm.cc -o $(TARGET)
	chmod +x $(TARGET)

clean:
	rm example