#include "terreno.h"

Terreno::Terreno(int tamanho) : tamanho(std::pow(2, tamanho) + 1) {}

Terreno::~Terreno() {
  liberarMemoria();
}

// (x, y)
int Terreno::operator() (int largura, int profundidade) {
  return dados[profundidade][largura];
}

void Terreno::criarMatriz() {
  dados = new int*[tamanho];

  for (int i = 0; i < tamanho; i++) {
    dados[i] = new int[tamanho];

    // Inicializa como 0
    for (int j = 0; j < tamanho; j++) {
      dados[i][j] = 0;
    }
  }
}

void Terreno::liberarMemoria() {
  if (dados != nullptr) {
    for (int i = 0; i < tamanho; i++) {
      delete[] dados[i];
    }
    delete[] dados;
  }
}

int Terreno::gerarNumero(int min, int max) {   
    int rnd = (rand() % (max - min + 1)) + min;
    return rnd;
}

void Terreno::diamond(int constante, int deslocamento) {
  int mconstante = constante / 2;
  for (int y = mconstante; y < tamanho - 1; y += constante) {
    for (int x = mconstante; x < tamanho - 1; x += constante) {
      int p1 = dados[y - mconstante][x - mconstante];
      int p2 = dados[y - mconstante][x + mconstante];
      int p3 = dados[y + mconstante][x - mconstante];
      int p4 = dados[y + mconstante][x + mconstante];

      int valor = round((p1 + p2 + p3 + p4) / 4.0) + gerarNumero(-deslocamento, deslocamento);
      dados[y][x] = valor < 0 ? 0 : valor;
    }
  }
};

void Terreno::square(int constante, int deslocamento) {
  int mconstante = constante / 2;
  for (int y = 0; y < tamanho; y += mconstante) {
    for (int x = ((y / mconstante) % 2 == 0) ? mconstante : 0; x < tamanho; x += constante) {
      int valor = media_square({ x, y }, mconstante) + gerarNumero(-deslocamento, deslocamento);
      dados[y][x] = valor < 0 ? 0 : valor;
    }
  }
}

int Terreno::media_square(Ponto ponto, int constante) {
  Ponto pontos[4] { 
    { ponto.x - constante, ponto.y },
    { ponto.x + constante, ponto.y },
    { ponto.x, ponto.y - constante },
    { ponto.x, ponto.y + constante },
  };

  int qtd = 0;
  int sum = 0;
  for (int i = 0; i < 4; i++) {
    if (pontos[i].x >= 0 && pontos[i].x < tamanho && pontos[i].y >= 0 && pontos[i].y < tamanho) {
      sum += dados[pontos[i].y][pontos[i].x]; 
      qtd++;
    }
  }
  return round(sum / qtd);
}

void Terreno::imagemCores(Imagem& imagem, Paleta& cores) {
  // A cor do pixel será determinada por certo intervalo
  // Sendo n o tamanho da paleta
  // O tamanho dos intervalos é calculado por 100/n
  // O intervalo a que uma coisa pertence é x/(100/n) ou melhor (x*n)/100

  for (int y = 0; y < tamanho; y++) {
    for (int x = 0; x < tamanho; x++) {
      int intervalo = dados[y][x] == 1000 ? cores.obterTamanho() - 1 : (cores.obterTamanho() * (int) dados[y][x])/ 1000;
      Pixel cor = intervalo > cores.obterTamanho() ? cores.obterCor(cores.obterTamanho() - 1) :cores.obterCor(intervalo);
      imagem(x, y) = cor;
    }
  }
}

void Terreno::imagemLuz(Imagem& imagem, Paleta& cores, int reducao) {
  imagemCores(imagem, cores);
  for (int y = 1; y < tamanho; y++) {
    for (int x = 1; x < tamanho; x++) {
      if (dados[y-1][x-1] > dados[y][x]) {
        imagem(x, y).r /= reducao;
        imagem(x, y).g /= reducao;
        imagem(x, y).b /= reducao;
      }
    }
  }
}

bool Terreno::gerarTerreno(int rugosidade){
    criarMatriz();

    srand(time(0));
    dados[0][0] = gerarNumero();
    dados[0][tamanho-1] = gerarNumero();
    dados[tamanho-1][0] = gerarNumero();
    dados[tamanho-1][tamanho-1] = gerarNumero();

    int constante = tamanho - 1;
    int deslocamento = 500;

    while (constante > 1) {
      diamond(constante, deslocamento);
      square(constante, deslocamento);
      
      deslocamento /= rugosidade;
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

bool Terreno::salvarImagem(int tipo, const char* arquivo, Paleta& cores, int reducao) {
  Imagem imagem(tamanho, tamanho);

  switch (tipo) {
    case IMAGEM_TIPO_GRAYSCALE:
      return false;
    case IMAGEM_TIPO_COR:
      imagemCores(imagem, cores);
      break;
    case IMAGEM_TIPO_LUZ:
      imagemLuz(imagem, cores, reducao);
      break;
  }

  imagem.salvarPPM(arquivo);

  return true;
}
