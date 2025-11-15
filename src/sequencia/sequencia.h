template <typename T>
class Sequencia {
private:
  int capacidade;
  int tamanho;
  T *dados;
  
public:
  Sequencia<T>() : capacidade(0), tamanho(0), dados(nullptr) {};

  Sequencia<T>(int cap) : capacidade(cap), tamanho(0) {
    dados = new T[capacidade];
  }

  ~Sequencia<T>() {
    delete[] dados;
  }

  T& operator[] (int index) {
    return dados[index];
  }

  void resize(int size) {
    T *novo = new T[size];

    for (int i = 0; i < size; i++) {
      if (i < capacidade) {
        novo[i] = dados[i];
      }
      else if (i < size){
        novo[i] = T();
      }
    }

    delete[] dados;
    dados = novo;

    capacidade = size;
    tamanho = size;
  }
  void resize(int size, T init) {
    T *novo = new T[size];

    for (int i = 0; i < size; i++) {
      if (i < capacidade) {
        novo[i] = dados[i];
      }
      else if (i < size){
        novo[i] = init;
      }
    }

    delete[] dados;
    dados = novo;

    capacidade = size;
    tamanho = size;
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
