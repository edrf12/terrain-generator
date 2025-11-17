template <typename T>
class Sequencia {
private:
  int capacidade;
  int tamanho;
  T *dados;
  
public:
  Sequencia() : capacidade(-1), tamanho(0), dados(nullptr) {};

  Sequencia(int cap) : capacidade(cap), tamanho(0) {
    dados = new T[capacidade];
  }

  ~Sequencia() {
    delete[] dados;
  }

  T& operator[] (int index) {
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
    if (tamanho < capacidade) {
      dados[tamanho] = elemento;
      tamanho++;
    }
    else {
      resize(capacidade + 1, elemento);
    }
  }

  void removerUltimo() {
    if (tamanho > 0) {
      tamanho--;
    }
  };
};
