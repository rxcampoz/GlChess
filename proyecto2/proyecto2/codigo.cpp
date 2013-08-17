#include "global.h"


//Manejo de la camara
GLdouble thethacamara=30;
GLdouble thRcamara=0;
GLdouble zoom=0.2;

//Conversion angulos a radianes
float d2r = 3.14159265 / 180.0;

//Camara se podra mover alrededor del objeto y tambien acercarse o alejarse
void camara(){
	thRcamara=thethacamara*d2r;
	//gluLookAt(0.1,-0.1,0.1,0,0,0,0,0.5,0);
	//gluLookAt(0.2+zoom*sin(thRcamara),-0.2,(0.1-zoom*cos(thRcamara)),0.0,0.0,0.5,0,1,0);
	gluLookAt(cos(thRcamara)/2,-0.2,sin(thRcamara)/2,0.0,0.0,0,0,0.5,0);
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
		zoom+=0.1;
		break;

	//Mueve la camara hacia atras
	case GLUT_KEY_UP:
		zoom-=0.1;
		break;
	}
}


// ****************** FUNCIONES DE ILUMINACION ******************
void setMaterial(float especular[], float ambiental[], float difusa[], float brillo[]){
	// Se le asigna un color de material a las cosas y objetos presentes en la escena
	glMaterialfv(GL_FRONT, GL_SPECULAR, especular);
	glMaterialfv(GL_FRONT, GL_SHININESS, brillo);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambiental);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, difusa);
}

void setLuz(GLenum luzN, float especular[], float ambiental[], float difusa[], float apertura, float atenuacion){
	//glEnable(GL_LIGHTING);
	glLightfv(luzN, GL_AMBIENT, ambiental);
	glLightfv(luzN, GL_SPECULAR, especular);
	glLightfv(luzN, GL_DIFFUSE, difusa);	
	glLightf(luzN, GL_SPOT_CUTOFF, apertura);
	glLightf(luzN, GL_SPOT_EXPONENT, atenuacion);
	//glEnable(luzN);	
}

void luzActivarDesactivar(GLenum luzN, bool activar){
	//activa o desactiva la luz enviada como parametro
	if (activar==true){
		glEnable(luzN);
	}
	else{
		glDisable(luzN);
	}
}

void luzUbicarFuente(GLenum luzN, float posicion[], float direccion[], float foco_emision[], float mat_emision[]){
	//Ubica un cono que se muestra como cuerpo emisor de luz
	glPushMatrix();		
		glLightfv(luzN, GL_POSITION, posicion);
		glLightfv(luzN, GL_SPOT_DIRECTION, direccion);
		
		glTranslatef(posicion[0],posicion[1],posicion[2]);
		glColorMaterial(GL_FRONT,GL_EMISSION);
		
		glEnable(GL_COLOR_MATERIAL);
			glColor4fv(foco_emision);
				glPushMatrix();
					glRotatef(270, 1.0, 0.0, 0.0); //volteamos el cono
					glutSolidCone(0.04,0.08,25,20);
				glPopMatrix();
			glColor4fv(mat_emision);
		glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();
}
void iluminacionActDesact(bool act){
	if (act == true){
		glDisable(GL_LIGHTING);
	}
	else{
		glEnable(GL_LIGHTING);
	}
}


// ****************** FUNCIONES DE TEXTURA ******************
static GLuint nombresTexturas[7];
char* archivosTexturas[7] = {"chess.bmp","madera.bmp", "RedLeavesTexture.bmp", "IvyTexture.bmp", "WoodGrain.bmp", "planeta4.bmp", "planeta.bmp"};


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

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	gluBuild2DMipmaps(GL_TEXTURE_2D, 3,theTexMap.GetNumCols(), theTexMap.GetNumRows(), GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData() );
}


void cargarTexturas( char* filenames[] ){
	glGenTextures( 6, nombresTexturas );	// Load varias texturas en un arreglo
	for ( int i=0; i<7; i++ ) {
		glBindTexture(GL_TEXTURE_2D, nombresTexturas[i]);	// Texture #i is active now
		loadTextureFromFile( filenames[i] );			// Load texture #i
	}
}

void texturaActDesact(bool act){
	if (act == true){
		glEnable(GL_TEXTURE_2D);
	}
	else{
		glDisable(GL_TEXTURE_2D);
	}
}

// ****************** FUNCIONES DE DIBUJADO ******************

