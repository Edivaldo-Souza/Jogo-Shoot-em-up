#pragma once
#include <SDL.h>
#include <string>

// Classe das TEXTURAS
class LTextura
{
public:

	// fun��o que atribui os valores inicias as vari�veis da classe
	LTextura();

	// fun��o que redefine os valores das vari�veis da classe para como iniciamente foram definidas em LTextura()
	~LTextura();

	// fun��o que recebe uma string correspondente ao caminho(nome_da_pasta/imagem.png) da imagem a ser definida como textura 
	bool loadFromFile(std::string path, Uint32 r, Uint32 g, Uint32 b);

	// fun��o que apaga a textura mas recente carregada, e redifine suas dimens�es para o valor de 0 
	void free();

	// fun�ao para realizar a modula��o das cores de uma textura 
	void setColor(Uint8 r, Uint8 g, Uint8 b);

	// fun��o que renderiza uma textura na janela recebendo sua posi��o(x,y), um SDL_Rect para o caso
	// de ser necess�rio renderizar apenas uma parcela da imagem carregada, um �ngulo de rota��o,
	// um SDL_Point para definir um ponto de refer�ncia para a rota��o, e um SDL_RendererFlip para
	// espelhar sua posi��o na vertical e horizontal.
	void renderizar(int x, int y, SDL_Rect* clip = NULL, double angulo = 0.0, SDL_Point* centro = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// fun��o que retorna a vari�vel mLargura;
	int getLargura();

	// fun��o que retorna a vari�vel mAltura;
	int getAltura();

private:

	// Vari�vel que recebe a textura para os objetos da classe LTextura
	SDL_Texture* mTextura;

	// inteiro que recebe a largura da textura
	int mLargura;

	// inteiro que recebe a altura da textura
	int mAltura;
};

class cronometro
{
public:
	cronometro();
	void comecar();
	void parar();
	void pausar();
	void despausar();
	Uint32 getTempo();
	bool foiIniciado();
	bool foiPausado();
private:
	Uint32 TempoQuandoIniciado;
	Uint32 TempoQuandoPausado;
	bool pausado;
	bool iniciado;
};

// Classe do objeto que representa o jogador
class objJogador
{
public:
	// declara��o da constante referente a largura da textura do jogador 
	static const int larJogador = 40;

	// declara��o da constante referente a altura da textura do jogador
	static const int altJogador = 43;

	// declara��o da constante referente a quantidade de pixels que a textura do jogador se desloca
	// por apertar de tecla.
	static const int deslocamento = 5;

	Uint32 tempoImortal = 1000;

	// fun��o que atribui os valores iniciais as vari�veis desta classe
	objJogador();

	// fun��o que recebe como par�metro eventos (apertar de teclas) e define qual o sentido do
	// deslocamento da textura do jogador ao somar ou subtrair a constante deslocamento
	// a vari�vel mVelY, a qual ser� somada a posi��o da textura pela fun��o move()
	void avaliarEventos(SDL_Event& e);

	// fun��o que recebe como par�metro eventos (tecla SPACE) e define quando um projetil deve ser disparado
	void avaliarEventosLaser(SDL_Event& e);

	void avaliarColisao();

	void redefinir();

	// fun��o que altera a posi��o Y da textura do jogador com base no sinal(sentido) da vari�vel mVelY
	void move();

	// fun��o que renderiza a textura do jogador
	void renderizar();

	// fun��o que retorna o valor da altura da textura do jogador
	int getAltura();

	// fun��o que retorna o valor da largura da textura do jogador
	int getLargura();

	// fun��o que retorna a posi��o Y da textura do jogador
	int getPosY();

	int getHP();

	// fun��o que retorna a posi��o X da textura do jogador
	int getPosX();

	// fun��o que retorna a caixa de colis�o do jogador
	SDL_Rect getCaixaDeColisao();

private:
	// inteiros correspondentes as posi��es X e Y da textura do jogador
	int mPosY, mPosX;

	// inteiros correspondentes ao sentido do deslocamento da textura do jogador
	int mVelY, mVelX;

	int HP;
	// Caixa de colis�o do jogador
	SDL_Rect caixaDeColisao;

	cronometro tempoInvencibilidade;
};

// classe que define o tipo Proj�til
class objProjetilLaser
{
public:
	static const int larProjetil = 41;
	static const int altProjetil = 24;
	static const int velocidadeProjetil = 15;

