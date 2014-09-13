
IN = bf.c
OUT = bf
FLAGS = ""

all: clean
	$(CC) $(IN) -o $(OUT) $(FLAGS)

install: all
	mv $(OUT) /usr/local/bin

clean:
	rm -fr $(OUT)
