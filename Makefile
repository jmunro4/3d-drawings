OPTS = -Wall
LIBS = -lGL -lGLU -lglui -lglut

all: sgp

sgp: sgp.cc points.o edge.o polygon.o conics.o matrix.o
	g++ ${OPTS} -o sgp sgp.cc points.o edge.o polygon.o conics.o matrix.o ${LIBS}

points.o: points.cc points.h
	g++ ${OPTS} -c points.cc ${LIBS}

edge.o: edge.cc edge.h
	g++ ${OPTS} -c edge.cc ${LIBS}

polygon.o: polygon.cc polygon.h
	g++ ${OPTS} -c polygon.cc ${LIBS}

conics.o: conics.cc conics.h
	g++ ${OPTS} -c conics.cc ${LIBS}

matrix.o: matrix.cc matrix.h
	g++ ${OPTS} -c matrix.cc ${LIBS}

clean:
	rm *.o
	rm sgp
cleanemacs:
	rm *~
