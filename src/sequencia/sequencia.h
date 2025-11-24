#pragma once
#include <iostream>
template <typename T>
class Sequencia {
private:
  int capacidade;
  int tamanho;
  T *dados;
  
public:
  Sequencia() : capacidade(0), tamanho(0), dados(nullptr) {};

  Sequencia(int cap) : capacidade(cap), tamanho(0) {
    dados = new T[capacidade];
  }

  ~Sequencia() {
    delete[] dados;
  }

  T& operator[] (int index) {
    if (index > tamanho) {
      std::cerr << "[Sequencia]: Tried to read out of bounds index (" << index << ")." << std::endl;
    }

    return dados[index];
  }

  void resize(int size, T init = T(), bool keep_size = false) {
    T *novo = new T[size];

    for (int i = 0; i < size; i++) {
      if (i < tamanho) {
        novo[i] = dados[i];
      }
      else if (i < size){
        novo[i] = init;
      }
    }

    delete[] dados;
    dados = novo;

    capacidade = size;

    if (!keep_size) {
      tamanho = size;
    }
  }

  int obterTamanho() { 
    return tamanho; 
  };

  void adicionar(T elemento) {
    if (tamanho < capacidade / 2) {
      dados[tamanho] = elemento;
      tamanho++;
    }
    else {
      resize(capacidade == 0 ? 2 : capacidade * 2, T(), true);
      dados[tamanho] = elemento;
      tamanho++;
    }
  }

  void removerUltimo() {
    if (tamanho > 0) {
      tamanho--;

      if (tamanho <= capacidade / 4) {
        resize(capacidade / 2, T(), true);
      }
    }
  };
};
