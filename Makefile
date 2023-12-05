CC = gcc
FLAGS = -std=c99 -O3
PATH_ALLEGRO=/usr/lib
LIB_ALLEGRO=-lallegro -lallegro_acodec -lallegro_audio -lallegro_color -lallegro_dialog -lallegro_font -lallegro_image -lallegro_primitives -lallegro_ttf

all: tp

tp: tp.o
	$(CC) $(FLAGS) -o tp tp.o -L $(PATH_ALLEGRO) -lm $(LIB_ALLEGRO)

tp.o: tp.c
	$(CC) $(FLAGS) -c tp.c
	
clean:
	del tp.o