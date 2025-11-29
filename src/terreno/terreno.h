#include <cmath>
#include <fstream>
#include <ctime>
#include <cstdlib>

struct Ponto {
  int x, y;
};

class Terreno {
private:   
  double** dados = nullptr;
  int tamanho;

  void diamond(Ponto p1, Ponto p2, Ponto p3, Ponto p4);
  double media_square(Ponto ponto, int constante);
  void square(Ponto centro, Ponto referencia);

  void rand_altura();

  void criarMatriz();
  void liberarMemoria();
  int gerarNumero();

public:
  Terreno(int tamanho);
  ~Terreno();
  int operator() (int largura, int profundidade);

  bool gerarTerreno(double rugosidade = 0.5);
  bool lerTerreno(const char* arquivo);
  bool salvarTerreno(const char* arquivo);

  int obterLargura() {
    return tamanho;
  }

  int obterProfundidade() {
    return tamanho;
  }
};
