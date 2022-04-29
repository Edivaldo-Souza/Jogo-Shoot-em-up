#pragma once
#include <SDL.h>;
// Declara��o da largura da janela;
const int larJanela = 640;

// Declara��o da altura da janela;
const int altJanela = 480;

// Define a quantidade de proj�teis a serem criados
const int quantLaser = 15;

const int quantProjetilBoss02 = 4;

// Define a quantidade de inimigos01 a serem criados
const int quantInimigos01 = 3;

const int quantInimigos02 = 2;

// Declara��o do inteiro usado para selecionar os indices do vetor de objProjeteis "laser"
int indiceVetorLaser;

int Div = larJanela / 4;

// Declara��o da Janela
SDL_Window* gJanela = NULL;

// Declara��o do Renderizador
SDL_Renderer* gRenderizador = NULL;

// Declara��o do vetor de SDL_Rect que armazena os sprites da nave do jogador enquanto parada
SDL_Rect naveClipParado[3];

// Declara��o do vetor de SDL_Rect que armazena os sprites do objProjetil "laser"
SDL_Rect laserClip[2];

// Declara��o do vetor de SDL_Rect que armazena os sprites do objInimigo01 "inimigo01"
SDL_Rect inimigo01Clip[2];

SDL_Rect inimigo02Clip[2];

SDL_Rect BossClip;

SDL_Rect BossProjetilClip[2];

SDL_Rect menuInicialClip[3];