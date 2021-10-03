CC = g++
OBJS = branching_vc.o graph_input.o graph.o

a.out : ${OBJS}
	${CC} ${OBJS}
	./a.out

branching_vc.o: branching_vc.cpp
	${CC} -c branching_vc.cpp

graph_input.o : graph_input.cpp
	${CC} -c graph_input.cpp

graph.o : graph.cpp
	${CC} -c graph.cpp

clean:
	rm a.out *.o 

test:
	./a.out