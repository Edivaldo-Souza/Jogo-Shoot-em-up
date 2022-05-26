// inclusão das bibliotecas
#define _CRT_SECURE_NO_WARNINGS
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
	bool encerrar = false;
	bool fase01,fase02,fase03 = false;

	do
	{
		switch (iniciarMenu())
		{
		case 1:
			fase01 = true;
			pontuacaoAtual = 0;
			reiniciarFase();
			try
			{
				fase02 = iniciarFase(fase01, 1, 1, 20, 0.0005);
				fase03 = iniciarFase(fase02, 3, 1, 40, 0.0008);
				escreveNoRanking(receberNome(), pontuacaoAtual);
			}
			catch (bool sair)
			{
				encerrar = true;
				break;
			}
			break;
		case 2:
			//ranking
			break;

		case 3:
			encerrar = true;
			break;
		}
		//SDL_SetRenderDrawColor(gRenderizador, 0, 0, 0, 255);
		//SDL_RenderClear(gRenderizador);
	} while (encerrar == false);
	close();
	return 0;
}
