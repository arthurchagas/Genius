#include <SFML/Graphics.hpp>
#include <iostream>
#include <cinttypes>
#include "Util.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Rupoc Genius");
    sf::Clock timer;
    sf::Event event;
    int k = 2;
    int64_t uTimeout = 0;
    bool menu = true, esperar = true, click_pendente = false, derrota = false;

    auto jogar = new Botao(200, 250, JOGAR);
    sf::Texture bckgrnd_txtr;
    bckgrnd_txtr.loadFromFile(BACKGROUND);
    sf::Sprite bckgrnd(bckgrnd_txtr);

    Fila *resultado = gerar_sequencia(k);
    Fila *sequencia = resultado->clone();

    Botao *botoes[5];

    botoes[ADORE] = new Botao(100, 50, ADORE_FILE, ADORE_SELECTED_FILE, ADORE_AUDIO_FILE);
    botoes[ALYSSA] = new Botao(300, 50, ALYSSA_FILE, ALYSSA_SELECTED_FILE, ALYSSA_AUDIO_FILE);
    botoes[DETOX] = new Botao(500, 50, DETOX_FILE, DETOX_SELECTED_FILE, DETOX_AUDIO_FILE);
    botoes[JINKX] = new Botao(200, 200, JINKX_FILE, JINKX_SELECTED_FILE, JINKX_AUDIO_FILE);
    botoes[VANJIE] = new Botao(400, 200, VANJIE_FILE, VANJIE_SELECTED_FILE, VANJIE_AUDIO_FILE);

    while (window.isOpen()) {
        if (!menu) {
            if (!click_pendente && esperar) {
                if (timer.getElapsedTime().asSeconds() > TEMPO_INICIO) {
                    esperar = false;
                    timer.restart();
                    liberar_todos(botoes);
                } else
                    continue;
            } else if (click_pendente && uTimeout < timer.getElapsedTime().asMicroseconds()) {
                liberar_todos(botoes);
                click_pendente = false;
                continue;
            } else if (!click_pendente && !sequencia->vazia()) {
                botoes[sequencia->top()]->get_snd().play();
                uTimeout = botoes[sequencia->pop()]->toggle();
                timer.restart();
                travar_todos(botoes);
                click_pendente = true;
            } else if (derrota) {
                std::cout << "derrota!" << std::endl;
                window.close();
            } else if (resultado->vazia()) {
                delete resultado;
                delete sequencia;
                
                resultado = gerar_sequencia(++k);
                sequencia = resultado->clone();

                continue;
            }
        }

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (menu) {
                    if (jogar->clicado(event.mouseButton.x, event.mouseButton.y)) {
                        delete jogar;
                        menu = false;
                        travar_todos(botoes);
                        timer.restart();
                    }
                } else if (!derrota && !click_pendente && !resultado->vazia()) {
                    auto x = encontrar_clicado(botoes, event.mouseButton.x, event.mouseButton.y, uTimeout, timer, click_pendente);
                    if (x != -1 && resultado->pop() != x) {
                        derrota = true;
                        for (auto i = 0; i < 5; ++i)
                            delete botoes[i];
                    }
                }
                
            }
        }

        window.clear();
        
        if (menu) {
            window.draw(bckgrnd);
            window.draw(jogar->get_spr());
        } else {
			if (!derrota)
				for (auto i = 0; i < 5; ++i)
					window.draw(botoes[i]->get_spr());
        }

        window.display();
    }

    for (auto i = 0; i < 5; ++i)
        delete botoes[i];
    delete resultado;
    delete sequencia;
    delete jogar;

    return 0;
}