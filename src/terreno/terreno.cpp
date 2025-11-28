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
  dados = new int*[tamanho];

  for (int i = 0; i < tamanho; i++) {
    dados[i] = new int[tamanho];
  }
}

void Terreno::liberarMemoria() {
  for (int i = 0; i < tamanho; i++) {
    delete[] dados[i];
  }
  delete[] dados;
}

bool Terreno::gerarTerreno(double rugosidade) {
  
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
