#include <iostream>
#include <string>
#include <conio.h>
#include <vector>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <colorwin.hpp>
using namespace std;
using namespace colorwin;
//--------------------------------------------Variables Generales-----------------------------------------
string palabra_original;
string palabra_mostrar;
/*Si se piensa cambiar el número de vidas tambien tiene que cambiarlas en la 
  funcion void Ganar() y void Perder()*/
int corazones=6;
int score=0;
int nivel=1;
char letra;
string nombre;
//--------------------------------------------Llamar Funciones--------------------------------------------
void gotoxy(int x,int y);
void Escenario();
void Ahorcado();
void Presentacion();
void Cargando();
int Menu();
string Palabras();
void Inicializar();
void Adivinar();
void Ganar();
void Perder();
void Creditos();
//--------------------------------------------Función Principal-------------------------------------
int main(){
	//Música
	char soundfile[]="Soundtrack.wav";
	cout<<PlaySound((LPCSTR)soundfile,NULL,SND_FILENAME|SND_ASYNC)<<endl;
	//Variables
	int opcion;
	//Proceso
	Ahorcado();
	Presentacion();
	do{
		opcion=Menu();
		switch(opcion){
			//JUGAR
			case 1:{
				system("cls");
				Escenario();
				Cargando();
				//system("pause");
				score=0;
				do{
					system("cls");
					Escenario();
					Inicializar();
					Adivinar();
					Ganar();
					nivel+=1;
				}while(corazones!=0);
				Perder();
				break;
			}
			//CREDITOS
			case 2:{
				system("cls");
				Creditos();
				Escenario();
				gotoxy(40,16);
				system("pause");
				break;
			}
			//SALIR
			case 3:{
				system("cls");
				Escenario();
				gotoxy(40,10);
				cout<<color(green)<<"Adios poliamigo..."<<endl;
				gotoxy(40,16);
				system("pause");
				break;
			}
		}
	}while(opcion!=3);
	return 0;
}
//----------------------------------------Función de Dibujo-----------------------------------------
//GOTOXY (posicionar en pantalla)
void gotoxy(int x,int y){  
	 HANDLE hcon;
     COORD dwPos;
     dwPos.X = x;
     dwPos.Y= y;
     hcon = GetStdHandle(STD_OUTPUT_HANDLE);
     SetConsoleCursorPosition(hcon,dwPos);
}
//--------------------------------------------Dibujos-------------------------------------------
//Pintar escenario
void Escenario(){
	char LH=205, LV=186;
	//Lineas horizontales
	for(int i=2;i<116;i++){
		//Horizontales arriba
		gotoxy(i,3);
		cout<<color(cyan)<<LH;
		//Horizontales abajo
		gotoxy(i,28);
		cout<<color(cyan)<<LH;
	}
	//lineas verticales
	for(int i=4;i<28;i++){
		//Verticales Derecha
		gotoxy(2,i);
		cout<<color(cyan)<<LV;
		//Verticales Izquierda
		gotoxy(116,i);
		cout<<color(cyan)<<LV;
	}
	char C1=201,C2=200,C3=187,C4=188;
	//Esquinas Izquierda
	gotoxy(2,3);
	cout<<color(cyan)<<C1;
	gotoxy(2,28);
	cout<<color(cyan)<<C2;
	//Esquinas Derecha
	gotoxy(116,3);
	cout<<color(cyan)<<C3;
	gotoxy(116,28);
	cout<<color(cyan)<<C4;
}
//Palabra Ahorcado
void Ahorcado_Palabra(){
	//Palabra Ahorcado
	gotoxy(25,5);
	cout<<color(green)<<"     $$                                                                  "<<endl;
	gotoxy(25,6);
	cout<<color(green)<<"    $  $      $   $    $$$$   $$$$$     $$$$     $$     $$$$     $$$$    "<<endl;
	gotoxy(25,7);
	cout<<color(green)<<"   $    $     $   $   $    $  $    $   $        $  $    $   $   $    $   "<<endl;
	gotoxy(25,8);
	cout<<color(green)<<"  $      $    $   $   $    $  $    $  $        $    $   $    $  $    $   "<<endl;
	gotoxy(25,9);
	cout<<color(green)<<"  $      $    $$$$$   $    $  $    $  $       $      $  $    $  $    $   "<<endl;
	gotoxy(25,10);
	cout<<color(green)<<"  $ $$$$ $    $   $   $    $  $$$$$   $       $ $$$$ $  $    $  $    $   "<<endl;
	gotoxy(25,11);
	cout<<color(green)<<"  $      $    $   $   $    $  $    $   $      $      $  $   $   $    $   "<<endl;
	gotoxy(25,12);
	cout<<color(green)<<"  $      $    $   $    $$$$   $    $    $$$$  $      $  $$$$     $$$$    "<<endl;
}
//Dibujo Ahorcado
void Ahorcado_Dibujo(){
	gotoxy(55,16);
	cout<<"------   "<<endl;
	gotoxy(55,17);
	cout<<"|   |    "<<endl;
	gotoxy(55,18);
	cout<<"|   o    "<<endl;
	gotoxy(55,19);
	cout<<"|  /|/   "<<endl;
	gotoxy(55,20);
	cout<<"|  / /   "<<endl;
	gotoxy(55,21);
	cout<<"|        "<<endl;
	gotoxy(55,22);
	cout<<"_________"<<endl;
}
//GAME OVER
void GameOver_Palabra(){
	gotoxy(4,5);
	cout<<color(red)<<"  $$$$$                                                               "<<endl;
	gotoxy(5,6);
	cout<<color(red)<<" $            $$     $     $  $$$$$     $$$$   $     $  $$$$$  $$$$$  "<<endl;
	gotoxy(6,7);
	cout<<color(red)<<"$            $  $    $$   $$  $        $    $  $     $  $      $    $ "<<endl;
	gotoxy(7,8);
	cout<<color(red)<<"$           $    $   $ $ $ $  $        $    $   $   $   $      $    $ "<<endl;
	gotoxy(8,9);
	cout<<color(red)<<"$    $$$$  $      $  $  $  $  $$$      $    $   $   $   $$$    $    $ "<<endl;
	gotoxy(9,10);
	cout<<color(red)<<"$       $  $ $$$$ $  $     $  $        $    $    $ $    $      $$$$$  "<<endl;
	gotoxy(10,11);
	cout<<color(red)<<" $     $   $      $  $     $  $        $    $    $ $    $      $    $ "<<endl;
	gotoxy(11,12);
	cout<<color(red)<<"  $$$$$    $      $  $     $  $$$$$     $$$$      $     $$$$$  $    $ "<<endl;
}
//Dibujo Ahorcado Grande
void Ahorcado_Dibujo_Grande(){
	gotoxy(82,6);
	cout<<"--------------------";
	for(int i=6;i<=10;i++){
		gotoxy(101,i);
		cout<<"|";
	}
	gotoxy(101,11);
	cout<<"o";
	for(int i=6;i<=24;i++){
		gotoxy(82,i);
		cout<<"|";
	}
	gotoxy(82,24);
	cout<<"--------------------------------";	
	for(int i=12;i<=14;i++){
		gotoxy(101,i);
		cout<<"|";
	}
	gotoxy(100,12);
	cout<<"|";
	gotoxy(102,12);
	cout<<"|";
	gotoxy(100,14);
	cout<<"|";
	gotoxy(102,14);
	cout<<"|";
	gotoxy(100,15);
	cout<<"|";
	gotoxy(102,15);
	cout<<"|";
}
//----------------------------------HUD(Presentación de Información)------------------------------
//Vidas
void Vidas(int corazones){
	//Coordenadas de la palabra Vidas
	gotoxy(2,1);
	cout<<"VIDAS: ";
	//Coordenadas borrar corazones
	for(int j=0;j<corazones;j++){
		gotoxy(9+j,1);
		cout<<" ";
	}
	//Coordenas imprimir corazones
	for(int i=0;i<corazones;i++){
		gotoxy(9+i,1);
		cout<<color(red)<<"\3";
	}
}
//Nivel
void Nivel(){
	gotoxy(25,1);
	cout<<"Nivel: "<<nivel;
}
//Mostrar Nombre
void Nombre(){
	gotoxy(55,1);
	cout<<"Nombre: ";
	for(int i=0;i<nombre.length();i++){
		gotoxy(63+i,1);
		cout<<" ";
	}
	gotoxy(63,1);
	cout<<nombre;
}
//Puntos
void Puntos(){
	gotoxy(100,1);
	cout<<"Puntaje: "<<score;
}
//HUD
void HUD(){
	//Vidas
	Vidas(corazones);
	cout<<"\n";
	//Puntos
	Puntos();
	cout<<"\n";
	//Nombre
	Nombre();
	cout<<"\n";
	//Nivel
	Nivel();
	cout<<"\n";
}
//-------------------------------------Funciones de Presentación------------------------------------
//Presentación
void Presentacion(){
	Escenario();
	Ahorcado_Palabra();
	gotoxy(40,14);
	cout<<color(cyan)<<"\tBienvenido Jugador"<<endl;
	gotoxy(40,16);
	cout<<color(blue)<<"Ingrese su nombre: ";
	//Condicion para que no acepte cadenas vacías
	do{
		gotoxy(59,16);
		getline(cin,nombre);
	}while(nombre.length()==0);
	//Coordenas imprimir simbolos
	for(int i=0;i<30;i++){
		gotoxy(40+i,18);
		cout<<color(green)<<"\4";
		Sleep(50);
	}
}
//Mostrar Presentación
void Mostrar_Presentacion(){
	Escenario();
	gotoxy(40,14);
	cout<<color(cyan)<<"\tBienvenido Jugador"<<endl;
	gotoxy(40,16);
	cout<<color(blue)<<"Ingrese su nombre: ";
	gotoxy(59,16);
	cout<<nombre;
	//Coordenas imprimir simbolos
	for(int i=0;i<30;i++){
		gotoxy(40+i,18);
		cout<<color(green)<<"\4";
	}
}
//Palabra ahorcado y Dibujo
void Ahorcado(){
	Escenario();
	//Palabra Ahorcado
	Ahorcado_Palabra();
	//Dibujo Ahorcado
	Ahorcado_Dibujo();
	//Mensaje Pausa
	gotoxy(25,25);
	system("pause");
	system("cls");
}
//Menu
int Menu(){
	int opc;
	system("cls");
	Ahorcado_Palabra();
	Mostrar_Presentacion();
	gotoxy(40,20);
	cout<<"1. Jugar"<<endl;
	gotoxy(40,21);
	cout<<"2. Creditos"<<endl;
	gotoxy(40,22);
	cout<<"3. Salir"<<endl;
	gotoxy(40,23);
	cout<<"Opcion -> ";
	cin>>opc;
	return opc;
}
//Creditos
void Creditos(){
	Escenario();
	gotoxy(40,10);
	cout<<"\t\tCreditos\n"<<endl;
	gotoxy(40,11);
	cout<<"Codigo: \t\tGinno Taimal"<<endl;
	gotoxy(40,12);
	cout<<"Codigo: \t\tLeonardo Asitimbaya"<<endl;
	gotoxy(40,13);
	cout<<"Decoracion: \t\tFausto Roman"<<endl;
	gotoxy(40,14);
	cout<<"Mejores Puntajes: \tKarla Vivas"<<endl;
	gotoxy(40,15);
	cout<<"Informe: \t\tFredviner Bailon"<<endl;
}
//------------------------------------Funciones para Jugar-----------------------------------------
//Rellenar variables palabra_original y palabra_mostrar
void Inicializar(){
	palabra_original=Palabras();
	//Convertir la palabra en minusculas
	for(int i=0; i<palabra_original.length(); i++){
		if(palabra_original[i]>='A' && palabra_original[i]<='Z'){
			palabra_original[i]+=32;
		}
	}
	//Sobreescribir palabra_mostrar
	for(int i=0; i<palabra_original.length(); i++){
		if(palabra_original[i]>='a' && palabra_original[i]<='z'){
			//Si es una letra colocara el guion
			palabra_mostrar+='-';
		}else{
			//Si es un caracter especial, permanecera el caracter especial
			palabra_mostrar+=palabra_original[i];
		}
	}
}
//Comparar letras con la palabra original
void Ingresar(char letra){
	bool LostVidas=true;
	//Comprobar letra con la palabra_original y reemplazar en la palabra_mostrar
	for(int i=0; i<palabra_original.length(); i++){
		if(letra==palabra_original[i]){
			LostVidas=false;
			palabra_mostrar[i]=letra;
		}
	}
	//Perder Vidas
	if(LostVidas==true){
		corazones--;
		//argumento 1: frecuencia o tono del sonido, y el argumento 2: duración.
		Beep(523,500);
	}
}
//Abrir archivo de texto - contenedor de palabras
vector<string> Coleccion_Palabras(){
	vector<string> palabras;
	string palabra;
	ifstream file_input_stream("Historial_de_Palabras.txt");
	while(file_input_stream>>palabra){
		palabras.push_back(palabra);
	}
	file_input_stream.close();
	return palabras;
}
//Dar un número Aleatorio
int Numero_Aleatorio(int a){
	srand(time(0));
	int numero_aleatorio=rand();
	return numero_aleatorio%a;
}
//Sacar una palabra aleatoria
string Palabras(){
	vector<string> palabras=Coleccion_Palabras();
	int numero_aleatorio=Numero_Aleatorio(palabras.size());
	return palabras[numero_aleatorio];
}
//Ingreso de la letra
void Adivinar(){
	while(corazones>0 && palabra_mostrar!=palabra_original){
		Escenario();
		HUD();
		//Palabra_Mostrar (------)
		gotoxy(20,13);
		cout<<"Adivina la Palabra:"<<endl;
		gotoxy(20,14);
		cout<<palabra_mostrar<<endl;
		//Letra Ingresada
		gotoxy(20,16);
		cout<<"Ingrese una letra:"<<endl;
		gotoxy(20,17);
		cin>>letra;
		Ingresar(letra);
		system("cls");
		switch(corazones){
			case 5:{
				gotoxy(70,24);
				cout<<"------------------------------------------";
				break;
			}
			case 4:{
				for(int i=6;i<=24;i++){
					gotoxy(70,i);
					cout<<"|";
				}
				gotoxy(70,24);
				cout<<"------------------------------------------";
				break;
			}
			case 3:{
				gotoxy(70,6);
				cout<<"--------------------";
				for(int i=6;i<=24;i++){
					gotoxy(70,i);
					cout<<"|";
				}
				gotoxy(70,24);
				cout<<"------------------------------------------";
				break;
			}
			case 2:{
				gotoxy(70,6);
				cout<<"--------------------";
				for(int i=6;i<=10;i++){
					gotoxy(89,i);
					cout<<"|";
				}
				for(int i=6;i<=24;i++){
					gotoxy(70,i);
					cout<<"|";
				}
				gotoxy(70,24);
				cout<<"------------------------------------------";
				break;
			}
			case 1:{
				gotoxy(70,6);
				cout<<"--------------------";
				for(int i=6;i<=10;i++){
					gotoxy(89,i);
					cout<<"|";
				}
				gotoxy(89,11);
				cout<<"o";
				for(int i=6;i<=24;i++){
					gotoxy(70,i);
					cout<<"|";
				}
				gotoxy(70,24);
				cout<<"------------------------------------------";	
				break;
			}
			case 0:{
				
				break;
			}
		}
	}
}
//Ganar
void Ganar(){
	if(corazones>0){
		system("cls");
		Escenario();
		gotoxy(40,8);
		cout<<"Palabra acertada"<<endl;
		gotoxy(40,9);
		cout<<color(green)<<palabra_mostrar<<endl;
		gotoxy(40,14);
		cout<<"Siguiente Nivel"<<endl;
		score+=10;
		corazones=6;
		palabra_mostrar.clear();
		gotoxy(40,25);
		system("pause");
	}
}
//Perder
void Perder(){
	system("cls");
	Escenario();
	GameOver_Palabra();
	gotoxy(25,18);
	cout<<color(blue)<<"La palabra era: "<<color(red)<<palabra_original<<endl;
	gotoxy(25,20);
	cout<<"El puntaje obtenido es: "<<color(green)<<score;
	palabra_mostrar.clear();
	corazones=6;
	nivel=1;
	Ahorcado_Dibujo_Grande();
	gotoxy(19,25);
	system("pause");
	system("cls");
}
//Pantalla de Cargando
void Cargando(){
	gotoxy(52,15);
	cout<<"Cargando..."<<endl;
	for(int i=0;i<100;i++){
		gotoxy(10+i,20);
		cout<<color(green)<<"\4";
		Sleep(10);
	}
	gotoxy(40,25);
	system("pause");
}
//
