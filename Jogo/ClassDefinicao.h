#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include"ClassDeclaracao.h"
#include"FuncaoDeclaracao.h"
#include"constantes.h"
#include"Objetos.h"

// fun��o que atribui os valores inicias as vari�veis da classe
LTextura::LTextura()
{
	mTextura = NULL;
	mLargura = 0;
	mAltura = 0;
}

// fun��o que redefine os valores das vari�veis da classe para como iniciamente foram definidas em LTextura()
LTextura::~LTextura()
{
	free();
}
// fun��o que recebe uma string correspondente ao caminho(nome_da_pasta/imagem.png) da imagem a ser utilizada como textura
bool LTextura::loadFromFile(std::string path, Uint32 r, Uint32 g, Uint32 b)
{
	// free() apaga qualquer defini��o de mTextura e suas dimens�es antes de carregar uma nova imagem
	free();

	// novaTextura � uma SDL_Texture que est� apenas no escopo dessa fun��o para criar a textura
	// e retornar seu valor para a vari�vel da classe mTextura
	SDL_Texture* novaTextura = NULL;

	// loadSurface � a SDL_Surface onde se � carregada a imagem correspondente ao caminho passado no par�metro da fun��o
	SDL_Surface* loadSuperficie = IMG_Load(path.c_str());

	// SDL_ColorKey torna certa tonalidade de pixels transparentes de uma SDL_Surface
	SDL_SetColorKey(loadSuperficie, SDL_TRUE, SDL_MapRGB(loadSuperficie->format, r, g, b));

	// novaTextura cria recebe o valor da cria��o de uma textura a partir de loadSuperficie
	novaTextura = SDL_CreateTextureFromSurface(gRenderizador, loadSuperficie);

	// mLargura recebe a largura de loadSuperficie
	mLargura = loadSuperficie->w;

	// mAltura recebe a altura de loadSuperficie
	mAltura = loadSuperficie->h;

	// Apaga a imagem carregada em loadSuperficie
	SDL_FreeSurface(loadSuperficie);

	// mTextura recebe a textura de novaTextura
	mTextura = novaTextura;

	// a fun��o retorna true quando mTextura armazenar alguma coisa  
	return mTextura != NULL;
}

// fun��o que apaga a textura mas recente carregada, e redifine suas dimens�es para o valor de 0
void LTextura::free()
{
	// Caso mTextura n�o esteja vazio, o que este armazena e suas dimens�es ser�o redefinidas
	if (mTextura != NULL)
	{
		SDL_DestroyTexture(mTextura);
		mTextura = NULL;
		mLargura = 0;
		mAltura = 0;
	}
}

// fun�ao para realizar a modula��o das cores de uma textura 
void LTextura::setColor(Uint8 r, Uint8 g, Uint8 b)
{
	SDL_SetTextureColorMod(mTextura, r, g, b);
}


// fun��o que renderiza uma textura na janela recebendo sua posi��o(x,y), um SDL_Rect para o caso
// de ser necess�rio renderizar apenas uma parcela da imagem carregada, um �ngulo de rota��o,
// um SDL_Point para definir um ponto de refer�ncia para a rota��o, e um SDL_RendererFlip para
// espelhar sua posi��o na vertical e horizontal.
void LTextura::renderizar(int x, int y, SDL_Rect* clip, double angulo, SDL_Point* centro, SDL_RendererFlip flip)
{
	// Como a vari�vel clip representa a SDL_Rect em que ser� armazenada a parcela da textura,
	// a vari�vel renderQuad � utilizada para especificar a posi��o x,y e as dimens�es de tal
	// parcela.
	SDL_Rect renderQuad = { x,y,mLargura,mAltura };
	// Caso o par�metro clip esteja preenchido com o endere�o de algum SDL_Rect...
	if (clip != NULL)
	{
		// A largura de renderQuad recebe o valor da largura de clip
		renderQuad.w = clip->w;
		// A altura de renderQuad recebe o valor da altura de clip
		renderQuad.h = clip->h;
		// Dessa maneira s� � necess�rio preencher os valores das dimens�es da SDL_Rect que for
		// definir o par�metro clip 
	}
	SDL_RenderCopyEx(gRenderizador, mTextura, clip, &renderQuad, angulo, centro, flip);
}

