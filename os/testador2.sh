#!/bin/bash
PID=3506

for i in {1..2000}
do
	kill -SIGUSR1 $PID
done
kill -SIGUSR2 $PID
sleep 0
kill -SIGINT $PID
for i in {1..500}
do
	kill -SIGUSR1 $PID
done
kill -SIGUSR2 $PID
sleep 0
kill -SIGHUP $PID
for i in {1..10000}
do
	kill -SIGUSR1 $PID
done
sleep 0
kill -SIGUSR2 $PID
sleep 0
kill -SIGALRM $PID
