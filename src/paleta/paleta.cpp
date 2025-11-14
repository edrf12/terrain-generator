#include "paleta.h"

Paleta::Paleta(const char *arquivo) {
    std::ifstream paleta(arquivo);
    if (paleta.is_open()) {
        int linha = 1;
        while (!paleta.eof()) {
            std::string cor;
            std::getline(paleta, cor);

            if (cor.empty()) {
              break;
            }

            this->adicionarCor(hexToColor(cor, arquivo, linha));
            linha++;
        }
    }
    else {
      std::cerr << "[Paleta]: Não foi possível abrir o arquivo especificado pelo nome " << arquivo << std::endl;
    }
    paleta.close();
}

uint8_t Paleta::hexToNumber(const char hex) {
  switch (std::toupper(hex)) {
    case 'A':
      return 10;
    case 'B':
      return 11;
    case 'C':
      return 12;
    case 'D':
      return 13;
    case 'E':
      return 14;
    case 'F':
      return 15;
    default:
      return hex - '0';
  }
}

Cor Paleta::hexToColor(const std::string color, const char *arquivo, const int linha) {
  if ((color[0] == '#' && color.size() == 7) || color.size() == 6) {
    uint8_t n = 0;
    if (color[0] == '#') {
      n++;
    }

    uint8_t r = hexToNumber(color[n]) * 16 + hexToNumber(color[n + 1]); 
    uint8_t g = hexToNumber(color[n + 2]) * 16 + hexToNumber(color[n + 3]); 
    uint8_t b = hexToNumber(color[n + 4]) * 16 + hexToNumber(color[n + 5]); 

    return Cor{r, g, b};
  } else {
    std::cerr << "[Paleta]: O arquivo especificado " << arquivo << " contêm uma cor inválida na linha " << linha << std::endl;
    return Cor{};
  }
}

void Paleta::adicionarCor(Cor cor) {
    this->cores.adicionar(cor);
}

int Paleta::obterTamanho() {
    return this->cores.obterTamanho();
}

Cor Paleta::obterCor(int indice) {
    return this->cores[indice];
}
