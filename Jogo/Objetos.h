#pragma once
#include<SDL.h>
#include"ClassDeclaracao.h"
#include"constantes.h"

// Declaração do objeto LTextura que armazena a imagem com todos os sprites da nave do jogador
LTextura naveSpriteSheet;

LTextura propulsorSpriteSheet;

// Declaração do objeto LTextura que armazena a imagem com todos os sprites do projétil laser;
LTextura projeteisSpriteSheet;

// Armazena a imagem com os sprites do inimigo01
LTextura inimigoSpriteSheet;

LTextura explosaoSpriteSheet;

LTextura background[10];

LTextura bossSpriteSheet;

LTextura DisparosSpriteSheet;

LTextura menuInicial;

LTextura menuSelecao;

LTextura telaGameOver;

LTextura TextoGameOver[3];

LTextura telaVitoria;

LTextura TextoVitoria[2];

LTextura InserirNome;

LTextura EntradaNome;

LTextura PlayerOnRanking[10];

// Declaração do objJogador que corresponde ao objeto manipulável pelo jogador
objJogador nave;

// Declaração do vetor objProjetilLaser que armazena todos os projéteis  
objProjetilLaser laser[quantLaser];

// Declaração do vetor objInimigo01 que armazena todos os inimigos01 
objInimigo01 inimigo01[quantInimigos01];

objInimigo02 inimigo02[quantInimigos02]; //quantInimigos02 = 2

objInimigo03 inimigo03[quantInimigos03];

objBoss BossInimigo;

objProjetilBoss BossDisparo;

objProjetilBoss02 BossProjetil02;

AnimExplosao vetorAnimExplosao[quantExplosoes];

AnimExplosao vetorExplosoesBoss[quantExplosoesBoss];

