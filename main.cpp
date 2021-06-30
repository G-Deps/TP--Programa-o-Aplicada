#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct tComplexo{
  int real;
  int imaginario;
  tComplexo* proximo;
};
tComplexo* criaComplexo(int NumReal, int NumImaginario){
  tComplexo* complexo = new tComplexo;

  complexo -> real = NumReal;
  complexo -> imaginario = NumImaginario;

  return complexo;
}
struct tLista{
  tComplexo* primeiro;
  tComplexo* ultimo;
  tComplexo* marcador;
  int tamanho;
};
void iniciaLista(tLista* pLista){
  pLista -> primeiro = NULL;
  pLista -> ultimo = NULL;
  pLista -> marcador = NULL;
  pLista -> tamanho = 0;
}
int obterTamanho(tLista* pLista){
  return pLista->tamanho;
}
bool listaVazia(tLista* pLista){
  return (pLista -> tamanho == 0);
}
bool finalLista(tLista* pLista){
  return (pLista -> marcador == NULL);
}
void incluirNoFim(tLista* pLista, int real, int imaginario){
  tComplexo* complexo = criaComplexo(real, imaginario);

  if(listaVazia(pLista)){
    pLista -> primeiro = complexo;
  } else{
    pLista -> ultimo -> proximo = complexo;
  }

  pLista -> ultimo = complexo;
  pLista -> marcador = complexo;
  pLista -> tamanho++;
}
void gravarLista(tLista* pLista,ofstream* outfile){
  pLista -> marcador = pLista-> primeiro;

  while(!finalLista(pLista)){
    int real = pLista->marcador->real;
    int imaginario = pLista->marcador->imaginario;
    //*outfile << "Real" << " " << "Imaginario" << endl;
    cout<<"Parte real: "<< real <<" ,Parte imaginaria: "<<imaginario<<endl;
    *outfile << real << " " << imaginario << " "<< endl;

    pLista->marcador = pLista->marcador->proximo;
  }
  *outfile << flush;
  
}
void escrever(int quant,tLista* pLista){
  ofstream arquivo("db.txt", ios::out );
  if (! arquivo)
  { cout << "Arquivo db.txt nao pode ser aberto" << endl;
  abort();
  }
  int parteReal, parteImaginaria;
  for(int i=0; i<quant; i++){
    cout<<"Insira a parte real do "<<i+1<<" numero\n";
    cin>>parteReal;
    cout<<"Insira a parte imaginaria do "<<i+1<<" numero\n";
    cin>>parteImaginaria;
    incluirNoFim(pLista,parteReal,parteImaginaria);
  }

  gravarLista(pLista,&arquivo);
  arquivo.close();
  free(pLista);
}
void ler(){
  int real,imaginario,escreve=0;
  string valor;
  tLista* leitura = new tLista;
  iniciaLista(leitura);

  ifstream inFile("db.txt", ios::in);
  if (! inFile)
  { cout << "Arquivo db.txt nao pode ser aberto" << endl;
  abort();
  }
  if(inFile.peek() == ifstream::traits_type::eof() ){
    cout<<"Arquivo vazio\n";
  }
  while (! inFile.eof() ){ 
    int cont = 0;
    getline (inFile,valor);
    string aux;
    for(int i=0;i<=valor.length();i++){
      if(valor[i]!=' '){
        aux+=valor[i];
      }else{
        cont++;
        if(cont == 1){
          real = stoi(aux,nullptr,10);
          aux = "";
        }else if(cont == 2){ 
          imaginario = stoi(aux,nullptr,10);
          incluirNoFim(leitura,real,imaginario);
          aux = "";
        }
        
        
      }
    }
  }

  leitura -> marcador = leitura-> primeiro;

  while(!finalLista(leitura)){
    int real = leitura->marcador->real;
    int imaginario = leitura->marcador->imaginario;
    cout<<"Parte real: "<< real <<" ,Parte imaginaria: "<<imaginario<<endl;

    leitura->marcador = leitura->marcador->proximo;
  }

  free(leitura);
}


int main() {
  int loop = 1;
  tLista* Complexo = new tLista;
  iniciaLista(Complexo);
  while(loop ==1){
    int input;
    cout<<"Digite 1 para escrever / 2 para ler / 3 para sair\n";
    cin>>input;

    switch(input){
      case (1):
          int quant;
          cout<<"Quantos numeros complexos deseja gravar?\n";
          cin>>quant;
          if(quant>0){
            escrever(quant, Complexo);
          }else{
            cout<<"Quantidade inválida\n";
          }
          
        break;
      case (2):
          ler();
        break;
      case (3): 
          loop = 2;
        break;

      default:
          cout<<"Valor indefinido\n";
        break;
    }
  }
}