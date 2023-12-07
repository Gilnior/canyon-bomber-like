# canyon-bomber-like

## Sobre o projeto
Projeto final da disciplina de Programação e Desenvolvimento de Software I. O objetivo é fazer um jogo inspitado em [Canyon Bomber](https://en.wikipedia.org/wiki/Canyon_Bomber), usando a biblioteca Allegro na linguagem C. Para facilitar o desenvolvimento, só foi pensando o suporte para Linux, especificamente, Manjaro (muito provavelmente qualquer distribuição baseada em Arch deve funcionar).


## Dependências
- allegro5

### Instalando dependências
Usando o gerenciador de pacotes [pacman](https://wiki.archlinux.org/title/Pacman) disponível para sistemas baseados em Arch:
```
sudo pacman -S allegro
```


## Como executar o jogo
Ir para a raiz do projeto e seguir os próximos passos.

Para compilar o jogo:

```
make
```
Isso gerará o executável canyon_bomb_like, que pode ser executado clicando no jogo ou pelo comando:
```
./canyon_bomb_like 
```

### Opcional
Remover arquivos intermediários gerados durante a compilação
```
make clean
```

## Sobre o jogo

### Objetivo do jogo
Esse é um jogo para dois jogadores, onde o objetivo é fazer mais score que o outro jogador.

### Regras do jogo
- Se não houverem mais alvos, o jogador com mais score vence
- Todo jogador tem direito a 3 vidas, todo tiro que não acertar nenhum alvo e atingir alguma borda reduz uma vida
- Se um jogador chega a 0 vidas, o outro vence

### Como jogar
- Um jogando atira usando space e o outro usando enter

## Detalhes de implementação
### Código
O código foi estrurado de uma forma bem simples: todo o código do jogo está estruturado em apenas um arquivo, com toda a parte lógica estando ao redor da função main.
A inicialização do allegro se dá no inicío da main, e após isso, inicializa-se as estrutura que serão usandas ao longo do loop de gameplay (naves, tiros, blocos/targets) com paramêtros iniciais que ditam o início do jogo.
Após isso se dá o loop do jogo, onde as estruturas inicializadas antes são usadas para a execução da lógica jogo em conjunto com as funções da biblioteca gráfica para renderização.


### Estrutura criadas
Foram criadas três estruturas:
- Tiro: essa é a estrutura responsável por armazenar todas as informações relevantes sobre o projétil solto pelas naves
- Nave: esse é a estrutura responsável por armazenar todas as informações relevantes sobre as naves
- Target: esse é a estrutura responsável por armazenar todas as informações relevantes sobre os blocos/alvos que são acertados pelo Tiro

