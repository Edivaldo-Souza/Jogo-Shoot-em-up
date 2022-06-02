#pragma once
#include<iostream>
#include<cstdio>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include"constantes.h"
#include"FuncaoDeclaracao.h"
#include"Objetos.h"

// Função responsável pela inicialização da biblioteca SDL
bool init()
{
	// Inicialização da biblioteca SDL
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	// Criação da Janela
	gJanela = SDL_CreateWindow("Jogo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, larJanela, altJanela, SDL_WINDOW_SHOWN);
	// Criação do renderizador
	gRenderizador = SDL_CreateRenderer(gJanela, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(gRenderizador, 0xFF, 0xFF, 0xFF, 0xFF);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	return 0;
}

bool loadMedia()
{
	naveSpriteSheet.loadFromFile("spritesheets/spaceships.png", 0xFF, 0xFF, 0xFF);
	naveSpriteSheet.setBlendMode(SDL_BLENDMODE_BLEND);
	propulsorSpriteSheet.loadFromFile("spritesheets_2/Thruster_04.png", 0xFF, 0xFF, 0xFF);
	projeteisSpriteSheet.loadFromFile("spritesheets_2/Fx_012.png", 0xFF, 0, 0xFF);
	inimigoSpriteSheet.loadFromFile("spritesheets/Spaceships.png", 0xFF, 0, 0xFF);
	explosaoSpriteSheet.loadFromFile("spritesheets_2/explosion.png", 0xFF, 0, 0xFF);
	background[0].loadFromFile("background/background.png", 0xFF, 0, 0);
	background[1].loadFromFile("background/Surface_Layer3.png", 0xFF, 0, 0);
	background[2].loadFromFile("background/Surface_Layer4.png", 0xFF, 0, 0);
	background[3].loadFromFile("background/Surface_Layer1.png", 0xFF, 0, 0);
	background[4].loadFromFile("background/asteroide1.png", 0xFF, 0, 0);
	background[5].loadFromFile("background/asteroide2.png", 0xFF, 0, 0);
	background[6].loadFromFile("background/asteroide3.png", 0xFF, 0, 0);
	background[7].loadFromFile("background/asteroide4.png", 0xFF, 0, 0);
	bossSpriteSheet.loadFromFile("boss_spritesheet/boss_sprites.png", 0, 0xFF, 0);
	DisparosSpriteSheet.loadFromFile("spritesheets_2/beams.png", 0, 0xFF, 0);
	menuInicial.loadFromFile("menu_inicial_spritesheet/menu_botoes.png", 0, 0xFF, 0);
	menuSelecao.loadFromFile("menu_inicial_spritesheet/menu_botoes.png", 0, 0xFF, 0);
	telaGameOver.loadFromFile("menu_inicial_spritesheet/gameover.png", 0, 0xFF, 0);
	gFonte = TTF_OpenFont("fontes/arial_bold.TTF", 40);
	gFonte2 = TTF_OpenFont("fontes/Pixel_Sans_Serif.ttf", 20);
	gFonte3 = TTF_OpenFont("fontes/Pixel_Sans_Serif.ttf", 36);
	somDisparoBoss01 = Mix_LoadWAV("efeitos_sonoros/space_laser.wav");
	somExplosao = Mix_LoadWAV("efeitos_sonoros/synthetic_explosion_1.flac");

	// Definição dos parâmetros da SDL_Rect que armazenará certa porção da textura com os sprites da nave 
	naveClipParado[0].x = 256;
	naveClipParado[0].y = 128;
	naveClipParado[0].w = 64;
	naveClipParado[0].h = 64;

	PropulsorClip[0].x = 0;
	PropulsorClip[0].y = 0;
	PropulsorClip[0].w = 32;
	PropulsorClip[0].h = 32;

	PropulsorClip[1].x = 0;
	PropulsorClip[1].y = 0;
	PropulsorClip[1].w = 32;
	PropulsorClip[1].h = 32;

	PropulsorClip[2].x = 32;
	PropulsorClip[2].y = 0;
	PropulsorClip[2].w = 32;
	PropulsorClip[2].h = 32;

	PropulsorClip[3].x = 32;
	PropulsorClip[3].y = 0;
	PropulsorClip[3].w = 32;
	PropulsorClip[3].h = 32;

	// Definição dos parâmetros da SDL_Rect que armazenará certa porção da textura com os sprites dos projéteis
	laserClip[0].x = 64;
	laserClip[0].y = 1;
	laserClip[0].w = 32;
	laserClip[0].h = 32;
	// Declaração dos parâmetros da SDL_Rect que armazenará certa porção da textura com os sprites do inimigo01
	inimigoClip[0].x = 125;
	inimigoClip[0].y = 70;
	inimigoClip[0].w = 65;
	inimigoClip[0].h = 61;

	inimigoClip[1].x = 190;
	inimigoClip[1].y = 70;
	inimigoClip[1].w = 65;
	inimigoClip[1].h = 61;

	inimigoClip[2].x = 0;
	inimigoClip[2].y = 70;
	inimigoClip[2].w = 65;
	inimigoClip[2].h = 61;

	explosaoclip[0].x = 0;
	explosaoclip[0].y = 0;
	explosaoclip[0].w = 32;
	explosaoclip[0].h = 32;

	explosaoclip[1].x = 32;
	explosaoclip[1].y = 0;
	explosaoclip[1].w = 32;
	explosaoclip[1].h = 32;

	explosaoclip[2].x = 64;
	explosaoclip[2].y = 0;
	explosaoclip[2].w = 32;
	explosaoclip[2].h = 32;

	explosaoclip[3].x = 96;
	explosaoclip[3].y = 0;
	explosaoclip[3].w = 32;
	explosaoclip[3].h = 32;

	explosaoclip[4].x = 128;
	explosaoclip[4].y = 0;
	explosaoclip[4].w = 32;
	explosaoclip[4].h = 32;

	explosaoclip[5].x= 160;
	explosaoclip[5].y = 0;
	explosaoclip[5].w = 32;
	explosaoclip[5].h = 32;

	explosaoclip[6].x = 192;
	explosaoclip[6].y = 0;
	explosaoclip[6].w = 32;
	explosaoclip[6].h = 32;

	explosaoclip[7].x = 224;
	explosaoclip[7].y = 0;
	explosaoclip[7].w = 32;
	explosaoclip[7].h = 32;	

	BossClip.x = 0;
	BossClip.y = 0;
	BossClip.w = 180;
	BossClip.h = 410;

	BossProjetilClip[0].x = 210;
	BossProjetilClip[0].y = 305;
	BossProjetilClip[0].w = 35;
	BossProjetilClip[0].h = 83;

	BossProjetilClip[1].x = 0;
	BossProjetilClip[1].y = 105;
	BossProjetilClip[1].w = 30;
	BossProjetilClip[1].h = 35;

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
	inimigoSpriteSheet.free();
	bossSpriteSheet.free();
	Mix_FreeMusic(musicaFase);
	musicaFase = NULL;
	Mix_FreeChunk(somDisparoBoss01);
	somDisparoBoss01 = NULL;

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

void ondaInimigos03(bool flag)
{

	if (flag == true)
	{
		if (inimigo03[0].morto == true && inimigo03[1].morto == true && inimigo03[2].morto == true)
		{
			inimigo03[0].morto = false;
			inimigo03[1].morto = false;
			inimigo03[2].morto = false;
			inimigo03[0].partida = false;
			inimigo03[1].partida = false;
			inimigo03[2].partida = false;
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
	for (int i = 0; i < quantInimigos03; i++)
	{
		inimigo03[i].definePosicao();
	}
	for (int i = 0; i < quantLaser; i++)
	{
		laser[i].redefinir();
	}
	BossInimigo.redefinir();
	BossDisparo.redefinir();
	BossProjetil02.redefinir();
}

int iniciarMenu()
{
	bool sair = false;
	bool menu = false;
	bool recemIniciado = true;
	SDL_Event e;
	int escolha = 1;

	while (!menu)
	{
		menuSelecao.setColor(0, 0, 255);
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				menu = true;
				escolha = 3;
			}
			if (e.type == SDL_KEYDOWN)
			{

				switch (e.key.keysym.sym)
				{
				case SDLK_RETURN:
					menu = true;
					break;

				case SDLK_DOWN:
					escolha = escolha + 1;
					if (recemIniciado == true)
					{
						recemIniciado == false;
					}
					break;

				case SDLK_UP:
					escolha = escolha - 1;
					if (recemIniciado == true)
					{
						recemIniciado == false;
					}
					break;
				}
			}
			nave.avaliarEventos(e);
		}
		SDL_SetRenderDrawColor(gRenderizador, 0, 0, 0, 255);
		SDL_RenderClear(gRenderizador);
		menuInicial.renderizar(larJanela / 2 - 156 / 2, 120, &menuInicialClip[0]);
		menuInicial.renderizar(larJanela / 2 - 159 / 2, 240, &menuInicialClip[1]);
		menuInicial.renderizar(larJanela / 2 - 93 / 2, 360, &menuInicialClip[2]);

		switch (escolha)
		{
		case 0:
			menuSelecao.renderizar(larJanela / 2 - 93 / 2, 360, &menuInicialClip[2]);
			escolha = 3;
			break;
		case 1:
			menuSelecao.renderizar(larJanela / 2 - 156 / 2, 120, &menuInicialClip[0]);
			break;
		case 2:
			menuSelecao.renderizar(larJanela / 2 - 159 / 2, 240, &menuInicialClip[1]);
			break;
		case 3:
			menuSelecao.renderizar(larJanela / 2 - 93 / 2, 360, &menuInicialClip[2]);
			break;
		case 4:
			menuSelecao.renderizar(larJanela / 2 - 156 / 2, 120, &menuInicialClip[0]);
			escolha = 1;
			break;
		}
		SDL_RenderPresent(gRenderizador);
	}
	return escolha;
}
void Gameover()
{
	int deslocamentoTela = 0;
	SDL_Event e;
	SDL_Color c1 = { 0xFF,0xFF,0xFF};
	bool sair = false;
	int escolha = 1; 
	cronometro tempoDeExibicao;
	tempoDeExibicao.comecar();
	TextoGameOver[0].carregarTexto("CONTINUAR", c1, gFonte2);
	TextoGameOver[1].carregarTexto("SAIR", c1, gFonte2);
	TextoGameOver[2].carregarTexto("GAME OVER !", c1, gFonte3);

	while (!sair)
	{
		deslocamentoTela -= 1;
		if (deslocamentoTela < telaGameOver.getLargura() * -1)
		{
			deslocamentoTela = 0;
		}
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				sair = true;
				throw sair;
			}
			else if (e.type == SDL_KEYDOWN)
			{

				switch (e.key.keysym.sym)
				{
				case SDLK_RETURN:
					sair = true;
					break;

				case SDLK_DOWN:
					escolha = escolha + 2;
					break;

				case SDLK_UP:
					escolha = escolha - 2;
					break;
				}
			}
			nave.avaliarEventos(e);
		}
		switch (escolha)
		{
		case -1:
			TextoGameOver[1].setColor(255,0,0);
			TextoGameOver[0].setColor(255,255, 255);
			escolha = 3;
			break;
		case 1:
			TextoGameOver[0].setColor(255, 0, 0);
			TextoGameOver[1].setColor(255, 255, 255);
			break;
		case 3:
			TextoGameOver[1].setColor(255, 0, 0);
			TextoGameOver[0].setColor(255, 255, 255);
			break;
		case 5:
			TextoGameOver[0].setColor(255, 0, 0);
			TextoGameOver[1].setColor(255, 255, 255);
			escolha = 1;
			break;
		}
		telaGameOver.renderizar(deslocamentoTela, 0);
		telaGameOver.renderizar(deslocamentoTela + telaGameOver.getLargura(), 0);
		TextoGameOver[2].renderizar(160, 50);
		TextoGameOver[0].renderizar(110, 180);
		TextoGameOver[1].renderizar(110, 240);
		SDL_RenderPresent(gRenderizador);
	}
	if (escolha == -1 || escolha == 3)
	{
		throw sair;
	}
}

void vitoria()
{
	SDL_Event e;
	SDL_Color c = { 255,255,255 };
	bool sair = false;
	TextoVitoria[0].carregarTexto("FASE CONCLUIDA !", c, gFonte3);
	cronometro tempoDeExibicao;
	tempoDeExibicao.comecar();

	while (tempoDeExibicao.getTempo()<3000)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				sair = true;
				throw sair;
			}
			nave.avaliarEventos(e);
		}
		SDL_SetRenderDrawColor(gRenderizador, 0, 0, 0, 255);
		SDL_RenderClear(gRenderizador);
		TextoVitoria[0].renderizar(80, 50);
		SDL_RenderPresent(gRenderizador);
	}
}

