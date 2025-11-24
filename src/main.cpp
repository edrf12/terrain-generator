#include <iostream>
#include "sequencia/sequencia.h"

int main() {
  Sequencia<int> seq;
  seq.resize(10, 10);

  for (int i = 0; i < seq.obterTamanho(); i++) {
    std::cout << seq[i];
  }

  return 0;
}
