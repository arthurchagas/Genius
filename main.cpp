#include <SFML/Graphics/RenderWindow.hpp>

#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Event.hpp>

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

    auto jogar = new Botao(200, 250, BOTAO_INICIO);
    
    sf::Texture fundos[2];
    sf::Sprite fundos_spr[2];

    fundos[0].loadFromFile(FUNDO_INICIO);
    fundos[1].loadFromFile(FUNDO_JOGO);
    
    fundos_spr[0].setTexture(fundos[0]);
    fundos_spr[1].setTexture(fundos[1]);

    Fila *resultado = gerar_sequencia(k);
    Fila *sequencia = resultado->clone();

    Botao *botoes[5];

    botoes[ADORE] = new Botao(100, 87, ADORE_FILE, ADORE_SELECTED_FILE, ADORE_AUDIO_FILE);
    botoes[ALYSSA] = new Botao(100, 350, ALYSSA_FILE, ALYSSA_SELECTED_FILE, ALYSSA_AUDIO_FILE);
    botoes[DETOX] = new Botao(550, 75, DETOX_FILE, DETOX_SELECTED_FILE, DETOX_AUDIO_FILE);
    botoes[JINKX] = new Botao(550, 350, JINKX_FILE, JINKX_SELECTED_FILE, JINKX_AUDIO_FILE);
    botoes[VANJIE] = new Botao(325, 225, VANJIE_FILE, VANJIE_SELECTED_FILE, VANJIE_AUDIO_FILE);

    while (window.isOpen()) {
        if (!menu) {
            if (esperar) {
                if (timer.getElapsedTime().asSeconds() < TEMPO_INICIO) continue;
                
                esperar = false;
                timer.restart();

                std::cout << "Iniciando" << std::endl;

                continue;
            } else if (click_pendente && uTimeout < timer.getElapsedTime().asMicroseconds()) {
                click_pendente = false;
                std::cout << "Liberando click" << std::endl;

                for (auto i = 0; i < 5; ++i)
                    botoes[i]->set_clicavel(true);
                
                continue;
            } else if (!click_pendente && !sequencia->vazia()) {
                botoes[sequencia->top()]->get_snd().play();
                uTimeout = botoes[sequencia->pop()]->toggle();
                timer.restart();
                
                click_pendente = true;
                std::cout << "Travando click" << std::endl;
            } else if (derrota) {
                std::cout << "Derrota!" << std::endl;
                window.close();
            } else if (resultado->vazia()) {
                std::cout << "Gerando proxima lista" << std::endl;

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
                std::cout << "Clicou em (" << event.mouseButton.x << "," << event.mouseButton.y << ")" << std::endl;
                if (menu) {
                    if (jogar->clicado(event.mouseButton.x, event.mouseButton.y)) {
                        delete jogar;
                        menu = false;
                        timer.restart();
                    }
                } else if (!derrota && !click_pendente && !esperar && !resultado->vazia()) {
                    auto x = encontrar_clicado(botoes, event.mouseButton.x, event.mouseButton.y);

                    if (x == -1)
                        continue;
                    
                    std::cout << "Clicou em " << x << " (esperado: " << resultado->top() << ")" << std::endl;

                    botoes[x]->get_snd().play();
                    uTimeout = botoes[x]->toggle();
                    timer.restart();
                    
                    click_pendente = true;

                    if (resultado->pop() != x) {
                        derrota = true;
                        for (auto i = 0; i < 5; ++i)
                            delete botoes[i];
                    }
                }
                
            }
        }

        window.clear();
        
        if (menu) {
            window.draw(fundos_spr[0]);
            window.draw(jogar->get_spr());
        } else if (!derrota) {
            window.draw(fundos_spr[1]);
			
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