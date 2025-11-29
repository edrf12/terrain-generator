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

void Terreno::diamond(Ponto p1, Ponto p2, Ponto p3, Ponto p4) {
  if (p4.x - p1.x > 1 && p4.y - p1.y > 1) {
    Ponto atual = { (p4.x - p1.x) / 2 + p1.x, (p4.y - p1.y ) / 2 + p1.y };
    dados[atual.y][atual.x] = (dados[p1.y][p1.x] + dados[p2.y][p2.x] + dados[p3.y][p3.x] + dados[p4.y][p4.x]) / 4;

    square(atual, p1);
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

void Terreno::square(Ponto centro, Ponto referencia) {
  if (centro.y - referencia.y > 0 && centro.x - referencia.x > 0) {
    int constante = centro.x - referencia.x;
    Ponto p1 = { centro.x, referencia.y};
    Ponto p2 = { referencia.x, centro.y };
    Ponto p3 = { centro.x, centro.y + constante};
    Ponto p4 = { centro.x + constante, centro.y};

    dados[p1.y][p1.x] = media_square(p1, constante);
    dados[p2.y][p2.x] = media_square(p2, constante);
    dados[p3.y][p3.x] = media_square(p3, constante);
    dados[p4.y][p4.x] = media_square(p4, constante);

    diamond(referencia, p1, p2, centro);
    diamond(p1, { p1.x + constante, p1.y }, centro, p4);
    diamond(p2, centro, { p3.x - constante, p3.y }, p3);
    diamond(centro, p2, p3, { p3.x + constante, p3.y });
  }
}

int Terreno::gerarNumero() {   
    // int min(0), max(100);
    // int rnd = (rand() % (max - min + 1)) + min;
    // return rnd;
    return 1;
}

bool Terreno::gerarTerreno(double rugosidade){
    criarMatriz();

    srand(time(0));
    dados[0][0] = gerarNumero();
    dados[0][tamanho-1] = gerarNumero();
    dados[tamanho-1][0] = gerarNumero();
    dados[tamanho-1][tamanho-1] = gerarNumero();

    diamond({0, 0}, {tamanho - 1, 0}, {0, tamanho - 1}, {tamanho -1 , tamanho - 1});

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
