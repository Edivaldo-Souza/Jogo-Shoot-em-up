#pragma once
#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include"constantes.h"
#include"FuncaoDeclaracao.h"
#include"Objetos.h"

// Função responsável pela inicialização da biblioteca SDL
bool init()
{
	// Inicialização da biblioteca SDL
	SDL_Init(SDL_INIT_VIDEO);
	// Criação da Janela
	gJanela = SDL_CreateWindow("Jogo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, larJanela, altJanela, SDL_WINDOW_SHOWN);
	// Criação do renderizador
	gRenderizador = SDL_CreateRenderer(gJanela, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(gRenderizador, 0xFF, 0xFF, 0xFF, 0xFF);
	IMG_Init(IMG_INIT_PNG);
	return 0;
}

bool loadMedia()
{
	naveSpriteSheet.loadFromFile("spritesheets/STRIP-1.gif", 0xFF, 0xFF, 0xFF);
	projeteisSpriteSheet.loadFromFile("spritesheets_2/projetil_Laser.png", 0xFF, 0, 0xFF);
	inimigo01SpriteSheet.loadFromFile("spritesInimigos/inimigo01.png", 0xFF, 0, 0xFF);
	background.loadFromFile("background/background.png", 0xFF, 0, 0);
	bossSpriteSheet.loadFromFile("boss_spritesheet/boss_sprites.png", 0, 0xFF, 0);
	menuInicial.loadFromFile("menu_inicial_spritesheet/menu_botoes.png", 0, 0xFF, 0);
	menuSelecao.loadFromFile("menu_inicial_spritesheet/menu_botoes.png", 0, 0xFF, 0);

	// Definição dos parâmetros da SDL_Rect que armazenará certa porção da textura com os sprites da nave 
	naveClipParado[0].x = 1;
	naveClipParado[0].y = 1;
	naveClipParado[0].w = 46;
	naveClipParado[0].h = 44;
	// Definição dos parâmetros da SDL_Rect que armazenará certa porção da textura com os sprites dos projéteis
	laserClip[0].x = 1;
	laserClip[0].y = 1;
	laserClip[0].w = 24;
	laserClip[0].h = 41;
	// Declaração dos parâmetros da SDL_Rect que armazenará certa porção da textura com os sprites do inimigo01
	inimigo01Clip[0].x = 1;
	inimigo01Clip[0].y = 1;
	inimigo01Clip[0].w = 45;
	inimigo01Clip[0].h = 43;

	inimigo01Clip[1].x = 45;
	inimigo01Clip[1].y = 1;
	inimigo01Clip[1].w = 37;
	inimigo01Clip[1].h = 45;

	BossClip.x = 0;
	BossClip.y = 0;
	BossClip.w = 180;
	BossClip.h = 410;

	BossProjetilClip[0].x = 18;
	BossProjetilClip[0].y = 414;
	BossProjetilClip[0].w = 201;
	BossProjetilClip[0].h = 70;

	BossProjetilClip[1].x = 0;
	BossProjetilClip[1].y = 414;
	BossProjetilClip[1].w = 15;
	BossProjetilClip[1].h = 14;

	menuInicialClip[0].x = 0;
	menuInicialClip[0].y = 0;
	menuInicialClip[0].w = 156;
	menuInicialClip[0].h = 55;

	menuInicialClip[1].x = 0;
	menuInicialClip[1].y = 56;
	menuInicialClip[1].w = 159;
	menuInicialClip[1].h = 55;

	menuInicialClip[2].x = 0;
	menuInicialClip[2].y = 110;
	menuInicialClip[2].w = 93;
	menuInicialClip[2].h = 43;


	return 0;
}

void close()
{
	// Apaga os valores das variáveis desse objeto LTextura 
	naveSpriteSheet.free();
	projeteisSpriteSheet.free();
	inimigo01SpriteSheet.free();
	bossSpriteSheet.free();

	// Desfaz a Janela
	SDL_DestroyWindow(gJanela);
	// Desfaz o Renderizador
	SDL_DestroyRenderer(gRenderizador);
	// Redifine as variáveis como vazias
	gJanela = NULL;
	gRenderizador = NULL;

	// Desligamento das bibliotecas inicializadas
	IMG_Quit();
	SDL_Quit();
}

bool verificaColisao(SDL_Rect a, SDL_Rect b)
{
	int esquerdaA = a.x;
	int topoA = a.y;
	int direitaA = a.x + a.w;
	int fundoA = a.y + a.h;
	int esquerdaB = b.x;
	int topoB = b.y;
	int direitaB = b.x + b.w;
	int fundoB = b.y + b.h;

	if (((esquerdaA >= direitaB) || (direitaA <= esquerdaB) || (topoA >= fundoB) || (fundoA <= topoB)) == false)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ondaInimigos01(bool flag)
{
	int indiceInimigo = rand() % 3;
	if (flag == true)
	{
		if (inimigo01[indiceInimigo].morto == true)
		{
			inimigo01[indiceInimigo].morto = false;
		}
	}
}

void ondaInimigos02(bool flag) 
{
	int indiceInimigo = rand() % quantInimigos02;
	if (flag == true)
	{
		if (inimigo02[indiceInimigo].morto == true)
		{
			inimigo02[indiceInimigo].morto = false;
		}
	}
}

void reiniciarFase()
{
	nave.redefinir();
	for (int i = 0; i < quantInimigos01; i++)
	{
		inimigo01[i].definePosicao();
	}
	for (int i = 0; i < quantInimigos02; i++)
	{
		inimigo02[i].definePosicao();
	}
	for (int i = 0; i < quantLaser; i++)
	{
		laser[i].redefinir();
	}
	BossInimigo.redefinir();
	BossDisparo.redefinir();
	for (int i = 0; i < quantProjetilBoss02; i++)
	{
		BossProjetil02[i].redefinir();
	}
}

bool iniciarFase(bool iniciar, int HPinimigo01, int HPinimigo02, int HPBoss)
{
	bool sair = true;
	bool momentoDaFase = true;
	bool gameover = false;
	Uint32 tempoParaOBoss = 20000;
	Uint32 tempoParaDisparo = 5000;
	Uint32 tempoParaDisparo2 = 2000;
	int deslocamentoBackground = 0;
	SDL_Event e;
	cronometro timerBoss;
	cronometro timerDisparo;
	cronometro intervaloEntreDisparos;


	for (int i = 0; i < quantInimigos01; i++)
	{
		inimigo01[i].HPdefinido = HPinimigo01;
	}
	for (int i = 0; i < quantInimigos02; i++)
	{
		inimigo02[i].HPdefinido = HPinimigo02;
	}
	*BossInimigo.ponteiroHP = HPBoss;

	if (iniciar == true)
	{
		sair = false;
		timerBoss.comecar();
	}

	while (sair==false)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			// Caso o evento lido seja o apertar do botão Fechar, a variável sair recebe true
			// e o looping principal é finalizado
			if (e.type == SDL_QUIT)
			{
				sair = true;
				return false;
			}
			nave.avaliarEventos(e);
			nave.avaliarEventosLaser(e);
		}
		if (gameover == false)
		{
			if (timerBoss.getTempo() > tempoParaOBoss)
			{
				momentoDaFase = false;
				BossInimigo.aparecer = true;
				timerBoss.parar();
				timerDisparo.comecar();
				intervaloEntreDisparos.comecar();
			}

			if (timerDisparo.getTempo() > tempoParaDisparo && BossInimigo.morto == false)
			{
				BossDisparo.disparado = true;
				timerDisparo.parar();
				timerDisparo.comecar();
			}

			nave.move();
			nave.avaliarColisao();

			deslocamentoBackground -= 1;
			if (deslocamentoBackground < background.getLargura() * -1)
			{
				deslocamentoBackground = 0;
			}

			for (int i = 0; i < quantInimigos01; i++)
			{
				ondaInimigos01(momentoDaFase);
			}

			for (int i = 0; i < quantInimigos02; i++)
			{
				ondaInimigos02(momentoDaFase);
			}

			for (int i = 0; i < quantInimigos01; i++)
			{
				inimigo01[i].move();
			}

			inimigo02[0].move1();
			inimigo02[1].move2();

			for (int i = 0; i < quantLaser; i++)
			{
				laser[i].move();
				laser[i].avaliaColisao();
			}

			BossDisparo.move();

			BossProjetil02[0].definePosicao();
			BossProjetil02[0].move();

			SDL_SetRenderDrawColor(gRenderizador, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(gRenderizador);

			background.renderizar(deslocamentoBackground, 0);
			background.renderizar(deslocamentoBackground + background.getLargura(), 0);

			nave.renderizar();

			for (int i = 0; i < quantLaser; i++)
			{
				laser[i].renderizar();
			}


			for (int i = 0; i < quantInimigos01; i++)
			{
				inimigo01[i].renderizar();
			}

			inimigo02[0].renderizar();
			inimigo02[1].renderizar();

			BossDisparo.renderizar();

			BossInimigo.renderizar();

			BossProjetil02[0].renderizar();

		}

		SDL_RenderPresent(gRenderizador);
		if (nave.getHP() <= 0)
		{
			sair = true;
			std::cout << "false";
			return false;
		}
		if (BossInimigo.getHP() <= 0)
		{
			sair = true;
			reiniciarFase();
			std::cout << "true";
			return true;
		}
	}
}