// fun��o que retorna a vari�vel mLargura;
int LTextura::getLargura()
{
	return mLargura;
}

// fun��o que retorna a vari�vel mAltura;
int LTextura::getAltura()
{
	return mAltura;
}

// fun��o que atribui os valores iniciais as vari�veis desta classe
objJogador::objJogador()
{
	mPosY = altJanela / 2 - altJogador / 2;
	mPosX = 10;
	mVelY = 0;
	mVelX = 0;
	HP = 5;
	caixaDeColisao.x = mPosX;
	caixaDeColisao.y = mPosY;
	caixaDeColisao.w = larJogador;
	caixaDeColisao.h = altJogador;
}

// fun��o que recebe como par�metro eventos (apertar de teclas) e define qual o sentido do
// deslocamento da textura do jogador ao somar ou subtrair a constante deslocamento
// a vari�vel mVelY, a qual ser� somada a posi��o da textura pela fun��o move()
void objJogador::avaliarEventos(SDL_Event& e)
{
	// Se uma tecla for pressionada uma �nica vez...
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		// E caso essa tecla seja..
		switch (e.key.keysym.sym)
		{
			// Igual a "w", mVelY assume um valor negativo que faz a posi��o em Y da textura do jogador se aproximar de 0
		case SDLK_w: mVelY -= deslocamento; break;
			// Igual a "s", mVelY assume um valor positivo que faz a posi��o em Y da textura do jogador se aproximar da altura da janela
		case SDLK_s: mVelY += deslocamento; break;
			// Igual a "a", mVelY assume um valor negativo que faz a posi��o em X da textura do jogador se aproximar de 0
		case SDLK_a: mVelX -= deslocamento; break;
			// Igual a "d", mVelY assume um valor positivo que faz a posi��o em X da textura do jogador se aproximar da altura da janela
		case SDLK_d: mVelX += deslocamento; break;
		}
	}
	// Se uma tecla for solta um �nica vez...
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		// E caso essa tecla seja...
		switch (e.key.keysym.sym)
		{
			// Igual a "w", o valor de mVelY ser� incrementado no mesmo valor em que foi reduzido a fim
			// de evitar um ac�mulo de subtra��es que poderiam aumentar a taxa de pixels deslocados por
			// apertar de tecla
		case SDLK_w: mVelY += deslocamento; break;
			// A mesma ideia se aplica quando se aperta a tecla "s", apenas as opera��es s�o invertidas;
		case SDLK_s: mVelY -= deslocamento; break;
		case SDLK_a: mVelX += deslocamento; break;
		case SDLK_d: mVelX -= deslocamento; break;
		}
	}
}
// fun��o que recebe como par�metro eventos (tecla SPACE) e define quando um projetil deve ser disparado
void objJogador::avaliarEventosLaser(SDL_Event& e)
{
	// vari�vel que define quando a o "indiceVetorLaser" deve ser acrescido em 1 para
	// que esta fun��o seja capaz de "disparar" todos os objProjetil do vetor "laser"
	bool proximoLaser = false;
	// Caso a tecla SPACE seja pressionada uma �nica vez...
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE && e.key.repeat == 0)
	{
		// proximoLaser recebe true para aumentar "indiceVetorLaser em 1"
		proximoLaser = true;
		// Caso "indiceVetorLaser" adquira um valor que ultrapasse a capacidade do vetor laser"
		// o valor de "indiceVetorLaser" retorna a 0 para que a fun��o reaproveite os membros do vetor
		// que j� foram utilizados
		if (indiceVetorLaser == quantLaser)
		{
			indiceVetorLaser = 0;
		}
		// Determina que dado menbro do vetor laser pode ser movido e renderizado pela tela
		laser[indiceVetorLaser].disparado = true;
		// Determina que dado membro do vetor laser deve atualizar sua posi��o para a �ltima posi��o da nave do jogador
		laser[indiceVetorLaser].atualizaPosicaoDePartida = true;
		indiceVetorLaser += 1;
		proximoLaser = false;
	}
}

