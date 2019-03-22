/* Version 0.6.1 del proyecto "Buscaminas" realizado por 'Grupo 5':
 * Leonardo Aravena, Ivonne Flores, David Torres
 *
 * Programación I, Ingeniería Civil Informática, UdeC
 *
 * v0.6.1 (11-07-18):
 * - Se corrigen errores al guardar registro de ganadores.
 *
 * v0.6.0 (10-07-18):
 * - Se implementa la opción de guardar y cargar partida.
 *
 * v0.5.1 (09-07-18):
 * - Se corrige bug que se producía al marcar una mina incorrectamente y luego revelar esa casilla, no se desmarcaba como mina incorrecta.
 *
 * v0.5.0 (08-07-18):
 * - Se optimizan las funciones de lectura y registro de ganadores.
 *
 * v0.4.9 (07-07-18):
 * - Se implementa el registro de ganadores según los mejores tiempos.
 *
 * v0.4.8 (06-07-18):
 * - Se corrige bug en la selección del menú de instrucciones.
 * - Se agregan colores al tablero.
 *
 * v0.4.7 (05-07-18):
 * - Se hacen funciones la selección de los niveles.
 *
 * v0.4.6 (03-07-18):
 * - En el menu personalizado se muestra al usuario la cantidad maxima de minas que puede colocar.
 * - En el menu personalizado se leen los valores ingresados por el usuario como cadena de caracteres.
 * - Se cambia el tamaño minimo de filas y columnas a 4.
 * - Se corrige bug en la entrada al marcar las minas con 'x' al cambiar la lectura de la entrada a fgets.
 *
 * v0.4.5 (03-07-18):
 *  - Se ha implementado la funcion de crear un tablero personalizado.
 *
 * v0.4.4 (03-07-18):
 * - Se ha implementado la funcion de mostrar el tiempo de juego.
 *
 * v0.4.3 (03-07-18):
 * - Se modifica ligeramente el menú de perder y ganar para que no avance el menú de selección cuando se ingresan opciones incorrectas.
 *
 * v0.4.2 (02-07-18):
 * - Se modifica ligeramente la función de validación de entrada para que muestre el tablero.
 *
 * v0.4.1 (02-07-18):
 * - Se optimiza la función de creación del tablero, quitando la matriz de números enteros.
 *
 * v0.4 (30-06-18):
 * - Se agrega 3 modos de dificultad con su respectivo menú para elegirlos.
 * - Se cambian las coordenadas, las filas se indican ahora con números y las columnas con letras.
 * - Se cambia a 'x' la tecla para marcar minas.
 * - Se corrige bug que permitía ganar si se marcaban todas las casillas.
 *
 * v0.3.1 (29-06-18):
 * - Se modifican las funciones para aceptar tamaños de tablero variables.
 *
 * v0.3 (27-06-18):
 * - Se agrega opcion para marcar y desmarcar minas.
 * - Se modifica la entrada de coordenadas, permitiendo espacios.
 * - Se modifica la funcion para ganar, permitiendo que se gane al marcar correctamente todas las minas.
 *
 * v0.2 (27-06-18):
 * - Se agrega protección del primer turno.
 * - Se revela el tablero completo al perder o ganar.
 *
 * v0.1 (15-06-18):
 * - Primera versión del proyecto Buscaminas.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct{ //Esctructura para almacenar los ganadores con menor tiempo.

	double tiempo; //Tiempo que demoró el usuario en ganar la partida.
	char jugador[30]; //Nombre que registra el usuario al ganar.

} Puntaje;

void guardarPartida(int m, int n, char nivel, double tiempo, int minas, int minasAcertadas, int minasIncorrectas, char tablero[m][n], char mostrar[m][n]){

	//Función para guardar la partida
	int i,j;

	FILE * Partida;

	//Abre el archivo en modo de esctritura. Si no existe lo crea:
	Partida = fopen("partidaGuardada.dat","w+b");

	//Guarda el nivel del juego:
	fprintf(Partida,"%c ",nivel);

	//Guarda el número de filas del tablero de juego:
	fprintf(Partida,"%d ",m);

	//Guarda el número de columnas del tablero de juego:
	fprintf(Partida,"%d ",n);

	//Guarda la cantidad de minas:
	fprintf(Partida,"%d ",minas);

	//Guarda el tiempo transcurrido:
	fprintf(Partida,"%.lf ",tiempo);

	//Guarda la cantidad de minas marcadas correctamente:
	fprintf(Partida,"%d ",minasAcertadas);

	//Guarda la cantidad de minas marcadas incorrectamente:
	fprintf(Partida,"%d ",minasIncorrectas);

	//Guarda el tablero:
	for(i=0; i<m; ++i){

		for(j=0; j<n; ++j){

			fprintf(Partida,"%c",tablero[i][j]);

		}
	}

	//Añade un espacio en blanco:
	fprintf(Partida," ");

	//Guarda el tablero a mostrar al usuario:
	for(i=0; i<m; ++i){

		for(j=0; j<n; ++j){

			fprintf(Partida,"%c",mostrar[i][j]);

		}
	}

	//Cierra el archivo:
	fclose(Partida);
}

int entregaDimensiones(char *nivel, int *m, int *n){
	//Función que lee el archivo guardado de la partida y entrega las dimensiones del tablero guardado

	char dimensiones[1000]; //string que guarda los datos que posee el archivo.
	char mC[3]; // string con 2 caracteres que son las filas de la matriz.
	char nC[3]; // string con 2 caracteres ''
	char nivC[3];
	int i, j;
	int tam;

	FILE * Partida;

	//Abre el archivo de la partida guardad en modo de lectura:
	Partida = fopen("partidaGuardada.dat","r+b");

	//Si no existe el archivo o está vacío retorna '0'
	if(Partida == NULL) return (0);

	else{

		//Copia los primeros  caracteres del archivo, que son los que contienen las dimensiones del tablero a la cadena 'dimensiones':
		fgets(dimensiones,1000,Partida);

		fclose(Partida);

		nivel[0]=dimensiones[0];

		i=2;
		j=0;

		//Mientras no encuentra un espacio en blanco:
		while(dimensiones[i]!=' '){

			//Copia los caracteres que indican el número de filas del tablero en una cadena temporal:
			mC[j]=dimensiones[i];
			++i;
			++j;
		}

		//Finaliza la cadena:
		mC[i]='\0';

		//Pasa la cadena de caracteres a entero:
		*m=atoi(mC);
		j=0;
		++i;

		while(dimensiones[i]!=' '){

			//Copia los caracteres que indican el número de columnas del tablero en una cadena temporal:
			nC[j]=dimensiones[i];
			++i;
			++j;
		}

		//Finaliza la cadena:
		nC[j]='\0';

		//Pasa la cadena de caracteres a entero:
		*n=atoi(nC);

		//Retorna el índice desde donde seguir leyendo el archivo para la función que carga la partida:
		return(i);
	}
}

void cargarPartida(int d, int *m, int *n, double *tiempo, int *minas, int *minasAcertadas, int *minasIncorrectas, char tablero[*m][*n], char mostrar[*m][*n]){

	//Función que carga una partida guardada en archivo.

	int i,j,k;
	char guardada[1000]; //Cadena de caracteres para guardar la información del archivo guardado.
	char tiempoC[10]; //Cadena temporal para guardar el tiempo.
	char minasC[3]; //Cadena temporal para guardar la cantidad de minas.
	char minasAcertadasC[3]; //Cadena temporal para guardar la cantidad de minas marcadas correctamente.
	char minasIncorrectasC[4]; //Cadena temporal para guardar la cantidad de minas marcadas incorrectamente.
	char nivelC[4]; //Cadena temporal para guardar el nivel del juego.

	FILE * Partida;

	//Abre el archivo que contiene la partida guardada.
	Partida = fopen("partidaGuardada.dat","r+b");

	//Copia el contenido en la cadena de caracteres 'guardada'
	fgets(guardada,1000,Partida);

	//Cierra el archivo:
	fclose(Partida);


	i=d; //El índice 'i' indica desde donde leer el archivo.

	j=0;
	++i;

	while(guardada[i]!=' '){

		minasC[j]=guardada[i];
		++i;
		++j;
	}

	minasC[j]='\0';
	*minas=atoi(minasC);

	j=0;
	++i;

	//Mientras no haya un espacio en blanco:
	while(guardada[i]!=' '){

		//Guarda la información del tiempo transcurrido guardado:
		tiempoC[j]=guardada[i];
		++i;
		++j;
	}

	//Finaliza la cadena y convierte la cadena de caracteres a double:
	tiempoC[j]='\0';
	*tiempo=atof(tiempoC);

	j=0;
	++i;

	while(guardada[i]!=' '){
		//Guarda la información de las minas marcadas correctamente por el usuario.
		minasAcertadasC[j]=guardada[i];
		++i;
		++j;
	}

	//Finaliza la cadena y convierte la cadena de caracteres a entero.
	minasAcertadasC[j]='\0';
	*minasAcertadas=atoi(minasAcertadasC);

	j=0;
	++i;

	while(guardada[i]!=' '){

		//Guarda la información de las minas marcadas incorrectamente por el usuario.
		minasIncorrectasC[j]=guardada[i];
		++i;
		++j;
	}

	//Finaliza la cadena y convierte la cadena de caracteres a entero.
	minasIncorrectas[j]='\0';
	*minasIncorrectas=atoi(minasIncorrectasC);

	++i;

	//Copia los caracteres correspondientes al tablero del juego.
	for(k=0; k<*m; ++k){

		for(j=0; j<*n; ++j){

			tablero[k][j]=guardada[i];
			++i;
		}
	}

	++i;

	//Copia los caracteres correspondientes al tablero a mostrar al usuario del juego.
	for(k=0; k<*m; ++k){

		for(j=0; j<*n; ++j){

			mostrar[k][j]=guardada[i];
			++i;
		}
	}
}

double calcularTiempo(time_t inicio, double *tiempoCargado){

	//Función para calcular el tiempo transcurrido desde que se inicia el juego.
	time_t actual;

	time(&actual); //Guarda el tiempo al ingresar la coordenada

	//Retorna la cantidad de segundos que han transcurrido. Si se ha cargado una partida se suma el tiempo guardado.
	return(difftime(actual,inicio) + (*tiempoCargado));
}

int mostrarPuntajes(char nivel){ //Función que muestra el registro de ganadores del nivel.

	FILE * archivo; //Puntero para el manejo de archivos.

	Puntaje puntajeRegistro[11]; //Vector a estructura Puntaje.

	int i=0, j=0, n=0, s=0, p=0, tam; //Variables auxiliares.
	int estadoArchivo=0; //Variable que indica si existe o no el archivo de registro de los ganadores.
	char registro[1000]; //Cadena de caracteres para almacenar el contenido del archivo.
	int dim;
	char nombre[30]; //Cadena temporal para los nombres de los ganadores.
	char puntos[100]; //Cadena temporal para el tiempo de los ganadores.
	char opcion[100]; //Cadena para leer las entradas del usuario en el menú.
	char op,op2;

	if (nivel==1) archivo = fopen("puntajesFacil.dat","rb"); //Abre el archivo de registro del nivel correspondiente en modo de lectura.

	else if (nivel==2) archivo = fopen("puntajesMedio.dat","rb");

	else if (nivel==3) archivo = fopen("puntajesDificil.dat","rb");

	if(archivo==NULL) estadoArchivo=1; //El 'estadoArchivo' se vuelve a '1' indicando que el archivo no existía o era nulo.

	else{ //Si existe el archivo y tiene contenido:

		fgets(registro,1000,archivo); //Se copia todo el contenido del archivo a la cadena 'registro'

		fclose(archivo); //Se cierra el archivo;

		dim=strlen(registro);

		registro[dim-1]='\0';

		while(registro[i]!='\0'){ //Mientras no se llegue al final de la cadena.

			j=0;

			while(registro[i]!=' '){ //Mientras no se llegue a un espacio en blanco.

				puntos[j]=registro[i]; //Se copian los caracteres que indican el tiempo del ganador.
				++i;
				++j;
			}

			puntos[j]='\0'; //Se cierra la cadena.

			puntajeRegistro[n].tiempo=atoi(puntos); //Se copia como double la cadena 'puntos' al campo de tiempo de un elemento del vector puntaje.

			++i;
			j=0;

			while(registro[i]!=' '){ //Mientras no se llegue a un espacio en blanco.

				nombre[j]=registro[i]; //Se copian los caracteres del nombre del ganador
				++i;
				++j;
			}
			nombre[j]='\0'; //Se cierra la cadena.

			strcpy(puntajeRegistro[n].jugador,nombre); //Se copia el nombre del ganador en el campo de 'nombre' de un elemento del vector puntaje.

			++i;
			++n; //Se incrementa el ínidice del vector
		}

		estadoArchivo=0; //El 'estadoArchivo' se vuelve a '0' indicando que el archivo existía y no era nulo.
	}

	while(1){

		system("clear");

		if(estadoArchivo){ //Si el archivo no existe o está vacío:

			printf("\n\x1B[0m~~~~ NO HAY REGISTRO DE PUNTAJES ~~~~\n");

			printf("\n\x1B[0mSeleccione una opcion:\n\n1: Iniciar Nuevo Juego\n2: Volver a atras\n3: Volver al Menu Principal\n\n");

			scanf("%s",opcion); //Lee las opciones del menú.

			op=opcion[0];

			s=strlen(opcion);

			if(s==1){

				if(op=='1') return(1); //Inicia un nuevo juego.

				else if(op=='2') return(5); //Vuelve al menú para elegir el registro a mostrar según el nivel de dificultad.

				else if(op=='3') return(0); //Vuelve al menú principal.
			}
		}


		else{ //Si el archivo existe y tiene contenido se muestra en pantalla:

			if (nivel==1) printf("\n\x1B[0m~~~~ MEJORES JUGADORES NIVEL FACIL ~~~~\n\n");

			else if (nivel==2) printf("\n\x1B[0m~~~~ MEJORES JUGADORES NIVEL MEDIO ~~~~\n\n");

			else if (nivel==3) printf("\n\x1B[0m~~~~ MEJORES JUGADORES NIVEL DIFICIL ~~~~\n\n");

			for(i=0; i<n; ++i){

				printf("%2d) ",(i+1)); //Muestra la posición del jugador

				tam=strlen(puntajeRegistro[i].jugador); //Obtiene el tamaño del nombre del jugador para seleccionar la cantidad de tabulaciones.

				if(tam<4) printf("%s\t\t\t",puntajeRegistro[i].jugador); //Si el tamaño es menor a 5 se aplican 3 tabulaciones luego de mostrar el nombre.

				else if(tam>12) printf("%s\t",puntajeRegistro[i].jugador); //Si el tamaño es mayor a 12 se aplican 12 tabulaciones.

				else printf("%s\t\t",puntajeRegistro[i].jugador); //En caso contrario se aplican 2 tabulaciones.

				printf("%.lf\n",puntajeRegistro[i].tiempo); //Muestra el tiempo de cada jugador.
			}

			printf("\n\x1B[0mSeleccione una opcion:\n\n1: Iniciar Nuevo Juego\n2: Volver a atras\n3: Volver al Menu Principal\n\n4: Borrar Registro\n\n");

			scanf("%s",opcion);

			op=opcion[0];

			s=strlen(opcion);

			if(s==1){

				if(op=='1') return(1); //Inicia un nuevo juego.

				else if(op=='2') return(5); //Vuelve al menú para elegir el registro a mostrar según el nivel de dificultad.

				else if(op=='3') return(0); //Vuelve al menú principal.

				else if(op=='4'){ //Entra al menú para borrar el registro de los ganadores.

					while(1){

						system("clear");

						printf("\n\x1B[0m~~~~ BORRAR REGISTRO ~~~~\n\n");
						printf("\nEsta seguro de que desea borrar el registro de los mejores jugadores?\n\n1: Borrar\n2: Volver a atras\n\n");

						scanf("%s",opcion);

						op2=opcion[0];

						p=strlen(opcion);

						if(p==1){

							if(op2=='1'){

								if (nivel==1) remove("puntajesFacil.dat"); //Borra el archivo correspondiente.

								else if (nivel==2) remove("puntajesMedio.dat");

								else if (nivel==3) remove("puntajesDificil.dat");

								estadoArchivo=1; //Cambia el 'estadoArchivo' indicando que ya no existe este archivo.
								break;

							}

							else if(op2=='2') break; //Vuelve al menú anterior
						}
					}
				}
			}
		}
	}
}

void mainMenu(){ //Menú principal.

	printf("\n\x1B[0m~~~~~~~~~~~~~ BUSCAMINAS ~~~~~~~~~~~~~\n\nBienvenido a 'Buscaminas' v0.6.1 by Grupo 5\n\nSeleccione una opcion:\n\n1: Nuevo Juego\n2: Leer instrucciones\n3: Cargar Partida\n4: Registro Mejores Jugadores\n\n5: Salir\n\n");
}

void instrMenu(){ //Menú de Instrucciones.

	printf("\n\x1B[0m~~~~~~~~~~~~~ INSTRUCCIONES ~~~~~~~~~~~~~\n\nEste juego consiste en despejar el tablero de juego sin acertar las minas\no marcar la ubicacion de todas las minas, con la ayuda de los numeros\nque le indican la cantidad de minas que rodean esa casilla.\n\nPara despejar las casillas escriba las coordenadas correspondientes mostradas en el tablero.\nLos numeros indican las filas de las casillas y las letras indican las columnas.\nPuede ingresar indistintamente primero una letra o un numero, en mayuscula o minuscula, con o sin espacio.\nPor ejemplo: 'A1' o '1 a' despeja la primera casilla arriba a la izquierda del tablero.\nDesde el segundo turno puede marcar (o desmarcar) la posicion de una mina\ningresando la letra 'x' antes de la coordenada a marcar (o desmarcar).\n\nSe gana el juego cuando se han despejado todas las casillas donde no hay minas\no se hayan marcado correctamente la ubicacion de todas las minas.\nSe pierde el juego cuando se despeja una casilla donde esta ubicada alguna mina.\n\nExisten cuatro niveles de dificultad:\n'Facil': El tablero tiene dimension de 8x8 casillas con 8 minas.\n'Medio': El tablero tiene dimension de 9x15 casillas con 25 minas.\n'Dificil': El tablero tiene dimension de 9x23 casillas con 50 minas.\n'Personalizado': Usted elije las dimensiones del tablero y la cantidad de minas.\n\nAl estar en una partida puede escribir 'guardar' para guardar una partida.\nSolamente se puede guardar desde el segundo turno.\nPara cargar la partida guardada debe seleccionar la opcion 'Cargar Partida'\nen el menu principal o en este menu.\nAl estar en una partida puede escribir 'salir' para volver al menu principal\n\nEn la opcion 'Registro Mejores Jugadores' puede ver a los ganadores con\nmenor registro de tiempo de acuerdo en el nivel que ganaron (Facil, Medio o Dificil).\nCuando usted gana una partida puede escribir su nombre (sin espacios) para ser parte de este registro.\n\nSeleccione una opcion:\n\n1: Nuevo Juego\n2: Cargar Partida\n3: Volver al Menu Principal\n4: Salir\n\n");
}

void selecMenu(){ //Menú de selección al perder o ganar.

	printf("\n\x1B[0mSeleccione una opcion:\n\n1: Nuevo Juego\n2: Volver al Menu Principal\n3: Salir\n\n");
}

void nivelMenu(){ //Menú de selección de nivel de dificultad.

	printf("\n\x1B[0m~~~~~~~~~~~~~ DIFICULTAD ~~~~~~~~~~~~~\n\nSeleccione el nivel de dificultad:\n\n1: Facil\n2: Medio\n3: Dificil\n4: Personalizado\n\n5: Volver al Menu Principal\n\n");
}

void instruccionesPersonalizada(){
	system("clear");
	printf("\n\x1B[0m~~~~~~~~~~~~~ PERSONALIZADO ~~~~~~~~~~~~~\n\nEste es el menu de personalizacion de tablero\nIngrese la cantidad de filas, columnas y minas que desee en su juego.\n\nEl numero de filas debera estar entre 4 y 9.\n\nEl numero de columnas debera estar entre 4 y 23.\n\nEl numero de minas no debera exceder la cuarta parte de las casillas totales.\n\n");
}

void menuPuntajes(){

	printf("\n\x1B[0m~~~~~~~~~~~~~ REGISTRO MEJORES JUGADORES ~~~~~~~~~~~~~\n\nSeleccione el nivel para ver los mejores jugadores\n\n1: Facil\n2: Medio\n3: Dificil\n\n4: Iniciar nuevo juego\n5: Volver al Menu Principal\n\n");
}

int menuSinPartidas(){
	//Se muestra este menú cuando se accede a la opción de cargar partida y no hay ninguna partida guardada.

	char opcion[100];
	char op;
	int s;

	while(1){

		system("clear");

		printf("\n\x1B[0m~~~~ NO HAY PARTIDAS GUARDADAS ~~~~\n");
		printf("\nSeleccione una opcion:\n\n1: Iniciar Nuevo Juego\n2: Volver al Menu Principal\n\n");

		scanf("%s",opcion); //Lee las opciones del menú.

		op=opcion[0];

		s=strlen(opcion);

		if(s==1){

			if(op=='1') return(1); //Inicia un nuevo juego.

			else if(op=='2') return(0); //Vuelve al menú principal.
		}
	}
}

int ** restringido(int a, int b){

	/*Esta funcion recibe la primera coordenada y crea una matriz dinamica que contiene
	 las coordenada de la casilla seleccionada y de las casillas que la rodean
	 para evitar que se situen minas en esa posicion al crear el tablero y proteger
	 el primer turno y que además en el primer turno se despeje al menos un espacio vacio
	 y facilitar el juego */
	int i;
	int ** m;

	m=(int **)malloc(2*sizeof(int*));

	for(i=0; i<2; ++i){

		m[i]= (int*)malloc(9*sizeof(int));
	}

	//Guarda en la matriz las coordenadas de las 9 casillas restringidas:
	m[0][0]=a-1;
	m[1][0]=b-1;

	m[0][1]=a-1;
	m[1][1]=b;

	m[0][2]=a-1;
	m[1][2]=b+1;

	m[0][3]=a;
	m[1][3]=b-1;

	m[0][4]=a;
	m[1][4]=b;

	m[0][5]=a;
	m[1][5]=b+1;

	m[0][6]=a+1;
	m[1][6]=b-1;

	m[0][7]=a+1;
	m[1][7]=b;

	m[0][8]=a+1;
	m[1][8]=b+1;

	return(m); //Devuelve la matriz.
}

