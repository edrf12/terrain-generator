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

  void diamond(int constante, double deslocamento);
  double media_square(Ponto ponto, int constante);
  void square(int constante, double deslocamento);

  void criarMatriz();
  void liberarMemoria();
  double gerarNumero(int min = 0, int max = 100);

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
