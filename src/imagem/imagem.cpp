#include "imagem.h"

Imagem::Imagem(int largura, int altura) : altura(altura), largura(largura) {
 criarMatriz(); 
}

Imagem::~Imagem() {
  liberarMemoria();
}

void Imagem::criarMatriz() {
  dados = new Pixel*[altura];

  for (int i = 0; i < altura; i++) {
    dados[i] = new Pixel[largura];
  }
}

void Imagem::liberarMemoria() {
  if (dados != nullptr) {
    for (int i = 0; i < altura; i++) {
      delete[] dados[i];
    }
    delete[] dados;
  }
}

Pixel& Imagem::operator() (int largura, int altura) {
  return dados[altura][largura];
}

bool Imagem::lerPPM(const char* arquivo) {
  int altura;
  int largura;

  std::ifstream imagem(arquivo);
  if (imagem.is_open()) {
    int linha = 1;


    while (linha <= 3) {
      if (linha == 1) {
        std::string line;
        std::getline(imagem, line);
        if (line != "P3") return false;
      }

      if (linha == 2) {
        imagem >> largura >> altura;
      }

      if (linha == 3) {
        int size;
        imagem >> size;

        if (size != 255) return false;
      }

      linha++;
    }

    liberarMemoria();

    this->altura = altura;
    this->largura = largura;

    criarMatriz();

    for (int i = 0; i < altura; i++) {
      for (int j = 0; j < largura; j++) {
        int r, g, b;
        imagem >> r >> g >> b;
        dados[i][j].r = r;
        dados[i][j].g = g;
        dados[i][j].b = b;
      }
    }
    return true;
  }

  return false;
}

bool Imagem::salvarPPM(const char* arquivo) {
  std::ofstream imagem(arquivo);

  if (imagem.is_open()) {
    imagem << "P3" << std::endl;
    imagem << largura << " " << altura << std::endl;
    imagem << 255 << std::endl;

    for (int i = 0; i < altura; i++) {
      for (int j = 0; j < largura; j++) {
        imagem << (int) dados[i][j].r << " " << (int) dados[i][j].g << " " << (int) dados[i][j].b;

        // if (j != largura - 1) {
          // imagem << "  ";
        // }
        imagem << std::endl;
      }
    }
    imagem.close();
    return true;
  }

  return false;
}
