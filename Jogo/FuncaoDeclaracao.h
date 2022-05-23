#pragma once
#include<SDL.h>


// Função responsável pela inicialização da biblioteca SDL
bool init();

// Função responsável por carregar mídias(imagens,áudios,fonts)
bool loadMedia();

// Função responsável por "desligar" a biblioteca SDL e apagar os valores de estruturas globais(SDL_Window,SDL_Renderer,SDL_Textue)
void close();

// Função que verifica se duas caixas de colisão se cruzaram
bool verificaColisao(SDL_Rect a, SDL_Rect b);

int iniciarMenu();

bool iniciarFase(bool iniciar, int HPinimigo01, int HPinimigo02, int HPBoss, float tempoDisparo);

std::string receberNome();

void escreveNoRanking(std::string nomeJogador, int pontuacao);