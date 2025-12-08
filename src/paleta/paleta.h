#pragma once

#include "../sequencia/sequencia.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdint>

struct Cor {
    uint8_t r, g, b;
};

class Paleta {
private:
    Sequencia<Cor> cores;
    uint8_t hexToNumber(const char hex);
    Cor hexToColor(const std::string color, const char* arquivo, const int linha);
    
public:
    Paleta() : cores() {}; // cria paleta vazia
    Paleta(const char* arquivo); // cria paleta de arquivo
    void adicionarCor(Cor cor);
    int obterTamanho();
    Cor obterCor(int indice);
};
