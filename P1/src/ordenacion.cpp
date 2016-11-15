#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include <vector> 
#include <string>
#include <time.h>
#include <algorithm>
#include <map>

#define POS_NULA -1 

// practica 1
// ANALISIS DE EFICIENCIA DE ALGORITMOS
//

/* El objetivo de la practica es doble, por una lado ilustrar de forma empirica cómo se puede computar el tiempo de ejecución de un algoritmo
y, por otro, ilustrar como el uso de distintas estructuras de datos nos permite mejorar la eficiencia de los algoritmos
*/



using namespace std;
/* Lee un fichero  sobre un vector de string
 nf: nombre del fichero
 V: vector sobre el que se lee el fichero
 */
void lee_fichero( const char * nf, vector<string> & V) {
 ifstream fe;
  string s;
 fe.open(nf, ifstream::in);
 while ( !fe.eof() )
   { fe >> s;
     if (!fe.eof())
       V.push_back(s);
   }
 fe.close();
}

/* algoritmo de ordenacion por burbuja
 T: vector sobre el que se lee el fichero
 inicial: primera posicion desde la que buscar
 final : posicion siguiente a la ultima para buscar (desde V[0] hasta V[fin-1])
 */
void burbuja(vector<string> & T, int inicial, int final) {
int i, j;
string aux;
for (i = inicial; i < final - 1; i++)
for (j = final - 1; j > i; j--)
if (T[j] < T[j-1]) {
  aux = T[j];
T[j]= T[j-1];
T[j-1] = aux;
}

}

void insercion(vector<string> & T, int inicial, int final)
{
  int i, j;
  string aux;
  for (i = inicial + 1; i < final; i++) {
    aux = T[i];
    for (j = i; j > 0 && T[j - 1] > aux; --j)
      T[i] = T[j-1];

  }
}
 
void seleccion(vector<string> & T, int inicial, int final)
{
  int i, j, indice_menor;
  string menor, aux;
  for (i = inicial; i < final - 1; i++) {
    indice_menor = i;
    menor = T[i];
    for (j = i; j < final; j++)
      if (T[j] < menor) {
	indice_menor = j;
	menor = T[j];
      }
    aux = T[i];
    T[i] = T[indice_menor];
    T[indice_menor] = aux;
  }
}


int main() {

 vector<string> Dicc;
 vector<string> Q;
 int pos;
 clock_t start,end;
  
vector<int> frecuencia;
vector<string> palabra;

 int contador =0;
 
 lee_fichero("lema.txt", Dicc); // Ojo, el vector no esta ordenado!!!
 //cout << Dicc.size() << " " << Dicc.capacity() << endl;
 
 lee_fichero("quijote.txt", Q);
 //cout << Q.size() << " " << Q.capacity() << endl;
 
 
 
 vector<string> aux;

////////////////////////////////////////////////////
 // ORDENACION POR BURBUJA
 ////////////////////////////////////////////////////

cout << "Ordenacion Burbuja"<< endl;
for (int tama = 100; tama < Dicc.size()*0.75 ; tama+= 3000){
  aux =Dicc;
  start = clock();
  burbuja(aux, 0,tama );
 //sort(aux.begin(), aux.begin()+tama);
  end= clock(); 
  double dif = end-start;
  cout << tama << " " << dif/CLOCKS_PER_SEC <<  endl;

}

////////////////////////////////////////////////////
 // ORDENACION POR SELECCION
 ////////////////////////////////////////////////////

cout << "Ordenacion Seleccion"<< endl;
for (int tama = 100; tama < Dicc.size()*0.75 ; tama+= 3000){
  aux =Dicc;
  start = clock();
  seleccion(aux, 0,tama );
  end= clock(); 
  double dif = end-start;
  cout << tama << " " << dif/CLOCKS_PER_SEC <<  endl;

}

////////////////////////////////////////////////////
 // ORDENACION POR INSERCION
 ////////////////////////////////////////////////////

cout << "Ordenacion Insercion"<< endl;
for (int tama = 100; tama < Dicc.size()*0.75 ; tama+= 3000){
  aux =Dicc;
  start = clock();
  insercion(aux, 0,tama );
  end= clock(); 
  double dif = end-start;
  cout << tama << " " << dif/CLOCKS_PER_SEC <<  endl;

}




}
 