	SDL_Rect* ponteiroCaixaDeColisao = &caixaDeColisao;
	// a vari�vel disparado � uma flag que indica quando o projetil deve mover ou n�o
	// a vari�vel "atualizaPosicaoDePartida" � uma flag que indica quando o proj�til deve atualizar sua posi��o de partida
	bool atualizaPosicaoDePartida = false;

	bool disparado = false;

	// fun��o que define valores padr�es para as vari�veis do tipo objProjetil
	objProjetilLaser();

	void avaliaColisao();

	void redefinir();

	// m�todo respons�vel por modificar a posi��o X de um objProjetil fazendo com que este se mova  
	void move();

	// renderiza a textura do proj�til na tela
	void renderizar();

	// Fun��o que retorna a caixa de colis�o do projetil
	SDL_Rect getCaixaDeColisao();
private:
	// inteiro correspondente a posi��o X do proj�til
	int posX;
	// inteiro correspondente a posi��o Y do proj�til
	int posY;
	SDL_Rect caixaDeColisao;
};

//classe do Inimigo01
class objInimigo01
{
public:
	// largura do inimigo
	const int larInimigo = 43;

	// altura do inimigo
	const int altInimigo = 45;

	// velocidade no eixo x do inimigo
	const int velocidadeEixoX = 5;

	// velocidade no eixo y do inimigo
	const int velocidadeEixoY = 1;

	// flag que decide quando a textura do inimigo deve se mover e ser renderizada
	bool morto = true;

	// define valores para as vari�veis da classe
	objInimigo01();

	// move o inimigo
	void move();

	void definePosicao();

	// renderiza a textura do inimigo
	void renderizar();

	// retorna a altura do inimigo
	int getAltura();

	// retorn a largura do inimigo
	int getLargura();

	// retorn a posi��o em X do inimigo
	int getPosX();

	// retorna a caixa de colis�o do inimigo
	SDL_Rect getCaixaDeColisao();
private:
	// Posi��o em X do inimigo
	int posX;

	// Posi��o em Y do inimigo
	int posY;

	// Caixa de colis�o do inimigo
	SDL_Rect caixaDeColisao;
};

class objInimigo02
{
public:
	const int larInimigo = 37;

	const int altInimigo = 45;

	const int velocidadeEixoX = 5;

	const int velocidadeEixoY = 6;

	bool morto = true;

	objInimigo02();

	void definePosicao();

	void move1();

	void move2();

	void renderizar();

	int getAltura();

	int getLargura();


	SDL_Rect getCaixaDeColisao();

private:
	int posX;

	int posY;

	SDL_Rect caixaDeColisao;
};

class objBoss
{
public:
	enum Dimensoes
	{
		totalDeCaixas = 3,
		larTotal = 190,
		altTotal = 410,
		larCanhao = 160,
		altCanhao = 40,
	};
	SDL_Rect* ponteiroCaixaDeColisao = caixasDeColisao;
	bool aparecer = false;
	bool morto = true;
	objBoss();
	void redefinir();
	void definirCaixasDeColisao();
	void renderizar();
private:
	int posXBoss;
	int posYBoss;
	int HP;
	SDL_Rect caixasDeColisao[totalDeCaixas];
};

class objProjetilBoss
{
public:
	static const int larProjetil = 190;
	static const int altProjetil = 70;
	static const int velocidadeProjetil = 8;

	bool disparado = false;

	objProjetilBoss();

	void redefinir();

	void move();

	void renderizar();

	SDL_Rect getCaixaDeColisao();
private:
	int posX;

	int posY;

	SDL_Rect CaixaDeColisao;
};

class objProjetilBoss02
{
public:
	static const int quantCaixasDeColisao = 2;
	const int larProjetil = 15;
	const int altProjetil = 14;
	const int velocidadeProjetil = 5;
	bool disparado1 = false;
	bool disparado2 = false;
	bool sentidoProjetil1 = false;
	bool sentidoProjetil2 = false;
	objProjetilBoss02();
	void redefinir();
	void definePosicao();
	void move();
	void renderizar();
private:
	int posX01;
	int posY01;
	int posX02;
	int posY02;
	int posYAlvo;
	SDL_Rect caixaDeColisao[quantCaixasDeColisao];
};
