# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/utp/zmq/lib
#ZMQDIR = /home/utp/zmq
ZMQDIR = /home/local/zmq

CC=clang++ -std=c++11 -Wall
LDFLAGS= -lpthread -lzmqpp -lzmq -I$(ZMQDIR)/include -L$(ZMQDIR)/lib -lsfml-audio

all: client workers recollector

client: client.cc
	$(CC) -o client client.cc $(LDFLAGS)

workers: workers.cc
	$(CC) -o workers workers.cc $(LDFLAGS)

recollector: recollector.cc
	$(CC) -o recollector recollector.cc $(LDFLAGS)

clean:
	rm -f client workers recollector
