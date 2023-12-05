CC = gcc
FLAGS = -std=c99 -O3
PATH_ALLEGRO=/usr/lib
LIB_ALLEGRO=-lallegro -lallegro_acodec -lallegro_audio -lallegro_color -lallegro_dialog -lallegro_font -lallegro_image -lallegro_primitives -lallegro_ttf

all: tp bola circles passaro_andante teclado bouncer louco frogger pong passaro_raivoso tela allegro_base enduro-0

tp: tp.o
	$(CC) $(FLAGS) -o tp tp.o -L $(PATH_ALLEGRO) -lm $(LIB_ALLEGRO)

tp.o: tp.c
	$(CC) $(FLAGS) -c tp.c

bola: bola.o
	$(CC) $(FLAGS) -o bola bola.o -L $(PATH_ALLEGRO) -lm $(LIB_ALLEGRO)

bola.o: bola.c
	$(CC) $(FLAGS) -c bola.c		

circles: circles.o
	$(CC) $(FLAGS) -o circles circles.o -L $(PATH_ALLEGRO) -lm $(LIB_ALLEGRO)

circles.o: circles.c
	$(CC) $(FLAGS) -c circles.c		

passaro_andante: passaro_andante.o
	$(CC) $(FLAGS) -o passaro_andante passaro_andante.o -L $(PATH_ALLEGRO) -lm $(LIB_ALLEGRO)

passaro_andante.o: passaro_andante.c
	$(CC) $(FLAGS) -c passaro_andante.c
	
passaro_raivoso: passaro_raivoso.o
	$(CC) $(FLAGS) -o passaro_raivoso passaro_raivoso.o -L $(PATH_ALLEGRO) -lm $(LIB_ALLEGRO)

passaro_raivoso.o: passaro_raivoso.c
	$(CC) $(FLAGS) -c passaro_raivoso.c	
	
bouncer: bouncer.o
	$(CC) $(FLAGS) -o bouncer bouncer.o -L $(PATH_ALLEGRO) -lm $(LIB_ALLEGRO)

bouncer.o: bouncer.c
	$(CC) $(FLAGS) -c bouncer.c	
	
teclado: teclado.o
	$(CC) $(FLAGS) -o teclado teclado.o -L $(PATH_ALLEGRO) -lm $(LIB_ALLEGRO)

teclado.o: teclado.c
	$(CC) $(FLAGS) -c teclado.c	

louco: louco.o
	$(CC) $(FLAGS) -o louco louco.o -L $(PATH_ALLEGRO) -lm $(LIB_ALLEGRO)

louco.o: louco.c
	$(CC) $(FLAGS) -c louco.c		
	
frogger: frogger.o
	$(CC) $(FLAGS) -o frogger frogger.o -L $(PATH_ALLEGRO) -lm $(LIB_ALLEGRO)

frogger.o: frogger.c
	$(CC) $(FLAGS) -c frogger.c		
	
pong: pong.o
	$(CC) $(FLAGS) -o pong pong.o -L $(PATH_ALLEGRO) -lm $(LIB_ALLEGRO)

pong.o: pong.c
	$(CC) $(FLAGS) -c pong.c	
	
tela: tela.o
	$(CC) $(FLAGS) -o tela tela.o -L $(PATH_ALLEGRO) -lm $(LIB_ALLEGRO)

tela.o: tela.c
	$(CC) $(FLAGS) -c tela.c	
	
allegro_base: allegro_base.o
	$(CC) $(FLAGS) -o allegro_base allegro_base.o -L $(PATH_ALLEGRO) -lm $(LIB_ALLEGRO)

allegro_base.o: allegro_base.c
	$(CC) $(FLAGS) -c allegro_base.c	

enduro-0: enduro-0.o
	$(CC) $(FLAGS) -o enduro-0 enduro-0.o -L $(PATH_ALLEGRO) -lm $(LIB_ALLEGRO)

enduro-0.o: enduro-0.c
	$(CC) $(FLAGS) -c enduro-0.c		
	
	
clean:
	del bola.o 
	del bola
	del circles.o 
	del circles
	del passaro_andante.o 
	del passaro_andante
	del passaro_raivoso.o 
	del passaro_raivoso	
	del louco.o 
	del louco
	del teclado.o 
	del teclado
	del bouncer.o 
	del bouncer	
	del frogger.o
	del frogger
	del pong.o
	del pong
	del tela.o
	del tela
	del allegro_base.o
	del allegro_base
	del enduro-0.o
	del enduro-0	

