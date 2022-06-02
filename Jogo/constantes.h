#pragma once
#include <SDL.h>;
#include<SDL_mixer.h>
#include<SDL_ttf.h>

// Declaração da largura da janela;
const int larJanela = 640;

// Declaração da altura da janela;
const int altJanela = 480;

enum PontosPorInimigo
{
	PONT_INIMIGO01 = 10,
	PONT_INIMIGO02 = 10,
	PONT_INIMIGO03 = 10,
	PONT_BOSS = 100,
};

// Define a quantidade de projéteis a serem criados
const int quantLaser = 15;

const int quantProjetilBoss02 = 4;

// Define a quantidade de inimigos01 a serem criados
const int quantInimigos01 = 3;

const int quantInimigos02 = 2;

const int quantInimigos03 = 3;

const int quantExplosoes = 15;

const int quantExplosoesBoss = 8;

// Declaração do inteiro usado para selecionar os indices do vetor de objProjeteis "laser"
int indiceVetorLaser;

int Div = larJanela / 4;

int frame = 0;

int pontuacaoAtual = 0;


// Declaração da Janela
SDL_Window* gJanela = NULL;

// Declaração do Renderizador
SDL_Renderer* gRenderizador = NULL;

Mix_Music* musicaFase = NULL;

Mix_Chunk* somDisparoBoss01 = NULL;

Mix_Chunk* somExplosao = NULL;

TTF_Font* gFonte = NULL;

TTF_Font* gFonte2 = NULL;

TTF_Font* gFonte3 = NULL;

// Declaração do vetor de SDL_Rect que armazena os sprites da nave do jogador enquanto parada
SDL_Rect naveClipParado[4];

SDL_Rect PropulsorClip[4];

SDL_Rect clipAtual;

// Declaração do vetor de SDL_Rect que armazena os sprites do objProjetil "laser"
SDL_Rect laserClip[2];

// Declaração do vetor de SDL_Rect que armazena os sprites do objInimigo01 "inimigo01"
SDL_Rect inimigoClip[3];

SDL_Rect explosaoclip[8];

SDL_Rect BossClip;

SDL_Rect BossProjetilClip[2];

SDL_Rect menuInicialClip[3];

SDL_Rect TextoGameOverClip[2];
