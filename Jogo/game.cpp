// inclusão das bibliotecas
#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include<string>
#include"constantes.h"
#include"ClassDeclaracao.h"
#include"FuncaoDeclaracao.h"
#include"Objetos.h"
#include"ClassDefinicao.h"
#include"FuncaoDefinicao.h"


int main(int argc, char* args[])
{
	init();
	loadMedia();
	bool sair = false;
	bool momentoDaFase = true;
	bool gameover = false;
	bool menu = false;
	bool recemIniciado = true;
	Uint32 tempoParaOBoss = 5000;
	Uint32 tempoParaDisparo = 5000;
	Uint32 tempoParaDisparo2 = 2000;
	SDL_Event e;
	int deslocamentoBackground = 0;
	int escolha = 1;
	cronometro timerBoss;
	cronometro timerDisparo;
	cronometro intervaloEntreDisparos;
	// Enquanto sair for o que ele não 


	while (!sair)
	{
		while (!menu)
		{
			menuSelecao.setColor(0, 0, 255);
			while (SDL_PollEvent(&e) != 0)
			{
				menuInicial.renderizar(larJanela / 2 - 156 / 2, 120, &menuInicialClip[0]);
				menuInicial.renderizar(larJanela / 2 - 159 / 2, 240, &menuInicialClip[1]);
				menuInicial.renderizar(larJanela / 2 - 93 / 2, 360, &menuInicialClip[2]);
				if (e.type == SDL_KEYDOWN)
				{

					switch (e.key.keysym.sym)
					{
					case SDLK_e:
						menu = true;
						if ((escolha == 1 && recemIniciado == true) || escolha == 0 || escolha == 3)
						{
							timerBoss.comecar();
						}
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
			}
			SDL_RenderPresent(gRenderizador);
		}

		switch (escolha)
		{
			case 1:

				// Looping responsável por ler os eventos, que termina apenas quando a quantidade de eventos
				// acumulados seja igual a 0
				while (SDL_PollEvent(&e) != 0)
				{
					// Caso o evento lido seja o apertar do botão Fechar, a variável sair recebe true
					// e o looping principal é finalizado
					if (e.type == SDL_QUIT)
					{
						sair = true;
					}
					nave.avaliarEventos(e);
					nave.avaliarEventosLaser(e);
					if (gameover == true && e.type == SDL_KEYUP && e.key.repeat == 0 && e.key.keysym.sym == SDLK_r)
					{
						SDL_SetRenderDrawColor(gRenderizador, 0, 0, 0, 0);
						SDL_RenderClear(gRenderizador);
						reiniciarFase();
						momentoDaFase = true;
						gameover = false;
						timerBoss.comecar();
					}
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

				}

				SDL_RenderPresent(gRenderizador);
				if (nave.getHP() <= 0)
				{
					gameover = true;
				}
				break;

			case 2:
				//ranking
				sair = true;
				break;

			case 3:
				sair = true;
				break;
		}
	}
	close();
	return 0;
}