std::string receberNome()
{
	bool sair = true;
	bool recemIniciado = true;
	SDL_Event e;
	SDL_Color corDoTexto = { 0xFF,0xFF,0xFF,0xFF };
	std::string nomeJogador = " ";
	InserirNome.carregarTexto("Insira seu nome: ", corDoTexto,gFonte);
	EntradaNome.carregarTexto(nomeJogador.c_str(), corDoTexto,gFonte);
	
	SDL_SetRenderDrawColor(gRenderizador, 0, 0, 0, 0xFF);
	SDL_RenderClear(gRenderizador);
	
	SDL_StartTextInput();
	while (sair == true)
	{
		bool atualizarTexto = false;

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				throw sair;
			}
			
			if (e.type == SDL_KEYUP)
			{
				if (e.key.keysym.sym == SDLK_RETURN && recemIniciado == false)
				{
					sair = false;
				}
			}
			
			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_BACKSPACE && nomeJogador.length() > 0)
				{
					nomeJogador.pop_back();
					atualizarTexto = true;
					std::cout << nomeJogador << std::endl;
				}
			}
			else if (e.type == SDL_TEXTINPUT)
			{
				nomeJogador += e.text.text;
				recemIniciado = false;
				atualizarTexto = true;
				std::cout << nomeJogador << std::endl;
			}
			nave.avaliarEventos(e);
		}
		if (atualizarTexto == true)
		{
			if (nomeJogador != "")
			{
				EntradaNome.carregarTexto(nomeJogador.c_str(), corDoTexto,gFonte);
			}
			else
			{
				EntradaNome.carregarTexto(" ", corDoTexto,gFonte);
			}
		}
		SDL_SetRenderDrawColor(gRenderizador,0, 0, 0, 0xFF);
		SDL_RenderClear(gRenderizador);

		InserirNome.renderizar(larJanela / 2 - InserirNome.getLargura() / 2, altJanela / 2 - InserirNome.getAltura() / 2);
		EntradaNome.renderizar((larJanela - EntradaNome.getLargura())/2, (altJanela - EntradaNome.getAltura())/2 + InserirNome.getAltura());
		SDL_RenderPresent(gRenderizador);
	}
	SDL_StopTextInput();
	return nomeJogador;
}