// fun��o que altera a posi��o Y da textura do jogador com base no sinal(sentido) da vari�vel mVelY
void objJogador::move()
{
	// O incremento (ou decremento) a vari�vel mPosY, reajusta a posi��o da textura do jogador
	mPosY += mVelY;
	caixaDeColisao.y += mVelY;
	// Caso a posi��o da textura assuma um valor menor do que 0, ou se a textura do jogador tenda
	// a ultrapassar o limite da tela por conta de sua altura em rela��o a posi��o que ela assume...
	if ((mPosY < 0) || (mPosY + altJogador > altJanela))
	{
		// A posi��o em Y da textura � decrementada ou incrementada de modo a evitar que a textura ultrapasse a tela
		mPosY -= mVelY;
		caixaDeColisao.y -= mVelY;
	}

	// o mesmo se aplica para o deslocamento em Y
	mPosX += mVelX;
	caixaDeColisao.x += mVelX;
	if ((mPosX < 0) || (mPosX + larJogador > larJanela))
	{
		mPosX -= mVelX;
		caixaDeColisao.x -= mVelX;
	}
}

void objJogador::avaliarColisao()
{
	if (tempoInvencibilidade.foiIniciado() == false)
	{
		for (int i = 0; i < quantInimigos01; i++)
		{
			if (verificaColisao(caixaDeColisao, inimigo01[i].getCaixaDeColisao()) == true)
			{
				HP -= 1;
				inimigo01[i].definePosicao();
				tempoInvencibilidade.comecar();
			}
		}
		for (int i = 0; i < quantInimigos02; i++)
		{
			if (verificaColisao(caixaDeColisao, inimigo02[i].getCaixaDeColisao()) == true)
			{
				HP -= 1;
				inimigo02[i].definePosicao();
				tempoInvencibilidade.comecar();
			}
		}

		if (verificaColisao(caixaDeColisao, BossDisparo.getCaixaDeColisao()) == true && BossDisparo.disparado == true)
		{
			HP -= 3;
			BossDisparo.disparado = false;
			tempoInvencibilidade.comecar();
		}
	}
	else if (tempoInvencibilidade.getTempo() > tempoImortal)
	{
		tempoInvencibilidade.parar();
	}
}

void objJogador::redefinir()
{
	mPosY = altJanela / 2 - altJogador / 2;
	mPosX = 10;
	mVelY = 0;
	mVelX = 0;
	HP = 5;
	caixaDeColisao.x = mPosX;
	caixaDeColisao.y = mPosY;
	caixaDeColisao.w = larJogador;
	caixaDeColisao.h = altJogador;
}

// fun��o que retorna a lagura da textura do jogador
int objJogador::getLargura()
{
	return larJogador;
}

// fun��o que retorna a altura da textura do jogador
int objJogador::getAltura()
{
	return altJogador;
}

// fun��o que retorna a posi��o em Y da textura do jogador
int objJogador::getPosY()
{
	return mPosY;
}

// fun��o que retorna a posi��o em X da textura do jogador
int objJogador::getPosX()
{
	return mPosX;
}

int objJogador::getHP()
{
	return HP;
}

// retorna a caixa de colis�o do jogador
SDL_Rect objJogador::getCaixaDeColisao()
{
	return caixaDeColisao;
}

// fun��o que renderiza a textura do jogador
void objJogador::renderizar()
{
	naveSpriteSheet.renderizar(mPosX, mPosY, &naveClipParado[0], 90, NULL);
}

// fun��o que define os valores de suas vari�veis  
objProjetilLaser::objProjetilLaser()
{
	posX = 0;
	posY = 0;
	caixaDeColisao.x = NULL;
	caixaDeColisao.y = NULL;
	caixaDeColisao.w = larProjetil;
	caixaDeColisao.h = altProjetil;
}

