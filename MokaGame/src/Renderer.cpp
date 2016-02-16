#include "Renderer.h"
#include "Camera.h"


Renderer::Renderer()
{
    width = 800;
    height = 600;
    (!initSDL())? std::cout << "Initialization SDL2 OK!" << std::endl : std::cout << "Initialization SDL2 ERROR!" << std::endl ;
    initOpenGL();
    ratio = 0;
    last_time = 0;
    a.init("data/fonts/ab.ttf", 22);
    wMesh = new WorldMesh();
    statek.imageID = statek.imgToTexture("data/img/statek.png");
    gui = new GUI();
    gui->init();
    gui->createTest();

}



Renderer& Renderer::getInstance()   // singletone pattern
{
    static Renderer instance;
    return instance;
}


Renderer::~Renderer()
{
	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

/*
int Renderer::addObject(Object aa )
{
    Object* a = new Object(aa);
    obiekty.push_back(a);
    return obiekty.size()-1;
}  */

void Renderer::calcTime()
{
    unsigned int curr_time;

    do{
    curr_time = SDL_GetTicks();
    Sleep(0);
    } while ((curr_time - last_time)/1000.0f < 1.0f/121);           // fps max = 100 //fix

    ratio = (double)(curr_time - last_time) / 1000.0f;
    CEGUI::System::getSingleton().injectTimePulse( static_cast<float>(
	  curr_time - last_time ) ) ;
    last_time = curr_time;
}

void Renderer::drawAll()
{
    calcTime();
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);         // Clear The Screen And The Depth Buffer
    glColor4f (1,1,1,1);

    glLoadIdentity();
    glTranslatef(-game->ships[0]->position[0],-game->ships[0]->position[1],-30);
  //  glTranslatef(0,0,-30);

    drawAxis(0,0,0);
    glColor3f( 0.0, 1.0, 1.0 );
    wMesh->drawPolygon(-width*0.023,-height*0.023,0);


    drawShip();
    drawModules();
    drawMissles();
    drawAsteroids();


 //   DrawQuadTexture(obiekty[0]->position[0],obiekty[0]->position[1],3,3,obiekty[0]->fOrientation, statek.imageID);

//    DrawQuadTexture(2.0f,2.0f,5.0f,5.0f,a[0]->myId);



   // drawAxis(0,0,0);
    //glPushMatrix();
   // wMesh->drawPolygon(-width*0.023,-height*0.023,0);

    glPopMatrix();
    glColor3f( 0.0, 1.0, 1.0 );

    glLoadIdentity();
    freetype::print(a, 77, 77, "Siemanko....");
    CEGUI::System::getSingleton().renderAllGUIContexts();

    glPushMatrix();

    glTranslatef(0.0f, 0.0f, -15.0f);


    //obiekty.drawAll();

    //DrawQuadTexture(1, 1, 10, 10, statek.imageID);





	SDL_GL_SwapWindow(window);
}


void Renderer::initOpenGL(){

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);						// Black Background
	glClearDepth(1.0f);											// Depth Buffer Setup
	glDepthFunc(GL_LESS);										// Type Of Depth Testing
	glEnable(GL_DEPTH_TEST);									// Enable Depth Testing
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);			// Enable Alpha Blending
	glEnable(GL_BLEND);											// Enable Blending
	glAlphaFunc(GL_GREATER,0.1f);								// Set Alpha Testing
	glEnable(GL_ALPHA_TEST);									// Enable Alpha Testing
	//glEnable(GL_TEXTURE_2D);									// Enable Texture Mapping
	//glEnable(GL_CULL_FACE);									    // Remove Back Face
	glShadeModel(GL_SMOOTH);
	glViewport(0, 0, width, height);							// Ustawienie pola rzutowania (wsp. okna = (0,0) do (Width, Height))
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();											// Reset The Projection Matrix
	gluPerspective(90.0f,(GLfloat)width/(GLfloat)height,0.1f,330.0f); // Obliczanie parametróe rzutowanie (ciekawa funcja, zobaczcie do dokumentacji w necie)
	glMatrixMode(GL_MODELVIEW);									// Rysowanie czas zacz¹æ :)

    }

