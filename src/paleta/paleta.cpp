#include "paleta.h"

Sequencia<int> seq;
int n = seq.obterTamanho();

Paleta::Paleta(const char *arquivo) {
    std::ifstream paleta(arquivo);
    if (paleta.is_open()) {
        while (!paleta.eof()) {
            this->adicionarCor(); // fazer
        }
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
