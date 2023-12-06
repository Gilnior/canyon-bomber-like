#include <allegro5/altime.h>
#include <allegro5/color.h>
#include <allegro5/display.h>
#include <allegro5/drawing.h>
#include <allegro5/keycodes.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <stdlib.h>
#include <unistd.h>

#define TARGET_COLS 20
#define TARGET_ROWS 8

const float FPS = 60;  
const int SCREEN_W = 960;
const int SCREEN_H = 540;
const int NAVE_W = 50;
const int NAVE_H = 30;
const int RAIO_TIRO = 3;
const float ACEL_TIRO = 0.077;
const float VEL_DEFAULT = 3;


typedef struct Tiro {
	float x, y;
	int ativo;
	int hit;
	float vel_y;
} Tiro;


typedef struct Nave {
	int id;
	float x,y;
	ALLEGRO_COLOR cor;
	int dir;
	float vel;
	Tiro tiro;
	int score;
	int hp;
} Nave;

typedef struct Target {
	float x1, x2, y1, y2;
	ALLEGRO_COLOR cor;
	int active, value;
} Target;

void desenha_targets(Target targets[TARGET_ROWS][TARGET_COLS]){
	int i, j;

	for(i=0; i<TARGET_ROWS; i++){
		for(j=0; j<TARGET_COLS; j++) {
			if(targets[i][j].active == 1) {
			al_draw_filled_rectangle(targets[i][j].x1, targets[i][j].y1, targets[i][j].x2, targets[i][j].y2, targets[i][j].cor);
			}
		}
	}
}

void desenha_cenario() {
	ALLEGRO_COLOR cor = al_map_rgb(119, 113, 202);
	al_clear_to_color(cor);
}

void desenha_nave(Nave nave) {
	al_draw_filled_triangle(nave.x, nave.y,
							nave.x - (nave.dir*NAVE_W),
							nave.y - NAVE_H/2.,
							nave.x - (nave.dir*NAVE_W),
							nave.y + NAVE_H/2.,
							nave.cor);

	//desenha tiro:
	if(nave.tiro.ativo)
		al_draw_filled_circle(nave.tiro.x,
						  nave.tiro.y,
						  RAIO_TIRO, nave.cor);	
}

void atualiza_nave(Nave *nave) {
	int collision;
	int missed;
	
	nave->x += (nave->dir)*nave->vel;
	if(nave->x > SCREEN_W + NAVE_W ||
	   nave->x < -NAVE_W) {
		nave->dir *= -1;
	
	}

	//atualiza tiro
	if(nave->tiro.ativo) {
		nave->tiro.x = nave->x;
		nave->tiro.vel_y += ACEL_TIRO;
		nave->tiro.y += nave->tiro.vel_y;
	}
	
	collision = nave->tiro.x < -RAIO_TIRO ||
	   nave->tiro.x > SCREEN_W + RAIO_TIRO ||
	   nave->tiro.y > SCREEN_H + RAIO_TIRO;

	if(collision && nave->tiro.ativo == 1) {
		   nave->tiro.ativo = 0;
			missed = nave->tiro.hit == 0;

		   if(missed) {
				nave->hp--;
		   }
	}
}

