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
  int** dados = nullptr;
  int tamanho;

  void criarMatriz();
  void liberarMemoria();

  int gerarNumero(int min = 0, int max = 1000);
  void diamond(int constante, int deslocamento);
  void square(int constante, int deslocamento);
  int media_square(Ponto ponto, int constante);
  
  void imagemCores(Imagem& imagem, Paleta& cores);
  void imagemLuz(Imagem& imagem, Paleta& cores, int reducao = 2);
public:
  Terreno(int tamanho);
  ~Terreno();
  int operator() (int largura, int profundidade);

  bool gerarTerreno(int rugosidade = 2);
  bool lerTerreno(const char* arquivo);
  bool salvarTerreno(const char* arquivo);
  bool salvarImagem(int tipo, const char* arquivo, Paleta& cores, int reducao = 2);

  int obterLargura() {
    return tamanho;
  }

  int obterProfundidade() {
    return tamanho;
  }
};
