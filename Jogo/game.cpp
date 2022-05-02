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
	bool menu = false;
	bool recemIniciado = true;
	bool fase01,fase02,fase03 = false;
	SDL_Event e;
	int escolha = 1;
	// Enquanto sair for o que ele não 


	while (!menu)
	{
		menuSelecao.setColor(0, 0, 255);
		while (SDL_PollEvent(&e) != 0)
		{
			menuInicial.renderizar(larJanela / 2 - 156 / 2, 120, &menuInicialClip[0]);
			menuInicial.renderizar(larJanela / 2 - 159 / 2, 240, &menuInicialClip[1]);
			menuInicial.renderizar(larJanela / 2 - 93 / 2, 360, &menuInicialClip[2]);
			if (e.type == SDL_QUIT)
			{
				menu = true;
				sair = true;
			}
			if (e.type == SDL_KEYDOWN)
			{

				switch (e.key.keysym.sym)
				{
				case SDLK_e:
					menu = true;
					if ((escolha == 1 && recemIniciado == true) || escolha == 0 || escolha == 3)
					{
						fase01 = true;
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
				
				fase02 = iniciarFase(fase01,1,1,20);
				fase03 = iniciarFase(fase02,3,1,40);

				break;

			case 2:
				//ranking
				sair = true;
				break;

			case 3:
				sair = true;
				break;
	}
	close();
	return 0;
}