bool Renderer::initSDL(){
	// m0rf: nie bêdê opisywa³ tej funkcji, napisa³em j¹ zgodnie z wytycznymi na wikipedii SDLowskiej
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
		return 1;
		}


  // Create a window. Window mode MUST include SDL_WINDOW_OPENGL for use with OpenGL.
	window = SDL_CreateWindow(
        "MOKA GAME",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width,
		height,
		SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE
	);

	if(window==NULL){		// In the event that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	// Create an OpenGL context associated with the window.
	glcontext = SDL_GL_CreateContext(window);
	if(glcontext==NULL){		// In the event that the window could not be made...
		printf("Could not create glcontext: %s\n", SDL_GetError());
		return 1;
	}
	// if(SDL_SetRelativeMouseMode(SDL_TRUE)<0){ // przechwycenie kursora przez okno = dostêpne tylko wzglêdne przesuniêcia
		// fprintf(stderr, "Unable to set Relative Mouse Mode: %s\n", SDL_GetError());
		// }
    SDL_ShowCursor(SDL_ENABLE);
    SDL_SetRelativeMouseMode(SDL_FALSE);
	return 0;
}

void Renderer::drawShip ()
{
    for (unsigned int i=0;i<game->ships.size();i++ )
    {
      /*  DrawQuadTexture(game->ships[i]->position[0],
                      game->ships[i]->position[1],
                        game->ships[i]->w,
                        game->ships[i]->h,
                        game->ships[i]->fOrientation,
                        game->ships[i]->myID);  */
            float x = game->ships[i]->position[0];
            float y = game->ships[i]->position[1];

            float angle = game->ships[i]->fOrientation;

            int vc = game->ships[i]->vertexCount;


            glPushMatrix ();
            glLineWidth (3.0f);

            glTranslatef(x,y,0);

            glRotatef( RADTODEG(angle) , 0, 0, 1 );
            glBegin (GL_LINE_LOOP);
                for(int j=0;j<vc;j++)
                {
                    x = game->ships[i]->vertices[j].x;
                    y = game->ships[i]->vertices[j].y;
                  //  glColor3f (0.7,1,1);
                  if ( game->ships[i]->m_contacting )
                    glColor3f(1,0,0);//red
                  else
                    glColor3f(1,1,1);//white
                    glVertex3f (x,y,0);
                }
            glEnd();
            glPopMatrix ();
            // DRAWING MODULE
    }
}

void Renderer::drawModules (){

    for (unsigned int i=0;i<game->ships[0]->modules.size();i++ )
    {
            float x = game->ships[0]->modules[i]->position[0];
            float y = game->ships[0]->modules[i]->position[1];
            int vc = game->ships[0]->modules[i]->vertexCount;
            float angle = game->ships[0]->modules[i]->fOrientation;


            glPushMatrix ();
            glLineWidth (3.0f);
            glTranslatef(x,y,0);
            glRotatef( RADTODEG(angle) , 0, 0, 1 );
            glBegin (GL_LINE_LOOP);
                for(int j=0;j<vc;j++)
                {
                    x = game->ships[0]->modules[i]->vertices[j].x;
                    y = game->ships[0]->modules[i]->vertices[j].y;
                    if ( game->ships[0]->modules[i]->m_contacting )
                      glColor3f(1,0,0);//red
                    else
                      glColor3f(1,1,1);//white
                    glVertex3f (x,y,0);
                }
            glEnd();

            glPopMatrix ();

    }

}

