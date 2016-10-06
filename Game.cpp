#include "Game.h"

Game::Game()
{
    //ctor
    CROOM = 0;
    done=false;
    Tanks.resize(NUM_TANKS);
    BLOQUES.resize(NUM_BLOQUES);
    BALAS.resize(NUM_BALAS);

    SCREEN = NULL;
    LINEA = NULL;
    PANTALLA_INI = NULL;
    VIDA = NULL;
    MARKERP1 = NULL;
    MARKERP2 = NULL;

    EXPLOCION = NULL;
    diferencia = 0;
    tiempo_juego=TIME_GAME;
}

Game::~Game()
{
    //dtor
}

//! CRONOMETRO
void Game::Cronometro()
{
   //while (diferencia < 120 ){
      time_fin = time(NULL); /* obtener tiempo 2 */

      diferencia = difftime(time_fin, time_ini);

      //!Retro del cronometro
      diferencia = tiempo_juego - diferencia;
      //!----------------

      minutos = diferencia / 60.0;
      segundos = diferencia - minutos * 60;

      //miliseg = segundos/1000;

      if (temp != segundos){ /* ha transcurrido un segundo */
         temp = segundos; /* guarda el valor previo */
         char bufer[100];
         sprintf (bufer,"%02d:%02d", minutos, segundos);//cout<<diferencia<<endl;
         TextCrono.Text = TextCrono.drawtext(TextCrono.font, 255-diferencia*(255/TIME_GAME), 0, 0, 70, 0, 0, 0, 0, bufer,blended);
      }

}

//! Vuelve transparente RGB del Surface destination
bool Game::Transparent(SDL_Surface* destination, int R, int G, int B) {
	if(destination == NULL) {
		return false;
	}

	SDL_SetColorKey(destination, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(destination->format, R, G, B));

	return true;
}

//! Aqui colocaremos todos los Surface que necesitan una parte Transparente, USAMOS EL COLOR WHITE=255,255,255
void Game::SurfacesTransparents()
{
    Transparent(EXPLOCION,TRANSPARENT_R,TRANSPARENT_G,TRANSPARENT_B);
    Transparent(VIDA,TRANSPARENT_R,TRANSPARENT_G,TRANSPARENT_B);
    Transparent(MARKERP1,TRANSPARENT_R,TRANSPARENT_G,TRANSPARENT_B);
    Transparent(MARKERP2,TRANSPARENT_R,TRANSPARENT_G,TRANSPARENT_B);
    for(int i=0;i<NUM_TANKS;i++){
        Transparent(Tanks[i],TRANSPARENT_R,TRANSPARENT_G,TRANSPARENT_B);
    }
    for(int i=0;i<NUM_BALAS;i++){
        Transparent(BALAS[i],TRANSPARENT_R,TRANSPARENT_G,TRANSPARENT_B);
    }
}

//! Dibuja superficie/imagen=destination en la posicion x,y sobre source, pero destination es una animacion=(imagen mas larga), solo dibuja una parte de destination W,H
bool Game::DrawSurface(SDL_Surface* source, SDL_Surface* destination, int X, int Y, int X2, int Y2, int W, int H)
{
    if(destination == NULL || source == NULL) {
		return false;
	}

	SDL_Rect DestR;

	DestR.x = X;
	DestR.y = Y;

	SDL_Rect SrcR;

	SrcR.x = X2;
	SrcR.y = Y2;
	SrcR.w = W;
	SrcR.h = H;

	SDL_BlitSurface(source, &SrcR, destination, &DestR);//cout<<X2<<" - "<<Y2<<endl;

	return true;
}

//! Dibuja superficie/imagen=destination en la posicion x,y sobre source
void Game::DrawSurface(int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
    // Crea una superfice rectangular
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;

    // Blit
    SDL_BlitSurface(source, NULL, destination, &offset);
}

