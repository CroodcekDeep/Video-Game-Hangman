<!-- Deber: Seleccionar un proyecto previo de código y crear un README.md utilizando MarkDown -->

# **Project: Videogame Hangman**

## Introduction
Hangman (also called Hanged Man) is a pencil and paper guessing game for two or more players. One player thinks of a word, phrase or sentence and the other tries to guess it based on what he suggests with letters or within a certain number of possibilities.

## Tech Stack

**Programming Language:** C++

**IDE:** DevC++

## Introduction

## Libraries Used
```C++
#include <iostream>
#include <string>
#include <conio.h>
#include <vector>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <colorwin.hpp>
```

## Functions

### Gotoxy

In charge of positioning the items on the screen.
```C++
void gotoxy(int x,int y){  
	 HANDLE hcon;
     COORD dwPos;
     dwPos.X = x;
     dwPos.Y= y;
     hcon = GetStdHandle(STD_OUTPUT_HANDLE);
     SetConsoleCursorPosition(hcon,dwPos);
}
```
### Lifes
Place the hearts of life on the screen.
```C++
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
```

### Initialize the words
Extract the words from the text file and replace the values of the variables: `palabra_original` and `palabra_mostrar`.

```C++
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
```

### Compare the words
If the entered letter is correct, it will replace the letter in the word to guess. Else, it lowers the life counter.

```C++
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
```

### Open text file
Extract the words from the text file.

```C++
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
```

### Random number
Returns the number at random.

```C++
//Dar un número Aleatorio
int Numero_Aleatorio(int a){
	srand(time(0));
	int numero_aleatorio=rand();
	return numero_aleatorio%a;
}
```

### Extract random word
Select a word from the text file at random.

```C++
//Sacar una palabra aleatoria
string Palabras(){
	vector<string> palabras=Coleccion_Palabras();
	int numero_aleatorio=Numero_Aleatorio(palabras.size());
	return palabras[numero_aleatorio];
}
```

### Win
If you win, the score increases and lives are regenerated.

```C++
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
```

### Lose
If he loses, he regenerates lives and returns to level 1.

```C++
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
```