void escreveNoRanking(std::string nomeJogador, int pontuacao)
{
	FILE* ranking = NULL;
	int colocacao = 1;
	
	ranking = fopen("planilha/ranking.tsv", "w");
	//fprintf(ranking, "%i\t%s\t%i", colocacao,nomeJogador, pontuacao);
	fclose(ranking);
}

bool iniciarFase(bool iniciar, int HPinimigo01, int HPinimigo02, int HPinimigo03, int HPBoss, float tempoDisparo)
{
	bool sair = true;
	bool momentoDaFase = true;
	bool gameover = false;
	bool receberEventos = true;
	Uint32 tempoParaOBoss = 20000;
	Uint32 tempoParaDisparo = 5000;
	Uint32 tempoParaEncerramento = 2000;
	int deslocamentoBackground = 0;
	int deslocamentoAsteroide = 0;
	int deslocamentoAsteroide2 = 300;
	int deslocamentoAsteroide3 = 500;
	int r1 = 0;
	int r2 = 0;
	int r3 = 0;
	int y1 = 0;
	int y2 = 0;
	int y3 = 0;
	SDL_Event e;
	cronometro timerBoss;
	cronometro timerDisparo;
	
	for (int i = 0; i < quantInimigos01; i++)
	{
		inimigo01[i].HPdefinido = HPinimigo01;
	}
	for (int i = 0; i < quantInimigos02; i++)
	{
		inimigo02[i].HPdefinido = HPinimigo02;
	}
	for (int i = 0; i < quantInimigos02; i++)
	{
		inimigo03[i].HPdefinido = HPinimigo03;
	}
	*BossInimigo.ponteiroHP1 = HPBoss;
	*BossInimigo.ponteiroHP2 = HPBoss;

	BossProjetil02.velocidade = tempoDisparo;

	if (iniciar == true) {
		sair = false;
		timerBoss.comecar();
		while (sair == false)
		{
			while (SDL_PollEvent(&e) != 0 && receberEventos == true)
			{
				// Caso o evento lido seja o apertar do botão Fechar, a variável sair recebe true
				// e o looping principal é finalizado
				if (e.type == SDL_QUIT)
				{
					sair = true;
					throw sair;
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
				if (deslocamentoBackground < background[0].getLargura() * -1)
				{
					deslocamentoBackground = 0;
				}
				deslocamentoAsteroide -= 1;
				{
					if (deslocamentoAsteroide < -700)
						deslocamentoAsteroide = 0;
				}
				deslocamentoAsteroide2 -= 1;
				{
					if (deslocamentoAsteroide2 < -700)
						deslocamentoAsteroide2 = 0;
				}
				deslocamentoAsteroide3 -= 1;
				{
					if (deslocamentoAsteroide3 < -700)
						deslocamentoAsteroide3 = 0;
				}

				for (int i = 0; i < quantInimigos01; i++)
				{
					ondaInimigos01(momentoDaFase);
				}

				for (int i = 0; i < quantInimigos02; i++)
				{
					ondaInimigos02(momentoDaFase);
				}

				for (int i = 0; i < quantInimigos03; i++)
				{
					ondaInimigos03(momentoDaFase);
				}

				for (int i = 0; i < quantInimigos01; i++)
				{
					inimigo01[i].move();
				}

				inimigo02[0].move1();
				inimigo02[1].move2();

				
				inimigo03[0].partida = true;
				inimigo03[0].move();

				if (inimigo03[0].getPosX() < 580)
				{
					inimigo03[1].partida = true;
				}
				if (inimigo03[1].getPosX() < 580)
				{
					inimigo03[2].partida = true;
				}
				
				inimigo03[1].move();
				inimigo03[2].move();
				

				for (int i = 0; i < quantLaser; i++)
				{
					laser[i].move();
					vetorAnimExplosao[i].definirPosicao();
					laser[i].avaliaColisao();
				}

				if (BossInimigo.getHP1() <= 0)
				{
					for (int i = 0; i < quantExplosoesBoss / 2; i++)
					{
						vetorExplosoesBoss[i].atingido = true;
					}
				}
				if (BossInimigo.getHP2() <= 0)
				{
					for (int i = 4; i < quantExplosoesBoss; i++)
					{
						vetorExplosoesBoss[i].atingido = true;
					}
				}

				BossDisparo.move();

				BossProjetil02.definePosicao();
				BossProjetil02.move();

				SDL_SetRenderDrawColor(gRenderizador, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderizador);
				background[0].renderizar(deslocamentoBackground, 0);
				background[0].renderizar(deslocamentoBackground + background[0].getLargura(), 0);

				for (int i = 0;i < larJanela;i = i + 128)
				{
					background[1].renderizar(deslocamentoBackground + i, 416);
					background[1].renderizar(deslocamentoBackground + background[1].getLargura() * 5 + i, 416);
				}

				for (int i = 0; i < larJanela; i = i + 128)
				{
					background[2].renderizar(deslocamentoBackground + i, 352);
					background[2].renderizar(deslocamentoBackground + background[1].getLargura() * 5 + i, 352);
				}

				for (int i = 0; i < larJanela; i = i + 128)
				{
					background[3].renderizar(deslocamentoBackground + i, 320);
					background[3].renderizar(deslocamentoBackground + background[1].getLargura() * 5 + i, 320);
				}

				if (deslocamentoAsteroide <= -700)
				{
					r1 = 1 + rand() % (4 - 1 + 1);
					y1 = 1 + rand() % (270 - 1 + 1);
				}

				if (deslocamentoAsteroide2 <= -700)
				{
					r2 = 1 + rand() % (4 - 1 + 1);
					y2 = 1 + rand() % (270 - 1 + 1);
				}
				if (deslocamentoAsteroide3 <= -700)
				{
					r3 = 1 + rand() % (4 - 1 + 1);
					y3 = 1 + rand() % (270 - 1 + 1);
				}

				switch (r1)
				{
				case 1:
					background[4].renderizar(deslocamentoAsteroide + larJanela, y1);
					break;
				case 2:
					background[5].renderizar(deslocamentoAsteroide + larJanela, y1);
					break;
				case 3:
					background[6].renderizar(deslocamentoAsteroide + larJanela, y1);
					break;
				case 4:
					background[7].renderizar(deslocamentoAsteroide + larJanela, y1);
					break;
				}
				switch (r2)
				{
				case 1:
					background[4].renderizar(deslocamentoAsteroide2 + larJanela, y2);
					break;
				case 2:
					background[5].renderizar(deslocamentoAsteroide2 + larJanela, y2);
					break;
				case 3:
					background[6].renderizar(deslocamentoAsteroide2 + larJanela, y2);
					break;
				case 4:
					background[7].renderizar(deslocamentoAsteroide2 + larJanela, y2);
					break;
				}

				switch (r3)
				{
				case 1:
					background[4].renderizar(deslocamentoAsteroide3 + larJanela, y3);
					break;
				case 2:
					background[5].renderizar(deslocamentoAsteroide3 + larJanela, y3);
					break;
				case 3:
					background[6].renderizar(deslocamentoAsteroide3 + larJanela, y3);
					break;
				case 4:
					background[7].renderizar(deslocamentoAsteroide3 + larJanela, y3);
					break;
				}

				nave.renderizar();

				SDL_Rect* clipAtual = &PropulsorClip[frame / 4];
				propulsorSpriteSheet.renderizar(nave.getPosX(), nave.getPosY() + 7, clipAtual, 180);
				propulsorSpriteSheet.renderizar(nave.getPosX(), nave.getPosY() + 22, clipAtual, 180);

				frame++;

				if (frame / 4 >= 4)
				{
					frame = 0;
				}

				for (int i = 0; i < quantLaser; i++)
				{
					laser[i].renderizar();
				}

				for (int i = 0; i < quantExplosoes; i++)
				{
					vetorAnimExplosao[i].renderizar();
				}

				for (int i = 0; i < quantInimigos01; i++)
				{
					inimigo01[i].renderizar();
				}

				inimigo02[0].renderizar();
				inimigo02[1].renderizar();

				for (int i = 0; i < quantInimigos03; i++)
				{
					inimigo03[i].renderizar();
				}

				BossDisparo.renderizar();

				BossInimigo.renderizar();

				BossProjetil02.renderizar();

				vetorExplosoesBoss[0].renderizar02(500, 120);
				vetorExplosoesBoss[1].renderizar02(590, 130);
				vetorExplosoesBoss[2].renderizar02(530, 140);
				vetorExplosoesBoss[3].renderizar02(550, 110);

				vetorExplosoesBoss[4].renderizar02(500, 320);
				vetorExplosoesBoss[5].renderizar02(590, 330);
				vetorExplosoesBoss[6].renderizar02(530, 340);
				vetorExplosoesBoss[7].renderizar02(550, 310);
			}

			
			SDL_RenderPresent(gRenderizador);
			if (nave.getHP() <= 0)
			{
				receberEventos = false;
				sair = true;
				std::cout << "false";
				if (iniciar == true)
				{
					Gameover();
				}
				return false;
			}
			else if (BossInimigo.getHP1() <= 0 && BossInimigo.getHP2() <= 0)
			{
				receberEventos = false;
				sair = true;
				pontuacaoAtual += PONT_BOSS;
				reiniciarFase();
				std::cout << "true";
				vitoria();
				return true;
			}
		}
	}
	return false;
}