void objProjetilLaser::move()
{
	// Caso a vari�vel "atualizaPosicaoDePartida" tenha valor true, a posi��o da textura do projetil
	// recebe as coordenadas xy correspondentes a frente da textura da nave do jogador em sua �ltima posi��o 
	if (atualizaPosicaoDePartida == true)
	{
		// posi��o em X logo a frente da nave
		posX = nave.getPosX() + nave.getLargura();
		caixaDeColisao.x = nave.getPosX() + nave.getLargura();
		// posi��o em Y no meio da frente da nave
		posY = (nave.getPosY() + nave.getAltura() / 2) - altProjetil / 2;
		caixaDeColisao.y = (nave.getPosY() + nave.getAltura() / 2) - altProjetil / 2;
		// o valor de "atualizaPosicaoDePartida" recebe false para que est� condi��o n�o seja mais satisfeita
		atualizaPosicaoDePartida = false;
	}
	// Caso disparado tenha valor true, a posi��o em X ser� encrementada em 15 toda vez que a fun��o for chamada
	if (disparado == true)
	{
		posX += velocidadeProjetil;
		caixaDeColisao.x += velocidadeProjetil;
	}
	else
	{
		caixaDeColisao.x = nave.getPosX();
		caixaDeColisao.y = nave.getPosY() + nave.getAltura() / 2 - altProjetil / 2;
	}
	// No momento em que a posi��o X textura do projetil for igual ao largura da janela, ou seja o final desta
	if (posX == larJanela)
	{
		// disparado recebe false para cancelar as adi��es de 15 na posi��o da textura do projetil
		disparado = false;
	}
}

void objProjetilLaser::avaliaColisao()
{
	for (int i = 0; i < quantInimigos01; i++)
	{
		if (verificaColisao(caixaDeColisao, inimigo01[i].getCaixaDeColisao()) == true && disparado == true)
		{
			*inimigo01[i].ponteiroHP -= DANO;
			if (*inimigo01[i].ponteiroHP <= 0)
			{
				inimigo01[i].definePosicao();
			}
			disparado = false;
		}
	}
	for (int i = 0; i < quantInimigos02; i++)
	{
		if (verificaColisao(caixaDeColisao, inimigo02[i].getCaixaDeColisao()) == true && disparado == true)
		{
			*inimigo02[i].ponteiroHP -= DANO;
			if (*inimigo02[i].ponteiroHP <= 0)
			{
				inimigo02[i].definePosicao();
			}
			disparado = false;
		}
	}
	for (int i = 0; i < BossInimigo.totalDeCaixas; i++)
	{
		if (verificaColisao(caixaDeColisao, BossInimigo.ponteiroCaixaDeColisao[i]) == true && disparado == true && BossInimigo.morto == false)
		{
			if (i == 0 || i == 1)
			{
				*BossInimigo.ponteiroHP = *BossInimigo.ponteiroHP - DANO;
				disparado = false;
			}
			else
			{
				disparado = false;
			}
		}
	}
}

void objProjetilLaser::redefinir()
{
	posX = 0;
	posY = 0;
	caixaDeColisao.x = NULL;
	caixaDeColisao.y = NULL;
	caixaDeColisao.w = larProjetil;
	caixaDeColisao.h = altProjetil;
	disparado = false;
}

// renderiza a textura do proj�til na tela
void objProjetilLaser::renderizar()
{
	// Enquanto disparado for igual a true, a textura do projetil ser� renderizada na tela toda vez que for chamada
	if (disparado == true)
	{
		projeteisSpriteSheet.renderizar(posX, posY, &laserClip[0], 90);
	}
}

// retorna a caixa de colis�o do proj�til
SDL_Rect objProjetilLaser::getCaixaDeColisao()
{
	return caixaDeColisao;
}

// Define valores para as vari�veis da classe
objInimigo01::objInimigo01()
{
	HPmutavel = HPdefinido;
	posX = larJanela;
	posY = rand() % ((altJanela - altInimigo) + 1);
	caixaDeColisao.x = posX;
	caixaDeColisao.y = posY;
	caixaDeColisao.w = larInimigo;
	caixaDeColisao.h = altInimigo;
}

void objInimigo01::definePosicao()
{
	HPmutavel = HPdefinido;
	posX = larJanela;
	posY = rand() % ((altJanela - altInimigo) + 1);
	caixaDeColisao.x = posX;
	caixaDeColisao.y = posY;
	morto = true;
}

