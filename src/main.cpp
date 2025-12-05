#include <cctype>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include "paleta/paleta.h"
#include "terreno/terreno.h"

int main(int argc, char* argv[]) {
  //=======================================//
  //======== Argument verification ========//
  //=======================================//
  
  // Check if all arguments were given
  if (argc != 4) {
    std::cerr << "usage: " << argv[0] << " <paleta> <tamanho> <saida>" << std::endl;
    return 1;
  }

  // Check if paleta is a valid file
  std::ifstream paleta(argv[1]);

  if (!paleta.is_open()) {
    std::cerr << argv[0] << ": " << argv[1] << ": File not found" << std::endl;
  }

  paleta.close();

  // Check if tamanho is an integer
  if (argv[2] == NULL || *argv[2] == '\0') {
    std::cerr << argv[0] << ": Size cannot be null" << std::endl;
    return 0;
  }

  for (int i = 0; argv[2][i] != '\0'; i++) {
    if (!std::isdigit(argv[2][i])) {
      std::cerr << argv[0] << ": Size needs to be a number" << std::endl;
      return 0;
    }
  }

  // Check if we will not overwrite a existing file
  std::ifstream saida(argv[3]);

  if (saida.is_open()) {
    std::cerr << argv[0] << ": " << argv[3] << ": File already exists" << std::endl;
  }

  saida.close();
  
  Paleta cores(argv[1]);
  Terreno altitudes(std::stoi(argv[2]));
  altitudes.salvarImagem(IMAGEM_TIPO_COR, argv[3], cores);
}
