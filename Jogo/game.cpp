// inclusão das bibliotecas
#include<SDL.h>
#include<SDL_image.h>
#include<stdio.h>
#include<string>

// Declaração da largura da janela;
const int larJanela = 640;

// Declaração da altura da janela;
const int altJanela = 480;

// Função responsável pela inicialização da biblioteca SDL
bool init();

// Função responsável por carregar mídias(imagens,áudios,fonts)
bool loadMedia();

// Função responsável por "desligar" a biblioteca SDL e apagar os valores de estruturas globais(SDL_Window,SDL_Renderer,SDL_Textue)
void close();

// Declaração da Janela
SDL_Window* gJanela = NULL;

// Declaração do Renderizador
SDL_Renderer* gRenderizador = NULL;

// Declaração do vetor de SDL_Rect que armazena os sprites da nave do jogador enquanto parada
SDL_Rect naveClipParado[3];

// Classe das TEXTURAS
class LTextura
{
public:
	
	// função que atribui os valores inicias as variáveis da classe
	LTextura();
	
	// função que redefine os valores das variáveis da classe para como iniciamente foram definidas em LTextura()
	~LTextura();
	
	// função que recebe uma string correspondente ao caminho(nome_da_pasta/imagem.png) da imagem a ser definida como textura 
	bool loadFromFile(std::string path);
	
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

// Declaração do objeto LTextura que armazena o imagem com todos os sprites da nave do jogador
LTextura naveSpriteSheet;

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
bool LTextura::loadFromFile(std::string path)
{
	// free() apaga qualquer definição de mTextura e suas dimensões antes de carregar uma nova imagem
	free();
	
	// novaTextura é uma SDL_Texture que está apenas no escopo dessa função para criar a textura
	// e retornar seu valor para a variável da classe mTextura
	SDL_Texture* novaTextura = NULL;
	
	// loadSurface é a SDL_Surface onde se é carregada a imagem correspondente ao caminho passado no parâmetro da função
	SDL_Surface* loadSuperficie = IMG_Load(path.c_str());
	
	// SDL_ColorKey torna certa tonalidade de pixels transparentes de uma SDL_Surface
	SDL_SetColorKey(loadSuperficie, SDL_TRUE, SDL_MapRGB(loadSuperficie->format, 0xFF, 0xFF, 0xFF));
	
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
	
	// função que atribui os valores iniciais as variáveis desta classe
	objJogador();
	
	// função que recebe como parâmetro eventos (apertar de teclas) e define qual o sentido do
	// deslocamento da textura do jogador ao somar ou subtrair a constante deslocamento
	// a variável mVelY, a qual será somada a posição da textura pela função move()
	void avaliarEventos(SDL_Event& e);
	
	// função que altera a posição Y da textura do jogador com base no sinal(sentido) da variável mVelY
	void move();
	
	// função que renderiza a textura do jogador
	void renderizar();

	// função que retorna o valor da altura da textura do jogador
	int getAltura();
private:
	// inteiro correspondente a posição em Y da textura do jogador
	int mPosY;
	
	// inteiro correspondente ao sentido do deslocamento da textura do jogador
	int mVelY;
};

// função que atribui os valores iniciais as variáveis desta classe
objJogador::objJogador()
{
	// A posição em Y da textura do jogador é definida para o centro do eixo
	mPosY = altJanela/2 - altJogador/2;

	mVelY = 0;
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
		}
	}
}

// função que altera a posição Y da textura do jogador com base no sinal(sentido) da variável mVelY
void objJogador::move()
{
	// O incremento (ou decremento) a variável mPosY, reajusta a posição da textura do jogador
	mPosY += mVelY;
	// Caso a posição da textura assuma um valor menor do que 0, ou se a textura do jogador tenda
	// a ultrapassar o limite da tela por conta de sua altura em relação a posição que ela assume...
	if ((mPosY < 0) || (mPosY + altJogador > altJanela))
	{
		// A posição em Y da textura é decrementada ou incrementada de modo a evitar que a textura ultrapasse a tela
		mPosY -= mVelY;
	}
}

// função que renderiza a textura do jogador
void objJogador::renderizar()
{
	naveSpriteSheet.renderizar(10, mPosY,&naveClipParado[0], 90, NULL);
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
	naveSpriteSheet.loadFromFile("spritesheets/STRIP-1.gif");
	// Definição dos parâmetro da SDL_Rect que armazenará certa porção de uma textura 
	naveClipParado[0].x = 1;
	naveClipParado[0].y = 1;
	naveClipParado[0].w = 46;
	naveClipParado[0].h = 44;
	return 0;
}

void close()
{
	// Apaga os valores das variáveis desse objeto LTextura 
	naveSpriteSheet.free();

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