// move o inimigo01
void objInimigo01::move()
{
	// Caso "morto" seja falso, o inimigo01 se mover� da esquerda para a direita
	if (morto == false)
	{
		posX -= velocidadeEixoX;
		caixaDeColisao.x -= velocidadeEixoX;
		// Caso a posi��o em Y do inimigo seja inferior a do jogador, a posi��o do inimigo 
		// tender� a se aproximar da posi��o do jogador
		if (posY < nave.getPosY())
		{
			posY += velocidadeEixoY;
			caixaDeColisao.y += velocidadeEixoY;
		}
		// Caso a posi��o em Y do inimigo seja superior a do jogador, a posi��o do inimigo 
		// tender� a se aproximar da posi��o do jogador
		else if (posY > nave.getPosY())
		{
			posY -= velocidadeEixoY;
			caixaDeColisao.y -= velocidadeEixoY;
		}
	}
	// Caso o inimigo ultrapasse a tela
	if (posX < larInimigo * -1)
	{
		definePosicao();
	}
}

void objInimigo01::renderizar()
{
	if (morto == false)
	{
		inimigo01SpriteSheet.renderizar(posX, posY, &inimigo01Clip[0], 90);
	}
}

int objInimigo01::getPosX()
{
	return posX;
}

SDL_Rect objInimigo01::getCaixaDeColisao()
{
	return caixaDeColisao;
}

objInimigo02::objInimigo02()
{
	HPmutavel = HPdefinido;
	posX = larJanela;
	posY = altJanela / 2;
	caixaDeColisao.x = posX;
	caixaDeColisao.y = posY;
	caixaDeColisao.w = larInimigo;
	caixaDeColisao.h = altInimigo;
}

void objInimigo02::definePosicao()
{
	HPmutavel = HPdefinido;
	posX = larJanela;
	posY = altJanela / 2;
	caixaDeColisao.x = posX;
	caixaDeColisao.y = posY;
	morto = true;
}

void objInimigo02::move1()
{
	if (morto == false)
	{
		posX -= velocidadeEixoX;
		caixaDeColisao.x -= velocidadeEixoX;

		if (posX > larJanela - Div)
		{
			posY -= velocidadeEixoY;
			caixaDeColisao.y -= velocidadeEixoY;
		}
		else
		{
			if (posX > larJanela - (2 * Div))
			{
				posY += velocidadeEixoY;
				caixaDeColisao.y += velocidadeEixoY;
			}
			else
			{
				if (posX > larJanela - (3 * Div))
				{
					posY += velocidadeEixoY;
					caixaDeColisao.y += velocidadeEixoY;
				}
				else
				{
					posY -= velocidadeEixoY;
					caixaDeColisao.y -= velocidadeEixoY;
				}
			}
		}

	}
	if (posX < larInimigo * -1)
	{
		definePosicao();
	}
}

void objInimigo02::move2()
{
	if (morto == false)
	{
		posX -= velocidadeEixoX;
		caixaDeColisao.x -= velocidadeEixoX;

		if (posX > 480)
		{
			posY += velocidadeEixoY;
			caixaDeColisao.y += velocidadeEixoY;
		}
		else
		{
			if (posX > 320)
			{
				posY -= velocidadeEixoY;
				caixaDeColisao.y -= velocidadeEixoY;
			}
			else
			{
				if (posX > 160)
				{
					posY -= velocidadeEixoY;
					caixaDeColisao.y -= velocidadeEixoY;
				}
				else
				{
					posY += velocidadeEixoY;
					caixaDeColisao.y += velocidadeEixoY;
				}
			}
		}

	}
	if (posX < larInimigo * -1)
	{
		definePosicao();
	}
}


void objInimigo02::renderizar()
{
	if (morto == false)
	{
		inimigo01SpriteSheet.renderizar(posX, posY, &inimigo01Clip[1], 0);
	}
}

SDL_Rect objInimigo02::getCaixaDeColisao()
{
	return caixaDeColisao;
}

