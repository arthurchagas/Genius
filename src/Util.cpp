#include <random>
#include <chrono>
#include "Util.h"

Fila* gerar_sequencia(int tamanho) {
    std::default_random_engine gerador;
    std::uniform_int_distribution<int> distribuicao(ADORE, VANJIE);

    gerador.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());    

    Fila* resultado = new Fila();

    for (int i = 0; i < tamanho; ++i)
        resultado->push(distribuicao(gerador));
    
    return resultado;
}

int encontrar_clicado(Botao *botoes[5], int x, int y) {
    for (auto i = 0; i < 5; ++i)
        if (botoes[i]->clicado(x, y))
            return i;

    return -1;
}