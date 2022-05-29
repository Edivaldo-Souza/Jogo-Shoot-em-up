#pragma once
#include <SDL.h>
#include <string>

// Classe das TEXTURAS
class LTextura
{
public:

	// função que atribui os valores inicias as variáveis da classe
	LTextura();

	// função que redefine os valores das variáveis da classe para como iniciamente foram definidas em LTextura()
	~LTextura();

	// função que recebe uma string correspondente ao caminho(nome_da_pasta/imagem.png) da imagem a ser definida como textura 
	bool loadFromFile(std::string path, Uint32 r, Uint32 g, Uint32 b);

	bool carregarTexto(std::string textoTextura, SDL_Color corDoTexto,TTF_Font* font);

	// função que apaga a textura mas recente carregada, e redifine suas dimensões para o valor de 0 
	void free();

	// funçao para realizar a modulação das cores de uma textura 
	void setColor(Uint8 r, Uint8 g, Uint8 b);

	void setBlendMode(SDL_BlendMode blending);

	void setAlpha(Uint8 alpha);

	// função que renderiza uma textura na janela recebendo sua posição(x,y), um SDL_Rect para o caso
	// de ser necessário renderizar apenas uma parcela da imagem carregada, um ângulo de rotação,
	// um SDL_Point para definir um ponto de referência para a rotação, e um SDL_RendererFlip para
	// espelhar sua posição na vertical e horizontal.
	void renderizar(int x, int y, SDL_Rect* clip = NULL, double angulo = 0.0, SDL_Point* centro = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// função que retorna a variável mLargura;
	int getLargura();

	// função que retorna a variável mAltura;
	int getAltura();

private:

	// Variável que recebe a textura para os objetos da classe LTextura
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
	// declaração da constante referente a largura da textura do jogador 
	static const int larJogador = 40;

	// declaração da constante referente a altura da textura do jogador
	static const int altJogador = 40;

	// declaração da constante referente a quantidade de pixels que a textura do jogador se desloca
	// por apertar de tecla.
	static const int deslocamento = 5;

	Uint32 tempoImortal = 1000;

	// função que atribui os valores iniciais as variáveis desta classe
	objJogador();

	// função que recebe como parâmetro eventos (apertar de teclas) e define qual o sentido do
	// deslocamento da textura do jogador ao somar ou subtrair a constante deslocamento
	// a variável mVelY, a qual será somada a posição da textura pela função move()
	void avaliarEventos(SDL_Event& e);

	// função que recebe como parâmetro eventos (tecla SPACE) e define quando um projetil deve ser disparado
	void avaliarEventosLaser(SDL_Event& e);

	void avaliarColisao();

	void redefinir();

	// função que altera a posição Y da textura do jogador com base no sinal(sentido) da variável mVelY
	void move();

	// função que renderiza a textura do jogador
	void renderizar();

	// função que retorna o valor da altura da textura do jogador
	int getAltura();

	// função que retorna o valor da largura da textura do jogador
	int getLargura();

	// função que retorna a posição Y da textura do jogador
	int getPosY();

	int getHP();

	// função que retorna a posição X da textura do jogador
	int getPosX();

	// função que retorna a caixa de colisão do jogador
	SDL_Rect getCaixaDeColisao();

private:
	// inteiros correspondentes as posições X e Y da textura do jogador
	int mPosY, mPosX;

	// inteiros correspondentes ao sentido do deslocamento da textura do jogador
	int mVelY, mVelX;

	int HP;
	// Caixa de colisão do jogador
	SDL_Rect caixaDeColisao;

	cronometro tempoInvencibilidade;
};

// classe que define o tipo Projétil
class objProjetilLaser
{
public:
	static const int larProjetil = 41;
	static const int altProjetil = 24;
	static const int velocidadeProjetil = 15;
	const int DANO = 1;

	SDL_Rect* ponteiroCaixaDeColisao = &caixaDeColisao;
	// a variável disparado é uma flag que indica quando o projetil deve mover ou não
	// a variàvel "atualizaPosicaoDePartida" é uma flag que indica quando o projétil deve atualizar sua posição de partida
	bool atualizaPosicaoDePartida = false;

	bool disparado = false;

	// função que define valores padrões para as variáveis do tipo objProjetil
	objProjetilLaser();

	void avaliaColisao();

	void redefinir();

	// método responsável por modificar a posição X de um objProjetil fazendo com que este se mova  
	void move();

	// renderiza a textura do projétil na tela
	void renderizar();

	// Função que retorna a caixa de colisão do projetil
	SDL_Rect getCaixaDeColisao();
private:
	// inteiro correspondente a posição X do projétil
	int posX;
	// inteiro correspondente a posição Y do projétil
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

	int HPdefinido = 1;

	int* ponteiroHP = &HPmutavel;

	// flag que decide quando a textura do inimigo deve se mover e ser renderizada
	bool morto = true;

	// define valores para as variáveis da classe
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

	// retorn a posição em X do inimigo
	int getPosX();

	int getPosY();

	// retorna a caixa de colisão do inimigo
	SDL_Rect getCaixaDeColisao();
private:

	int HPmutavel;
	
	// Posição em X do inimigo
	int posX;

	// Posição em Y do inimigo
	int posY;

	// Caixa de colisão do inimigo
	SDL_Rect caixaDeColisao;
};

class objInimigo02
{
public:
	const int larInimigo = 37;

	const int altInimigo = 45;

	const int velocidadeEixoX = 5;

	const int velocidadeEixoY = 6;

	int HPdefinido = 1;

	int* ponteiroHP = &HPmutavel;

	bool morto = true;

	objInimigo02();

	void definePosicao();

	void move1();

	void move2();

	void renderizar();

	int getAltura();

	int getLargura();

	int getPosX();

	int getPosY();


	SDL_Rect getCaixaDeColisao();

private:
	
	int HPmutavel;

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
	int* ponteiroHP1 = &HP1;
	int* ponteiroHP2 = &HP2;
	bool aparecer = false;
	bool morto = true;
	objBoss();
	void redefinir();
	void definirCaixasDeColisao();
	void renderizar();
	int getHP1();
	int getHP2();
private:
	int posXBoss;
	int posYBoss;
	int HP1;
	int HP2;
	SDL_Rect caixasDeColisao[totalDeCaixas];
};

class objProjetilBoss
{
public:
	static const int larProjetil = 83;
	static const int altProjetil = 35;
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
	float velocidade = 1;
	SDL_Rect* ponteiroCaixaDeColisao = caixaDeColisao;
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
	int posXAlvo;
	int vetorNormal01[2];
	int vetorNormal02[2];
	float velocidadeProjetil;
	SDL_Rect caixaDeColisao[quantCaixasDeColisao];
};

class AnimExplosao
{
	public:
		bool atingido;
		bool defPos = false;
		int* ponteiroPosX = &posX;
		int* ponteiroPosY = &posY;
		AnimExplosao();
		void renderizar();
		void renderizar02(int x, int y);
		void definirPosicao();
	private:
		int posX;
		int posY;
		int contador;
};
