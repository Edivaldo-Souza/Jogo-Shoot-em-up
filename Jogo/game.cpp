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
	bool fase01,fase02,fase03 = false;

	switch (iniciarMenu())
	{
			case 1:
				
				fase01 = true;
				fase02 = iniciarFase(fase01,1,1,20,0.0005);
				fase03 = iniciarFase(fase02,3,1,40,0.0008);

				break;

			case 2:
				//ranking
				break;

			case 3:
				break;
	}
	close();
	return 0;
}
