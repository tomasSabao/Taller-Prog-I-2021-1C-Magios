//Using SDL, SDL_image, standard IO, and strings

#include <stdio.h>
#include <string>
#include "../View/Vista.h"
#include "../Modelo/Modelo.h"






int main( int argc, char* args[] )
{
  //  Modelo_Jugador* jug= new Modelo_Jugador();
    //jug->caminar();
   // jug->caminar();
   // printf("%d\n",jug->getFrame());

  Modelo* modelo=new Modelo();
    Modelo_Jugador* jug2=modelo->getModeloJugador();
    jug2->caminar();
    jug2->caminar();
    jug2->caminar();
   printf("%d\n",jug2->getFrame());



    //Modelo  modelo ;
    Vista  vista(modelo);




	if( !vista.init( ))
	{
		printf( "Failed to initialize!\n" );
	}
	//else
	//{

		//Load media

	//	if( !vista.loadMedia( ))
	//	{
	//		printf( "Failed to load media!\n" );
	//	}
	//	else
	//	{
			//Main loop flag
		//	bool quit = false;

			//Event handler
		//	SDL_Event e;


			//While application is running
		//	while( !quit )
		//	{
				//Handle events on queue
			//	while( SDL_PollEvent( &e ) != 0 )
			//	{
					//User requests quit
			//		if( e.type == SDL_QUIT )
			//		{
			//			quit = true;
			//		}

            //    modelo.getModeloJugador()->caminar();

           //     vista.render();

			//	}



           // SDL_Delay(1000);
			//}
		//}
	//}

	//Free resources and close SDL
	 vista.close();

	return 0;
}