void dibujarTablero(){
	
	glPushMatrix();	//Frontal
		setMaterial(material_especularAMARILLO, material_ambientalAMARILLO, material_difusaAMARILLO, material_brilloAMARILLO);
		glColor3f(1,1,0);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, nombresTexturas[0]); //Aplicar texturas al piso del escenario
		
		glBegin(GL_QUADS);	//Top
			glTexCoord2i(0, 0);glVertex3f(-0.7,0.1,-0.7);			
			glTexCoord2i(1, 0);glVertex3f(-0.7,0.1,0.7);		
			glTexCoord2i(1, 1);glVertex3f(0.7,0.1,0.7);			
			glTexCoord2i(0, 1);glVertex3f(0.7,0.1,-0.7);			
		glEnd();

		glDisable(GL_TEXTURE_2D);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, nombresTexturas[1]); //Aplicar texturas al piso del escenario
		
		glBegin(GL_QUADS);	//Cara Frontal
			glTexCoord2i(0, 0); glVertex3f(-0.7,-0.1,0.7);			
			glTexCoord2i(1, 0); glVertex3f(-0.7,0.1,0.7);		
			glTexCoord2i(1, 1); glVertex3f(0.7,0.1,0.7);			
			glTexCoord2i(0, 1); glVertex3f(0.7,-0.1,0.7);			
		glEnd();

		glBegin(GL_QUADS);	//Far
			glTexCoord2i(0, 0);glVertex3f(-0.7,-0.1,-0.7);			
			glTexCoord2i(1, 0);glVertex3f(-0.7,0.1,-0.7);		
			glTexCoord2i(1, 1);glVertex3f(0.7,0.1,-0.7);			
			glTexCoord2i(0, 1);glVertex3f(0.7,-0.1,-0.7);			
		glEnd();

		glBegin(GL_QUADS); //Lado derecho
			glTexCoord2i(0, 0);glVertex3f(0.7,-0.1,-0.7);			
			glTexCoord2i(1, 0);glVertex3f(0.7,-0.1,0.7);		
			glTexCoord2i(1, 1);glVertex3f(0.7,0.1,0.7);			
			glTexCoord2i(0, 1);glVertex3f(0.7,0.1,-0.7);			
		glEnd();

		
		glBegin(GL_QUADS);	//Lado izquierdo
			glTexCoord2i(0, 0);glVertex3f(-0.7,-0.1,-0.7);			
			glTexCoord2i(1, 0);glVertex3f(-0.7,-0.1,0.7);		
			glTexCoord2i(1, 1);glVertex3f(-0.7,0.1,0.7);			
			glTexCoord2i(0, 1);glVertex3f(-0.7,0.1,-0.7);			
		glEnd();

		glBegin(GL_QUADS);	//Bottom
			glTexCoord2i(0, 0);glVertex3f(-0.7,-0.1,-0.7);			
			glTexCoord2i(1, 0);glVertex3f(-0.7,-0.1,0.7);		
			glTexCoord2i(1, 1);glVertex3f(0.7,-0.1,0.7);			
			glTexCoord2i(0, 1);glVertex3f(0.7,-0.1,-0.7);			
		glEnd();
		
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void dibujarESfera(){
	//Objeto para representar la esfera
	GLUquadricObj * qEsfera = gluNewQuadric(); // crea un objeto cuadrático
	gluQuadricDrawStyle(qEsfera, GLU_FILL); //estilo alámbrico
	setMaterial(material_especularROJO, material_ambientalROJO, material_difusaROJO, material_brilloROJO);
	glColor3f(1.0,0.0,0.0); //fondo con textura

	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, nombresTexturas[2]); //textura de placa metalica
		gluQuadricTexture(qEsfera,GL_TRUE);
		glTranslatef (-0.65, 0.2, 0.0);
		gluSphere (qEsfera, 0.1, 15, 15);
		glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void dibujarCilindro(){
	//Objeto para representar la esfera
	GLUquadricObj * qCilindro = gluNewQuadric(); // crea un objeto cuadrático
	gluQuadricDrawStyle(qCilindro, GLU_FILL); //estilo alámbrico
	setMaterial(material_especularVERDE, material_ambientalVERDE, material_difusaVERDE, material_brilloVERDE);
	glColor3f(0.0,1.0,0.0); //fondo con textura

	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, nombresTexturas[3]); //textura de placa metalica
		gluQuadricTexture(qCilindro,GL_TRUE);
		glTranslatef (-0.65, 0.3, 0.3);
		//gluSphere (qCilindro, 0.1, 15, 15);
		glRotatef(90,0.5,0,0);
		gluCylinder(qCilindro,0.1,0.1,0.2,15,15);
		glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void dibujarDisco(){
	//Objeto para representar la esfera
	GLUquadricObj * qCilindro = gluNewQuadric(); // crea un objeto cuadrático
	gluQuadricDrawStyle(qCilindro, GLU_FILL); //estilo alámbrico
	setMaterial(material_especularOLIVA, material_ambientalOLIVA, material_difusaOLIVA, material_brilloOLIVA);
	glColor3f(1.0,1.0,0.6); //fondo con textura

	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, nombresTexturas[4]); //textura de placa metalica
		gluQuadricTexture(qCilindro,GL_TRUE);
		glTranslatef (-0.65, 0.3, 0.6);
		//gluSphere (qCilindro, 0.1, 15, 15);
		//glRotatef(90,0.5,0,0);
		//gluCylinder(qCilindro,0.1,0.1,0.2,15,15);
		gluDisk(qCilindro,0.05,0.15,15,15);
		glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void dibujarEscena(){
	dibujarTablero();
	dibujarESfera();
	dibujarCilindro();
	dibujarDisco();
}