objBoss::objBoss()
{
	posXBoss = larJanela;
	posYBoss = altJanela / 2 - altTotal / 2;
	HP = 100;
	for (int i = 0; i < totalDeCaixas - 1; i++)
	{
		caixasDeColisao[i].x = NULL;
		caixasDeColisao[i].y = NULL;
		caixasDeColisao[i].w = larCanhao;
		caixasDeColisao[i].h = altCanhao;
	}
	caixasDeColisao[2].x = NULL;
	caixasDeColisao[2].y = NULL;
	caixasDeColisao[2].w = larTotal;
	caixasDeColisao[2].h = altTotal;

}

void objBoss::definirCaixasDeColisao()
{
	caixasDeColisao[0].x = posXBoss + 7;  // posi��o X do Canh�o Superior
	caixasDeColisao[0].y = posYBoss + 84; // posi��o Y do Canh�o Superior
	caixasDeColisao[1].x = posXBoss + 7;  // posi��o X do Canh�o Inferior
	caixasDeColisao[1].y = caixasDeColisao[0].y + 205; // posi��o Y do Canh�o Inferior
	caixasDeColisao[2].x = posXBoss + 10; // posi��o X do Boss 
	caixasDeColisao[2].y = posYBoss; // posi��o Y do Boss

}

void objBoss::redefinir()
{
	posXBoss = larJanela;
	posYBoss = altJanela / 2 - altTotal / 2;
	HP = 100;
	for (int i = 0; i < totalDeCaixas - 1; i++)
	{
		caixasDeColisao[i].x = NULL;
		caixasDeColisao[i].y = NULL;
		caixasDeColisao[i].w = larCanhao;
		caixasDeColisao[i].h = altCanhao;
	}
	caixasDeColisao[2].x = NULL;
	caixasDeColisao[2].y = NULL;
	caixasDeColisao[2].w = larTotal;
	caixasDeColisao[2].h = altTotal;

	aparecer = false;
	morto = true;
}

void objBoss::renderizar()
{
	if (aparecer == true)
	{
		if (posXBoss != larJanela - larTotal)
		{
			posXBoss -= 5;
			bossSpriteSheet.renderizar(posXBoss, posYBoss, &BossClip);
		}
		else
		{
			aparecer = false;
			definirCaixasDeColisao();
			morto = false;
		}
	}
	else
	{
		bossSpriteSheet.renderizar(posXBoss, posYBoss, &BossClip);
	}
}

int objBoss::getHP()
{
	return HP;
}

objProjetilBoss::objProjetilBoss()
{
	posX = larJanela - 250;
	posY = 410 / 2;
	CaixaDeColisao.x = posX;
	CaixaDeColisao.y = posY;
	CaixaDeColisao.w = larProjetil;
	CaixaDeColisao.h = altProjetil;
}



void objProjetilBoss::move()
{
	if (disparado == true)
	{
		posX -= velocidadeProjetil;
		CaixaDeColisao.x -= velocidadeProjetil;
	}
	else
	{
		posX = larJanela - 250;
		CaixaDeColisao.x = posX;

	}
	if (posX < 0 - larProjetil)
	{
		disparado = false;

	}
}

void objProjetilBoss::redefinir()
{
	posX = larJanela - 250;
	posY = 410 / 2;
	CaixaDeColisao.x = posX;
	CaixaDeColisao.y = posY;
	CaixaDeColisao.w = larProjetil;
	CaixaDeColisao.h = altProjetil;
	disparado = false;
}

void objProjetilBoss::renderizar()
{
	if (disparado == true)
	{
		bossSpriteSheet.renderizar(posX, posY, &BossProjetilClip[0], 180);
	}

}

SDL_Rect objProjetilBoss::getCaixaDeColisao()
{
	return CaixaDeColisao;
}

objProjetilBoss02::objProjetilBoss02()
{
	posX01 = 0;
	posY01 = 0;
	posX02 = 0;
	posY02 = 0;
	posYAlvo = 0;
	posXAlvo = 0;
	for (int i = 0; i < quantCaixasDeColisao; i++)
	{
		caixaDeColisao[i].x = 0;
		caixaDeColisao[i].y = 0;
		caixaDeColisao[i].w = larProjetil;
		caixaDeColisao[i].h = altProjetil;
	}
}

