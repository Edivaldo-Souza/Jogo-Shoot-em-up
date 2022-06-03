#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include"ClassDeclaracao.h"
#include"FuncaoDeclaracao.h"
#include"constantes.h"
#include"Objetos.h"

// função que atribui os valores inicias as variáveis da classe
LTextura::LTextura()
{
	mTextura = NULL;
	mLargura = 0;
	mAltura = 0;
}

// função que redefine os valores das variáveis da classe para como iniciamente foram definidas em LTextura()
LTextura::~LTextura()
{
	free();
}
// função que recebe uma string correspondente ao caminho(nome_da_pasta/imagem.png) da imagem a ser utilizada como textura
bool LTextura::loadFromFile(std::string path, Uint32 r, Uint32 g, Uint32 b)
{
	// free() apaga qualquer definição de mTextura e suas dimensões antes de carregar uma nova imagem
	free();

	// novaTextura é uma SDL_Texture que está apenas no escopo dessa função para criar a textura
	// e retornar seu valor para a variável da classe mTextura
	SDL_Texture* novaTextura = NULL;

	// loadSurface é a SDL_Surface onde se é carregada a imagem correspondente ao caminho passado no parâmetro da função
	SDL_Surface* loadSuperficie = IMG_Load(path.c_str());

	// SDL_ColorKey torna certa tonalidade de pixels transparentes de uma SDL_Surface
	SDL_SetColorKey(loadSuperficie, SDL_TRUE, SDL_MapRGB(loadSuperficie->format, r, g, b));

	// novaTextura cria recebe o valor da criação de uma textura a partir de loadSuperficie
	novaTextura = SDL_CreateTextureFromSurface(gRenderizador, loadSuperficie);

	// mLargura recebe a largura de loadSuperficie
	mLargura = loadSuperficie->w;

	// mAltura recebe a altura de loadSuperficie
	mAltura = loadSuperficie->h;

	// Apaga a imagem carregada em loadSuperficie
	SDL_FreeSurface(loadSuperficie);

	// mTextura recebe a textura de novaTextura
	mTextura = novaTextura;

	// a função retorna true quando mTextura armazenar alguma coisa  
	return mTextura != NULL;
}

bool LTextura::carregarTexto(std::string textoTextura, SDL_Color corDoTexto,TTF_Font* font)
{
	free();
	SDL_Surface* superficie_Texto = TTF_RenderText_Solid(font, textoTextura.c_str(), corDoTexto);
	if (superficie_Texto == NULL)
	{
		std::cout << TTF_GetError();
	}
	else
	{
		mTextura = SDL_CreateTextureFromSurface(gRenderizador, superficie_Texto);
		mLargura = superficie_Texto->w;
		mAltura = superficie_Texto->h;
		SDL_FreeSurface(superficie_Texto);
	}
	return mTextura != NULL;
}

// função que apaga a textura mas recente carregada, e redifine suas dimensões para o valor de 0
void LTextura::free()
{
	// Caso mTextura não esteja vazio, o que este armazena e suas dimensões serão redefinidas
	if (mTextura != NULL)
	{
		SDL_DestroyTexture(mTextura);
		mTextura = NULL;
		mLargura = 0;
		mAltura = 0;
	}
}

// funçao para realizar a modulação das cores de uma textura 
void LTextura::setColor(Uint8 r, Uint8 g, Uint8 b)
{
	SDL_SetTextureColorMod(mTextura, r, g, b);
}

void LTextura::setBlendMode(SDL_BlendMode blending)
{
	SDL_SetTextureBlendMode(mTextura, blending);
}

void LTextura::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(mTextura, alpha);
}


