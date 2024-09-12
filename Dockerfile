FROM ubuntu:latest

RUN apt update && apt install -yy make gcc valgrind

ADD . /app
WORKDIR /app

RUN make re
ENTRYPOINT ["/usr/bin/valgrind", "--leak-check=full", "--show-leak-kinds=all", "--track-origins=yes", "./philo"]