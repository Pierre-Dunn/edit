TARGET = edit

all: $(TARGET)
functions.o: functions.c
	gcc -c functions.c
main.o: main.c
	gcc -c main.c
cmd_parser.o: cmd_parser.c
	gcc -c cmd_parser.c
libparser.a: cmd_parser.o
	 ar cr libparser.a  cmd_parser.o
$(TARGET): main.o functions.o libparser.a
	gcc -o $(TARGET) main.o functions.o -lcurses -L. -lparser 
clean:
	rm -rf *.o
.PHONY: clean