void freeRestringido(int **m){

	//Función que libera la memoria dinamica de las coordenadas restringidas para el primer turno.
	int i;

	for(i=0; i<2; ++i){

		free(m[i]);
	}

	free(m);
}

void crearMostrar(int m, int n,  char v1[m][n]){

	//Función que crea el tablero a mostrar al usuario
	int i, j, c;

	//Las esquinas del tablero a mostrar:
	v1[0][0]='>';
	v1[0][n-1]='<';
	v1[m-1][0]='>';
	v1[m-1][n-1]='<';

	//Se colocan números para identificar las filas:
	for(i=1,c=0; i<(m-1); ++i,++c){

		v1[i][0]='1'+c;
 		v1[i][n-1]='1'+c;
	}

	//Se colocan letras desde la 'A' para identificar las columnas:
	for(j=1,c=0; j<(n-1); ++j,++c){

		v1[0][j]='A'+c;
 		v1[m-1][j]='A'+c;
	}

	//Se llena el tablero a mostrar con '-', que indica las casillas sin descubrir:
	for(i=1; i<(m-1); ++i){

		for(j=1; j<(n-1); ++j){

			v1[i][j]='-';
		}
	}
}

void crearTablero(int m, int n, int minas, char v1[m][n], int ** noM){

	//Función que crea el tablero con las minas y los correspondientes números que indican su ubicación.
	int cont=0; //Contador de minas colocadas.

	int i, j, a, q=0;

	for(i=0; i<m; ++i){ //Matriz de caracteres inicializada con espacios en blancos.

		for(j=0; j<n; ++j){

			v1[i][j]=' ';
		}
	}

	srand(time(NULL)); //Semilla variable con el tiempo.

	while(cont<minas){

		//Genera las cordenadas de manera aleatoria desde el 0 hasta el 9 para la ubicación de las minas:
		i=rand()%(m-1);
		j=rand()%(n-1);

		//Si las coordenadas i o j están en la orilla (0) se aumenta en uno:
		if(i==0) ++i;
		if(j==0) ++j;

		/* En este ciclo se comprueba que las coordenadas generadas de manera aleatoria no estén en las
		   coordenadas restringidas generadas en el primer turno.  */

		while(1){

			for(a=0; a<9; ++a){

				/* Si coincide la componente de la fila de la coordenada luego se comprueba
				   la componente de la columna:  */

				if(noM[0][a]==i){

					if(noM[1][a]==j){

						//Se generan nuevas coordenadas y se repite todo el ciclo de comprobación.
						i=rand()%(m-1);
						j=rand()%(n-1);

						if(i==0) ++i;
						if(j==0) ++j;
						q=1; //variable para que se repita todo el ciclo de comprobación.
					}
				}
			}

			//La variable 'q' controla la salida del ciclo de comprobación:
			if(q==0) break;

			else q=0;
		}

		//Se colocan las minas en el tablero y los números indicadores alrededor de las minas:

		if(v1[i][j]!='*'){ //Esto evita colocar minas en el mismo lugar

			v1[i][j]='*'; //Se colocan las minas representados por el '*'

			if(v1[i-1][j-1]==' ') v1[i-1][j-1]='1'; //Si el espacio alrededor de la mina es un espacio en blanco se coloca el '1'

			else if(v1[i-1][j-1]!='*') ++v1[i-1][j-1]; //Si es distinto a una mina, entonces es un número y se le suma '1'

			if(v1[i-1][j]==' ') v1[i-1][j]='1';

			else if(v1[i-1][j]!='*') ++v1[i-1][j];

			if(v1[i-1][j+1]==' ') v1[i-1][j+1]='1';

			else if(v1[i-1][j+1]!='*') ++v1[i-1][j+1];

			if(v1[i][j+1]==' ') v1[i][j+1]='1';

			else if(v1[i][j+1]!='*') ++v1[i][j+1];

			if(v1[i+1][j+1]==' ') v1[i+1][j+1]='1';

			else if(v1[i+1][j+1]!='*') ++v1[i+1][j+1];

			if(v1[i+1][j]==' ') v1[i+1][j]='1';

			else if(v1[i+1][j]!='*') ++v1[i+1][j];

			if(v1[i+1][j-1]==' ') v1[i+1][j-1]='1';

			else if(v1[i+1][j-1]!='*') ++v1[i+1][j-1];

			if(v1[i][j-1]==' ') v1[i][j-1]='1';

			else if(v1[i][j-1]!='*') ++v1[i][j-1];

			cont++;//Aumenta el contador con cada mina colocada
		}
	}

	//Llena el borde del tablero con '~', para no dejar en blanco ni con numeros, ni minas:
	for(i=0; i<m; ++i){

		v1[i][0]=126; // ~ = 126 en ASCII
		v1[i][n-1]=126;
	}

	for(j=0; j<n; ++j){

		v1[0][j]=126;
		v1[m-1][j]=126;
	}
}

