#pragma once
#include<SDL.h>
#include"ClassDeclaracao.h"
#include"constantes.h"

// Declara��o do objeto LTextura que armazena a imagem com todos os sprites da nave do jogador
LTextura naveSpriteSheet;

// Declara��o do objeto LTextura que armazena a imagem com todos os sprites do proj�til laser;
LTextura projeteisSpriteSheet;

// Armazena a imagem com os sprites do inimigo01
LTextura inimigo01SpriteSheet;

LTextura inimigo02SpriteSheet;

LTextura background;

LTextura bossSpriteSheet;

LTextura menuInicial;

LTextura menuSelecao;

// Declara��o do objJogador que corresponde ao objeto manipul�vel pelo jogador
objJogador nave;

// Declara��o do vetor objProjetilLaser que armazena todos os proj�teis  
objProjetilLaser laser[quantLaser];

// Declara��o do vetor objInimigo01 que armazena todos os inimigos01 
objInimigo01 inimigo01[quantInimigos01];

objInimigo02 inimigo02[quantInimigos02]; //quantInimigos02 = 2

objBoss BossInimigo;

objProjetilBoss BossDisparo;

objProjetilBoss02 BossProjetil02[quantProjetilBoss02];
