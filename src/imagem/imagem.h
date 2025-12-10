#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "../paleta/paleta.h"

using Pixel = Cor;

class Imagem {
private:
  Pixel** dados;
  int altura;
  int largura;
  void criarMatriz();
  void liberarMemoria();

public:
  Imagem() : dados(nullptr), altura(0), largura(0) {};
  Imagem(int largura, int altura);
  ~Imagem();
  Pixel& operator() (int largura, int altura);

  int obterAltura() {
    return altura;
  }

  int obterLargura() {
    return largura;
  }

  bool lerPPM(const char* arquivo);
  bool salvarPPM(const char* arquivo);
};