## Example
![Pantalla de Inicio](https://southcentralus1-mediap.svc.ms/transform/thumbnail?provider=spo&inputFormat=png&cs=fFNQTw&docid=https%3A%2F%2Fepnecuador-my.sharepoint.com%3A443%2F_api%2Fv2.0%2Fdrives%2Fb!h5-hxdKS80W1ueq4mR_YxWQ8z4XhlrdIubUiYLMYKTQGt6zdaNN8Q7TcxFR7P6A3%2Fitems%2F01FI2B4E3N67P2RV7OBBH3AYOOFAN4CDWH%3Fversion%3DPublished&access_token=eyJ0eXAiOiJKV1QiLCJhbGciOiJub25lIn0.eyJhdWQiOiIwMDAwMDAwMy0wMDAwLTBmZjEtY2UwMC0wMDAwMDAwMDAwMDAvZXBuZWN1YWRvci1teS5zaGFyZXBvaW50LmNvbUA2ODJhNGU2YS1hNzdmLTQ5NTgtYTNhYy05ZTI2NmQxOGFhMzciLCJpc3MiOiIwMDAwMDAwMy0wMDAwLTBmZjEtY2UwMC0wMDAwMDAwMDAwMDAiLCJuYmYiOiIxNjM0MTU4Nzk5IiwiZXhwIjoiMTYzNDE4MDM5OSIsImVuZHBvaW50dXJsIjoibEt4SG1XSk91RWxjUmZOUlFuZ1JYTzBTWFBuQzgvUmRHNHNSMU9PcFJ0az0iLCJlbmRwb2ludHVybExlbmd0aCI6IjEyMCIsImlzbG9vcGJhY2siOiJUcnVlIiwidmVyIjoiaGFzaGVkcHJvb2Z0b2tlbiIsInNpdGVpZCI6Ill6VmhNVGxtT0RjdE9USmtNaTAwTldZekxXSTFZamt0WldGaU9EazVNV1prT0dNMSIsInNpZ25pbl9zdGF0ZSI6IltcImttc2lcIl0iLCJuYW1laWQiOiIwIy5mfG1lbWJlcnNoaXB8Z2lubm8udGFpbWFsQGVwbi5lZHUuZWMiLCJuaWkiOiJtaWNyb3NvZnQuc2hhcmVwb2ludCIsImlzdXNlciI6InRydWUiLCJjYWNoZWtleSI6IjBoLmZ8bWVtYmVyc2hpcHwxMDAzMDAwMGFlMzE0YWYzQGxpdmUuY29tIiwic2Vzc2lvbmlkIjoiZGRjNjQxZjMtYzk3NS00ZTgzLTg1NzAtYmRkN2RhMzIwZDE2IiwidHQiOiIwIiwidXNlUGVyc2lzdGVudENvb2tpZSI6IjMiLCJpcGFkZHIiOiIyMDAuMTI1LjI1MC41NyJ9.MGZZY2hJVk42aUhnVDlpRnFLTy84Z0NxNHBVT1JvSWZiVXMyYlVUY0hlUT0&cTag=%22c%3A%7BA8DFF76D-EED7-4F08-B061-CE281BC10EC7%7D%2C1%22&encodeFailures=1&width=1319&height=614&srcWidth=&srcHeight=)

![Pantalla de Opciones](https://southcentralus1-mediap.svc.ms/transform/thumbnail?provider=spo&inputFormat=png&cs=fFNQTw&docid=https%3A%2F%2Fepnecuador-my.sharepoint.com%3A443%2F_api%2Fv2.0%2Fdrives%2Fb!h5-hxdKS80W1ueq4mR_YxWQ8z4XhlrdIubUiYLMYKTQGt6zdaNN8Q7TcxFR7P6A3%2Fitems%2F01FI2B4E7KNKU3JPET7ZGZX7DQVTNWCLZI%3Fversion%3DPublished&access_token=eyJ0eXAiOiJKV1QiLCJhbGciOiJub25lIn0.eyJhdWQiOiIwMDAwMDAwMy0wMDAwLTBmZjEtY2UwMC0wMDAwMDAwMDAwMDAvZXBuZWN1YWRvci1teS5zaGFyZXBvaW50LmNvbUA2ODJhNGU2YS1hNzdmLTQ5NTgtYTNhYy05ZTI2NmQxOGFhMzciLCJpc3MiOiIwMDAwMDAwMy0wMDAwLTBmZjEtY2UwMC0wMDAwMDAwMDAwMDAiLCJuYmYiOiIxNjM0MTU4Nzk5IiwiZXhwIjoiMTYzNDE4MDM5OSIsImVuZHBvaW50dXJsIjoibEt4SG1XSk91RWxjUmZOUlFuZ1JYTzBTWFBuQzgvUmRHNHNSMU9PcFJ0az0iLCJlbmRwb2ludHVybExlbmd0aCI6IjEyMCIsImlzbG9vcGJhY2siOiJUcnVlIiwidmVyIjoiaGFzaGVkcHJvb2Z0b2tlbiIsInNpdGVpZCI6Ill6VmhNVGxtT0RjdE9USmtNaTAwTldZekxXSTFZamt0WldGaU9EazVNV1prT0dNMSIsInNpZ25pbl9zdGF0ZSI6IltcImttc2lcIl0iLCJuYW1laWQiOiIwIy5mfG1lbWJlcnNoaXB8Z2lubm8udGFpbWFsQGVwbi5lZHUuZWMiLCJuaWkiOiJtaWNyb3NvZnQuc2hhcmVwb2ludCIsImlzdXNlciI6InRydWUiLCJjYWNoZWtleSI6IjBoLmZ8bWVtYmVyc2hpcHwxMDAzMDAwMGFlMzE0YWYzQGxpdmUuY29tIiwic2Vzc2lvbmlkIjoiZGRjNjQxZjMtYzk3NS00ZTgzLTg1NzAtYmRkN2RhMzIwZDE2IiwidHQiOiIwIiwidXNlUGVyc2lzdGVudENvb2tpZSI6IjMiLCJpcGFkZHIiOiIyMDAuMTI1LjI1MC41NyJ9.MGZZY2hJVk42aUhnVDlpRnFLTy84Z0NxNHBVT1JvSWZiVXMyYlVUY0hlUT0&cTag=%22c%3A%7BB4A96AEA-93BC-4DFE-9BFC-70ACDB612F28%7D%2C1%22&encodeFailures=1&width=1319&height=614&srcWidth=&srcHeight=)

![Interfaz de Juego - Sección Adivinar](https://southcentralus1-mediap.svc.ms/transform/thumbnail?provider=spo&inputFormat=png&cs=fFNQTw&docid=https%3A%2F%2Fepnecuador-my.sharepoint.com%3A443%2F_api%2Fv2.0%2Fdrives%2Fb!h5-hxdKS80W1ueq4mR_YxWQ8z4XhlrdIubUiYLMYKTQGt6zdaNN8Q7TcxFR7P6A3%2Fitems%2F01FI2B4E3DCJEVJDI2QZBIERPMHMFVF6XU%3Fversion%3DPublished&access_token=eyJ0eXAiOiJKV1QiLCJhbGciOiJub25lIn0.eyJhdWQiOiIwMDAwMDAwMy0wMDAwLTBmZjEtY2UwMC0wMDAwMDAwMDAwMDAvZXBuZWN1YWRvci1teS5zaGFyZXBvaW50LmNvbUA2ODJhNGU2YS1hNzdmLTQ5NTgtYTNhYy05ZTI2NmQxOGFhMzciLCJpc3MiOiIwMDAwMDAwMy0wMDAwLTBmZjEtY2UwMC0wMDAwMDAwMDAwMDAiLCJuYmYiOiIxNjM0MTU4Nzk5IiwiZXhwIjoiMTYzNDE4MDM5OSIsImVuZHBvaW50dXJsIjoibEt4SG1XSk91RWxjUmZOUlFuZ1JYTzBTWFBuQzgvUmRHNHNSMU9PcFJ0az0iLCJlbmRwb2ludHVybExlbmd0aCI6IjEyMCIsImlzbG9vcGJhY2siOiJUcnVlIiwidmVyIjoiaGFzaGVkcHJvb2Z0b2tlbiIsInNpdGVpZCI6Ill6VmhNVGxtT0RjdE9USmtNaTAwTldZekxXSTFZamt0WldGaU9EazVNV1prT0dNMSIsInNpZ25pbl9zdGF0ZSI6IltcImttc2lcIl0iLCJuYW1laWQiOiIwIy5mfG1lbWJlcnNoaXB8Z2lubm8udGFpbWFsQGVwbi5lZHUuZWMiLCJuaWkiOiJtaWNyb3NvZnQuc2hhcmVwb2ludCIsImlzdXNlciI6InRydWUiLCJjYWNoZWtleSI6IjBoLmZ8bWVtYmVyc2hpcHwxMDAzMDAwMGFlMzE0YWYzQGxpdmUuY29tIiwic2Vzc2lvbmlkIjoiZGRjNjQxZjMtYzk3NS00ZTgzLTg1NzAtYmRkN2RhMzIwZDE2IiwidHQiOiIwIiwidXNlUGVyc2lzdGVudENvb2tpZSI6IjMiLCJpcGFkZHIiOiIyMDAuMTI1LjI1MC41NyJ9.MGZZY2hJVk42aUhnVDlpRnFLTy84Z0NxNHBVT1JvSWZiVXMyYlVUY0hlUT0&cTag=%22c%3A%7B54491263-1A8D-4286-8245-EC3B0B52FAF4%7D%2C1%22&encodeFailures=1&width=1319&height=614&srcWidth=&srcHeight=)

![Ganar - Parte 1](https://southcentralus1-mediap.svc.ms/transform/thumbnail?provider=spo&inputFormat=png&cs=fFNQTw&docid=https%3A%2F%2Fepnecuador-my.sharepoint.com%3A443%2F_api%2Fv2.0%2Fdrives%2Fb!h5-hxdKS80W1ueq4mR_YxWQ8z4XhlrdIubUiYLMYKTQGt6zdaNN8Q7TcxFR7P6A3%2Fitems%2F01FI2B4EYDRGLGAXMKVNALAFQRH4LK5TGH%3Fversion%3DPublished&access_token=eyJ0eXAiOiJKV1QiLCJhbGciOiJub25lIn0.eyJhdWQiOiIwMDAwMDAwMy0wMDAwLTBmZjEtY2UwMC0wMDAwMDAwMDAwMDAvZXBuZWN1YWRvci1teS5zaGFyZXBvaW50LmNvbUA2ODJhNGU2YS1hNzdmLTQ5NTgtYTNhYy05ZTI2NmQxOGFhMzciLCJpc3MiOiIwMDAwMDAwMy0wMDAwLTBmZjEtY2UwMC0wMDAwMDAwMDAwMDAiLCJuYmYiOiIxNjM0MTU4Nzk5IiwiZXhwIjoiMTYzNDE4MDM5OSIsImVuZHBvaW50dXJsIjoibEt4SG1XSk91RWxjUmZOUlFuZ1JYTzBTWFBuQzgvUmRHNHNSMU9PcFJ0az0iLCJlbmRwb2ludHVybExlbmd0aCI6IjEyMCIsImlzbG9vcGJhY2siOiJUcnVlIiwidmVyIjoiaGFzaGVkcHJvb2Z0b2tlbiIsInNpdGVpZCI6Ill6VmhNVGxtT0RjdE9USmtNaTAwTldZekxXSTFZamt0WldGaU9EazVNV1prT0dNMSIsInNpZ25pbl9zdGF0ZSI6IltcImttc2lcIl0iLCJuYW1laWQiOiIwIy5mfG1lbWJlcnNoaXB8Z2lubm8udGFpbWFsQGVwbi5lZHUuZWMiLCJuaWkiOiJtaWNyb3NvZnQuc2hhcmVwb2ludCIsImlzdXNlciI6InRydWUiLCJjYWNoZWtleSI6IjBoLmZ8bWVtYmVyc2hpcHwxMDAzMDAwMGFlMzE0YWYzQGxpdmUuY29tIiwic2Vzc2lvbmlkIjoiZGRjNjQxZjMtYzk3NS00ZTgzLTg1NzAtYmRkN2RhMzIwZDE2IiwidHQiOiIwIiwidXNlUGVyc2lzdGVudENvb2tpZSI6IjMiLCJpcGFkZHIiOiIyMDAuMTI1LjI1MC41NyJ9.MGZZY2hJVk42aUhnVDlpRnFLTy84Z0NxNHBVT1JvSWZiVXMyYlVUY0hlUT0&cTag=%22c%3A%7B60968903-8A5D-40AB-B016-113F16AECCC7%7D%2C1%22&encodeFailures=1&width=1319&height=614&srcWidth=&srcHeight=)

![Ganar - Parte 2](https://southcentralus1-mediap.svc.ms/transform/thumbnail?provider=spo&inputFormat=png&cs=fFNQTw&docid=https%3A%2F%2Fepnecuador-my.sharepoint.com%3A443%2F_api%2Fv2.0%2Fdrives%2Fb!h5-hxdKS80W1ueq4mR_YxWQ8z4XhlrdIubUiYLMYKTQGt6zdaNN8Q7TcxFR7P6A3%2Fitems%2F01FI2B4E3XYWVHGGHVHBFKJ2PDKGSBTS3S%3Fversion%3DPublished&access_token=eyJ0eXAiOiJKV1QiLCJhbGciOiJub25lIn0.eyJhdWQiOiIwMDAwMDAwMy0wMDAwLTBmZjEtY2UwMC0wMDAwMDAwMDAwMDAvZXBuZWN1YWRvci1teS5zaGFyZXBvaW50LmNvbUA2ODJhNGU2YS1hNzdmLTQ5NTgtYTNhYy05ZTI2NmQxOGFhMzciLCJpc3MiOiIwMDAwMDAwMy0wMDAwLTBmZjEtY2UwMC0wMDAwMDAwMDAwMDAiLCJuYmYiOiIxNjM0MTU4Nzk5IiwiZXhwIjoiMTYzNDE4MDM5OSIsImVuZHBvaW50dXJsIjoibEt4SG1XSk91RWxjUmZOUlFuZ1JYTzBTWFBuQzgvUmRHNHNSMU9PcFJ0az0iLCJlbmRwb2ludHVybExlbmd0aCI6IjEyMCIsImlzbG9vcGJhY2siOiJUcnVlIiwidmVyIjoiaGFzaGVkcHJvb2Z0b2tlbiIsInNpdGVpZCI6Ill6VmhNVGxtT0RjdE9USmtNaTAwTldZekxXSTFZamt0WldGaU9EazVNV1prT0dNMSIsInNpZ25pbl9zdGF0ZSI6IltcImttc2lcIl0iLCJuYW1laWQiOiIwIy5mfG1lbWJlcnNoaXB8Z2lubm8udGFpbWFsQGVwbi5lZHUuZWMiLCJuaWkiOiJtaWNyb3NvZnQuc2hhcmVwb2ludCIsImlzdXNlciI6InRydWUiLCJjYWNoZWtleSI6IjBoLmZ8bWVtYmVyc2hpcHwxMDAzMDAwMGFlMzE0YWYzQGxpdmUuY29tIiwic2Vzc2lvbmlkIjoiZGRjNjQxZjMtYzk3NS00ZTgzLTg1NzAtYmRkN2RhMzIwZDE2IiwidHQiOiIwIiwidXNlUGVyc2lzdGVudENvb2tpZSI6IjMiLCJpcGFkZHIiOiIyMDAuMTI1LjI1MC41NyJ9.MGZZY2hJVk42aUhnVDlpRnFLTy84Z0NxNHBVT1JvSWZiVXMyYlVUY0hlUT0&cTag=%22c%3A%7B73AAC577-F518-4A38-A4E9-E351A419CB72%7D%2C1%22&encodeFailures=1&width=1319&height=614&srcWidth=&srcHeight=)

![Perder - Parte 1](https://southcentralus1-mediap.svc.ms/transform/thumbnail?provider=spo&inputFormat=png&cs=fFNQTw&docid=https%3A%2F%2Fepnecuador-my.sharepoint.com%3A443%2F_api%2Fv2.0%2Fdrives%2Fb!h5-hxdKS80W1ueq4mR_YxWQ8z4XhlrdIubUiYLMYKTQGt6zdaNN8Q7TcxFR7P6A3%2Fitems%2F01FI2B4E5CWXRXQPSGCFFYQBV6KFCXXPHS%3Fversion%3DPublished&access_token=eyJ0eXAiOiJKV1QiLCJhbGciOiJub25lIn0.eyJhdWQiOiIwMDAwMDAwMy0wMDAwLTBmZjEtY2UwMC0wMDAwMDAwMDAwMDAvZXBuZWN1YWRvci1teS5zaGFyZXBvaW50LmNvbUA2ODJhNGU2YS1hNzdmLTQ5NTgtYTNhYy05ZTI2NmQxOGFhMzciLCJpc3MiOiIwMDAwMDAwMy0wMDAwLTBmZjEtY2UwMC0wMDAwMDAwMDAwMDAiLCJuYmYiOiIxNjM0MTU4Nzk5IiwiZXhwIjoiMTYzNDE4MDM5OSIsImVuZHBvaW50dXJsIjoibEt4SG1XSk91RWxjUmZOUlFuZ1JYTzBTWFBuQzgvUmRHNHNSMU9PcFJ0az0iLCJlbmRwb2ludHVybExlbmd0aCI6IjEyMCIsImlzbG9vcGJhY2siOiJUcnVlIiwidmVyIjoiaGFzaGVkcHJvb2Z0b2tlbiIsInNpdGVpZCI6Ill6VmhNVGxtT0RjdE9USmtNaTAwTldZekxXSTFZamt0WldGaU9EazVNV1prT0dNMSIsInNpZ25pbl9zdGF0ZSI6IltcImttc2lcIl0iLCJuYW1laWQiOiIwIy5mfG1lbWJlcnNoaXB8Z2lubm8udGFpbWFsQGVwbi5lZHUuZWMiLCJuaWkiOiJtaWNyb3NvZnQuc2hhcmVwb2ludCIsImlzdXNlciI6InRydWUiLCJjYWNoZWtleSI6IjBoLmZ8bWVtYmVyc2hpcHwxMDAzMDAwMGFlMzE0YWYzQGxpdmUuY29tIiwic2Vzc2lvbmlkIjoiZGRjNjQxZjMtYzk3NS00ZTgzLTg1NzAtYmRkN2RhMzIwZDE2IiwidHQiOiIwIiwidXNlUGVyc2lzdGVudENvb2tpZSI6IjMiLCJpcGFkZHIiOiIyMDAuMTI1LjI1MC41NyJ9.MGZZY2hJVk42aUhnVDlpRnFLTy84Z0NxNHBVT1JvSWZiVXMyYlVUY0hlUT0&cTag=%22c%3A%7B78E3B5A2-463E-4B11-8806-BE51457BBCF2%7D%2C1%22&encodeFailures=1&width=1319&height=614&srcWidth=&srcHeight=)

![Perder - Parte 2](https://southcentralus1-mediap.svc.ms/transform/thumbnail?provider=spo&inputFormat=png&cs=fFNQTw&docid=https%3A%2F%2Fepnecuador-my.sharepoint.com%3A443%2F_api%2Fv2.0%2Fdrives%2Fb!h5-hxdKS80W1ueq4mR_YxWQ8z4XhlrdIubUiYLMYKTQGt6zdaNN8Q7TcxFR7P6A3%2Fitems%2F01FI2B4E5QJA6WO2I3FVDIDBUAOTUCLEL7%3Fversion%3DPublished&access_token=eyJ0eXAiOiJKV1QiLCJhbGciOiJub25lIn0.eyJhdWQiOiIwMDAwMDAwMy0wMDAwLTBmZjEtY2UwMC0wMDAwMDAwMDAwMDAvZXBuZWN1YWRvci1teS5zaGFyZXBvaW50LmNvbUA2ODJhNGU2YS1hNzdmLTQ5NTgtYTNhYy05ZTI2NmQxOGFhMzciLCJpc3MiOiIwMDAwMDAwMy0wMDAwLTBmZjEtY2UwMC0wMDAwMDAwMDAwMDAiLCJuYmYiOiIxNjM0MTU4Nzk5IiwiZXhwIjoiMTYzNDE4MDM5OSIsImVuZHBvaW50dXJsIjoibEt4SG1XSk91RWxjUmZOUlFuZ1JYTzBTWFBuQzgvUmRHNHNSMU9PcFJ0az0iLCJlbmRwb2ludHVybExlbmd0aCI6IjEyMCIsImlzbG9vcGJhY2siOiJUcnVlIiwidmVyIjoiaGFzaGVkcHJvb2Z0b2tlbiIsInNpdGVpZCI6Ill6VmhNVGxtT0RjdE9USmtNaTAwTldZekxXSTFZamt0WldGaU9EazVNV1prT0dNMSIsInNpZ25pbl9zdGF0ZSI6IltcImttc2lcIl0iLCJuYW1laWQiOiIwIy5mfG1lbWJlcnNoaXB8Z2lubm8udGFpbWFsQGVwbi5lZHUuZWMiLCJuaWkiOiJtaWNyb3NvZnQuc2hhcmVwb2ludCIsImlzdXNlciI6InRydWUiLCJjYWNoZWtleSI6IjBoLmZ8bWVtYmVyc2hpcHwxMDAzMDAwMGFlMzE0YWYzQGxpdmUuY29tIiwic2Vzc2lvbmlkIjoiZGRjNjQxZjMtYzk3NS00ZTgzLTg1NzAtYmRkN2RhMzIwZDE2IiwidHQiOiIwIiwidXNlUGVyc2lzdGVudENvb2tpZSI6IjMiLCJpcGFkZHIiOiIyMDAuMTI1LjI1MC41NyJ9.MGZZY2hJVk42aUhnVDlpRnFLTy84Z0NxNHBVT1JvSWZiVXMyYlVUY0hlUT0&cTag=%22c%3A%7B673D48B0-1B69-462D-8186-8074E825917F%7D%2C1%22&encodeFailures=1&width=1319&height=614&srcWidth=&srcHeight=)

![Créditos](https://southcentralus1-mediap.svc.ms/transform/thumbnail?provider=spo&inputFormat=png&cs=fFNQTw&docid=https%3A%2F%2Fepnecuador-my.sharepoint.com%3A443%2F_api%2Fv2.0%2Fdrives%2Fb!h5-hxdKS80W1ueq4mR_YxWQ8z4XhlrdIubUiYLMYKTQGt6zdaNN8Q7TcxFR7P6A3%2Fitems%2F01FI2B4E3VO3SQOFOKBBEYDSBS3LZ54F4M%3Fversion%3DPublished&access_token=eyJ0eXAiOiJKV1QiLCJhbGciOiJub25lIn0.eyJhdWQiOiIwMDAwMDAwMy0wMDAwLTBmZjEtY2UwMC0wMDAwMDAwMDAwMDAvZXBuZWN1YWRvci1teS5zaGFyZXBvaW50LmNvbUA2ODJhNGU2YS1hNzdmLTQ5NTgtYTNhYy05ZTI2NmQxOGFhMzciLCJpc3MiOiIwMDAwMDAwMy0wMDAwLTBmZjEtY2UwMC0wMDAwMDAwMDAwMDAiLCJuYmYiOiIxNjM0MTU4Nzk5IiwiZXhwIjoiMTYzNDE4MDM5OSIsImVuZHBvaW50dXJsIjoibEt4SG1XSk91RWxjUmZOUlFuZ1JYTzBTWFBuQzgvUmRHNHNSMU9PcFJ0az0iLCJlbmRwb2ludHVybExlbmd0aCI6IjEyMCIsImlzbG9vcGJhY2siOiJUcnVlIiwidmVyIjoiaGFzaGVkcHJvb2Z0b2tlbiIsInNpdGVpZCI6Ill6VmhNVGxtT0RjdE9USmtNaTAwTldZekxXSTFZamt0WldGaU9EazVNV1prT0dNMSIsInNpZ25pbl9zdGF0ZSI6IltcImttc2lcIl0iLCJuYW1laWQiOiIwIy5mfG1lbWJlcnNoaXB8Z2lubm8udGFpbWFsQGVwbi5lZHUuZWMiLCJuaWkiOiJtaWNyb3NvZnQuc2hhcmVwb2ludCIsImlzdXNlciI6InRydWUiLCJjYWNoZWtleSI6IjBoLmZ8bWVtYmVyc2hpcHwxMDAzMDAwMGFlMzE0YWYzQGxpdmUuY29tIiwic2Vzc2lvbmlkIjoiZGRjNjQxZjMtYzk3NS00ZTgzLTg1NzAtYmRkN2RhMzIwZDE2IiwidHQiOiIwIiwidXNlUGVyc2lzdGVudENvb2tpZSI6IjMiLCJpcGFkZHIiOiIyMDAuMTI1LjI1MC41NyJ9.MGZZY2hJVk42aUhnVDlpRnFLTy84Z0NxNHBVT1JvSWZiVXMyYlVUY0hlUT0&cTag=%22c%3A%7B07E57675-CA15-4908-81C8-32DAF3DE178C%7D%2C1%22&encodeFailures=1&width=1319&height=614&srcWidth=&srcHeight=)


## Authors

- [@GinnoTaimal](https://github.com/SWATrock)

## Documentation

[Report about Videogame](https://epnecuador-my.sharepoint.com/:b:/g/personal/ginno_taimal_epn_edu_ec/EfzmRDOkROpNgfIJXIL9Cl0BqwYLAu5obQG7k-R9NdW87A?e=pdQHTh)