void mostrarTablero(int m, int n, char v[m][n]){

	//Muestra en pantalla el tablero
	int i,j;

	system("clear");

	for(i=0; i<m; ++i){

		printf("\n");

		for(j=0; j<n; ++j){


			if(v[i][j]>='A' && v[i][j]<='W') printf("    \x1B[32m%3c", v[i][j]); //Las letras de coordenadas del tablero son de color verde.

			else if (v[i][j]=='-') printf("    \x1B[0m%3c", v[i][j]); //Los guiones del tablero son de color normal.

			else if(v[i][j]=='x') printf("    \x1B[36m%3c", v[i][j]); //Las marcas de las minas son de color cyan.

			else if(v[i][j]=='*') printf("    \x1B[33m%3c", v[i][j]); //Las minas son de color naranjo.

			else if(v[i][j]=='#') printf("    \x1B[31m%3c", v[i][j]); //La mina con la que pierde el usuario es de color rojo.

			else if (j>0 && j<(n-1)) printf("    \x1B[0m%3c", v[i][j]); //Los números indicadores de minas son de color normal.

			else printf("    \x1B[32m%3c", v[i][j]); //Los números de coordenadas son de color verde.

		}
		printf("\n\n");
	}
}

int entrada(time_t inicio, double *tiempoCargado, int x, int y, int * pi, int * pj, char mostrar[x][y], int menuGuardar){

	//Funcion para validar la entrada
	char entrada[100];

	char coord[100];

	char salida[]="salir"; //Cadena para comparar si se escribe 'salir'

	char guardar[]="guardar"; //Cadena para comparar si se escribe 'guardar'

	char c1, c2;

	double segundos; //Variable para mostrar la cantidad de segundos que han transcurrido del juego.

	int n, m=0, comp, i, j, marcar;

	while(m==0){

		c1=0;
		c2=0;
		marcar=0;
		comp=1;
		i=0;
		j=0;

		mostrarTablero(x, y, mostrar); //Llama a la función para mostrar el tablero.
		//Si 'menuGuardar' es '1' se muestra en pantalla que se guardó la partida:

		if(menuGuardar) printf("\n\x1B[0mSe ha guardado la partida\n");

		printf("\n\x1B[0mIngrese Coordenada:\t\t");

		//Llama a la función que cuenta el tiempo transcurrido:
		segundos=calcularTiempo(inicio,tiempoCargado);

		printf("Tiempo: %.lfs\n\n",segundos);//Muestra los segundos transcurridos.

		//Se lee la entrada, se permiten espacios:
		fgets(entrada, 100, stdin);

		//Se quitan los espacios a la cadena de entrada:
		while(entrada[i]!='\n'){

			if(entrada[i]==' ') ++i;

			else{
				coord[j]=entrada[i];
				++i;
				++j;
			}
		}

		coord[j]='\0';

		n=strlen(coord);

		//Se normalizan las letras dejándolas en minúsculas:
		for(i=0; i<n; ++i){

			if(coord[i]>64 && coord[i]<91){

				coord[i]=coord[i]+32;
			}
		}

		//Si se ingresa 'salir', la funcion retorna '1' para volver al menu principal:
		comp=strcmp(salida,coord);

		if(comp==0) return(1);

		//Si se ingresa 'guardar' la función retorna '3' para guardar la partida:
		comp=strcmp(guardar,coord);

		if(comp==0) return(3);



		//Si el primer caracter es 'x' se ingresa en modo de marcar minas:
		if(coord[0]=='x' && n==3){

			marcar=1; //Variable para retornar que se entra en modo de marcado.

			//Los siguientes caracteres corresponden a las coordenadas:
			c1=coord[1];
			c2=coord[2];
		}

		else if (n==2){
			//Los dos primeros caracteres son las coordenadas, ignorando el resto:
			c1=coord[0];
			c2=coord[1];
		}

		//Si primero se ingresa una letra, luego se espera un numero (dentro del rango del tablero):
		if(c1>96 && c1<(95+y)){

			if(c2>48 && c2<(47+x)) m=1;

			else m=0;
		}

		//Si primero se ingresa un número luego se espera una letra (dentro del rango del tablero):
		else if(c1>48 && c1<(47+x)){

			if(c2>96 && c2<(95+y)) m=2;

			else m=0;
		}

		//Si son dos letras, o dos numeros u otros caracteres, se mantiene en el ciclo hasta tener los caracteres correctos:
		else m=0;
	}

	//Se convierten las coordenadas de entrada en indices de la matriz del tablero:
	if(m==1){

		*pi=c2-48; //Indice de la fila.
		*pj=c1-96; //Indice de la columna.
	}

	else if(m==2){

		*pi=c1-48;
		*pj=c2-96;
	}

	//Si está en modo de marcar casillas se retorna '2':
	if(marcar) return (2);

	//Si se ingresan coordenadas correctas se retorna '0':
	else return(0);
}

