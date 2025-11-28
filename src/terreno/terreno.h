#include <cmath>
#include <fstream>
#include <ctime>
#include <cstdlib>

struct Ponto {
  int x, y;
};

class Terreno {
private:   
  double** dados;
  int tamanho;

  void diamond();
  void square();

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
