#include "terreno.h"

Terreno::Terreno(int tamanho) {
  this->tamanho =  std::pow(2, tamanho) + 1;
}

Terreno::~Terreno() {
  for (int i = 0; i < tamanho; i++) {
    delete[] dados[i];
  }
  delete[] dados;
}

// (x, y)
int Terreno::operator() (int largura, int profundidade) {
  return dados[profundidade][largura];
}

void Terreno::criarMatriz() {
  dados = new double*[tamanho];

  for (int i = 0; i < tamanho; i++) {
    dados[i] = new double[tamanho];
  }
}

void Terreno::liberarMemoria() {
  for (int i = 0; i < tamanho; i++) {
    delete[] dados[i];
  }
  delete[] dados;
}
int Terreno::gerarNumero() {   
    srand(time(0));
    int min(0), max(100);
    int rnd = (rand() % (max - min + 1)) + min;
    return rnd;
}
bool Terreno::gerarTerreno(double rugosidade){
    criarMatriz();

    dados[0][0] = gerarNumero();
    dados[0][tamanho-1] = gerarNumero();
    dados[tamanho-1][0] = gerarNumero();
    dados[tamanho-1][tamanho-1] = gerarNumero();
    int linha1 = 
    //primeira diamond
    dados[(tamanho-1)/2][(tamanho-1)/2] = gerarNumero(); 
    //primeira square
    dados[][(tamanho-1)/2] = gerarNumero();
    dados[(tamanho-1)/2][] = gerarNumero();
}

bool Terreno::lerTerreno(const char* arquivo) {
  std::ifstream terreno(arquivo);
  if (terreno.is_open()) {
    int linha = 1;

    liberarMemoria();
    while (linha == 1) {
      terreno >> tamanho; 
      linha++;
    }

    criarMatriz();

    return true;
  }
  return false;
}

bool Terreno::salvarTerreno(const char* arquivo) {
  std::ofstream terreno(arquivo);
  if (terreno.is_open()) {
    terreno << this->tamanho;

    for (int y = 0; y < tamanho; y++) {
      for (int x = 0; x < tamanho; x++) {
        terreno << dados[y][x];

        if (x == tamanho - 1) {
          terreno << std::endl;
        } else {
          terreno << " ";
        }
      }
    }

    return true;
  }

  return false;
}