//! Carga la imagen en una superficie
SDL_Surface *Game::LoadSurfaceFromFile(string filename)
{
    // Superficies
    SDL_Surface* LoadedImage = NULL;
    SDL_Surface* OptimizedImage = NULL;

    // Cargar Imagen
    LoadedImage = IMG_Load(filename.c_str());

    // Si la imagen es cargada
    if (LoadedImage != NULL)
    {
        // Crea una nueva imagen optimizada
        OptimizedImage = SDL_DisplayFormat(LoadedImage);

        // Liberar la superficie anterior
        SDL_FreeSurface(LoadedImage);
    }

    // retornar la nueva imagen optimizada
    return OptimizedImage;
}

//! Cargamos las superficies
void Game::LoadFiles()
{
    EXPLOCION = LoadSurfaceFromFile("imgs/explocion.jpg");
    LINEA = LoadSurfaceFromFile("imgs/linea.jpg");
    PANTALLA_INI = LoadSurfaceFromFile("imgs/portada.jpg");
    VIDA = LoadSurfaceFromFile("imgs/vida2.jpg");
    MARKERP1 = LoadSurfaceFromFile("imgs/markerP2.jpg");
    MARKERP2 = LoadSurfaceFromFile("imgs/markerP1.jpg");

    BLOQUES[0] = NULL;
    BLOQUES[1] = LoadSurfaceFromFile("imgs/bloque1.jpg");;
    BLOQUES[2] = LoadSurfaceFromFile("imgs/bloque2_1.jpg");
    BLOQUES[3] = LoadSurfaceFromFile("imgs/bloque2.jpg");;
    BLOQUES[4] = LoadSurfaceFromFile("imgs/bloque3_2.jpg");;
    BLOQUES[5] = LoadSurfaceFromFile("imgs/bloque3_1.jpg");;
    BLOQUES[6] = LoadSurfaceFromFile("imgs/bloque3.jpg");;
    BLOQUES[7] = LoadSurfaceFromFile("imgs/agua.jpg");;
    BLOQUES[8] = LoadSurfaceFromFile("imgs/bloque4.jpg");;

    //Tanques
    Tanks[0] = LoadSurfaceFromFile("imgs/tank1.jpg");
    Tanks[1] = LoadSurfaceFromFile("imgs/tank2.jpg");
    Tanks[2] = LoadSurfaceFromFile("imgs/tank3.jpg");
    Tanks[3] = LoadSurfaceFromFile("imgs/tank4.jpg");

    //BALAS
    BALAS[0] = LoadSurfaceFromFile("imgs/bala1.jpg");
    BALAS[1] = LoadSurfaceFromFile("imgs/bala2.jpg");
    BALAS[2] = LoadSurfaceFromFile("imgs/bala3.jpg");
}

//! Liberar memoria de las superficies
void Game::UnloadFiles()
{
    SDL_FreeSurface(LINEA);
    SDL_FreeSurface(EXPLOCION);
    SDL_FreeSurface(PANTALLA_INI);
    SDL_FreeSurface(VIDA);
    SDL_FreeSurface(MARKERP1);
    SDL_FreeSurface(MARKERP2);

    for(int i=0;i<NUM_TANKS;i++){
        SDL_FreeSurface(Tanks[i]);
    }Tanks.clear();

    for(int i=0;i<NUM_BLOQUES;i++){
        SDL_FreeSurface(BLOQUES[i]);
    }BLOQUES.clear();

    for(int i=0;i<NUM_BALAS;i++){
        SDL_FreeSurface(BALAS[i]);
    }BALAS.clear();

    SDL_FreeSurface(player1_name.Text);
    SDL_FreeSurface(player2_name.Text);
    SDL_FreeSurface(player1_vida.Text);
    SDL_FreeSurface(player2_vida.Text);
    SDL_FreeSurface(Mensaje_Fin.Text);
    SDL_FreeSurface(TextCrono.Text);
}

