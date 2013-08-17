#include "global.h"


/*			ESFERA TOROIDE PARTE V
Controles
Tecla arriba: Zoom +
Tecla abajo: Zoom -
Tecla derecha: girar la camara a la derecha
Tecla izquierda: girar la camara hacia la izquierda
Tecla ESC: Cerrar el programa
*/


//Manejo de la camara
GLdouble thethacamara=0;
GLdouble thRcamara=0;
GLdouble zoom=300;

static GLuint textureName[4];



//Conversion angulos a radianes
float d2r = 3.14159265 / 180.0;

//Camara se podra mover alrededor del objeto y tambien acercarse o alejarse
void camara(){
	thRcamara=thethacamara*d2r;
	gluLookAt(0+zoom*sin(thRcamara),80.0,-(300-zoom*cos(thRcamara)),0.0,0.0,-300.0,0,1,0);
}

void iluminacion(){
    //GLfloat mat_color [] = {1.0,0.0,1.0,1.0};
    GLfloat light_color [] = {1.0,1.0,1.0,1.0};
    GLfloat light_ambient [] = {0.0,0.0,0.0,1.0};
    //GLfloat normal [] = {0.0,1.0,0.0};
    GLfloat light_dir [] = {0.0,0.0,1.0,0.0};
     // Turn on OpenGL lighting.
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,light_color);
    glLightfv(GL_LIGHT0,GL_SPECULAR,light_color);
    
    //glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,mat_color);
    glLightfv(GL_LIGHT0,GL_POSITION,light_dir);
}


// ****************** FUNCIONES DE TEXTURA ******************

/*Esta Funcion void loadTextureFromFile(char *filename) de carga de imagenes fue obtenida de el
ejemplo en http://www.math.ucsd.edu/%7Esbuss/MathCG/OpenGLsoft/FourTextures/FourTextures.html
donde se obtuvo los archivos RgbImage.cpp y RgbImage.h
*/
void loadTextureFromFile(char *filename) {    
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);

	RgbImage theTexMap( filename );

	// Pixel alignment: each row is word aligned (aligned to a 4 byte boundary)
	//    Therefore, no need to call glPixelStore( GL_UNPACK_ALIGNMENT, ... );

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	gluBuild2DMipmaps(GL_TEXTURE_2D, 3,theTexMap.GetNumCols(), theTexMap.GetNumRows(), GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData() );
}


void cargarTexturas( char* filenames[] ){
	glGenTextures( 4, textureName );	// Load varias texturas en un arreglo
	for ( int i=0; i<4; i++ ) {
		glBindTexture(GL_TEXTURE_2D, textureName[i]);	// Texture #i is active now
		loadTextureFromFile( filenames[i] );			// Load texture #i
	}
}

void dibujarTablero(){
		 
	 glEnable(GL_TEXTURE_2D);
	 glBindTexture(GL_TEXTURE_2D, textureName[1]);
	 
	 /*glBegin(GL_QUADS);
	   glTexCoord2f(0.0, 0.0); glVertex3f(-50.0, -50.0, -250.0);
	   glTexCoord2f(0.0, 1.0); glVertex3f(-50.0, 50.0, -250.0);
	   glTexCoord2f(1.0, 1.0); glVertex3f(50.0, 50.0, -250.0);
	   glTexCoord2f(1.0, 0.0); glVertex3f(50.0, -50.0, -250.0);
	 glEnd();*/

	 glTranslatef(0.0,0.0,-300);
	 glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
glEnable(GL_TEXTURE_GEN_T);

	glutSolidTorus(5.0, 20.0, 50, 50);
	glDisable(GL_TEXTURE_GEN_T); //enable texture coordinate generation
glDisable(GL_TEXTURE_GEN_S);
	 glDisable(GL_TEXTURE_2D);
}

//Dibuja la casa, los ejes, y las líneas de matriz.
void dibujarescena(){ 
        
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//Limpio bit color y profundidad
	glLoadIdentity();
    
	iluminacion();//Defino iluminacion
    camara();//Coloco la camara

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glPushMatrix();
		dibujarTablero();
	glPopMatrix();

    glutSwapBuffers(); 
	glDisable(GL_TEXTURE_2D);
}

// define valores de del área a mostrar y ventana.
void escalar(GLsizei w, GLsizei h){
    GLfloat fAspect;
 
    // Prevent a divide by zero
    if(h == 0)
        h = 1;
 
    // Set Viewport to window dimensions
    glViewport(0, 0, w, h);
 
    // Calculate aspect ratio of the window
    fAspect = (GLfloat)w/(GLfloat)h;
 
    // Set the perspective coordinate system
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
 
    // field of view of 45 degrees, near and far planes 1.0 and 425
    gluPerspective(45.0f, fAspect, 1.0, 625.0);
 
    // Modelview matrix reset
    glMatrixMode(GL_MODELVIEW);
    glTranslatef(10.0,0.0,0.0); ///////////////////////////
    glLoadIdentity();
    /*gluLookAt(camarax,-50.0,0.0,0.0,0.0,-300.0,0,1,0);*/
    
}

// identifica acción y la ejecuta, según una tecla digitada por el usuario
void keyboard(unsigned char key,int x, int y){
    switch(key){

	//Salir del programa
    case 27:
        exit(0);
        break;
	}
}

//Usamos las teclas direccionales para manejar el zoom de la camara
void specialkey(int key,int x, int y){
    switch(key){
    //Mueve la camara a la izquierda
	case GLUT_KEY_LEFT :
		thethacamara+=10;
		break;
	//Mueve la camara a la derecha
	case GLUT_KEY_RIGHT:
		thethacamara-=10;
		break;

	//Mueve la camara hacia adelante
	case GLUT_KEY_DOWN:
		zoom+=10;
		break;

	//Mueve la camara hacia atras
	case GLUT_KEY_UP:
		zoom-=10;
		break;
	}
}



//Mediante esta funcion le decimos a openGL que cada 200ms redibuje la escena y cambie algunos parametros como la rotacion y traslacion
void TimerFunc(int value)
{
    glutPostRedisplay(); // Redibujo la escena

    glutTimerFunc(200, TimerFunc, 1);  //Disminuir para ir mas rapido
}

char* filenameArray[4] = { 
		"galaxia.bmp", 
		"LightningTexture.bmp",
		"IvyTexture.bmp",
		"RedLeavesTexture.bmp" 
};

//función principal que llama al resto de funciones y define parametros.
int main(int argc, char **argv){
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGBA | GLUT_DEPTH); // usando doble buffer
    glutInitWindowSize(700,700);        //definiendo tamaño de la ventana
    glutInitWindowPosition(400,50);		//Posicio inicial de la ventana
    glutCreateWindow("Toroide -Esfera - II Proy"); // Titulo del programa
    
    
    
	cargarTexturas( filenameArray );
	glClearColor(0.0,0.0,1.0,1.0);
    glutDisplayFunc(dibujarescena); // dibujando la escena principal
    glutTimerFunc(250, TimerFunc, 1); //Funcion timer para redibujar
    glutReshapeFunc(escalar); // llamando a la función que define el area ortogonal y viewport
	glutKeyboardFunc(keyboard); //llamandao a función que interpreta las acciones a realizar según la tecla digitada
	glutSpecialFunc(specialkey);// Teclas especiales
    glutMainLoop();
    
}


