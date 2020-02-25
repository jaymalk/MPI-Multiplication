
all:
	mpicc -o collective collective.c outline.c
	mpicc -o blocking blocking.c outline.c
	mpicc -o non_blocking non_blocking.c outline.c

clear:
	rm non_blocking blocking collective