// função que renderiza uma textura na janela recebendo sua posição(x,y), um SDL_Rect para o caso
// de ser necessário renderizar apenas uma parcela da imagem carregada, um ângulo de rotação,
// um SDL_Point para definir um ponto de referência para a rotação, e um SDL_RendererFlip para
// espelhar sua posição na vertical e horizontal.
void LTextura::renderizar(int x, int y, SDL_Rect* clip, double angulo, SDL_Point* centro, SDL_RendererFlip flip)
{
	// Como a variável clip representa a SDL_Rect em que será armazenada a parcela da textura,
	// a variável renderQuad é utilizada para especificar a posição x,y e as dimensões de tal
	// parcela.
	SDL_Rect renderQuad = { x,y,mLargura,mAltura };
	// Caso o parâmetro clip esteja preenchido com o endereço de algum SDL_Rect...
	if (clip != NULL)
	{
		// A largura de renderQuad recebe o valor da largura de clip
		renderQuad.w = clip->w;
		// A altura de renderQuad recebe o valor da altura de clip
		renderQuad.h = clip->h;
		// Dessa maneira só é necessário preencher os valores das dimensões da SDL_Rect que for
		// definir o parâmetro clip 
	}
	SDL_RenderCopyEx(gRenderizador, mTextura, clip, &renderQuad, angulo, centro, flip);
}

// função que retorna a variável mLargura;
int LTextura::getLargura()
{
	return mLargura;
}

// função que retorna a variável mAltura;
int LTextura::getAltura()
{
	return mAltura;
}

// função que atribui os valores iniciais as variáveis desta classe
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

// função que recebe como parâmetro eventos (apertar de teclas) e define qual o sentido do
// deslocamento da textura do jogador ao somar ou subtrair a constante deslocamento
// a variável mVelY, a qual será somada a posição da textura pela função move()
void objJogador::avaliarEventos(SDL_Event& e)
{
	// Se uma tecla for pressionada uma única vez...
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		// E caso essa tecla seja..
		switch (e.key.keysym.sym)
		{
			// Igual a "w", mVelY assume um valor negativo que faz a posição em Y da textura do jogador se aproximar de 0
		case SDLK_w: mVelY -= deslocamento; break;
			// Igual a "s", mVelY assume um valor positivo que faz a posição em Y da textura do jogador se aproximar da altura da janela
		case SDLK_s: mVelY += deslocamento; break;
			// Igual a "a", mVelY assume um valor negativo que faz a posição em X da textura do jogador se aproximar de 0
		case SDLK_a: mVelX -= deslocamento; break;
			// Igual a "d", mVelY assume um valor positivo que faz a posição em X da textura do jogador se aproximar da altura da janela
		case SDLK_d: mVelX += deslocamento; break;
		}
	}
	// Se uma tecla for solta um única vez...
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		// E caso essa tecla seja...
		switch (e.key.keysym.sym)
		{
			// Igual a "w", o valor de mVelY será incrementado no mesmo valor em que foi reduzido a fim
			// de evitar um acúmulo de subtrações que poderiam aumentar a taxa de pixels deslocados por
			// apertar de tecla
		case SDLK_w: mVelY += deslocamento; break;
			// A mesma ideia se aplica quando se aperta a tecla "s", apenas as operações são invertidas;
		case SDLK_s: mVelY -= deslocamento; break;
		case SDLK_a: mVelX += deslocamento; break;
		case SDLK_d: mVelX -= deslocamento; break;
		}
	}
}
// função que recebe como parâmetro eventos (tecla SPACE) e define quando um projetil deve ser disparado
void objJogador::avaliarEventosLaser(SDL_Event& e)
{
	// variável que define quando a o "indiceVetorLaser" deve ser acrescido em 1 para
	// que esta função seja capaz de "disparar" todos os objProjetil do vetor "laser"
	bool proximoLaser = false;
	// Caso a tecla SPACE seja pressionada uma única vez...
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE && e.key.repeat == 0)
	{
		// proximoLaser recebe true para aumentar "indiceVetorLaser em 1"
		proximoLaser = true;
		// Caso "indiceVetorLaser" adquira um valor que ultrapasse a capacidade do vetor laser"
		// o valor de "indiceVetorLaser" retorna a 0 para que a função reaproveite os membros do vetor
		// que já foram utilizados
		if (indiceVetorLaser == quantLaser)
		{
			indiceVetorLaser = 0;
		}
		// Determina que dado menbro do vetor laser pode ser movido e renderizado pela tela
		laser[indiceVetorLaser].disparado = true;
		// Determina que dado membro do vetor laser deve atualizar sua posição para a última posição da nave do jogador
		laser[indiceVetorLaser].atualizaPosicaoDePartida = true;
		indiceVetorLaser += 1;
		proximoLaser = false;
	}
}

