// inclus�o das bibliotecas
#include<SDL.h>
#include<SDL_image.h>
#include<stdio.h>
#include<string>

// Declara��o da largura da janela;
const int larJanela = 640;

// Declara��o da altura da janela;
const int altJanela = 480;

// Fun��o respons�vel pela inicializa��o da biblioteca SDL
bool init();

// Fun��o respons�vel por carregar m�dias(imagens,�udios,fonts)
bool loadMedia();

// Fun��o respons�vel por "desligar" a biblioteca SDL e apagar os valores de estruturas globais(SDL_Window,SDL_Renderer,SDL_Textue)
void close();

// Declara��o da Janela
SDL_Window* gJanela = NULL;

// Declara��o do Renderizador
SDL_Renderer* gRenderizador = NULL;

// Declara��o do vetor de SDL_Rect que armazena os sprites da nave do jogador enquanto parada
SDL_Rect naveClipParado[3];

// Classe das TEXTURAS
class LTextura
{
public:
	
	// fun��o que atribui os valores inicias as vari�veis da classe
	LTextura();
	
	// fun��o que redefine os valores das vari�veis da classe para como iniciamente foram definidas em LTextura()
	~LTextura();
	
	// fun��o que recebe uma string correspondente ao caminho(nome_da_pasta/imagem.png) da imagem a ser definida como textura 
	bool loadFromFile(std::string path);
	
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

// Declara��o do objeto LTextura que armazena o imagem com todos os sprites da nave do jogador
LTextura naveSpriteSheet;

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
bool LTextura::loadFromFile(std::string path)
{
	// free() apaga qualquer defini��o de mTextura e suas dimens�es antes de carregar uma nova imagem
	free();
	
	// novaTextura � uma SDL_Texture que est� apenas no escopo dessa fun��o para criar a textura
	// e retornar seu valor para a vari�vel da classe mTextura
	SDL_Texture* novaTextura = NULL;
	
	// loadSurface � a SDL_Surface onde se � carregada a imagem correspondente ao caminho passado no par�metro da fun��o
	SDL_Surface* loadSuperficie = IMG_Load(path.c_str());
	
	// SDL_ColorKey torna certa tonalidade de pixels transparentes de uma SDL_Surface
	SDL_SetColorKey(loadSuperficie, SDL_TRUE, SDL_MapRGB(loadSuperficie->format, 0xFF, 0xFF, 0xFF));
	
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
	
	// fun��o que altera a posi��o Y da textura do jogador com base no sinal(sentido) da vari�vel mVelY
	void move();
	
	// fun��o que renderiza a textura do jogador
	void renderizar();

	// fun��o que retorna o valor da altura da textura do jogador
	int getAltura();
private:
	// inteiro correspondente a posi��o em Y da textura do jogador
	int mPosY;
	
	// inteiro correspondente ao sentido do deslocamento da textura do jogador
	int mVelY;
};

// fun��o que atribui os valores iniciais as vari�veis desta classe
objJogador::objJogador()
{
	// A posi��o em Y da textura do jogador � definida para o centro do eixo
	mPosY = altJanela/2 - altJogador/2;

	mVelY = 0;
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
		}
	}
}

// fun��o que altera a posi��o Y da textura do jogador com base no sinal(sentido) da vari�vel mVelY
void objJogador::move()
{
	// O incremento (ou decremento) a vari�vel mPosY, reajusta a posi��o da textura do jogador
	mPosY += mVelY;
	// Caso a posi��o da textura assuma um valor menor do que 0, ou se a textura do jogador tenda
	// a ultrapassar o limite da tela por conta de sua altura em rela��o a posi��o que ela assume...
	if ((mPosY < 0) || (mPosY + altJogador > altJanela))
	{
		// A posi��o em Y da textura � decrementada ou incrementada de modo a evitar que a textura ultrapasse a tela
		mPosY -= mVelY;
	}
}

// fun��o que renderiza a textura do jogador
void objJogador::renderizar()
{
	naveSpriteSheet.renderizar(10, mPosY,&naveClipParado[0], 90, NULL);
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
	naveSpriteSheet.loadFromFile("spritesheets/STRIP-1.gif");
	// Defini��o dos par�metro da SDL_Rect que armazenar� certa por��o de uma textura 
	naveClipParado[0].x = 1;
	naveClipParado[0].y = 1;
	naveClipParado[0].w = 46;
	naveClipParado[0].h = 44;
	return 0;
}

void close()
{
	// Apaga os valores das vari�veis desse objeto LTextura 
	naveSpriteSheet.free();

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

int main(int argc, char* args[])
{
	init();
	loadMedia();
	bool sair = false;
	SDL_Event e;
	objJogador nave;
	// Enquanto 
	while (!sair)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				sair = true;
			}
			nave.avaliarEventos(e);
		}
		nave.move();

		SDL_SetRenderDrawColor(gRenderizador, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderizador);
		nave.renderizar();
		SDL_RenderPresent(gRenderizador);
	}
	close();
	return 0;
}