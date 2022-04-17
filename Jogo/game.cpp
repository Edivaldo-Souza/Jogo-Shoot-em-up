// inclus�o das bibliotecas
#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include<string>

// Declara��o da largura da janela;
const int larJanela = 640;

// Declara��o da altura da janela;
const int altJanela = 480;

// Define a quantidade de proj�teis a serem criados
const int quantLaser = 15;

// Define a quantidade de inimigos01 a serem criados
const int quantInimigos01 = 3;

// Declara��o do inteiro usado para selecionar os indices do vetor de objProjeteis "laser"
int indiceVetorLaser;

// Fun��o respons�vel pela inicializa��o da biblioteca SDL
bool init();

// Fun��o respons�vel por carregar m�dias(imagens,�udios,fonts)
bool loadMedia();

// Fun��o respons�vel por "desligar" a biblioteca SDL e apagar os valores de estruturas globais(SDL_Window,SDL_Renderer,SDL_Textue)
void close();

// Fun��o que verifica se duas caixas de colis�o se cruzaram
bool verificaColisao(SDL_Rect a, SDL_Rect b);

// Declara��o da Janela
SDL_Window* gJanela = NULL;

// Declara��o do Renderizador
SDL_Renderer* gRenderizador = NULL;

// Declara��o do vetor de SDL_Rect que armazena os sprites da nave do jogador enquanto parada
SDL_Rect naveClipParado[3];

// Declara��o do vetor de SDL_Rect que armazena os sprites do objProjetil "laser"
SDL_Rect laserClip[2];

// Declara��o do vetor de SDL_Rect que armazena os sprites do objInimigo01 "inimigo01"
SDL_Rect inimigo01Clip[2];

SDL_Rect BossClip;

// Classe das TEXTURAS
class LTextura
{
public:
	
	// fun��o que atribui os valores inicias as vari�veis da classe
	LTextura();
	
	// fun��o que redefine os valores das vari�veis da classe para como iniciamente foram definidas em LTextura()
	~LTextura();
	
	// fun��o que recebe uma string correspondente ao caminho(nome_da_pasta/imagem.png) da imagem a ser definida como textura 
	bool loadFromFile(std::string path,Uint32 r, Uint32 g, Uint32 b);
	
	// fun��o que apaga a textura mas recente carregada, e redifine suas dimens�es para o valor de 0 
	void free();
	
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

	// fun��o que atribui os valores iniciais as vari�veis desta classe
	objJogador();

	// fun��o que recebe como par�metro eventos (apertar de teclas) e define qual o sentido do
	// deslocamento da textura do jogador ao somar ou subtrair a constante deslocamento
	// a vari�vel mVelY, a qual ser� somada a posi��o da textura pela fun��o move()
	void avaliarEventos(SDL_Event& e);
	
	// fun��o que recebe como par�metro eventos (tecla SPACE) e define quando um projetil deve ser disparado
	void avaliarEventosLaser(SDL_Event& e);

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
	
	// fun��o que retorna a posi��o X da textura do jogador
	int getPosX();

	// fun��o que retorna a caixa de colis�o do jogador
	SDL_Rect getCaixaDeColisao();
private:
	// inteiros correspondentes as posi��es X e Y da textura do jogador
	int mPosY,mPosX;

	// inteiros correspondentes ao sentido do deslocamento da textura do jogador
	int mVelY,mVelX;

	// Caixa de colis�o do jogador
	SDL_Rect caixaDeColisao;

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
		bool aparecer = true;
		bool morto = true;
		objBoss();
		void definirCaixasDeColisao();
		void renderizar();
	private:
		int posXBoss;
		int posYBoss;
		int HP;
		SDL_Rect caixasDeColisao[totalDeCaixas];
};

class objBossProjetil01
{
	public:
		const int larProjetil = 15;
		const int altProjetil = 14;
		bool disparado = false;
		SDL_Rect* ponteiroCaixaDeColisao = &caixaDeColisao;
		objBossProjetil01();
		void move();
		void renderizar();
	private:
		int posX;
		int posY;
		SDL_Rect caixaDeColisao;
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

// Declara��o do objeto LTextura que armazena a imagem com todos os sprites da nave do jogador
LTextura naveSpriteSheet;

// Declara��o do objeto LTextura que armazena a imagem com todos os sprites do proj�til laser;
LTextura projeteisSpriteSheet;

// Armazena a imagem com os sprites do inimigo01
LTextura inimigo01SpriteSheet;

LTextura background;

LTextura bossSpriteSheet;

// Declara��o do objJogador que corresponde ao objeto manipul�vel pelo jogador
objJogador nave;

// Declara��o do vetor objProjetilLaser que armazena todos os proj�teis  
objProjetilLaser laser[quantLaser];

// Declara��o do vetor objInimigo01 que armazena todos os inimigos01 
objInimigo01 inimigo01[quantInimigos01];

objBoss BossInimigo;

void ondaInimigos01(bool flag);

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
bool LTextura::loadFromFile(std::string path,Uint32 r,Uint32 g,Uint32 b)
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
	mPosY = altJanela/2 - altJogador/2;
	mPosX = 10;
	mVelY = 0;
	mVelX = 0;
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
	if ((mPosY < 0)|| (mPosY + altJogador > altJanela))
	{
		// A posi��o em Y da textura � decrementada ou incrementada de modo a evitar que a textura ultrapasse a tela
		mPosY -= mVelY;
		caixaDeColisao.y -= mVelY;
	}
	
