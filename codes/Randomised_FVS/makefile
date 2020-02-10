CC = g++
OBJS = randomised_fvs.o graph_input.o graph.o

a.out : ${OBJS}
	${CC} ${OBJS}
	./a.out

randomised_fvs.o: randomised_fvs.cpp
	${CC} -c randomised_fvs.cpp

graph_input.o : graph_input.cpp
	${CC} -c graph_input.cpp

graph.o : graph.cpp
	${CC} -c graph.cpp

clean:
	\rm a.out *.o *.dot
