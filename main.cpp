#include <stdio.h>
#include "SDL/SDL.h"
#include <string>

// Resolução da Tela
const int SCREEN_LARGURA = 800;
const int SCREEN_ALTURA = 600;
const int SCREEN_BPP = 32;

//As Surfaces que vão ser usadas
SDL_Surface* mensagem = NULL;
SDL_Surface* bg = NULL;
SDL_Surface* tela = NULL;


SDL_Surface *load_image( std::string filename )
{
    // Surface temporaria, que carrega a imagem
    SDL_Surface* loadedImage = NULL;

    // Surface melhorada que vai ser utilizada
    SDL_Surface* optImagem = NULL;

    //Carregar a Imagem
    loadedImage = SDL_LoadBMP( filename.c_str() );

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


int main( int argc, char* args[] )
{

  // Inicializa o SDL
  if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
  {

      return 1;
  }

  // Inicia Vídeo
  tela = SDL_SetVideoMode( SCREEN_LARGURA, SCREEN_ALTURA, SCREEN_BPP, SDL_SWSURFACE);

  // Se houver algum erro na configuração da tela
  if( tela == NULL )
  {

   return 1;
  }

  // Nome da Form
  SDL_WM_SetCaption("Pokémon Engine", NULL);

  // Carregar Imagens
  mensagem = load_image( "hello.bmp" );
  bg = load_image( "cb.bmp" );

  // Desenha BG na tela
  apply_surface( 0, 0, bg, tela);

  // Atualiza a tela
  if( SDL_Flip( tela ) == -1)
  {
      return 1;
  }

  // Aguardar 2 segundos
  SDL_Delay( 2000 );

return 0;
}