void objProjetilBoss02::definePosicao()
{
	if (BossInimigo.morto == false && disparado1 == false && disparado2 == false)
	{
		posX01 = BossInimigo.ponteiroCaixaDeColisao[0].x;
		posY01 = BossInimigo.ponteiroCaixaDeColisao[0].y;
		caixaDeColisao[0].x = posX01;
		caixaDeColisao[0].y = posY01;
		disparado1 = true;

		posX02 = BossInimigo.ponteiroCaixaDeColisao[1].x;
		posY02 = BossInimigo.ponteiroCaixaDeColisao[1].y;
		caixaDeColisao[1].x = posX02;
		caixaDeColisao[1].y = posY02;
		disparado2 = true;
		
		posXAlvo = nave.getPosX() + nave.getLargura()/2;
		posYAlvo = nave.getPosY() + nave.getAltura()/2;
		if (posYAlvo > posY01)
		{
			sentidoProjetil1 = true;
		}
		if (posYAlvo > posY02)
		{
			sentidoProjetil2 = true;
		}
	}
}

void objProjetilBoss02::move()
{
	if ((posYAlvo > posY01 || posXAlvo < posX01) && sentidoProjetil1 == true)
	{
	
		posY01 += 3;
		posX01 -= velocidadeProjetil;
	}
	else
	{
		posY01 -= 3;
		posX01 -= velocidadeProjetil;
	}
	if (posX01 < larProjetil * -1 || posY01 > larJanela + larProjetil || posY01 < larProjetil * -1)
	{
		disparado1 = false;
	}
	if ((posYAlvo > posY02 || posXAlvo < posX02) && sentidoProjetil2 == true)
	{
		posY02 += 3;
		posX02 -= velocidadeProjetil;
	}
	else 
	{
		posY02 -= 3;
		posX02 -= velocidadeProjetil;
	}
	if (posX02 < larProjetil * -1 || posY02 > larJanela + larProjetil || posY02 < larProjetil * -1)
	{
		disparado2 = false;
	}
}

void objProjetilBoss02::redefinir()
{
	posX01 = 0;
	posY01 = 0;
	posX02 = 0;
	posY02 = 0;
	posYAlvo = 0;
	for (int i = 0; i < quantCaixasDeColisao; i++)
	{
		caixaDeColisao[i].x = 0;
		caixaDeColisao[i].y = 0;
		caixaDeColisao[i].w = larProjetil;
		caixaDeColisao[i].h = altProjetil;
	}
	disparado1 = false;
	disparado2 = false;
}

void objProjetilBoss02::renderizar()
{
	if (BossInimigo.morto == false)
	{
		bossSpriteSheet.renderizar(posX01, posY01, &BossProjetilClip[1]);
		bossSpriteSheet.renderizar(posX02, posY02, &BossProjetilClip[1]);
	}
}


cronometro::cronometro()
{
	TempoQuandoIniciado = 0;
	TempoQuandoPausado = 0;
	iniciado = false;
	pausado = false;
}
void cronometro::comecar()
{
	iniciado = true;
	pausado = false;
	TempoQuandoIniciado = SDL_GetTicks();
	TempoQuandoPausado = 0;
}

void cronometro::parar()
{
	iniciado = false;
	pausado = false;
	TempoQuandoIniciado = 0;
	TempoQuandoPausado = 0;
}

void cronometro::pausar()
{
	if (iniciado == true && pausado == false)
	{
		pausado = true;
		TempoQuandoPausado = SDL_GetTicks() - TempoQuandoIniciado;
		TempoQuandoIniciado = 0;
	}
}

void cronometro::despausar()
{
	if (iniciado == true && pausado == true)
	{
		pausado = false;
		TempoQuandoIniciado = SDL_GetTicks() - TempoQuandoPausado;
		TempoQuandoPausado = 0;
	}
}

Uint32 cronometro::getTempo()
{
	Uint32 tempo = 0;
	if (iniciado == true)
	{
		if (pausado == true)
		{
			tempo = TempoQuandoPausado;
		}
		else
		{
			tempo = SDL_GetTicks() - TempoQuandoIniciado;
		}
	}
	return tempo;
}

bool cronometro::foiIniciado()
{
	return iniciado;
}
bool cronometro::foiPausado()
{
	return pausado;
}


