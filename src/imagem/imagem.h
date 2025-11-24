#pragma once

#include "../sequencia/sequencia.h"
#include "../paleta/paleta.h"
#include <iostream>
#include <fstream>

using Pixel = Cor;

class Imagem {
private:
  Sequencia<Pixel> dados;
  int altura;
  int largura;

public:
  Imagem() : dados(), altura(0), largura(0) {};
  Imagem(int altura, int largura) : altura(altura), largura(largura) {};
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
