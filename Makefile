DAEMON		:= daemon
DAEMON_OBJS	:= daemon.o

%.o:%.cpp
	g++ -c $<

default:
	make $(DAEMON)

run:$(DAEMON)
	./$(DAEMON) &

killd:
	$(eval PID:=$(subst PID:,  ,$(shell cat PID)))
	kill $(PID)
	rm PID

$(DAEMON):$(DAEMON_OBJS)
	g++ -o $@ $^

