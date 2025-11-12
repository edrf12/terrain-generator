#pragma once

#include "../sequencia/sequencia.h"
#include <iostream>
#include <fstream>

struct Cor {
    uint8_t r, g, b;
};

class Paleta {
private:
    Sequencia<Cor> cores;
    
public:
    Paleta() : cores() {}; // cria paleta vazia
    Paleta(const char* arquivo); // cria paleta de arquivo
    void adicionarCor(Cor cor);
    int obterTamanho();
    Cor obterCor(int indice);
};
