#include "terreno.h"

Terreno::Terreno(int tamanho) : tamanho(std::pow(2, tamanho) + 1) {}

Terreno::~Terreno() {
  if (dados != nullptr) {
    for (int i = 0; i < tamanho; i++) {
      delete[] dados[i];
    }
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

    // Inicializa como 0
    for (int j = 0; j < tamanho; j++) {
      dados[i][j] = 0;
    }
  }
}

void Terreno::liberarMemoria() {
  for (int i = 0; i < tamanho; i++) {
    delete[] dados[i];
  }
  delete[] dados;
}

void Terreno::diamond(int constante, double deslocamento) {
  int mconstante = constante / 2;
  for (int y = mconstante; y < tamanho - 1; y += constante) {
    for (int x = mconstante; x < tamanho - 1; x += constante) {
      int p1 = dados[y - mconstante][x - mconstante];
      int p2 = dados[y - mconstante][x + mconstante];
      int p3 = dados[y + mconstante][x - mconstante];
      int p4 = dados[y + mconstante][x + mconstante];

      dados[y][x] = (p1 + p2 + p3 + p4) / 4.0 + gerarNumero(0, deslocamento);
    }
  }
};

double Terreno::media_square(Ponto ponto, int constante) {
  Ponto pontos[4] { 
    { ponto.x - constante, ponto.y },
    { ponto.x + constante, ponto.y },
    { ponto.x, ponto.y - constante },
    { ponto.x, ponto.y + constante },
  };

  int qtd = 0;
  double sum = 0;
  for (int i = 0; i < 4; i++) {
    if (pontos[i].x >= 0 && pontos[i].x < tamanho && pontos[i].y >= 0 && pontos[i].y < tamanho) {
      sum += dados[pontos[i].y][pontos[i].x]; 
      qtd++;
    }
  }
  return sum / qtd;
}

void Terreno::square(int constante, double deslocamento) {
  int mconstante = constante / 2;
  for (int y = 0; y < tamanho; y += mconstante) {
    for (int x = ((y / mconstante) % 2 == 0) ? mconstante : 0; x < tamanho; x += constante) {
      dados[y][x] = media_square({ x, y }, mconstante) + gerarNumero(0, deslocamento);
    }
  }
}

double Terreno::gerarNumero(int min, int max) {   
    double rnd = (double) rand() / RAND_MAX;
    return min + rnd * (max - min);
}

bool Terreno::gerarTerreno(double rugosidade){
    criarMatriz();

    srand(time(0));
    dados[0][0] = gerarNumero();
    dados[0][tamanho-1] = gerarNumero();
    dados[tamanho-1][0] = gerarNumero();
    dados[tamanho-1][tamanho-1] = gerarNumero();

    int constante = tamanho - 1;
    double deslocamento = 10;

    while (constante > 1) {
      diamond(constante, deslocamento);
      square(constante, deslocamento);
      
      deslocamento *= rugosidade;
      constante /= 2;
    }

    return true;
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
    terreno << this->tamanho << std::endl;

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