int check_collision(Tiro tiro, Target target){
	return tiro.ativo ==1  && target.active == 1 && tiro.x >= target.x1 && tiro.x <= target.x2 && tiro.y <= target.y1 && tiro.y >= target.y2;
}

 
int main(int argc, char **argv){	
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
    
	//inicializa o Allegro
	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}
	
    //inicializa o módulo de primitivas do Allegro
    if(!al_init_primitives_addon()){
		fprintf(stderr, "failed to initialize primitives!\n");
        return -1;
    }	
	
	//inicializa o modulo que permite carregar imagens no jogo
	if(!al_init_image_addon()){
		fprintf(stderr, "failed to initialize image module!\n");
		return -1;
	}
   
	//cria um temporizador que incrementa uma unidade a cada 1.0/FPS segundos
    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}
 
	//cria uma tela com dimensoes de SCREEN_W, SCREEN_H pixels
	display = al_create_display(SCREEN_W, SCREEN_H);
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
	}

	//instala o teclado
	if(!al_install_keyboard()) {
		fprintf(stderr, "failed to install keyboard!\n");
		return -1;
	}	

	//inicializa o modulo allegro que carrega as fontes
	al_init_font_addon();

	//inicializa o modulo allegro que entende arquivos tff de fontes
	if(!al_init_ttf_addon()) {
		fprintf(stderr, "failed to load tff font module!\n");
		return -1;
	}

	//carrega o arquivo arial.ttf da fonte Arial e define que sera usado o tamanho 32 (segundo parametro)
    ALLEGRO_FONT *size_24 = al_load_font("arial.ttf", 24, 1);   
	if(size_24 == NULL) {
		fprintf(stderr, "font file does not exist or cannot be accessed!\n");
	}

 	//cria a fila de eventos
	event_queue = al_create_event_queue();
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		return -1;
	}

	//registra na fila os eventos de tela (ex: clicar no X na janela)
	al_register_event_source(event_queue, al_get_display_event_source(display));
	//registra na fila os eventos de tempo: quando o tempo altera de t para t+1
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	//registra na fila os eventos de teclado (ex: pressionar uma tecla)
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	//Criar a Nave 1:
	Nave p1;
	p1.id = 1;
	p1.x = -1;
	p1.y = NAVE_H*2;
	p1.cor = al_map_rgb(255, 0, 0);
	p1.dir = 1;
	p1.vel = VEL_DEFAULT;
	p1.tiro.x = 0;
	p1.tiro.y = 0;
	p1.tiro.ativo = 0;
	p1.tiro.hit = 0;
	p1.tiro.vel_y = 0;
	p1.score = 0;
	p1.hp = 3;

	//Criar a Nave 2:
	Nave p2;
	p2.id = 2;
	p2.x = SCREEN_W;
	p2.y = NAVE_H*4;
	p2.cor = al_map_rgb(0, 0, 255);
	p2.dir = -1;
	p2.vel = VEL_DEFAULT;
	p2.tiro.x = 0;
	p2.tiro.y = 0;
	p2.tiro.ativo = 0;
	p2.tiro.hit = 0;
	p2.tiro.vel_y = 0;
	p2.score = 0;
	p2.hp = 3;

	//cria targets
	Target targets[TARGET_ROWS][TARGET_COLS];

	int i, j;
	float target_w = SCREEN_W/(TARGET_COLS*1.5);
	float target_h = SCREEN_H/TARGET_ROWS;
	ALLEGRO_COLOR cor;

	for (i=0;i<TARGET_ROWS;i++) {
		cor = al_map_rgb(rand()%256, rand()%256, rand()%256);
		
		for(j=0; j< TARGET_COLS; j++) {
			targets[i][j].x1 = j*target_h;
			targets[i][j].x2 = targets[i][j].x1 + target_h;
			targets[i][j].y1 = SCREEN_H - i*target_w;
			targets[i][j].y2 = targets[i][j].y1 - target_w;
			targets[i][j].cor = cor;
			targets[i][j].active = 1;
			targets[i][j].value = i+ 1;
		}
	}

	//inicia o temporizador
	al_start_timer(timer);

	unsigned int change_nave_type, flip_naves;
	float temp_h;
	int previous_p1_dir = p1.dir;
	int no_target_active;
	int playing = 1;
	Nave *winner;

	float score_screen_y = 7;

	while(playing) {
		ALLEGRO_EVENT ev;
		//espera por um evento e o armazena na variavel de evento ev
		al_wait_for_event(event_queue, &ev);

		//se o tipo de evento for um evento do temporizador, ou seja, se o tempo passou de t para t+1
		if(ev.type == ALLEGRO_EVENT_TIMER) {
			desenha_cenario();
			desenha_targets(targets);
			atualiza_nave(&p1);
			atualiza_nave(&p2);
			desenha_nave(p1);
			desenha_nave(p2);
			al_draw_textf(size_24, p1.cor, 40, score_screen_y, 1, "%d  %d", p1.hp, p1.score);
			al_draw_textf(size_24, p2.cor, SCREEN_W - 40, score_screen_y, 1, "%d  %d", p2.hp, p2.score);
			al_flip_display();

			if (previous_p1_dir != p1.dir) {
				previous_p1_dir = p1.dir;
				flip_naves = rand()%2;

				if (p1.vel > VEL_DEFAULT){
					change_nave_type = rand()%2;
				} else {
					change_nave_type = rand()%4 == 0;
				}

				if (flip_naves) {
					temp_h = p1.y;
					p1.y = p2.y;
					p2.y = temp_h;
				}

				if(change_nave_type) {
					if (p1.vel == VEL_DEFAULT){
						p1.vel = VEL_DEFAULT*1.5;
						p1.cor = al_map_rgb(0, 0, 0);
						p2.vel = VEL_DEFAULT*1.5;
						p2.cor = al_map_rgb(255, 255, 255);
					}
					else {
						p1.vel = VEL_DEFAULT;
						p1.cor = al_map_rgb(255, 0, 0);;
						p2.vel = VEL_DEFAULT;
						p2.cor = al_map_rgb(0, 0, 255);
					}
				}

			}

			no_target_active = 1;

			for (i=0;i<TARGET_ROWS;i++) {
				for(j=0; j< TARGET_COLS; j++) {
					if (check_collision(p1.tiro, targets[i][j])) {
						targets[i][j].active = 0;
						p1.score += targets[i][j].value;
						p1.tiro.hit = 1;
					} else if (check_collision(p2.tiro, targets[i][j])) {
						targets[i][j].active = 0;
						p2.score += targets[i][j].value;
						p2.tiro.hit = 1;
					}
					if (targets[i][j].active == 1) {
						no_target_active = 0;
					} 
				}
			}

			if (no_target_active || p1.hp == 0 || p2.hp == 0) {
				playing = 0;
				if ((p1.hp == 0) || (p2.score > p1.score && p2.hp > 0)) {
					winner = &p2;
				} else if ((p2.hp == 0) || (p1.score > p2.score && p1.hp > 0)) {
					winner = &p1;
				}
			}
			
			if(al_get_timer_count(timer)%(int)FPS == 0) {
					printf("\n%d segundos se passaram...", (int)(al_get_timer_count(timer)/FPS));
			}
		}
		//se o tipo de evento for o fechamento da tela (clique no x da janela)
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			playing = 0;
		}
		//se o tipo de evento for um pressionar de uma tecla
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			
			switch(ev.keyboard.keycode) {
				
				case ALLEGRO_KEY_SPACE:
					p1.tiro.ativo = 1;
					p1.tiro.hit = 0;
					p1.tiro.x = p1.x;
					p1.tiro.y = p1.y;
					p1.tiro.vel_y = 0;
				break;

				case ALLEGRO_KEY_ENTER:
					p2.tiro.ativo = 1;
					p2.tiro.hit = 0;
					p2.tiro.x = p2.x;
					p2.tiro.y = p2.y;
					p2.tiro.vel_y = 0;
				break;
				
			}

			// printf("\ncodigo tecla: %d", ev.keyboard.keycode);
		}
	}

	al_clear_to_color(al_map_rgb(144, 144, 0));
	al_draw_textf(size_24, winner->cor, SCREEN_W/2, SCREEN_H/2, 1, "P%d WINS! Score %d", winner->id, winner->score);
	al_flip_display();
	al_rest(4.7);


	al_clear_to_color(al_map_rgb(144, 144, 15));
	int p1_victories=0, p2_victories=0, last_victory_id=0, last_victory_score=0, last_victory_hp=0;

	char records_filename[] = "records.txt";
	char file_format[] = "%d,%d,%d,%d,%d";

	FILE *records;

	if (access(records_filename, F_OK) == 0) {
		records = fopen(records_filename, "r");
		fscanf(records, file_format, &p1_victories, &p2_victories, &last_victory_id, &last_victory_score, &last_victory_hp);
		fclose(records);
		records = fopen(records_filename, "w");
	} else {
		records = fopen(records_filename, "w");
	}

	if (last_victory_id != 0) {
		al_draw_textf(size_24, winner->cor, SCREEN_W/2, SCREEN_H*0.3, 1, "Previous game winner:  P%d with %d of score and %d lifes", last_victory_id, last_victory_score, last_victory_hp);
	};

	if (winner->id == 1) {
		p1_victories++;
	} else {
		p2_victories++;
	}
	
	al_draw_textf(size_24, winner->cor, SCREEN_W/2, SCREEN_H*0.7, 1, "P1: %d victories P2: %d victories", p1_victories, p2_victories);
	
	last_victory_id = winner->id;
	last_victory_score = winner->score;
	last_victory_hp = winner->hp;

	fprintf(records, file_format, p1_victories, p2_victories, last_victory_id, last_victory_score, last_victory_hp);
	fclose(records);
	al_flip_display();
	al_rest(7.64);

	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}