void nivelFacil(int *m, int *n, int *minas){

	//Dimensiones del nivel fácil:
	*m=10;
	*n=10;
	*minas=8;
}

void nivelMedio(int *m, int *n, int *minas){

	//Dimensiones del nivel medio:
	*m=11;
	*n=17;
	*minas=25;

}

void nivelDificil(int *m, int *n, int *minas){

	//Dimensiones del nivel difícil:
	*m=11;
	*n=25;
	*minas=50;
}

void nivelPersonalizado(int *m, int *n, int *minas){

	char t[100]; //Cadena de caracteres de lectura de los valores.

	/* Se lee la entrada como caracteres y se convierten a enteros. Si están fuera del rango permitido,
	   se sigue leyendo hasta que se ingresen los valores correctos: */
	do{
		instruccionesPersonalizada();
		printf("\x1B[0mIngrese el numero de filas (min: 4, max: 9): ");
		scanf("%s",t);
		*m=atoi(t);

	}while(*m>9 || *m<4);

	do{
		instruccionesPersonalizada();
		printf("\x1B[0mIngrese el numero de columnas (min: 4, max: 23): ");
		scanf("%s",t);
		*n=atoi(t);

	}while(*n>23 || *n<4);

	do{
		instruccionesPersonalizada();
		printf("\x1B[0mIngrese el numero de minas (min: 1, max: %d): ",((*m)*(*n))/4);
		scanf("%s",t);
		*minas=atoi(t);

	}while(*minas<1 || *minas>((*m)*(*n))/4);

	*m+=2;
	*n+=2;
}

