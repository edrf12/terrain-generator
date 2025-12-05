#pragma once

#include <cmath>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "../imagem/imagem.h"
#include "../paleta/paleta.h"

#define IMAGEM_TIPO_GRAYSCALE 0
#define IMAGEM_TIPO_COR 1
#define IMAGEM_TIPO_LUZ 2

struct Ponto {
  int x, y;
};

class Terreno {
private:   
  double** dados = nullptr;
  int tamanho;

  void criarMatriz();
  void liberarMemoria();

  double gerarNumero(int min = 0, int max = 100);
  void diamond(int constante, double deslocamento);
  double media_square(Ponto ponto, int constante);
  void square(int constante, double deslocamento);
  
  void imagemCores(Imagem& imagem, Paleta& cores);
  void imagemLuz(Imagem& imagem, Paleta& cores);
public:
  Terreno(int tamanho);
  ~Terreno();
  int operator() (int largura, int profundidade);

  bool gerarTerreno(double rugosidade = 0.5);
  bool lerTerreno(const char* arquivo);
  bool salvarTerreno(const char* arquivo);
  bool salvarImagem(int tipo, const char* arquivo, Paleta& cores);

  int obterLargura() {
    return tamanho;
  }

  int obterProfundidade() {
    return tamanho;
  }
};