//! Creamos la matriz para el mapa  y seteamos los valores del mapa de un archivo
void Game::Create_mapa()
{
    Mapa.clear();
    // Separamos espacio para el mapa
    Mapa.resize(MAPA_HEIGHT);
    for(int i=0;i<MAPA_HEIGHT;i++){
        Mapa[i].resize(MAPA_WIDTH);
    }
    //Leemos de archivo
    ifstream entrada("mapas/mapa1");
    int buffer;
    for(int i=0;i<MAPA_HEIGHT;i++){
        for(int j=0;j<MAPA_WIDTH;j++){
            entrada>>buffer;
            Objeto obj(i,j,buffer);
            //AQUI SE MODIFICA LA VIDA DEL BLOQUE
            if(buffer==1) obj.setVida(1);
            if(buffer==2) obj.setVida(1);
            if(buffer==3) obj.setVida(2);
            if(buffer==4) obj.setVida(1);
            if(buffer==5) obj.setVida(2);
            if(buffer==6) obj.setVida(3);
            Mapa[i][j] = obj;
        }
    }
}

//! Dibujamos el mapa de la matriz Mapa
void Game::DibujarMapa()
{
    int id;
    for(int i=0;i<MAPA_HEIGHT;i++){
        for(int j=0;j<MAPA_WIDTH;j++){
            id = Mapa[i][j].ID_obj;
            if(id > 0 ) DrawSurface(j*CELL_SIZE, i*CELL_SIZE+SPACE_POINTS, BLOQUES[id], SCREEN);
        }
    }
}

//! Eventos para el teclado
void Game::KeyWords()
{
    // check for messages
    switch (event.type)
    {
        // exit if the window is closed
        case SDL_QUIT:
            done = true;
            break;

        // check for keypresses
        case SDL_KEYDOWN:
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_ESCAPE: // exit if ESCAPE is pressed
                    done = true;
                    break;
                case SDLK_RETURN: //Enter
                    if (CROOM == 0) //Set todo los componentes para que empice el juego
                    {
                        Reset_Players();
                        time_ini = time(NULL);//Inicializamos el tiempo
                        //Cargamos el Mapa
                        Create_mapa();
                        CROOM  = 1;
                    }
                    if(CROOM == 3){
                        CROOM = 0;
                    }
                    break;
                case SDLK_SPACE: //BALA PLAYER 1
                    //Bala b();
                    //b.setBala(player_1.pos_x,player_1.pos_y,player_1.getDireccion(),1);
                    player_1.list_balas.push_back(Bala(player_1.position.x,player_1.position.y,player_1.getDireccion(),1));
                    break;
                case SDLK_RSHIFT: //BALA PLAYER 2
                    player_2.list_balas.push_back(Bala(player_2.position.x,player_2.position.y,player_2.getDireccion(),1));
                    break;
                default:
                    break;
            }
            break;
        }

    } // end switch
}

//! Sirve para ver que teclas estan siendo presionadas constantemente
void Game::KeyWordStates()
{
    //Get the keystates
    keystates = SDL_GetKeyState( NULL );
    //!     Movimientos del jugador 1
    //If left is pressed
    if( keystates[ SDLK_a ] )
    {
        player_1.setDireccion(GO_LEFT);
        if(player_1.verificaEnMatriz(Mapa)){
            player_1.Mover();
        }
    }

    //If up is pressed
    if( keystates[ SDLK_w ] )
    {
        player_1.setDireccion(GO_UP);
        if(player_1.verificaEnMatriz(Mapa)){
            player_1.Mover();
        }
    }

    //If down is pressed
    if( keystates[ SDLK_s ] )
    {
        player_1.setDireccion(GO_DOWN);
        if(player_1.verificaEnMatriz(Mapa)){
            player_1.Mover();
        }
    }

    //If right is pressed
    if( keystates[ SDLK_d ] )
    {
        player_1.setDireccion(GO_RIGHT);
        if(player_1.verificaEnMatriz(Mapa)){
            player_1.Mover();
        }
    }
    //!     Movimientos del jugador 2
    if( keystates[ SDLK_LEFT ] )
    {
        player_2.setDireccion(GO_LEFT);
        if(player_2.verificaEnMatriz(Mapa)){
            player_2.Mover();
        }
    }

    //If up is pressed
    if( keystates[ SDLK_UP ] )
    {
        player_2.setDireccion(GO_UP);
        if(player_2.verificaEnMatriz(Mapa)){
            player_2.Mover();
        }
    }

    //If down is pressed
    if( keystates[ SDLK_DOWN ] )
    {
        player_2.setDireccion(GO_DOWN);
        if(player_2.verificaEnMatriz(Mapa)){
            player_2.Mover();
        }
    }

    //If right is pressed
    if( keystates[ SDLK_RIGHT ] )
    {
        player_2.setDireccion(GO_RIGHT);
        if(player_2.verificaEnMatriz(Mapa)){
            player_2.Mover();
        }
    }

}