void revelarTablero(int m, int n, int i, int j, char v1[m][n], char v2[m][n]){
	/* Función para despejar los espacios vacios del tablero:
	   Si hay un espacio en blanco revela los numeros alrededor de este, si encuentra un espacio blanco que lo rodea
	   y que no haya sido despejado, llama recursivamente a la funcion */

		v2[i][j]=v1[i][j]; //Revela el espacio en blanco.

		//Comprueba todas las coordenas alrededor del espacio en blanco:

		if(v1[i-1][j-1]>48 && v1[i-1][j-1]<57) v2[i-1][j-1]=v1[i-1][j-1];

		else if(v1[i-1][j-1]==' ' && v1[i-1][j-1]!=v2[i-1][j-1]) revelarTablero(m, n, i-1, j-1, v1, v2);

		if(v1[i-1][j]>48 && v1[i-1][j]<57) v2[i-1][j]=v1[i-1][j];

		else if(v1[i-1][j]==' ' && v1[i-1][j]!=v2[i-1][j]) revelarTablero(m, n, i-1, j, v1, v2);

		if(v1[i-1][j+1]>48 && v1[i-1][j+1]<57) v2[i-1][j+1]=v1[i-1][j+1];

		else if(v1[i-1][j+1]==' ' && v1[i-1][j+1]!=v2[i-1][j+1]) revelarTablero(m, n, i-1, j+1, v1, v2);

		if(v1[i][j+1]>48 && v1[i][j+1]<57) v2[i][j+1]=v1[i][j+1];

		else if(v1[i][j+1]==' ' && v1[i][j+1]!=v2[i][j+1]) revelarTablero(m, n, i, j+1, v1, v2);

		if(v1[i+1][j+1]>48 && v1[i+1][j+1]<57) v2[i+1][j+1]=v1[i+1][j+1];

		else if(v1[i+1][j+1]==' ' && v1[i+1][j+1]!=v2[i+1][j+1]) revelarTablero(m, n, i+1, j+1, v1, v2);

		if(v1[i+1][j]>48 && v1[i+1][j]<57) v2[i+1][j]=v1[i+1][j];

		else if(v1[i+1][j]==' ' && v1[i+1][j]!=v2[i+1][j]) revelarTablero(m, n, i+1, j, v1, v2);

		if(v1[i+1][j-1]>48 && v1[i+1][j-1]<57) v2[i+1][j-1]=v1[i+1][j-1];

		else if(v1[i+1][j-1]==' ' && v1[i+1][j-1]!=v2[i+1][j-1]) revelarTablero(m, n, i+1, j-1, v1, v2);

		if(v1[i][j-1]>48 && v1[i][j-1]<57) v2[i][j-1]=v1[i][j-1];

		else if(v1[i][j-1]==' ' && v1[i][j-1]!=v2[i][j-1]) revelarTablero(m, n, i, j-1, v1, v2);
}