void Renderer::drawMissles()
{
    for (unsigned int i=0;i<game->missles.size();i++ )
    {

        if(game->missles[i]->type == LASER){
            float x = game->missles[i]->position[0];
            float y = game->missles[i]->position[1];
            glPushMatrix ();
            glLineWidth (10.0f);
                glBegin (GL_LINES);
                    glColor3f (1,0,0);
                    glVertex3f (game->missles[i]->positionStart.x,game->missles[i]->positionStart.y,0);
                    glColor3f (0,0,1);
                    glVertex3f (x,y,0);
                glEnd();
            glPopMatrix ();

          glPushMatrix ();
          glLineWidth (3.0f);
          glTranslatef(x,y,0);
          glBegin(GL_LINE_LOOP);
             if ( game->missles[i]->m_contacting )
                  glColor3f(1,0,0);//red
             else
                  glColor3f(1,1,1);//white
             for (int j=0; j < 360; j++){
                  float degInRad = DEGTORAD(j);
                  glVertex2f(cos(degInRad)*game->missles[i]->radius,sin(degInRad)*game->missles[i]->radius);
             }
          glEnd();
          glPopMatrix ();
        }
        else if(game->missles[i]->type == BULLET)
        {
            float x = game->missles[i]->position[0];
            float y = game->missles[i]->position[1];
          glPushMatrix ();
          glLineWidth (3.0f);
          glTranslatef(x,y,0);
          glBegin(GL_LINE_LOOP);
             if ( game->missles[i]->m_contacting )
                  glColor3f(1,0,0);//red
             else
                  glColor3f(1,1,1);//white
             for (int j=0; j < 360; j++){
                  float degInRad = DEGTORAD(j);
                  glVertex2f(cos(degInRad)*game->missles[i]->radius,sin(degInRad)*game->missles[i]->radius);
             }
          glEnd();
          glPopMatrix ();
        }
        else if(game->missles[i]->type == PLASMA)
        {
            float x = game->missles[i]->position[0];
            float y = game->missles[i]->position[1];
          glPushMatrix ();
          glLineWidth (3.0f);
          glTranslatef(x,y,0);
          glBegin(GL_LINE_LOOP);
             if ( game->missles[i]->m_contacting )
                  glColor3f(1,0,0);//red
             else
                  glColor3f(1,1,1);//white
             for (int j=0; j < 360; j++){
                  float degInRad = DEGTORAD(j);
                  glVertex2f(cos(degInRad)*game->missles[i]->radius,sin(degInRad)*game->missles[i]->radius);
             }
          glEnd();
          glPopMatrix ();
        }
        else if(game->missles[i]->type == ROCKET)
        {
            Renderer::getInstance().DrawQuadTexture(2.0f,2.0f,5.0f,5.0f,game->missles[i]->myID);
        }

    }
}

void Renderer::drawAsteroids()
{

    for (unsigned int i=0;i<game->asteroides.size();i++ )
    {
            float x = game->asteroides[i]->position[0];
            float y = game->asteroides[i]->position[1];
            int vc = game->asteroides[i]->vertexCount;
            float angle = game->asteroides[i]->fOrientation;

            // tego tu nie ma być morf
       //     game->asteroides[i]->move();


            glPushMatrix ();
            glLineWidth (3.0f);
            glTranslatef(x,y,0);
            glRotatef( RADTODEG(angle) , 0, 0, 1 );
            glBegin (GL_LINE_LOOP);
                for(int j=0;j<vc;j++)
                {
                    x = game->asteroides[i]->vertices[j].x;
                    y = game->asteroides[i]->vertices[j].y;
                    if ( game->asteroides[i]->m_contacting )
                      glColor3f(1,0,0);//red
                    else
                      glColor3f(1,1,1);//white
                    glVertex3f (x,y,0);
                }
            glEnd();

            glPopMatrix ();

    }
}


