#pragma once
#include<SDL.h>


// Fun��o respons�vel pela inicializa��o da biblioteca SDL
bool init();

// Fun��o respons�vel por carregar m�dias(imagens,�udios,fonts)
bool loadMedia();

// Fun��o respons�vel por "desligar" a biblioteca SDL e apagar os valores de estruturas globais(SDL_Window,SDL_Renderer,SDL_Textue)
void close();

// Fun��o que verifica se duas caixas de colis�o se cruzaram
bool verificaColisao(SDL_Rect a, SDL_Rect b);

int iniciarMenu();

bool iniciarFase(bool iniciar, int HPinimigo01, int HPinimigo02, int HPBoss, float tempoDisparo);

std::string receberNome();

void escreveNoRanking(std::string nomeJogador, int pontuacao);