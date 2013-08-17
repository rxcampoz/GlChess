#ifndef LUCES_H
#define LUCES_H

#include "glut.h"

float angulo_rotac_Y = 0.0;

bool activ0 = true;
bool activ1 = true;
bool activ2 = true;
bool activ3 = true;

//DEFINICION DE PARAMETROS Y VALORES DE LAS LUCES
float normal [] = {0.0,1.0,0.0};
float mat_emision [] = {0.0,0.0,0.0,1.0};			//No emite ningun color el material

//float ambientLight[4] = {0.2, 0.2, 0.2, 1.0};

//******* LUZ 0 (Blanca) ********
	//definimos los valores que tendran las componentes direccion y posicion de luz
	float luz0_ambient [] = {1.0,1.0,1.0,1.0};			//El color ambiental de la luz (si algo está fuera de la luz, no es iluminado)
	float luz0_difusa_especular [] = {1.0,1.0,1.0,1.0};	//color difuso y especular de la luz
	float luz0_posicion [] = {0.0,0.8,0.0,1.0};			//Posicion de la luz (centro sobre el robot)

	float spot0_dir [] = {0.0,-1.0,0.0};			//Vector de direccion de la luz
	float spot0_apertura = 25.0;					//Angulo de apertura de foco
	float spot0_atenuacion = 1.0;				//Factor de atenuacion de la luz

	float emision_foco0 [] = {0.9,0.9,0.9,1.0};


//******* LUZ 1 (Red - Rojo) ******** //Roja
	//definimos los valores que tendran las componentes direccion y posicion de luz
	float luz1_ambient [] = {1.0,0.0,0.0,1.0};			//El color ambiental de la luz (si algo está fuera de la luz, no es iluminado)
	float luz1_difusa_especular [] = {1.0,0.0,0.0,1.0};	//color difuso y especular de la luz
	float luz1_posicion [] = {0.0,0.8,0.4,1.0};			//Posicion de la luz

	float spot1_dir [] = {0.0,-1.0,0.0};			//Vector de direccion de la luz
	float spot1_apertura = 30.0;					//Angulo de apertura de foco
	float spot1_atenuacion = 0.5;				//Factor de atenuacion de la luz

	float emision_foco1 [] = {0.9,0.0,0.0,1.0};



//******* LUZ 2 (Green - Verde)********
	//definimos los valores que tendran las componentes direccion y posicion de luz
	float luz2_ambient [] = {0.0,0.1,0.0,1.0};			//El color ambiental de la luz (si algo está fuera de la luz, no es iluminado)
	float luz2_difusa_especular [] = {0.0,1.0,0.0,1.0};	//color difuso y especular de la luz
	float luz2_posicion [] = {0.4,0.8,-0.4,1.0};			//Posicion de la luz

	float spot2_dir [] = {0.0,-1.0,0.0};			//Vector de direccion de la luz
	float spot2_apertura = 20.0;					//Angulo de apertura de foco
	float spot2_atenuacion = 0.5;				//Factor de atenuacion de la luz

	float emision_foco2 [] = {0.0,0.9,0.0,1.0};



//******* LUZ 3 (Blue - Azul) ********
	//definimos los valores que tendran las componentes direccion y posicion de luz
	float luz3_ambient [] = {0.0,0.0,1.0,1.0};			//El color ambiental de la luz (si algo está fuera de la luz, no es iluminado)
	float luz3_difusa_especular [] = {0.0,0.0,1.0,1.0};	//color difuso y especular de la luz
	float luz3_posicion [] = {-0.4,0.8,-0.4,1.0};			//Posicion de la luz

	float spot3_dir [] = {0.0,-1.0,0.0};			//Vector de direccion de la luz
	float spot3_apertura = 20.0;					//Angulo de apertura de foco
	float spot3_atenuacion = 0.5;				//Factor de atenuacion de la luz

	float emision_foco3 [] = {0.0,0.0,0.9,1.0};

	
// ***** DEFINICION DE COLORES DE LOS MATERIALES ************

	float material_especularROJO[] ={0.75, 0.75, 0.75, 1.0};
	float material_ambientalROJO[] ={1.0, 0.0, 0.0, 1.0};
	float material_difusaROJO[] ={0.50, 0.50, 0.50, 1.0};
	float material_brilloROJO[] ={0.3};
	//float material_brilloROJO[] = 0.4; //128.0

	float material_especularNEGRUZCO[] ={0.235294118, 0.235294118, 0.235294118, 1.0};
	float material_ambientalNEGRUZCO[] ={0.25,0.25,0.25,1.0};
	float material_difusaNEGRUZCO[] ={0.50,0.50,0.50,1.0};
	float material_brilloNEGRUZCO[] ={0.4};

	float material_especularNEGRO[] ={0.01, 0.01, 0.01, 1.0};
	float material_ambientalNEGRO[] ={0.0,0.0,0.0,1.0};
	float material_difusaNEGRO[] ={0.50,0.50,0.50,1.0};
	float material_brilloNEGRO[] ={0.4};

	float material_especularPLATEADO[] ={0.835, 0.843, 0.824, 1.0};
	float material_ambientalPLATEADO[] ={0.85, 0.85, 0.85, 1.0};	
	float material_difusaPLATEADO[] ={0.50, 0.50, 0.50, 1.0};
	float material_brilloPLATEADO[] ={0.4};
	//float material_brillo[] = 0.4; //128.0

	float material_especularPLATEADOSCURO[] ={0.835, 0.843, 0.824, 1.0};
	float material_ambientalPLATEADOSCURO[] ={0.72, 0.72, 0.72, 1.0}; //***
	float material_difusaPLATEADOSCURO[] ={0.50, 0.50, 0.50, 1.0};
	float material_brilloPLATEADOSCURO[] ={0.7};

	float material_especularVERDE[] ={0.633, 0.727811, 0.633, 1.0};
	float material_ambientalVERDE[] ={0.0215, 0.1745, 0.0215, 1.0};
	float material_difusaVERDE[] ={0.07568, 0.61424, 0.07568, 1.0};
	float material_brilloVERDE[] ={0.4};

	float material_especularAMARILLO[] ={0.75, 0.75, 0.75, 1.0};
	float material_ambientalAMARILLO[] ={1.0, 1.0, 0.0, 1.0};
	float material_difusaAMARILLO[] ={0.50, 0.50, 0.50, 1.0};
	float material_brilloAMARILLO[] ={0.4};

	float material_especularOLIVA[] ={0.75, 0.75, 0.75, 1.0};
	float material_ambientalOLIVA[] ={0.73,0.73,0.73, 1.0};
	float material_difusaOLIVA[] ={0.50, 0.50, 0.50, 1.0};
	float material_brilloOLIVA[] ={0.2};
#endif                  /* LUCES_ */