void Renderer::drawAxis (float x = 1.0f,float y = 1.0f,float z = 1.0f){

	//glDisable(GL_LIGHTING);
    //glDisable(GL_COLOR_MATERIAL);

	glPushMatrix ();

		glTranslatef (x, y, z);					// trochê dalej od pocz¹tku uk³adu...
		glScalef     (2.25, 2.25, 2.25);					// powiêksz
		glLineWidth (1.0f);									// bruboœæ lini na 1px;
		glBegin (GL_LINES);									// rysowanie lini
			glColor3f (1,0,0);  glVertex3f (0,0,0);  glVertex3f (1,0,0);    // X axis is red.
			glColor3f (0,1,0);  glVertex3f (0,0,0);  glVertex3f (0,1,0);    // Y axis is green.
			glColor3f (0,0,1);  glVertex3f (0,0,0);  glVertex3f (0,0,1);    // z axis is blue.
		glEnd();
	glPopMatrix ();
	//glEnable(GL_LIGHTING);
	//glEnable(GL_COLOR_MATERIAL);

}

void Renderer::printSupportedExtensions()
{

}


void Renderer::DrawQuad(float x, float y, float w, float h)
{
  w /= 2.0f; h /= 2.0f;

  glBegin(GL_QUADS);

  glTexCoord2f(0.0f, 0.0f); glVertex3f(x - w, y - h,-10);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(x + w, y - h,-10);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(x + w, y + h,-10);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(x - w, y + h,-10);
  glEnd();
}

void Renderer::DrawQuadRGBA(float x, float y, float w, float h, float r, float g, float b, float a)
{
  // Get old color.
  float current_color[4];
  glGetFloatv(GL_CURRENT_COLOR, current_color);

  // Set new color and draw quad.
  glColor4f(r, g, b, a);
  DrawQuad(x, y, w, h);

  // Set old color.
  glColor4fv(current_color);
}

void Renderer::DrawQuadTexture(float x, float y, float w, float h, unsigned int texture_id)
{
  // Enable texturing if needed.
  bool texturing_enabled = glIsEnabled(GL_TEXTURE_2D);
  if(!texturing_enabled)
    glEnable(GL_TEXTURE_2D);

  // Bind texture and draw.
  glBindTexture(GL_TEXTURE_2D, texture_id);
  DrawQuad(x, y, w, h);

  // Disable if was disable.
  if(!texturing_enabled)
    glDisable(GL_TEXTURE_2D);
}
void Renderer::drawPoint(float x, float y){

  glTranslatef(x,y,0);
  glBegin(GL_POINT);
    glColor3f (0,1,0);
    glPointSize(3);
    glVertex3f(x,y,-9);
  glEnd();

}
void Renderer::DrawQuadTexture(float x, float y, float w, float h,float angle, unsigned int texture_id)
{
glPushMatrix ();
  w /= 2.0f; h /= 2.0f;
	 bool texturing_enabled = glIsEnabled(GL_TEXTURE_2D);
  if(!texturing_enabled)
    glEnable(GL_TEXTURE_2D);
	glColor3f (1,1,1);
	glTranslatef(x,y,0);
	glRotatef(RADTODEG(angle), 0.0f, 0.0f, 1.0f);
	glTranslatef(0,0,0);
  // Bind texture and draw.
  glBindTexture(GL_TEXTURE_2D, texture_id);
  glBegin(GL_QUADS);

  glTexCoord2f(0.0f, 1.0f); glVertex3f(0 - w, 0 - h,0.1f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(0 + w, 0 - h,0.1f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(0 + w, 0 + h,0.1f);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(0 - w, 0 + h,0.1f);



/*  glTexCoord2f(0.0f, 1.0f); glVertex3f(0+w, 0,0.1f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(0 , 0 ,0.1f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0+h,0.1f);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(0+w, 0+h,0.1f);  */

/*  glTexCoord2f(0.0f, 1.0f); glVertex3f(1/w, 1/h,0.1f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(1*w, 1/h,0.1f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(1*w, 1*h,0.1f);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(1/w, 1*h,0.1f);  */

  glEnd();

  // Disable if was disable.
  if(!texturing_enabled)
    glDisable(GL_TEXTURE_2D);

	  		glPopMatrix ();
}
