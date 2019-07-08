#include<iostream>
#include <stdlib.h>
using namespace std;

int main(){
  int r[12][12]{0},g[12][12]{0},b[12][12]{0};

//tratar o cabeçario;
  string aux,aux2;
  while (cin >> aux) {
    cin >> aux2;
    if(atoi(aux.c_str()) == 12 &&  atoi(aux2.c_str()) == 12){
        if(aux != aux2){
          cout << "A imagem não está no Tamanho 12 X 12" << endl;
          return 0;
          cin >> aux2;
        }
        break;
    }
  }

for(int j=0;j<12;j++)
  for(int i=0;i < 12;i++){
    cin >> aux;
    r[j][i] = atoi(aux.c_str());
    cin >> aux;
    g[j][i] = atoi(aux.c_str());
    cin >> aux;
    b[j][i] = atoi(aux.c_str());
  }

//imprimir a declaraçao das cores

  cout << endl << "unsigned int r[12][12]{" << endl;
  for(int j=0;j<12;j++){
    cout << endl;
    for(int i=0; i < 12 ; i++ ){
      cout << r[j][i] << ", ";
    }
  }
  cout << "};" << endl;

 cout << endl << "unsigned int g[12][12]{" << endl;
 for(int j=0;j<12;j++){
   cout << endl;
   for(int i=0; i < 12 ; i++ ){
     cout << g[j][i] << ", ";
    }
  }
 cout << "};" << endl;

 cout << endl << "unsigned int b[12][12]{" << endl;
 for(int j=0;j<12;j++){
   cout << endl;
   for(int i=0; i < 12 ; i++ ){
     cout << b[j][i] << ", ";
   }
  }
  cout << "};" << endl;

  return 0;
}
