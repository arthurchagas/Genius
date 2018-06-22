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

void carregar_botoes(Botao *&jogar, Botao *botoes[5]) {
    jogar = new Botao(200, 250, BOTAO_INICIO);
    botoes[ADORE] = new Botao(100, 87, ADORE_FILE, ADORE_SELECTED_FILE, ADORE_AUDIO_FILE);
    botoes[ALYSSA] = new Botao(100, 350, ALYSSA_FILE, ALYSSA_SELECTED_FILE, ALYSSA_AUDIO_FILE);
    botoes[DETOX] = new Botao(550, 75, DETOX_FILE, DETOX_SELECTED_FILE, DETOX_AUDIO_FILE);
    botoes[JINKX] = new Botao(550, 350, JINKX_FILE, JINKX_SELECTED_FILE, JINKX_AUDIO_FILE);
    botoes[VANJIE] = new Botao(325, 225, VANJIE_FILE, VANJIE_SELECTED_FILE, VANJIE_AUDIO_FILE);
}

void carregar_sprites_background(sf::Texture *fundos, sf::Sprite *fundos_spr) {
    fundos[0].loadFromFile(FUNDO_INICIO);
    fundos[1].loadFromFile(FUNDO_JOGO);
    fundos[2].loadFromFile(BOTAO_GAMEOVER);
    
    for (auto i = 0; i < 3; ++i)
        fundos_spr[i].setTexture(fundos[i]);
}

void carregar_sons_gameover(sf::SoundBuffer &sound_buffer_gameover, sf::Sound &sound_gameover) {
    sound_buffer_gameover.loadFromFile(GAMEOVER_AUDIO_FILE);
    sound_gameover.setBuffer(sound_buffer_gameover);
}

 void gerar_sequencia_e_resultado_esperado(Fila *&sequencia, Fila *&resultado, int &k) {
    delete sequencia;
    delete resultado;

    resultado = gerar_sequencia(k++);
    sequencia = resultado->clone();
 }

 void executar_clique(Botao *&bt, int64_t &timeout, sf::Clock &timer, bool &b) {
    bt->get_snd().play();
    timeout = bt->toggle();
    timer.restart();
    b = true;
 }