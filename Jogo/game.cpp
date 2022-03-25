// inclusão das bibliotecas
#include<SDL.h>
#include<SDL_image.h>
#include<stdio.h>
#include<string>

// Declaração da largura da janela;
const int larJanela = 640;

// Declaração da altura da janela;
const int altJanela = 480;

// Declaração do inteiro usado para selecionar os indices do vetor de objProjeteis "laser"
int indiceVetorLaser;

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
// Declaração do vetor de SDL_Rect que armazena os sprites do objProjetil "laser"
SDL_Rect laserClip[2];

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
	
	// função que recebe como parâmetro eventos (tecla SPACE) e define quando um projetil deve ser disparado
	void avaliarEventosLaser(SDL_Event& e);

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
	
	// função que retorna a posição X da textura do jogador
	int getPosX();
private:
	// inteiros correspondentes as posições X e Y da textura do jogador
	int mPosY,mPosX;

	// inteiros correspondentes ao sentido do deslocamento da textura do jogador
	int mVelY,mVelX;

};

// classe que define o tipo Projétil
class objProjetil
{
public:
	// a variável disparado é uma flag que indica quando o projetil deve mover ou não
	// a variàvel "atualizaPosicaoDePartida" é uma flag que indica quando o projétil deve atualizar sua posição de partida
	bool disparado,atualizaPosicaoDePartida;
	// função que define valores padrões para as variáveis do tipo objProjetil
	objProjetil();
	// método responsável por modificar a posição X de um objProjetil fazendo com que este se mova  
	void move();
	// renderiza a textura do projétil na tela
	void renderizar();
private:
	// inteiro correspondente a posição X do projétil
	int posX;
	// inteiro correspondente a posição Y do projétil
	int posY;
};

// Declaração do objeto LTextura que armazena a imagem com todos os sprites da nave do jogador
LTextura naveSpriteSheet;
// Declaração do objeto LTextura que armazena a imagem com todos os sprites do projétil laser;
LTextura projeteisSpriteSheet;
// Declaração do objJogador que corresponde ao objeto manipulável pelo jogador
objJogador nave;
// Declaração do vetor objProjetil que armazena todos os projéteis  
objProjetil laser[15];

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

// função que atribui os valores iniciais as variáveis desta classe
objJogador::objJogador()
{
	// A posição em Y da textura do jogador é definida para o centro do eixo
	mPosY = altJanela/2 - altJogador/2;
	mPosX = 10;
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
		if (indiceVetorLaser == 15)
		{
			indiceVetorLaser = 0;
		}
		// Determina que dado menbro do vetor laser pode ser movido e renderizado pela tela
		laser[indiceVetorLaser].disparado = true;
		// Determina que dado membro do vetor laser deve atualizar sua posição para a última posição da nave do jogador
		laser[indiceVetorLaser].atualizaPosicaoDePartida = true;
	}
	// Caso proximoLaser tem valor true, o indiceVetorLaser recebe +1 e o valor de proximoLaser volta a ser falso 
	if (proximoLaser == true)
	{
		indiceVetorLaser += 1;
		proximoLaser = false;
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
	mPosX += mVelX;
	if ((mPosX < 0) || (mPosX + larJogador > larJanela))
	{
		mPosX -= mVelX;
	}
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

// função que renderiza a textura do jogador
void objJogador::renderizar()
{
	naveSpriteSheet.renderizar(mPosX, mPosY,&naveClipParado[0], 90, NULL);
}

// função que define a posição inicial do projétil  
objProjetil::objProjetil()
{
	posX = nave.getPosX() + nave.getLargura();
	posY = (nave.getPosY() + nave.getAltura() / 2) - 12;
}

void objProjetil::move()
{
	// Caso a variável "atualizaPosicaoDePartida" tenha valor true, a posição da textura do projetil
	// recebe as coordenadas xy correspondentes a frente da textura da nave do jogador em sua última posição 
	if (atualizaPosicaoDePartida == true)
	{
		// posição em X logo a frente da nave
		posX = nave.getPosX() + nave.getLargura();
		// posição em Y no meio da frente da nave
		posY = (nave.getPosY() + nave.getAltura() / 2) - 12;
		// o valor de "atualizaPosicaoDePartida" recebe false para que está condição não seja mais satisfeita
		atualizaPosicaoDePartida = false;
	}
	// Caso disparado tenha valor true, a posição em X será encrementada em 15 toda vez que a função for chamada
	if (disparado == true)
	{
		posX += 15;
	}
	// No momento em que a posição X textura do projetil for igual ao largura da janela, ou seja o final desta
	if (posX == larJanela)
	{
		// disparado recebe false para cancelar as adições de 15 na posição da textura do projetil
		disparado = false;
		// a posição em xy da textura do projétil recebe novamente as coordenadas correspondentes a
		// frente da textura da nave do jogador
		posX = nave.getPosX() + nave.getLargura();
		posY = (nave.getPosY() + nave.getAltura() / 2) - 12;
	}
}

// renderiza a textura do projétil na tela
void objProjetil::renderizar()
{
	// Enquanto disparado for igual a true, a textura do projetil será renderizada na tela toda vez que for chamada
	if (disparado == true)
	{
		projeteisSpriteSheet.renderizar(posX, posY,&laserClip[0],90);
	}
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
	projeteisSpriteSheet.loadFromFile("spritesheets_2/projetil_Laser.gif");
	// Definição dos parâmetro da SDL_Rect que armazenará certa porção da textura com os sprites da nave 
	naveClipParado[0].x = 1;
	naveClipParado[0].y = 1;
	naveClipParado[0].w = 46;
	naveClipParado[0].h = 44;
	// Definição dos parâmetro da SDL_Rect que armazenará certa porção da textura com os sprites dos projéteis
	laserClip[0].x = 0;
	laserClip[0].y = 0;
	laserClip[0].w = 24;
	laserClip[0].h = 41;
	return 0;
}

void close()
{
	// Apaga os valores das variáveis desse objeto LTextura 
	naveSpriteSheet.free();
	projeteisSpriteSheet.free();

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
		}
		nave.move();
		laser[0].move();
		laser[1].move();
		laser[2].move();
		laser[3].move();
		laser[4].move();
		laser[5].move();
		laser[6].move();
		laser[7].move();
		laser[8].move();
		laser[9].move();
		laser[10].move();
		laser[11].move();
		laser[12].move();
		laser[13].move();
		laser[14].move();

		SDL_SetRenderDrawColor(gRenderizador, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderizador);
		
		nave.renderizar();
		laser[0].renderizar();
		laser[1].renderizar();
		laser[2].renderizar();
		laser[3].renderizar();
		laser[4].renderizar();
		laser[5].renderizar();
		laser[6].renderizar();
		laser[7].renderizar();
		laser[8].renderizar();
		laser[9].renderizar();
		laser[10].renderizar();
		laser[11].renderizar();
		laser[12].renderizar();
		laser[13].renderizar();
		laser[14].renderizar();
		SDL_RenderPresent(gRenderizador);
	}
	close();
	return 0;
}