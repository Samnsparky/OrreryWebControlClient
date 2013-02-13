OrreryWebControl_test: ./OrreryWebControl_test.cpp OrreryWebControl.o
	g++ -g -Wall ./OrreryWebControl_test.cpp OrreryWebControl.o HTTPClient.o -o OrreryWebControl_test

OrreryWebControl.o: ./OrreryWebControl.cpp ./OrreryWebControl.h HTTPClient.o
	g++ -g -Wall -c ./OrreryWebControl.cpp -o OrreryWebControl.o

HTTPClient.o: ./HTTPClient.cpp ./HTTPClient.h
	g++ -g -Wall -c ./HTTPClient.cpp -o HTTPClient.o

clean:
	rm *.o