int estadoGanar(int m, int n,char v1[m][n], char v2[m][n], int mT, int *mA, int *mI){

	//Se gana el juego cuando quedan las minas sin revelar o se han marcado todas las minas correctamente:
	int i,j,c=0;

	//Si se han marcado correctamente todas las minas y no hayan marcas incorrectas se retorna '1' indicando que se ganó:
	if(*mA==mT && *mI==0) return (1);

	/*En este ciclo se compara el tablero mostrado al usuario con el tablero de las minas.
	  Si son iguales, a excepción de las minas y las orillas, también se gana el juego */
	for(i=1; i<(m-1); ++i){

		for(j=1; j<(n-1); ++j){

			if(v1[i][j]!='*'){

				//Si todavía no se revela todo el tablero se retorna '0':
				if(v1[i][j]!=v2[i][j]) return (0);

				else c=1;
			}
		}
	}

	if (c==1) return (1); //Si se ha revelado todo a excepción de las minas se retorna '1'
}

void registrarGanador(char *nivel, double *tiempoJugador){

	//Función que guarda en archivo cuando se gana una partida.

	FILE * archivo;

	int i=0, j=0, n=1, m=0;
	char nombre[30];
	char tiempo[10];
	char ganador[30];
	int tam,dim;

	Puntaje puntajeRegistro[12]; //Vector para el registro del nivel.

	Puntaje aux; //Variable auxiliar del tipo 'Puntaje'.

	char registro[1000]; //Cadena de caracteres para almacenar el contenido del archivo.

	printf("\nIngrese su nombre:\n\n");

	scanf("%s",ganador); //Lee el nombre del ganador, no se permiten espacios.

	getchar();

	puntajeRegistro[0].tiempo= *tiempoJugador; //Guarda el tiempo del ganador en el campo de tiempo.

	strcpy(puntajeRegistro[0].jugador,ganador); //Guarda el nombre en el campo 'jugador'

	if(*nivel==1) archivo = fopen("puntajesFacil.dat","rb"); //Abre el archivo correspondiente a cada nivel.

	else if(*nivel==2) archivo = fopen("puntajesMedio.dat","rb");

	else if(*nivel==3) archivo = fopen("puntajesDificil.dat","rb");

	if(archivo!=NULL){ //Si el archivo existe y tiene ganadores registrados.

		fgets(registro,1000,archivo); //Copia el contenido del archivo a la cadena de caracteres 'registro'

		fclose(archivo); //Cierra el archivo.

		dim=strlen(registro);

		registro[dim-1]='\0';

		while(registro[i]!='\0'){ //Mientras no se llega al final de la cadena 'registro'.

			j=0;

			while(registro[i]!=' '){ //Mientras no se llegue a un espacio en blanco.

				tiempo[j]=registro[i]; //Se copia el registro del tiempo del ganador en la cadena 'tiempo'
				++i;
				++j;
			}

			tiempo[j]='\0'; //Se finaliza la cadena

			puntajeRegistro[n].tiempo=atof(tiempo); //Se copia al campo de tiempo como double.

			++i;
			j=0;

			while(registro[i]!=' '){ //Mientras no se llegue a un espacio en blanco.

				nombre[j]=registro[i]; //Se copia el registro del nombre del ganador en la cadena 'nombre'
				++i;
				++j;
			}

			nombre[j]='\0'; //Se finaliza la cadena.

			strcpy(puntajeRegistro[n].jugador,nombre); //Se copia al campo 'jugador'

			++i;
			++n; //Incrementa el índice del vector.
		}
	}

	if(n>1){

		for(i=0; i<(n-1); ++i){

			for(j=(i+1); j<n; ++j){

				if(puntajeRegistro[j].tiempo < puntajeRegistro[i].tiempo){

					aux=puntajeRegistro[i];
					puntajeRegistro[i]=puntajeRegistro[j];
					puntajeRegistro[j]=aux;
				}
			}
		}
	}

	//Abre el archivo de registro del nivel correspondiente en modo de escritura:
	if (*nivel==1) archivo = fopen("puntajesFacil.dat","w+b");

	else if (*nivel==2) archivo = fopen("puntajesMedio.dat","w+b");

	else if (*nivel==3) archivo = fopen("puntajesDificil.dat","w+b");

	//Esto restringe que en el registro de ganadores sólo se guardan los 10 mejores:
	//m=(n>10)?10:n; //Si el ínidice del vector de ganadores es mayor a 9 se restringe hasta el índice 9.

	if(n>10) m=10;

	else m=n;

	for(i=0; i<m; ++i){ //Guarda en el archivo todos los ganadores ya ordenados.

		fprintf(archivo,"%.lf ",puntajeRegistro[i].tiempo); //Primero guarda el tiempo, dejando un espacio al final.

		fputs(puntajeRegistro[i].jugador,archivo); //Luego el nombre.

		fprintf(archivo," "); //Se coloca un espacio después del nombre.
	}

	fprintf(archivo,"\n");

	fclose(archivo); //Se cierra el archivo.
}

void tableroFinal(int m, int n, char v1[m][n], char v2[m][n]){
	//Función que muestra todo el tablero al usuario, una vez haya perdido o ganado:

	int i,j;

	for(i=1; i<(m-1); ++i){

		for(j=1; j<(n-1); ++j){

			//Se mantienen las minas correctamente marcadas por el usuario:
			if(v1[i][j]=='*' && v2[i][j]=='x') continue;

			else v2[i][j]=v1[i][j];
		}
	}
}

