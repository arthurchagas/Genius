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

void travar_todos(Botao *botoes[5]) {
    for (auto i = 0; i < 5; ++i)
        if (botoes[i]->e_clicavel())
            botoes[i]->timeout();
}

void liberar_todos(Botao *botoes[5]) {
    for (auto i = 0; i < 5; ++i)
        if (botoes[i]->e_clicavel())
            botoes[i]->timeout();
        else
            botoes[i]->toggle();
}

int encontrar_clicado(Botao *botoes[5], int x, int y, int64_t &uTimeout, sf::Clock &timer, bool &click_pendente) {
    for (auto i = 0; i < 5; ++i)
        if (botoes[i]->clicado(x, y)) {
            botoes[i]->get_snd().play();
            uTimeout = botoes[i]->toggle();
            timer.restart();
            travar_todos(botoes);
            click_pendente = true;
            return i;
        }
    return -1;
}