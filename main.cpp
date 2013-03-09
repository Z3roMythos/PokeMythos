
// Bibliotecas
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>

// Resolução da Tela
const int SCREEN_LARGURA = 800;
const int SCREEN_ALTURA = 600;
const int SCREEN_BPP = 32;

//As Surfaces que vão ser usadas
SDL_Surface* mensagem = NULL;
SDL_Surface* bg = NULL;
SDL_Surface* tela = NULL;


// A estrutura de evento que vai ser usada
SDL_Event evento;


SDL_Surface *load_image( std::string filename )
{
    // Surface temporaria, que carrega a imagem
    SDL_Surface* loadedImage = NULL;

    // Surface melhorada que vai ser utilizada
    SDL_Surface* optImagem = NULL;

    // Agora ele vai carregar PNG
    loadedImage = IMG_Load( filename.c_str() );

    if( loadedImage != NULL)
    {
        //Cria a Surface melhorada
        optImagem = SDL_DisplayFormat( loadedImage );

        //Libera a imagem antiga
        SDL_FreeSurface( loadedImage );

    }

    // Retorna com a imagem melhorada :)
    return optImagem;

}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destino)
{

    // Cria um retangulo temporario e seus offsets
    SDL_Rect offset;

    // Valores do OffSet do Triângulo
    offset.x = x;
    offset.y = y;

    // Desenha a Surface
    SDL_BlitSurface( source, NULL, destino, &offset );

}


bool init()
{
    // Inicializa o SDL
  if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
  {

      return false;
  }

 // Inicia Vídeo
  tela = SDL_SetVideoMode( SCREEN_LARGURA, SCREEN_ALTURA, SCREEN_BPP, SDL_SWSURFACE);

  // Se houver algum erro na configuração da tela
  if( tela == NULL )
  {

   return false;
  }

  // Nome da Form
  SDL_WM_SetCaption("Pokémon Engine", NULL);

  // Se tudo ocorrer bem
  return true;

}

bool load_Files()
{


  // Carregar Imagens
  bg = load_image( "teste.png" );


  // Se der algum erro ao carregar a imagem
  if( bg == NULL )
  {
      return false;
  }

  // Caso a imagem carregar
  return true;

}

void clean_up()
{
    // Remove a imagem
    SDL_FreeSurface( bg );


    // Fechar o SDL
    SDL_Quit();

}

int main( int argc, char* args[] )
{

   bool sair = false;

   // Inicialização
   if( init() == false)
   {
       return 1;
   }

   // Carregar Arquivos
   if( load_Files() == false )
   {
       return 1;
   }


  // Desenha BG na tela
  apply_surface( 0, 0, bg, tela);

  // Atualiza a tela
  if( SDL_Flip( tela ) == -1)
  {
      return 1;
  }

  // While
  while( sair == false )
  {
      while( SDL_PollEvent( &evento ))
      {

          if(evento.type == SDL_QUIT )
          {
              sair = true;
          }
      }

  }

    clean_up();

return 0;
}


