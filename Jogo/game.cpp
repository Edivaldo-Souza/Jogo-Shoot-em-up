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
	bool fase01,fase02,fase03,fase04 = false;

	do
	{
		fase01, fase02, fase03, fase04 = false;
		switch (iniciarMenu())
		{
		case 1:
			fase01 = true;
			pontuacaoAtual = 0;
			reiniciarFase();
			try
			{
				fase02 = iniciarFase(fase01, 1, 1, 1, 10, 0.0005);
				fase03 = iniciarFase(fase02, 2, 2, 2, 20, 0.0008);
				fase04 = iniciarFase(fase03, 3, 3, 3, 30, 0.0009);
				escreveNoRanking(setPlayerName(), pontuacaoAtual);
				
			}
			catch (bool sair)
			{
				encerrar = true;
				break;
			}
			break;

		case 2:
			try
			{
				read_ranking();
			}
			catch (bool sair)
			{
				encerrar = true;
				break;
			}
			break;

		case 3:
			encerrar = true;
			break;
		}
	} while (encerrar == false);
	close();
	return 0;
}
