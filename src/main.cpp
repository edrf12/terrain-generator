#include <cctype>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "paleta/paleta.h"
#include "terreno/terreno.h"

int main(int argc, char* argv[]) {
  int rugosidade = 2;
  int tipo_imagem = IMAGEM_TIPO_LUZ;
  int reducao = 2;
  int opt;

  while ((opt = getopt(argc, argv, "r:t:s:")) != -1) {
    switch (opt) {
      case 'r':
        rugosidade = std::stoi(optarg);
        break;
      case 't':
        tipo_imagem = std::stoi(optarg);
        break;
      case 's':
        reducao = std::stoi(optarg);
        break;
      default: 
        std::cerr << "usage: " << argv[0] << " [-r rugosidade] [-t 0 (grayscale) 3 (cores) 2 (sombreada)] [-s intensidade sombra] <paleta> <tamanho> <saida>" << std::endl;
        return 1;
    }
  }

  if (argc - optind != 3) {
    std::cerr << "usage: " << argv[0] << " [-r rugosidade] [-t 0 (grayscale) 3 (cores) 2 (sombreada)] [-s intensidade sombra] <paleta> <tamanho> <saida>" << std::endl;
    return 1;
  }

  const char* arq_paleta = argv[optind];
  const char* tamanho_str = argv[optind + 1];
  const char* arq_saida = argv[optind + 2];

  // Check if paleta is a valid file
  std::ifstream paleta(arq_paleta);
  if (!paleta.is_open()) {
    std::cerr << argv[0] << ": " << arq_paleta << ": File not found" << std::endl;
    return 1;
  }
  paleta.close();

  // Check if tamanho is an integer
  for (int i = 0; tamanho_str[i] != '\0'; i++) {
    if (!std::isdigit(tamanho_str[i])) {
      std::cerr << argv[0] << ": Size needs to be a number" << std::endl;
      return 1;
    }
  }

  // Check if we will not overwrite a existing file
  std::ifstream saida(arq_saida);
  if (saida.is_open()) {
    std::cerr << argv[0] << ": " << arq_saida << ": File already exists" << std::endl;
    return 1;
  }
  saida.close();
  
  Paleta cores(arq_paleta);
  Terreno altitudes(std::stoi(tamanho_str));
  altitudes.gerarTerreno(rugosidade);
  altitudes.salvarImagem(tipo_imagem, arq_saida, cores, reducao);

  std::cout << "Imagem '" << arq_saida << "' gerada com sucesso!" << std::endl;
  
  return 0;
}