void Game::Info_Game()
{
        //DIbujamos linea divitoria entre el juego y los puntos
        DrawSurface(0, SPACE_POINTS-LINEA->h, LINEA, SCREEN);
        DrawSurface(50,10,player1_name.Text,SCREEN);
        DrawSurface(800,10,player2_name.Text,SCREEN);
        //Colocamos algunas imgs de ayuda
        DrawSurface(100,120,VIDA,SCREEN);
        DrawSurface(860,120,VIDA,SCREEN);

        DrawSurface(455,115,TextCrono.Text,SCREEN);

        //VIDA TEXTO
        char bufer[10];
        sprintf (bufer,"%d X", player_1.getVida());
        player1_vida.Text = player1_name.drawtext(player1_name.font,0,0,255,70,0,0,0,0,bufer,blended);
        sprintf (bufer,"%d X", player_2.getVida());
        player2_vida.Text = player2_name.drawtext(player2_name.font,255,0,0,70,0,0,0,0,bufer,blended);
        DrawSurface(50,110,player1_vida.Text ,SCREEN);
        DrawSurface(810,110,player2_vida.Text ,SCREEN);
}

//! Funcion update
bool Game::Update()
{
    // Limpiar pantalla
    SDL_FillRect(SCREEN, 0, SDL_MapRGB(SCREEN->format, 236, 226, 198));

    // Dibujamos la pantalla de inicio - PORTADA
    if(CROOM==0){
        DrawSurface(0, 0, PANTALLA_INI, SCREEN);
    }

    if(CROOM == 1){

        // draw mapa
        DibujarMapa();

        Info_Game();

        //Draw position tanks
        DrawSurface(MARKERP1, SCREEN, player_1.pos_x*CELL_SIZE, player_1.pos_y*CELL_SIZE+SPACE_POINTS, player_1.getDireccion() * CELL_SIZE, 0, CELL_SIZE, CELL_SIZE);
        DrawSurface(MARKERP2, SCREEN, player_2.pos_x*CELL_SIZE, player_2.pos_y*CELL_SIZE+SPACE_POINTS, player_2.getDireccion() * CELL_SIZE, 0, CELL_SIZE, CELL_SIZE);

        //TANQUES
        DrawSurface(Tanks[tank_modelo_p1], SCREEN, player_1.position.x, player_1.position.y+SPACE_POINTS, player_1.getDireccion() * CELL_SIZE, 0, CELL_SIZE, CELL_SIZE);
        DrawSurface(Tanks[tank_modelo_p2], SCREEN, player_2.position.x, player_2.position.y+SPACE_POINTS, player_2.getDireccion() * CELL_SIZE, 0, CELL_SIZE, CELL_SIZE);
        //DrawBalas();
        player_1.DrawBalas(EXPLOCION,SCREEN,Mapa,Anim_Explocion,BALAS,player_2.list_balas,player_2.pos_x,player_2.pos_y);
        player_2.DrawBalas(EXPLOCION,SCREEN,Mapa,Anim_Explocion,BALAS,player_1.list_balas,player_1.pos_x,player_1.pos_y);

        if(player_1.getVida()==player_2.getVida() && diferencia==0){
            //EMPATE
            Mensaje_Fin.Text = Mensaje_Fin.drawtext(Mensaje_Fin.font,0,0,0,70,0,0,0,0,"       EMPATE!!       ",blended);
            CROOM=3;
        }
        if(player_1.getVida()<=0 || (player_1.getVida()<player_2.getVida() && diferencia==0)){
            Mensaje_Fin.Text = Mensaje_Fin.drawtext(Mensaje_Fin.font,0,0,0,70,0,0,0,0,"EL GANADOR ES PLAYER 2",blended);
            CROOM=3;
        }
        if(player_2.getVida()<=0 || (player_1.getVida()>player_2.getVida() && diferencia==0)){
            Mensaje_Fin.Text = Mensaje_Fin.drawtext(Mensaje_Fin.font,0,0,0,70,0,0,0,0,"EL GANADOR ES PLAYER 1",blended);
            CROOM=3;
        }

    }
    if(CROOM==3){
        Info_Game();
        DrawSurface(150, 450, Mensaje_Fin.Text, SCREEN);
    }
    // Actualizar la pantalla principal
    if (SDL_Flip(SCREEN) == -1)
    {
        // Error
        cout << MESSAGE_UPDATE_SCREEN_ERROR << endl;
        return true;
    }
    return false;
}

