CC = gcc
CFLAGS = -Wall -pthread

all: worker_monitor adder subtractor multiplier divider

worker_monitor: worker_monitor.c
	$(CC) $(CFLAGS) -o worker_monitor worker_monitor.c -lm

adder: adder.c
	$(CC) $(CFLAGS) -o adder adder.c

subtractor: subtractor.c
	$(CC) $(CFLAGS) -o subtractor subtractor.c

multiplier: multiplier.c
	$(CC) $(CFLAGS) -o multiplier multiplier.c

divider: divider.c
	$(CC) $(CFLAGS) -o divider divider.c

.PHONY: clean run

clean:
	rm -f worker_monitor adder subtractor multiplier divider
	rm -f adder_pipe subtractor_pipe multiplier_pipe divider_pipe

run: all
	gnome-terminal --title="Worker Monitor" -- ./worker_monitor
	gnome-terminal --title="Adder Worker" -- ./adder
	gnome-terminal --title="Subtractor Worker" -- ./subtractor
	gnome-terminal --title="Multiplier Worker" -- ./multiplier
	gnome-terminal --title="Divider Worker" -- ./divider