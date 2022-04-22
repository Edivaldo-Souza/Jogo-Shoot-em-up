// inclusão das bibliotecas
#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include<string>


// Declaração da largura da janela;
const int larJanela = 640;

// Declaração da altura da janela;
const int altJanela = 480;

// Define a quantidade de projéteis a serem criados
const int quantLaser = 15;

const int quantProjetilBoss02 = 4;

// Define a quantidade de inimigos01 a serem criados
const int quantInimigos01 = 3;

const int quantInimigos02 = 2;

// Declaração do inteiro usado para selecionar os indices do vetor de objProjeteis "laser"
int indiceVetorLaser;

int Div = larJanela / 4;

// Função responsável pela inicialização da biblioteca SDL
bool init();

// Função responsável por carregar mídias(imagens,áudios,fonts)
bool loadMedia();

// Função responsável por "desligar" a biblioteca SDL e apagar os valores de estruturas globais(SDL_Window,SDL_Renderer,SDL_Textue)
void close();

// Função que verifica se duas caixas de colisão se cruzaram
bool verificaColisao(SDL_Rect a, SDL_Rect b);

void reiniciarFase();

// Declaração da Janela
SDL_Window* gJanela = NULL;

// Declaração do Renderizador
SDL_Renderer* gRenderizador = NULL;

// Declaração do vetor de SDL_Rect que armazena os sprites da nave do jogador enquanto parada
SDL_Rect naveClipParado[3];

// Declaração do vetor de SDL_Rect que armazena os sprites do objProjetil "laser"
SDL_Rect laserClip[2];

// Declaração do vetor de SDL_Rect que armazena os sprites do objInimigo01 "inimigo01"
SDL_Rect inimigo01Clip[2];

SDL_Rect inimigo02Clip[2];

SDL_Rect BossClip;

SDL_Rect BossProjetilClip[2];

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

	// função que apaga a textura mas recente carregada, e redifine suas dimensões para o valor de 0 
	void free();

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
	static const int altJogador = 43;

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

	// retorna a caixa de colisão do inimigo
	SDL_Rect getCaixaDeColisao();
private:
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
public :
	static const int larProjetil = 190;
	static const int altProjetil = 70;
	static const int velocidadeProjetil = 8;

	bool disparado = false;

	objProjetilBoss();

	void redefinir();

	void move();

	void renderizar();

	SDL_Rect getCaixaDeColisao();
private :
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


// Declaração do objeto LTextura que armazena a imagem com todos os sprites da nave do jogador
LTextura naveSpriteSheet;

// Declaração do objeto LTextura que armazena a imagem com todos os sprites do projétil laser;
LTextura projeteisSpriteSheet;

// Armazena a imagem com os sprites do inimigo01
LTextura inimigo01SpriteSheet;

LTextura inimigo02SpriteSheet;

LTextura background;

LTextura bossSpriteSheet;

// Declaração do objJogador que corresponde ao objeto manipulável pelo jogador
objJogador nave;

// Declaração do vetor objProjetilLaser que armazena todos os projéteis  
objProjetilLaser laser[quantLaser];

// Declaração do vetor objInimigo01 que armazena todos os inimigos01 
objInimigo01 inimigo01[quantInimigos01];

objInimigo02 inimigo02[quantInimigos02]; //quantInimigos02 = 2

objBoss BossInimigo;

objProjetilBoss BossDisparo;

objProjetilBoss02 BossProjetil02[quantProjetilBoss02];

void ondaInimigos01(bool flag);

void ondaInimigos02(bool flag);


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
	else if(tempoInvencibilidade.getTempo() > tempoImortal)
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
	naveSpriteSheet.renderizar(mPosX, mPosY, &naveClipParado[0], 90, NULL);
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
			inimigo01[i].definePosicao();
			disparado = false;
		}
	}
	for (int i = 0; i < quantInimigos02; i++)
	{
		if (verificaColisao(caixaDeColisao, inimigo02[i].getCaixaDeColisao()) == true && disparado == true)
		{
			inimigo02[i].definePosicao();
			disparado = false;
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
		projeteisSpriteSheet.renderizar(posX, posY, &laserClip[0], 90);
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
	posX = larJanela;
	posY = rand() % ((altJanela - altInimigo) + 1);
	caixaDeColisao.x = posX;
	caixaDeColisao.y = posY;
	caixaDeColisao.w = larInimigo;
	caixaDeColisao.h = altInimigo;
}

void objInimigo01::definePosicao()
{
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
	posX = larJanela;
	posY = altJanela / 2;
	caixaDeColisao.x = posX;
	caixaDeColisao.y = posY;
	caixaDeColisao.w = larInimigo;
	caixaDeColisao.h = altInimigo;
}

void objInimigo02::definePosicao()
{
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

objProjetilBoss::objProjetilBoss()
{
	posX = larJanela-250;
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
		posX =larJanela-250;
		CaixaDeColisao.x = posX;

	}
	if (posX < 0-larProjetil)
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
	if(disparado == true)
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
		if (nave.getPosY() > posY01)
		{
			sentidoProjetil1 = true;
		}
		else
		{
			sentidoProjetil1 = false;
		}
		if (nave.getPosY() > posY02)
		{
			sentidoProjetil2 = true;
		}
		else
		{
			sentidoProjetil2 = false;
		}
	}
}

