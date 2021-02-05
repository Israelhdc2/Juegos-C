#include <iostream>
#include <conio.h>
#include <time.h>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

#define ESC 27
#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80

using namespace std;

//declarar una matriz para que en una de sus posiciones alamcene las pártes del cuerpo serpiente
int cuerpo[200][2];
//para almacenar los distintos espacios del cuerpo
int n=1;
int tam = 4;
int x=10, y=12;
char tecla;
int direccion = 3;
//coordenadas de la comida
int xc = 30, yc=15;
int velocidad=100;
int score=0;

int h=1;

struct serpiente{
	int guardar_puntaje;
};

void delay(int secs){
	
	for(int i = (time(NULL) + secs); time(NULL) != i; time(NULL));
	
}

void letras(){
	//S
	for(int i=0; i<3; i++){
		printf("\n");
		printf("\t");
		for(int j=0; j<3; j++){
			Sleep(30);
			printf("*");
		}
		printf("\n");
		if(i==0){
			printf("\t*");
		}
		if(i==1){
			printf("\t  *");
		}
	}
	printf("\t\t\t* *");
	printf("\n");
	//N
	for(int i=0; i<4; i++){
		Sleep(50);
		printf("\t");
		if(i==0){
			printf("** *	\t *");
		}
		if(i==1){
			printf("* **	\t***");
		}
		if(i==2){
			printf("*  *\t       * * *");
		}
		if(i==3){
			printf("*  *	\t***");
		}
		printf("\n");
	}
	printf("\t\t\t***");
	printf("\n");
	//A
	for(int i=0; i<5; i++){
		Sleep(50);
		printf("\t");
		if(i==0){
			printf("****	\t ***\t      *****");
		}
		if(i==1){
			printf("*  *	\t  ***\t     *******");
		}
		if(i==2){
			printf("****	\t   ***\t    ***   ***     ***");
		}
		if(i==3){
			printf("*  *	\t    ***\t   ***     ***   ****");
		}
		if(i==4){
			printf("*  *	\t     ********	    ********");
		}
		printf("\n");
	}
	printf("\t\t\t      ******	     ******");
	printf("\n");
	//K
	for(int i=0; i<5; i++){
		Sleep(50);
		printf("\t");
		if(i==0){
			printf("*   *");
		}
		if(i==1){
			printf("*  *");
		}
		if(i==2){
			printf("***");
		}
		if(i==3){
			printf("*  *");
		}
		if(i==4){
			printf("*   *");
		}
		printf("\n");
	}
	//E
	for(int i=0; i<3; i++){
		Sleep(50);
		printf("\n");
		printf("\t");
		for(int j=0; j<3; j++){
			printf("*");
		}
		printf("\n");
		if(i==0){
			printf("\t*");
		}
		if(i==1){
			printf("\t*");
		}
	}
}

void gotoxy(int x, int y){
	
	HANDLE hCon;
	COORD dwPos;
	
	dwPos.X = x;
	dwPos.Y = y;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hCon, dwPos);
	
}

void marco(){
	//codigo asci 
	for(int i=2; i<78; i++){
		//eje x
		gotoxy(i, 3);
		//Con esto le decimos al compilador que vamos a utilizar uno de los caracteres del codigo asci
		printf("%c", 205);
		gotoxy(i, 23); 
		printf("%c", 205);
	}
	for(int i=4; i<23; i++){
		//eje y
		gotoxy(2, i);
		printf("%c", 186);
		gotoxy(77, i);
		printf("%c", 186);
	}
	///esquinas
	gotoxy(2, 3);printf("%c", 201);
	gotoxy(2, 23);printf("%c", 200);
	gotoxy(77, 3);printf("%c", 187);
	gotoxy(77, 23);printf("%c", 188);
			
}

void guardar_posicion(){
	cuerpo[n][0] = x;
	cuerpo[n][1] = y;
	n++;
	if(n==tam) n=1;
}

void dibujar_cuerpo(){
	for(int i=1; i<tam; i++){
		gotoxy(cuerpo[i][0], cuerpo[i][1]);
		printf("*");
	}
}