void Game::Reset_Players()
{
    srand(time(0));
    tank_modelo_p1 = rand()%NUM_TANKS;
    player_1.setPlayer(8,10,1,tank_modelo_p1);
    tank_modelo_p2 = (tank_modelo_p1+1)%NUM_TANKS;
    player_2.setPlayer(8,1,2,tank_modelo_p2);

    player_1.list_balas.clear();
    player_2.list_balas.clear();
}

//! ------------------------------Inicializar SDL y ejecutar juego---------------------------------------------------
void Game::ExecuteGame()
{
    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "%s %s\n", MESSAGE_SDL_INIT.c_str(), SDL_GetError() );
        return;
    }

    // Nos aseguramos que SDL este limpio antes de ser lanzado
    atexit(SDL_Quit);

    // create a new window
    SCREEN = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 16, SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !SCREEN )
    {
        printf("%s %d x %d : %s\n", MESSAGE_SDL_VIDEO.c_str(), WINDOW_HEIGHT, WINDOW_WIDTH, SDL_GetError());
        return;
    }
    // Colocar el titulo de la pantalla
    SDL_WM_SetCaption(TITLE_GAME.c_str(), NULL);

    // Cargar Archivos
    LoadFiles();

    // Colocamos los Srfaces Transparenets
    SurfacesTransparents();
    // Maximo numero de frames que tiene la animacion explocion
    Anim_Explocion.MaxFrames = 6;

    //!Inicializamos los tanques
    Reset_Players();

    //Iniciamos TTF
    TTF_Init();
    //Nombre a los jugadores
    player1_name.font = player1_name.loadfont("KhmerOSsys.ttf", 26);
    player2_name.font = player2_name.loadfont("KhmerOSsys.ttf", 26);
    Mensaje_Fin.font = Mensaje_Fin.loadfont("KhmerOSsys.ttf", 58);
    TextCrono.font = TextCrono.loadfont("KhmerOSsys.ttf", 36);
    player1_name.Text = player1_name.drawtext(player1_name.font,0,0,255,70,0,0,0,0,"PLAYER 1",blended);
    player2_name.Text = player2_name.drawtext(player2_name.font,255,0,0,70,0,0,0,0,"PLAYER 2",blended);


    time_ini = time(NULL);//Inicializamos el tiempo
    // program main loop
    while (!done)
    {
        if(CROOM==1){Cronometro();}
        frametime = SDL_GetTicks();
        if (Update() == 1)
        {
            // Error al actualizar la pantalla
            done = true;
        }
        // message processing loop
        while (SDL_PollEvent(&event))
        {
            KeyWords();
        }
        KeyWordStates();
        //controlando el tiempo  de fotogramas
        frametime = SDL_GetTicks() - frametime;
        if(frametime < TIME_FOTOGRAMA){
            SDL_Delay(Uint32(TIME_FOTOGRAMA-frametime));
        }

    } // end main loop

    TTF_Quit();
    // Unload Files - Liberar memoria de las superficies
    UnloadFiles();
    SDL_Quit();

}