// função que altera a posição Y da textura do jogador com base no sinal(sentido) da variável mVelY
void objJogador::move()
{
	// O incremento (ou decremento) a variável mPosY, reajusta a posição da textura do jogador
	mPosY += mVelY;
	caixaDeColisao.y += mVelY;
	// Caso a posição da textura assuma um valor menor do que 0, ou se a textura do jogador tenda
	// a ultrapassar o limite da tela por conta de sua altura em relação a posição que ela assume...
	if ((mPosY < 0) || (mPosY + altJogador > altJanela))
	{
		// A posição em Y da textura é decrementada ou incrementada de modo a evitar que a textura ultrapasse a tela
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
		naveSpriteSheet.setAlpha(255);
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
		for (int i = 0; i < quantInimigos03; i++)
		{
			if (verificaColisao(caixaDeColisao, inimigo03[i].getCaixaDeColisao()) == true)
			{
				HP -= 1;
				inimigo03[i].definePosicao();
				tempoInvencibilidade.comecar();
			}
		}

		if (verificaColisao(caixaDeColisao, BossDisparo.getCaixaDeColisao()) == true && BossDisparo.disparado == true)
		{
			HP -= 3;
			BossDisparo.disparado = false;
			tempoInvencibilidade.comecar();
		}

		for (int i = 0;i < BossProjetil02.quantCaixasDeColisao; i++)
		{
			if (verificaColisao(caixaDeColisao, BossProjetil02.ponteiroCaixaDeColisao[i])==true)
			{
				HP -= 1;
				if (i == 0)
				{
					BossProjetil02.disparado1 = false;
					tempoInvencibilidade.comecar();
				}
				else
				{
					BossProjetil02.disparado2 = false;
					tempoInvencibilidade.comecar();
				}
			}
		}
		for (int i = 0; i < BossInimigo.totalDeCaixas; i++)
		{
			if (verificaColisao(caixaDeColisao, BossInimigo.ponteiroCaixaDeColisao[i]) == true && BossInimigo.morto==false)
			{
				HP -= 1;
				mPosX -= 10;
				caixaDeColisao.x = mPosX;
			}
		}
	}
	else if (tempoInvencibilidade.getTempo() > tempoImortal)
	{
		tempoInvencibilidade.parar();
	}
	else
	{
		naveSpriteSheet.setAlpha(127);
	}
}

void objJogador::redefinir()
{
	mPosY = altJanela / 2 - altJogador / 2;
	mPosX = 10;
	HP = 5;
	caixaDeColisao.x = mPosX;
	caixaDeColisao.y = mPosY;
}

// função que retorna a lagura da textura do jogador
int objJogador::getLargura()
{
	return larJogador;
}

// função que retorna a altura da textura do jogador
int objJogador::getAltura()
{
	return altJogador;
}

// função que retorna a posição em Y da textura do jogador
int objJogador::getPosY()
{
	return mPosY;
}

// função que retorna a posição em X da textura do jogador
int objJogador::getPosX()
{
	return mPosX;
}

int objJogador::getHP()
{
	return HP;
}

// retorna a caixa de colisão do jogador
SDL_Rect objJogador::getCaixaDeColisao()
{
	return caixaDeColisao;
}

// função que renderiza a textura do jogador
void objJogador::renderizar()
{
	naveSpriteSheet.renderizar((int)mPosX,(int)mPosY, &naveClipParado[0], 0);
}