int main(){

	int i=0, j=0; //Variables de coordenadas.

	int m, n; //Dimensiones del tablero.

	int d=0, c=0, k=0, p=0, q=0, r=0, s=0, t=0; //Variables auxiliares.

	int cargar=0; //Variable que indica si se cargó una partida guardada.

	int minas; //Numero de Minas del juego..

	int primerTurno, minasAcertadas=0, minasIncorrectas=0;

	int menuGuardar=0;

	char nivel; //Indica en que nivel se está jugando.

	char opcion[100]; //Cadena de entrada de las opciones del menu.
	char op, op2;

	int ** noMina; //Matriz de casillas restringidas para el primer turno.

	time_t inicio; //Variable para contar el tiempo.

	double tiempoFinal; //Almacena el tiempo al ganar el juego, para el registro.

	double tiempoCargado=0; //Variable para el tiempo almacenado en la partida guardada.

	while(r==0){

		system("clear"); //Limpia la pantalla.

		mainMenu(); //Muestra el menú principal.

		scanf("%s",opcion); //Lee la opción ingresada por el usuario.

		q=strlen(opcion); //Calcula el tamaño de lo ingresado por el usuario.

		if(q==1){ //Sólo se permite la entrada de un caracter.

			op=opcion[0];

			if(op=='1'){

				cargar=0; //Al iniciar un nuevo juego la variable 'cargar' se inicializa en '0'
				r=1; //Nuevo juego.
			}

			while(op=='2'){ //Menú de Instrucciones del juego.

				system("clear");

				instrMenu(); //Muestra las instrucciones.

				scanf("%s",opcion);

				op2=opcion[0];

				s=strlen(opcion);

				if(s==1){ //Sólo se permite la entrada de un caracter.

					if(op2=='1'){

						r=1; //Inicia un nuevo juego.
						break;

					}

					else if(op2=='2'){

						op='3'; //Carga una partida guardada.
						break;
					}

					else if(op2=='3') { //Vuelve al menú principal.

						r=0;
						break;
					}

					else if(op2=='4'){

						r=3; //Sale del programa.
						break;
					}
				}
			}

			if(op=='3'){ //Carga una partida guardada.

				d=entregaDimensiones(&nivel, &m, &n); //Lee las dimensiones del tablero en el archivo guardado.

				if(d==0){

					r=menuSinPartidas(); //Si retorna '0' no hay partida guardada y se llama al menú correspondiente.

					cargar=0;

				}

				else{ //Cuando se carga la partida:

					cargar=1; //Indica que se inicia el juego desde una partida guardada.

					primerTurno=0; //No se comienza desde el primer turno.

					r=1; //Variable para entrar en el juego.
				}
			}

			while(op=='4'){

				//Menú para mostrar el registro de los mejores ganadores.
				system("clear");

				menuPuntajes(); //Muestra el menú correspondiente.

				scanf("%s",opcion); //Lee la opción que ingresa el usuario.

				op2=opcion[0];

				s=strlen(opcion);

				if(s==1){

					if(op2=='1'){

						//Muestra el registro del nivel fácil.
						r=mostrarPuntajes(1);
						if(r!=5) break;
					}

					else if(op2=='2'){

						//Muestra el registro del nivel medio.
						r=mostrarPuntajes(2);
						if(r!=5) break;
					}

					else if(op2=='3'){

						//Muestra el registro del nivel dificil.
						r=mostrarPuntajes(3);
						if(r!=5) break;
					}

					else if(op2=='4'){ //Inicia un nuevo juego.

						r=1;
						break;
					}

					else if(op2=='5'){ //Vuelve al Menú Principal.

						r=0;
						break;
					}
				}
			}

			while(r==1){

				//Menú de selección de dificultad:

				if(cargar==0){ //Sólo se selecciona dificultad en partidas nuevas.

					system("clear");

					nivelMenu(); //Muestra el menú de selección de dificultad.

					scanf("%s",opcion); //Lee la opción del usuario.

					s=strlen(opcion);

					if(s==1){ //Sólo se permite la entrada de un caracter.

						op=opcion[0];

						if(op=='1'){ //Nivel Facil, 9x9 con 8 minas.

							nivelFacil(&m, &n, &minas);
							nivel=1;
							r=2;
						}

						else if(op=='2') { //Nivel Medio, 9x15 con 25 minas.

							nivelMedio(&m, &n, &minas);
							nivel=2;
							r=2;
						}

						else if(op=='3') { //Nivel Dificil, 9x23 con 50 minas.

							nivelDificil(&m, &n, &minas);
							nivel=3;
							r=2;
						}

						else if(op=='4'){ //Nivel Personalizado.

							nivelPersonalizado(&m, &n, &minas);
							nivel=4;
							r=2;
						}

						else if(op=='5'){ //Vuelve al Menú Principal.

							r=0;
							op=0;
							break;
						}
					}

					op=0; //Se vuelve a '0' la variable de opciones.

				}

				else r=2; //Variable para entrar en modo de juego.

				while(r==2){

					//Ciclo del juego:
					if (cargar==0){ //Inicio del juego en partidas nuevas:

						system("clear");

						primerTurno=1; //Inicia con el primer turno.

						minasAcertadas=0; //Contador de las minas marcadas correctamente inicializado en '0'

						minasIncorrectas=0; //Contador de las minas marcadas incorrectamente inicializado en '0'

						menuGuardar=0;

						tiempoCargado=0;

					}

					char tablero[m][n]; //Tablero de juego con las minas y los números que las rodean.

					char mostrar[m][n]; //Tablero que ve el usuario.

					while(r==2){


						//En el primer turno se crea el tablero a mostrar y el tablero con las minas y sus numeros (no se permite marcar minas):
						if(primerTurno){

							time(&inicio); //Guarda el tiempo en el que se inicia el juego

							crearMostrar(m, n, mostrar); //Crea el tablero a mostrar al usuario.

							do{
								p=entrada(inicio, &tiempoCargado, m, n, &i, &j, mostrar, menuGuardar);//Función que lee las coordenadas del usuario y las valida. También muestra el tablero.
							} while(p==3 || p==2); //Si el usuario escribe 'guardar' o marca una mina en el primer turno, se mantiene en el ciclo de lectura y validación de entrada.

							if(p==1) break; //Si se escribe 'salir' se regresa al menú principal.

							p=0; //Se vuelve 'p' a '0' en caso de que se haya marcado una mina. Esto no se permite en el primer turno.

							noMina=restringido(i, j); //Función que restringe las casillas de minas en la primera coordenada ingresada y alrededores.

							crearTablero(m, n, minas, tablero, noMina); //Función que crea el tablero con las minas y sus correspondientes números indicadores.

							primerTurno=0; //Sale del primer turno.

							//Función que libera la memoria dinámica donde se almacenó las coordenadas restringidas de minas del primer turno:
							freeRestringido(noMina);
						}

						else if(cargar==1){ //Si cargar es '1'

								time(&inicio); //Inicia el contador del tiempo de juego.

								//Llama a la función para cargar la partida desde el archivo guardado.
								cargarPartida(d, &m, &n, &tiempoCargado, &minas, &minasAcertadas, &minasIncorrectas, tablero, mostrar);

								p=entrada(inicio, &tiempoCargado, m, n, &i, &j, mostrar, menuGuardar); //Se llama a función de validación de entrada y para mostrar tablero.
								cargar=0; //Sale del modo de carga.
						}

						else{
							//A partir del segundo turno se muestra el tablero al usuario, se validan las entradas, se permite el marcado de minas y guardar la partida:
							p=entrada(inicio, &tiempoCargado, m, n, &i, &j, mostrar, menuGuardar); //Se llama a función de validación de entrada y para mostrar tablero.
							menuGuardar=0;//Se vuelve a '0' la variable para mostrar en pantalla si se guardó una partida.

						}

						//Cuando las coordenadas del usuario coinciden con una mina (se pierde el juego) y si no está en modo de marcado (p=2) ni haya salido del juego (p=1) ni haya guardado la partida (p=3):

						if(tablero[i][j]=='*' && p==0){

							r=4; //Se ingresa al menú de perder.

							while(r==4){

								tableroFinal(m, n, tablero, mostrar); //Se revela todo el tablero.

								mostrar[i][j]='#'; //Se marca la mina que hizo perder al usuario con '#'

								mostrarTablero(m, n, mostrar); //Se muestra el tablero.

								tiempoFinal = calcularTiempo(inicio, &tiempoCargado); //Se muestra el tiempo total que duró el juego.

								printf("\x1B[0mTiempo: %.fs\n\n",tiempoFinal);

								printf("\x1B[0mHA PERDIDO :(\n"); //Mensaje para el usuario indicándole que perdió.

								//Menu mostrado al perder:
								selecMenu();

								scanf("%s",opcion);

								s=strlen(opcion);

								if(s==1){

									op=opcion[0];

									if(op=='1'){ //Inicia un nuevo juego.

										r=1; //Variable 'r' en '1' para seguir en modo de juego.
										k=1; //Variable 'k' en '1' para no entrar al menú de ganar.
									}

									else if(op=='2'){ //Vuelve al menú principal.

										r=0; //Variable 'r' en '0' para volver al menú principal.
										k=1;
									}

									else if(op=='3'){ //Sale del programa.

										r=3; //Variable 'r' en '3' para salir de todos los ciclos.
										k=1;
									}
								}
							}
						}

						//Cuando se despeja un espacio en blanco se llama a la funcion correspondiente:
						else if(tablero[i][j]==' ' && p==0) revelarTablero(m, n, i, j, tablero, mostrar);

						//En el modo de marcado de las minas si está con '-' se cambia a 'x' y viceversa:
						else if(p==2){

							if(mostrar[i][j]=='-'){

								mostrar[i][j]='x'; //Se marca con 'x'

								//Si se marca correctamente una mina se suma a las minas acertadas:
								if(tablero[i][j]=='*') ++minasAcertadas;

								//Si se marca una casilla que no tiene minas se suma a las minas marcadas incorrectamente:
								else if(tablero[i][j]!='*') ++minasIncorrectas;
							}

							else if(mostrar[i][j]=='x'){

								mostrar[i][j]='-'; //Se desmarca y se vuelve a '-'

								//Si se desmarca una mina correcta se descuenta a las minas acertadas:
								if(tablero[i][j]=='*') --minasAcertadas;

								//Si se desmarca una casilla que no tiene minas se descuenta a las minas marcadas incorrectamente:
								else if(tablero[i][j]!='*') --minasIncorrectas;
							}
						}

						else if(p==3){ //Si se escribe 'guardar':

							//Se obtiene el tiempo actual para guardarlo:
							tiempoFinal = calcularTiempo(inicio, &tiempoCargado);

							//Se llama a la función para guardar la partida, con los valores a guardar:
							guardarPartida(m, n, nivel, tiempoFinal, minas, minasAcertadas, minasIncorrectas, tablero, mostrar);

							//Variable 'menuGuardar' en '1' para mostrar en pantalla que se guardó la partida:
							menuGuardar=1;
						}

						/* En caso de que el usuario haya marcado una mina incorrectamente y se dio cuenta de su error y
						   revela esa casilla, se descuenta de las minas marcadas incorrectamente */
						else if(p==0 && tablero[i][j]!='*' && tablero[i][j]!=' ' && mostrar[i][j]=='x'){

							mostrar[i][j]=tablero[i][j];
							--minasIncorrectas;
						}

						else if(p==0 && tablero[i][j]==' ' && mostrar[i][j]=='x'){

							revelarTablero(m, n, i, j, tablero, mostrar);
							--minasIncorrectas;
						}

						//Revela el tablero en caso de que no se revele una mina ni un espacio en blanco:
						else if(p==0) mostrar[i][j]=tablero[i][j];

						//Se llama a la función para comprobar si se ganó el juego:
						c=estadoGanar(m, n, tablero, mostrar, minas, &minasAcertadas, &minasIncorrectas);

						if(c && k==0){ //Si estadoGanar devuelve '1' y 'k' está en '0' se entra al menú de ganar.

							r=4; //Se ingresa el menú de ganar.

							t=0; //Variable para controlar la llamada a la función de registro del ganador.

							while(r==4){

								//Cuando el usuario gana se revela todo el tablero:
								tableroFinal(m, n, tablero, mostrar);

								mostrarTablero(m, n, mostrar);

								tiempoFinal = calcularTiempo(inicio, &tiempoCargado); //Se guarda el tiempo total que duró el juego.

								printf("\x1B[0mTiempo: %.fs\n\n",tiempoFinal); //Se muestra el tiempo total del juego.

								printf("\x1B[0mHA GANADO! :)\n"); //Mensaje para el usuario indicándole que ganó.

								if(t==0 && nivel!=4){ //No se registran los ganadores del nivel personalizado.

									//Llama a la función para guardar al ganador, con el nivel en que estaba y el tiempo final.
									registrarGanador(&nivel, &tiempoFinal);

									t=1; //Variable 't' en '1' para no volver a pedir el nombre al ganador.
								}

								//Menú al ganar el juego:
								selecMenu();

								scanf("%s",opcion);

								s=strlen(opcion);

								if(s==1){

									op=opcion[0];

									if(op=='1'){ //Inicia un nuevo juego.

										r=1;
										k=1;
									}

									else if(op=='2') r=0; //Vuelve al menú principal.

									else if(op=='3') r=3; //Sale del programa.
								}
							}
						}

						if(p==1) break; //Vuelve al menú principal.

						if(k==1) break; //Inicia un nuevo juego.
					}//Cierre del ciclo con r=2.

					k=0; //Variable 'k' que controla el menú de ganar, se vuelve a '0'

					if(p==1) r=0; //Vuelve al menú principal.
				}
			}//Cierre del ciclo con r=1.

			if(op=='5') break; //Sale del programa.
		}
	}// Cierre del ciclo con r=0.

	system("clear"); //Limpia la pantalla al salir del programa.

	return(0);
}