void objProjetilBoss02::move()
{
	if (sentidoProjetil1 == true)
	{
		posY01 += velocidadeProjetil;
		posX01 -= velocidadeProjetil;
	}
	else
	{
		posY01 -= velocidadeProjetil;
		posX01 -= velocidadeProjetil;
	}
	if (posX01 < larProjetil * -1 || posY01 > larJanela + larProjetil || posY01 < larProjetil * -1)
	{
		disparado1 = false;
	}
	if (sentidoProjetil2 == true)
	{
		posY02 += velocidadeProjetil;
		posX02 -= velocidadeProjetil;
	}
	else
	{
		posY02 -= velocidadeProjetil;
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

// Função responsável pela inicialização da biblioteca SDL
bool init()
{
	// Inicialização da biblioteca SDL
	SDL_Init(SDL_INIT_VIDEO);
	// Criação da Janela
	gJanela = SDL_CreateWindow("Jogo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, larJanela, altJanela, SDL_WINDOW_SHOWN);
	// Criação do renderizador
	gRenderizador = SDL_CreateRenderer(gJanela, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(gRenderizador, 0xFF, 0xFF, 0xFF, 0xFF);
	IMG_Init(IMG_INIT_PNG);
	return 0;
}

bool loadMedia()
{
	naveSpriteSheet.loadFromFile("spritesheets/STRIP-1.gif", 0xFF, 0xFF, 0xFF);
	projeteisSpriteSheet.loadFromFile("spritesheets_2/projetil_Laser.png", 0xFF, 0, 0xFF);
	inimigo01SpriteSheet.loadFromFile("spritesInimigos/inimigo01.png", 0xFF, 0, 0xFF);
	background.loadFromFile("background/background.png", 0xFF, 0, 0);
	bossSpriteSheet.loadFromFile("boss_spritesheet/boss_sprites.png", 0, 0xFF, 0);

	// Definição dos parâmetros da SDL_Rect que armazenará certa porção da textura com os sprites da nave 
	naveClipParado[0].x = 1;
	naveClipParado[0].y = 1;
	naveClipParado[0].w = 46;
	naveClipParado[0].h = 44;
	// Definição dos parâmetros da SDL_Rect que armazenará certa porção da textura com os sprites dos projéteis
	laserClip[0].x = 1;
	laserClip[0].y = 1;
	laserClip[0].w = 24;
	laserClip[0].h = 41;
	// Declaração dos parâmetros da SDL_Rect que armazenará certa porção da textura com os sprites do inimigo01
	inimigo01Clip[0].x = 1;
	inimigo01Clip[0].y = 1;
	inimigo01Clip[0].w = 45;
	inimigo01Clip[0].h = 43;

	inimigo01Clip[1].x = 45;
	inimigo01Clip[1].y = 1;
	inimigo01Clip[1].w = 37;
	inimigo01Clip[1].h = 45;

	BossClip.x = 0;
	BossClip.y = 0;
	BossClip.w = 180;
	BossClip.h = 410;

	BossProjetilClip[0].x = 18;
	BossProjetilClip[0].y = 414;
	BossProjetilClip[0].w = 201;
	BossProjetilClip[0].h = 70;

	BossProjetilClip[1].x = 0;
	BossProjetilClip[1].y = 414;
	BossProjetilClip[1].w = 15;
	BossProjetilClip[1].h = 14;

	return 0;
}

void close()
{
	// Apaga os valores das variáveis desse objeto LTextura 
	naveSpriteSheet.free();
	projeteisSpriteSheet.free();
	inimigo01SpriteSheet.free();
	bossSpriteSheet.free();

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
	for (int i = 0; i < quantLaser; i++)
	{
		laser[i].redefinir();
	}
	BossInimigo.redefinir();
	BossDisparo.redefinir();
	for (int i = 0; i < quantProjetilBoss02; i++)
	{
		BossProjetil02[i].redefinir();
	}
}

int main(int argc, char* args[])
{
	init();
	loadMedia();
	bool sair = false;
	bool momentoDaFase = true;
	bool gameover = false;
	Uint32 tempoParaOBoss = 20000;
	Uint32 tempoParaDisparo = 5000;
	Uint32 tempoParaDisparo2 = 2000;
	SDL_Event e;
	int deslocamentoBackground = 0;
	cronometro timerBoss;
	timerBoss.comecar();
	cronometro timerDisparo;
	cronometro intervaloEntreDisparos;
	// Enquanto sair for o que ele não é  
	while (!sair)
	{

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
	}
	close();
	return 0;
}