	// o mesmo se aplica para o deslocamento em Y
	mPosX += mVelX;
	caixaDeColisao.x += mVelX;
	if ((mPosX < 0)||(mPosX + larJogador > larJanela))
	{
		mPosX -= mVelX;
		caixaDeColisao.x -= mVelX;
	}
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

// retorna a caixa de colis�o do jogador
SDL_Rect objJogador::getCaixaDeColisao()
{
	return caixaDeColisao;
}

// fun��o que renderiza a textura do jogador
void objJogador::renderizar()
{
	naveSpriteSheet.renderizar(mPosX,mPosY,&naveClipParado[0], 90, NULL);
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
		posY = (nave.getPosY() + nave.getAltura() / 2) - altProjetil/2;
		caixaDeColisao.y = (nave.getPosY() + nave.getAltura() / 2) - altProjetil/2;
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

// renderiza a textura do proj�til na tela
void objProjetilLaser::renderizar()
{
	// Enquanto disparado for igual a true, a textura do projetil ser� renderizada na tela toda vez que for chamada
	if (disparado == true)
	{
		projeteisSpriteSheet.renderizar(posX, posY,&laserClip[0],90);
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
	posX = larJanela;
	posY = rand() % ((altJanela - altInimigo)+1);
	caixaDeColisao.x = posX;
	caixaDeColisao.y = posY;
	caixaDeColisao.w = larInimigo;
	caixaDeColisao.h = altInimigo;
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
	// Caso o inimigo atinga o jogador
	if ((verificaColisao(caixaDeColisao, nave.getCaixaDeColisao())==true))
	{
		
		posX = larJanela;
		posY = rand() % ((altJanela - altInimigo) + 1);
		caixaDeColisao.x = posX;
		caixaDeColisao.y = posY;
		morto = true;
	}
	// Caso o inimigo ultrapasse a tela
	if (posX < larInimigo*-1)
	{
		posX = larJanela;
		posY = rand() % ((altJanela - altInimigo) + 1);
		caixaDeColisao.x = posX;
		caixaDeColisao.y = posY;
		morto = true;
	}
	
	// 
	for (int i = 0; i < quantLaser; i++)
	{
		if (verificaColisao(caixaDeColisao, laser[i].getCaixaDeColisao()) == true && laser[i].disparado==true)
		{
			posX = larJanela;
			posY = rand() % ((altJanela - altInimigo) + 1);
			caixaDeColisao.x = posX;
			caixaDeColisao.y = posY;
			morto = true;
			laser[i].disparado = false;
		}
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

objBoss::objBoss()
{
	posXBoss = larJanela;
	posYBoss = altJanela / 2 - altTotal / 2;
	HP = 100;
	for (int i = 0; i < totalDeCaixas-1; i++)
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
	caixasDeColisao[0].x = posXBoss + 7;
	caixasDeColisao[0].y = posYBoss + 84;
	caixasDeColisao[1].x = posXBoss + 7;
	caixasDeColisao[1].y = caixasDeColisao[0].y + 205;
	caixasDeColisao[2].x = posXBoss + 10;
	caixasDeColisao[2].y = posYBoss;

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

objBossProjetil01::objBossProjetil01()
{
	posX = 0;
	posY = 0;
	caixaDeColisao.x = 0;
	caixaDeColisao.y = 0;
	caixaDeColisao.w = larProjetil;
	caixaDeColisao.h = altProjetil;
}

void objBossProjetil01::move()
{

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
	if(iniciado == true)
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

// Fun��o respons�vel pela inicializa��o da biblioteca SDL
bool init()
{
	// Inicializa��o da biblioteca SDL
	SDL_Init(SDL_INIT_VIDEO);
	// Cria��o da Janela
	gJanela = SDL_CreateWindow("Jogo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, larJanela, altJanela, SDL_WINDOW_SHOWN);
	// Cria��o do renderizador
	gRenderizador = SDL_CreateRenderer(gJanela, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(gRenderizador, 0xFF, 0xFF, 0xFF, 0xFF);
	IMG_Init(IMG_INIT_PNG);
	return 0;
}

bool loadMedia()
{
	naveSpriteSheet.loadFromFile("spritesheets/STRIP-1.gif",0xFF,0xFF,0xFF);
	projeteisSpriteSheet.loadFromFile("spritesheets_2/projetil_Laser.png",0xFF,0,0xFF);
	inimigo01SpriteSheet.loadFromFile("spritesInimigos/inimigo01.png",0xFF,0,0xFF);
	background.loadFromFile("background/background.png", 0xFF, 0, 0);
	bossSpriteSheet.loadFromFile("boss_spritesheet/boss_sprites.png", 0, 0xFF, 0);
	// Defini��o dos par�metros da SDL_Rect que armazenar� certa por��o da textura com os sprites da nave 
	naveClipParado[0].x = 1;
	naveClipParado[0].y = 1;
	naveClipParado[0].w = 46;
	naveClipParado[0].h = 44;
	// Defini��o dos par�metros da SDL_Rect que armazenar� certa por��o da textura com os sprites dos proj�teis
	laserClip[0].x = 1;
	laserClip[0].y = 1;
	laserClip[0].w = 24;
	laserClip[0].h = 41;
	// Declara��o dos par�metros da SDL_Rect que armazenar� certa por��o da textura com os sprites do inimigo01
	inimigo01Clip[0].x = 1;
	inimigo01Clip[0].y = 1;
	inimigo01Clip[0].w = 45;
	inimigo01Clip[0].h = 43;

	BossClip.x = 0;
	BossClip.y = 0;
	BossClip.w = 180;
	BossClip.h = 410;
	return 0;
}

void close()
{
	// Apaga os valores das vari�veis desse objeto LTextura 
	naveSpriteSheet.free();
	projeteisSpriteSheet.free();
	inimigo01SpriteSheet.free();
	bossSpriteSheet.free();

	// Desfaz a Janela
	SDL_DestroyWindow(gJanela);
	// Desfaz o Renderizador
	SDL_DestroyRenderer(gRenderizador);
	// Redifine as vari�veis como vazias
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

int main(int argc, char* args[])
{
	init();
	loadMedia();
	bool sair = false;
	SDL_Event e;
	cronometro timerBoss;
	timerBoss.comecar();
	int deslocamentoBackground = 0;
	// Enquanto sair for o que ele n�o �  
	while (!sair)
	{
		// Looping respons�vel por ler os eventos, que termina apenas quando a quantidade de eventos
		// acumulados seja igual a 0
		while (SDL_PollEvent(&e) != 0)
		{
			// Caso o evento lido seja o apertar do bot�o Fechar, a vari�vel sair recebe true
			// e o looping principal � finalizado
			if (e.type == SDL_QUIT)
			{
				sair = true;
			}
			nave.avaliarEventos(e);
			nave.avaliarEventosLaser(e);
		}
		nave.move();

		deslocamentoBackground -= 1;
		if (deslocamentoBackground < background.getLargura()*-1)
		{
			deslocamentoBackground = 0;
		}
		
		for (int i = 0; i < quantInimigos01; i++)
		{
			if (timerBoss.getTempo() < 5000)
			{
				ondaInimigos01(true);
			}
			else
			{
				ondaInimigos01(false);
			}
		}
		
		for (int i = 0; i < quantInimigos01; i++)
		{
			inimigo01[i].move();
		}
		for (int i = 0; i < quantLaser; i++)
		{
			laser[i].move();
		}


		SDL_SetRenderDrawColor(gRenderizador, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderizador);
		
		background.renderizar(deslocamentoBackground, 0);
		background.renderizar(deslocamentoBackground + background.getLargura(),0);
		
		nave.renderizar();
		
		for (int i = 0; i < quantLaser; i++)
		{
			//SDL_SetRenderDrawColor(gRenderizador, 0, 0xFF, 0, 0xFF);
			//SDL_RenderDrawRect(gRenderizador, laser[i].ponteiroCaixaDeColisao);
			laser[i].renderizar();
		}

		for (int i = 0; i < quantInimigos01; i++)
		{
			inimigo01[i].renderizar();
		}

		for (int i = 0; i < BossInimigo.totalDeCaixas; i++)
		{
			SDL_SetRenderDrawColor(gRenderizador, 0xFF, 0, 0, 0xFF);
			SDL_RenderDrawRect(gRenderizador, &BossInimigo.ponteiroCaixaDeColisao[i]);
		}
		//BossInimigo.renderizar();

		SDL_RenderPresent(gRenderizador);
	}
	close();
	return 0;
}