// função que define os valores de suas variáveis  
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
	// Caso a variável "atualizaPosicaoDePartida" tenha valor true, a posição da textura do projetil
	// recebe as coordenadas xy correspondentes a frente da textura da nave do jogador em sua última posição 
	if (atualizaPosicaoDePartida == true)
	{
		// posição em X logo a frente da nave
		posX = nave.getPosX() + nave.getLargura();
		caixaDeColisao.x = nave.getPosX() + nave.getLargura();
		// posição em Y no meio da frente da nave
		posY = (nave.getPosY() + nave.getAltura() / 2) - altProjetil / 2;
		caixaDeColisao.y = (nave.getPosY() + nave.getAltura() / 2) - altProjetil / 2;
		// o valor de "atualizaPosicaoDePartida" recebe false para que está condição não seja mais satisfeita
		atualizaPosicaoDePartida = false;
	}
	// Caso disparado tenha valor true, a posição em X será encrementada em 15 toda vez que a função for chamada
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
	// No momento em que a posição X textura do projetil for igual ao largura da janela, ou seja o final desta
	if (posX == larJanela)
	{
		// disparado recebe false para cancelar as adições de 15 na posição da textura do projetil
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
				pontuacaoAtual += PONT_INIMIGO01;
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
				pontuacaoAtual += PONT_INIMIGO02;
			}
			disparado = false;
		}
	}
	for (int i = 0; i < quantInimigos03; i++)
	{
		if (verificaColisao(caixaDeColisao, inimigo03[i].getCaixaDeColisao()) == true && disparado == true)
		{
			*inimigo03[i].ponteiroHP -= DANO;
			if (*inimigo03[i].ponteiroHP <= 0)
			{
				inimigo03[i].definePosicao();
				pontuacaoAtual += PONT_INIMIGO03;
			}
			disparado = false;
		}
	}
	for (int i = 0; i < BossInimigo.totalDeCaixas; i++)
	{
		if (verificaColisao(caixaDeColisao, BossInimigo.ponteiroCaixaDeColisao[i]) == true && disparado == true && BossInimigo.morto == false)
		{
			if (i == 0)
			{
				if (BossInimigo.getHP1() > 0)
				{
					Mix_PlayChannel(-1, somExplosao, 0);
				}
				*BossInimigo.ponteiroHP1 = *BossInimigo.ponteiroHP1 - DANO;
				std::cout << *BossInimigo.ponteiroHP1 << std::endl;
				disparado = false;
			}
			else if (i == 1)
			{
				if (BossInimigo.getHP2() > 0)
				{
					Mix_PlayChannel(-1, somExplosao, 0);
				}
				*BossInimigo.ponteiroHP2 = *BossInimigo.ponteiroHP2 - DANO;
				std::cout << *BossInimigo.ponteiroHP2 << std::endl;
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

// renderiza a textura do projétil na tela
void objProjetilLaser::renderizar()
{
	// Enquanto disparado for igual a true, a textura do projetil será renderizada na tela toda vez que for chamada
	if (disparado == true)
	{
		projeteisSpriteSheet.renderizar(posX, posY,&laserClip[0]);
	}
}

// retorna a caixa de colisão do projétil
SDL_Rect objProjetilLaser::getCaixaDeColisao()
{
	return caixaDeColisao;
}

// Define valores para as variáveis da classe
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
	// Caso "morto" seja falso, o inimigo01 se moverá da esquerda para a direita
	if (morto == false)
	{
		posX -= velocidadeEixoX;
		caixaDeColisao.x -= velocidadeEixoX;
		// Caso a posição em Y do inimigo seja inferior a do jogador, a posição do inimigo 
		// tenderá a se aproximar da posição do jogador
		if (posY < nave.getPosY())
		{
			posY += velocidadeEixoY;
			caixaDeColisao.y += velocidadeEixoY;
		}
		// Caso a posição em Y do inimigo seja superior a do jogador, a posição do inimigo 
		// tenderá a se aproximar da posição do jogador
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
		inimigoSpriteSheet.renderizar(posX, posY, &inimigoClip[0], 0);
	}
}

int objInimigo01::getPosX()
{
	return posX;
}

int objInimigo01::getPosY()
{
	return posY;
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
		inimigoSpriteSheet.renderizar(posX, posY, &inimigoClip[1], 270);
	}
}

SDL_Rect objInimigo02::getCaixaDeColisao()
{
	return caixaDeColisao;
}

int objInimigo02::getPosX()
{
	return posX;
}

int objInimigo02::getPosY()
{
	return posY;
}

objInimigo03::objInimigo03()
{
	HPmutavel = HPdefinido;
	posX = larJanela;
	posY = altJanela / 4;
	caixaDeColisao.x = posX;
	caixaDeColisao.y = posY;
	caixaDeColisao.w = larInimigo;
	caixaDeColisao.h = altInimigo;
}

void objInimigo03::definePosicao()
{
	HPmutavel = HPdefinido;
	posX = larJanela;
	posY = altJanela / 4;
	caixaDeColisao.x = posX;
	caixaDeColisao.y = posY;
	morto = true;
	circ = false;
	partida = false;
}

void objInimigo03::move()
{

	if (partida == true)
	{
		if (morto == false)
		{

			if (posX == larJanela / 2 && posY == altJanela / 4)
			{
				circ = true;
			}
			else
			{
				if (posX < 260 && posY > 180)
				{
					sentidoX = 2;
				}
				else
				{
					if (posX > 380 && posY < 180)
					{
						sentidoX = 1;
					}
					else
					{
						if (posY > 240)
						{
							sentidoY = 2;
						}
						else
						{
							if (posX < 325 && posY < 120)
							{
								sentidoY = 1;
								circ = false;
							}
						}
					}
				}
			}
			if (circ == true)
			{
				if (sentidoX == 1)
				{
					posX -= velocidadeEixoX;
					caixaDeColisao.x -= velocidadeEixoX;
				}
				else
				{
					posX += velocidadeEixoX;
					caixaDeColisao.x += velocidadeEixoX;
				}
				if (sentidoY == 1)
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
			else
			{
				posX -= velocidadeEixoX;
				caixaDeColisao.x -= velocidadeEixoX;
			}

		}
	}
	
	if (posX < larInimigo * -1)
	{
		definePosicao();
	}
}

void objInimigo03::renderizar()
{
	if (morto == false)
	{
		if (sentidoX == 1 && sentidoY == 1 && circ==true)
		{
			inimigoSpriteSheet.renderizar(posX, posY, &inimigoClip[2], 120);
		}
		else
		{
			if (sentidoX == 1 && sentidoY == 1 && circ == false)
			{
				inimigoSpriteSheet.renderizar(posX, posY, &inimigoClip[2], 180);
			}
			else
			{
				if (sentidoX == 2 && sentidoY == 1 && circ==true)
				{
					inimigoSpriteSheet.renderizar(posX, posY, &inimigoClip[2], 70);
				}
				else
				{
					if (sentidoX == 2 && sentidoY == 2 && circ == true)
					{
						inimigoSpriteSheet.renderizar(posX, posY, &inimigoClip[2], 300);
					}
					else
					{
						if (sentidoX == 1 && sentidoY == 2 && circ == true)
						{
							inimigoSpriteSheet.renderizar(posX, posY, &inimigoClip[2], 230);
						}
					}
				}
			}
		}
	}
}

SDL_Rect objInimigo03::getCaixaDeColisao()
{
	return caixaDeColisao;
}

int objInimigo03::getPosX()
{
	return posX;
}

int objInimigo03::getPosY()
{
	return posY;
}

objBoss::objBoss()
{
	posXBoss = larJanela;
	posYBoss = altJanela / 2 - altTotal / 2;
	HP1 = 100;
	HP2 = 100;
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
	caixasDeColisao[0].x = posXBoss + 7;  // posição X do Canhão Superior
	caixasDeColisao[0].y = posYBoss + 84; // posição Y do Canhão Superior
	caixasDeColisao[1].x = posXBoss + 7;  // posição X do Canhão Inferior
	caixasDeColisao[1].y = caixasDeColisao[0].y + 205; // posição Y do Canhão Inferior
	caixasDeColisao[2].x = posXBoss + 10; // posição X do Boss 
	caixasDeColisao[2].y = posYBoss; // posição Y do Boss

}

void objBoss::redefinir()
{
	posXBoss = larJanela;
	posYBoss = altJanela / 2 - altTotal / 2;
	HP1 = 100;
	HP2 = 100;
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

int objBoss::getHP1()
{
	return HP1;
}

int objBoss::getHP2()
{
	return HP2;
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
		DisparosSpriteSheet.renderizar(posX, posY, &BossProjetilClip[0],90);
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
	velocidadeProjetil = 0;
	for (int i = 0; i < 2; i++)
	{
		vetorNormal01[i] = 0;
		vetorNormal02[i] = 0;
	}
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
		velocidadeProjetil = velocidade;
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
		
		vetorNormal01[0] = posXAlvo - posX01;
		vetorNormal01[1] = posYAlvo - posY01;
		vetorNormal02[0] = posXAlvo - posX02;
		vetorNormal02[1] = posYAlvo - posY02;
	}
}

void objProjetilBoss02::move()
{
	posX01 += vetorNormal01[0]*velocidadeProjetil;
	posY01 += vetorNormal01[1] * velocidadeProjetil;
	caixaDeColisao[0].x = posX01;
	caixaDeColisao[0].y = posY01;
	if (posX01 < larProjetil * -1 || posY01 > larJanela + larProjetil || posY01 < larProjetil * -1)
	{
		disparado1 = false;
	}
	posX02 += vetorNormal02[0] * velocidadeProjetil;
	posY02 += vetorNormal02[1] * velocidadeProjetil;
	caixaDeColisao[1].x = posX02;
	caixaDeColisao[1].y = posY02;
	if (posX02 < larProjetil * -1 || posY02 > larJanela + larProjetil || posY02 < larProjetil * -1)
	{
		disparado2 = false;
	}
	velocidadeProjetil += velocidade;
}

void objProjetilBoss02::redefinir()
{
	posX01 = 0;
	posY01 = 0;
	posX02 = 0;
	posY02 = 0;
	posYAlvo = 0;
	velocidadeProjetil = 0;
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
		if (disparado1 == true)
		{
			DisparosSpriteSheet.renderizar((int)posX01, (int)posY01, &BossProjetilClip[1]);
		}
		if (disparado2 == true)
		{
			DisparosSpriteSheet.renderizar((int)posX02, (int)posY02, &BossProjetilClip[1]);
		}
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

AnimExplosao::AnimExplosao()
{
	posX = 0;
	posY = 0;
	contador = 0;
}

void AnimExplosao::definirPosicao()
{
	for (int i = 0; i < quantLaser; i++)
	{
		for (int j = 0; j < quantInimigos01; j++)
		{
			if (verificaColisao(laser[i].getCaixaDeColisao(), inimigo01[j].getCaixaDeColisao()) && atingido == false && inimigo01[j].morto == false && laser[i].disparado==true && *inimigo01[j].ponteiroHP == 1)
			{
				Mix_PlayChannel(-1, somExplosao, 0);
				posX = inimigo01[j].getPosX();
				posY = inimigo01[j].getPosY();
				atingido = true;
				break;
			}
		}
		if (atingido == true)
		{
			break;
		}
	}
	if (atingido == false)
	{
		for (int i = 0; i < quantLaser; i++)
		{
			for (int j = 0; j < quantInimigos02; j++)
			{
				if (verificaColisao(laser[i].getCaixaDeColisao(), inimigo02[j].getCaixaDeColisao()) && atingido == false && inimigo02[j].morto == false && laser[i].disparado == true && *inimigo02[j].ponteiroHP == 1)
				{
					Mix_PlayChannel(-1,somExplosao,0);
					posX = inimigo02[j].getPosX();
					posY = inimigo02[j].getPosY();
					atingido = true;
					break;
				}
			}
			if (atingido == true)
			{
				break;
			}
		}
	}
	if (atingido == false)
	{
		for (int i = 0; i < quantLaser; i++)
		{
			for (int j = 0; j < quantInimigos03; j++)
			{
				if (verificaColisao(laser[i].getCaixaDeColisao(), inimigo03[j].getCaixaDeColisao()) && atingido == false && inimigo03[j].morto == false && laser[i].disparado == true && *inimigo03[j].ponteiroHP == 1)
				{
					Mix_PlayChannel(-1, somExplosao, 0);
					posX = inimigo03[j].getPosX();
					posY = inimigo03[j].getPosY();
					atingido = true;
					break;
				}
			}
			if (atingido == true)
			{
				break;
			}
		}
	}
}

void AnimExplosao::renderizar()
{
	if (atingido == true)
	{
		explosaoSpriteSheet.renderizar(posX, posY, &explosaoclip[contador]);
		contador += 1;
		if (contador == 8)
		{
			atingido = false;
			contador = 0;
		}
	}
}

void AnimExplosao::renderizar02(int x, int y)
{
	if (atingido == true)
	{
		explosaoSpriteSheet.renderizar(x, y, &explosaoclip[contador]);
		contador += 1;
		if (contador == 8)
		{
			atingido = false;
			contador = 0;
		}
	}
}


