CC = gcc
FLAGS = -std=c99 -O3
PATH_ALLEGRO=/usr/lib
LIB_ALLEGRO=-lallegro -lallegro_acodec -lallegro_audio -lallegro_color -lallegro_dialog -lallegro_font -lallegro_image -lallegro_primitives -lallegro_ttf

all: canyon_bomb_like

canyon_bomb_like: canyon_bomb_like.o
	$(CC) $(FLAGS) -o canyon_bomb_like canyon_bomb_like.o -L $(PATH_ALLEGRO) -lm $(LIB_ALLEGRO)

canyon_bomb_like.o: canyon_bomb_like.c
	$(CC) $(FLAGS) -c canyon_bomb_like.c
	
clean:
	rm canyon_bomb_like.o