void initgl(){
	
	cargarTexturas(archivosTexturas);
	glClearDepth(1.0f);			// Profundidad del buffer de profundidad. Lo que esta cerca se ve encima de lo que esta lejos.
	glDepthFunc(GL_LEQUAL);		// Comparacion del buffer de profundidad.  
	glEnable(GL_DEPTH_TEST);	// Habilita test de profundidad.
	glClearColor(0,0,0,1.0f);	// Color del fondo. Color con el que se borra la pantalla.
	glShadeModel(GL_SMOOTH);     // Smooth shading. Renderizado suave
	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Calculos de Perspectiva
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_FALSE);

	setLuz(GL_LIGHT0, luz0_difusa_especular, luz0_ambient, luz0_difusa_especular, spot0_apertura, spot0_atenuacion);
	setLuz(GL_LIGHT1, luz1_difusa_especular, luz1_ambient, luz1_difusa_especular, spot1_apertura, spot1_atenuacion);
	setLuz(GL_LIGHT2, luz2_difusa_especular, luz2_ambient, luz2_difusa_especular, spot2_apertura, spot2_atenuacion);
	setLuz(GL_LIGHT3, luz3_difusa_especular, luz3_ambient, luz3_difusa_especular, spot3_apertura, spot3_atenuacion);

	//Iniciamos con todas las luces activadas
	luzActivarDesactivar(GL_LIGHT0, true);
	luzActivarDesactivar(GL_LIGHT1, true);	
	luzActivarDesactivar(GL_LIGHT2, true);
	luzActivarDesactivar(GL_LIGHT3, true);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
}


void display(){
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glPushMatrix();
		luzUbicarFuente(GL_LIGHT0, luz0_posicion, spot0_dir, emision_foco0, mat_emision);
		luzUbicarFuente(GL_LIGHT1, luz1_posicion, spot1_dir, emision_foco1, mat_emision);
		luzUbicarFuente(GL_LIGHT2, luz2_posicion, spot2_dir, emision_foco2, mat_emision);	
		luzUbicarFuente(GL_LIGHT3, luz3_posicion, spot3_dir, emision_foco3, mat_emision);
	glPopMatrix();
	
	glLoadIdentity();
	

	camara();
	
	glPushMatrix();
		glScalef(0.5,0.5,0.5);

		dibujarEscena();
	glPopMatrix();
	
	glFlush();//resetea los valores de las variables
    glutSwapBuffers();
	glDisable(GL_TEXTURE_2D);
}

void keyboard(unsigned char key, int x, int y){
	int cuenta=0;

    switch(key){

		case 'z':   // luz0			
			if (activ0 == true){
				activ0 = false;
			}else{
				activ0 = true;
			}
			luzActivarDesactivar(GL_LIGHT0, activ0);
			break;

		case 'x':   // luz1
			if (activ1 == true){
				activ1 = false;
			}else{
				activ1 = true;
			}
			luzActivarDesactivar(GL_LIGHT1, activ1);
			break;

		case 'c':   // luz2
			if (activ2 == true){
				activ2 = false;
			}else{
				activ2 = true;
			}
			luzActivarDesactivar(GL_LIGHT2, activ2);
			break;

		case 'v':   // luz3
			if (activ3 == true){
				activ3 = false;
			}else{
				activ3 = true;
			}
			luzActivarDesactivar(GL_LIGHT3, activ3);
			break;

		case 'a' : //activar ilumincacion
			iluminacionActDesact(true);
			break;

		case 's' : //apagar iluminacion
			iluminacionActDesact(false);
			break;
		
		case 27:   // escape
			exit(0);
			break;
    }
}


//Mediante esta funcion le decimos a openGL que cada 200ms redibuje la escena y cambie algunos parametros como la rotacion y traslacion
void TimerFunc(int value)
{
    glutPostRedisplay(); // Redibujo la escena
    glutTimerFunc(200, TimerFunc, 1);  //Disminuir para ir mas rapido
}

int main(int argc, char **argv){

	glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGBA | GLUT_DEPTH); // usando doble buffer
    glutInitWindowSize(700,700);        //definiendo tamaño de la ventana
    glutInitWindowPosition(400,50);		//Posicio inicial de la ventana
    glutCreateWindow("Toroide -Esfera - II Proy"); // Titulo del programa
    
    initgl();					//valores de inicio
    //glClearColor(0.0,0.0,1.0,1.0);

    glutDisplayFunc(display); // dibujando la escena principal
    glutTimerFunc(250, TimerFunc, 1); //Funcion timer para redibujar
    //glutReshapeFunc(escalar); // llamando a la función que define el area ortogonal y viewport
	glutKeyboardFunc(keyboard); //llamandao a función que interpreta las acciones a realizar según la tecla digitada
	glutSpecialFunc(specialkey);// Teclas especiales
    glutMainLoop();
}