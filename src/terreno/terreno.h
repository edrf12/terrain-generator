#include <cmath>
#include <fstream>

class Terreno {
private:   
  int** dados;
  int tamanho;

  void diamond();
  void square();

  void rand_altura();

  void criarMatriz();
  void liberarMemoria();
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