void borrar(){
	for(int i=1; i<tam; i++){
		gotoxy(cuerpo[i][0], cuerpo[i][1]);
		printf(" ");
	}
}

void comida(){
	if(x==xc && y == yc){
		//para que no sea 0 y no quede fuera del rango
		xc = (rand()%73)+4;
		yc = (rand()%19)+4;
		//aumente el tamaño
		tam++;
		score += 10;
		//posicionar la comida
		gotoxy(xc, yc); printf("%c", 42);
	}
}

void teclear(){
	if(kbhit()){
		tecla = getch();
		switch(tecla){
			case ARRIBA:{
				if(direccion != 2)
				direccion=1;
				break;
			}
			case ABAJO:{
				if(direccion != 1)
				direccion=2;
				break;
			}
			case DERECHA:{
				if(direccion != 4)
				direccion = 3;
				break;
			}
			case IZQUIERDA:{
				if(direccion != 3)
				direccion=4;
				break;
			} 
		}
	}
}

bool game_over(){
	//3(choca con el margin de arriba) 2(margen izquierdo) 23(margen de abajo) 77(margen derecho)
	if(y==3 || y==23 || x==2 || x==77)
		return false;
	//si choca
	for(int j= tam-1; j>0; j--){
		if(cuerpo[j][0]==x && cuerpo[j][1]==y)
			return false; 
	}
	return true;	
}

void puntos(){
	gotoxy(3,1);
	printf("Puntaje: %d", score);
}

void cambiar_velocidad(){
	
	if(score==h*20){
		velocidad -= 10;
		h++;
	}
}

////////////////////////////////ARCHIVOS///////////////////////////////////

void escribir(int a, int b){
	serpiente es[b];
	FILE *archivo;
	archivo = fopen("snake.bin", "ab");
	if(archivo == NULL){
		cout << "NULL";
	}
	es[b].guardar_puntaje = a;
	fwrite(&es, sizeof(serpiente), 1, archivo);
	fclose(archivo);
	return;
}
void leer(){
	FILE* archivo;
	serpiente lee;
	archivo=fopen("snake.bin","rb");
	
	if(archivo==NULL){
		cout<<endl;
		cout<<" No existe archivo... "<<endl;
		cout<<"------------------------------------------------------------------";
		getch();
		return;
	}
	
	fseek(archivo,0,SEEK_SET);
	fread(&lee,sizeof(serpiente),1,archivo);
	while(!feof(archivo)){
		
		
		cout<<" Puntaje: "<<lee.guardar_puntaje<<endl;
		cout<<"============================================"<<endl;
	
		fread(&lee,sizeof(serpiente),1,archivo);
	}
	fclose(archivo);
	getch();
	return;	
}

int main(){ 
	int opcion;
	clock_t start, end; 
	start = clock(); 
			
	letras();
	
	//delay(2);
	
	printf("\n\tPulse una tecla para continuar...\n");
	
	getch();
	
	system("cls");
	
	while(true){	
	
		printf("\n\n\n\n\n");
		printf("\t\t\t1. Jugar\n");
		printf("\t\t\t2. Ver puntajes\n");
		printf("\t\t\t3. Salir\n");
		printf("\t\t\tEliga opci%cn: ", 162);
		cin >> opcion;
		system("cls");
		
		if(opcion == 1){
		
			printf("\n\n");
			marco();
			gotoxy(xc, yc); printf("%c", 42);
			while(tecla != ESC && game_over()){
				borrar();
				guardar_posicion();
				dibujar_cuerpo();
				comida();
				puntos();
				cambiar_velocidad();
				teclear();
				//
				teclear();
			
				if(direccion == 1) y--;
			
				if(direccion == 2) y++;
			
				if(direccion == 3) x++;
			
				if(direccion == 4) x--;
			
				Sleep(velocidad);
			}
			
			escribir(score, 0);
			end = clock();
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
			system("pause");
			system("cls");
		}
		else if(opcion == 2){
			leer();
			end = clock();
			printf("\n");
			system("pause");
			system("cls");
		}else if(opcion == 3){
			return 0;
		}else{
			printf("Opci%cn invalida", 162);
			system("pause");
			system("cls");
			continue;
		}
				
	}
	
}


