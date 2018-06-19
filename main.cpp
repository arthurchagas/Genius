#include <SFML/Graphics/RenderWindow.hpp>

#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Event.hpp>

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include <cinttypes>

#include "Util.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Rupoc Genius");
    sf::Clock timer;
    sf::Event event;
    sf::SoundBuffer sound_buffer_gameover;
    sf::Sound sound_gameover;
    sf::Texture fundos[3];
    sf::Sprite fundos_spr[3];

    Fila *resultado = nullptr, *sequencia = nullptr;
    Botao *botoes[5] = {nullptr}, *jogar = nullptr;

    bool menu = true, esperar = true, click_pendente = false, derrota = false;

    int k = TAMANHO_INICIO;
    int64_t timeout = 0;
    
    carregar_sons_gameover(sound_buffer_gameover, sound_gameover);
    carregar_sprites_background(fundos, fundos_spr);
    carregar_botoes(jogar, botoes);

    gerar_sequencia_e_resultado_esperado(sequencia, resultado, k);

    while (window.isOpen()) {
        if (!menu) {
            if (esperar) {
                if (timer.getElapsedTime().asSeconds() < TEMPO_INICIO) continue;
                
                esperar = false;
                timer.restart();

                continue;
            } else if (click_pendente && timeout < timer.getElapsedTime().asMicroseconds()) {
                click_pendente = false;

                for (auto i = 0; i < 5; ++i)
                    botoes[i]->set_clicavel(true);
                
                continue;
            } else if (!click_pendente && !sequencia->vazia()) {
                botoes[sequencia->top()]->get_snd().play();
                timeout = botoes[sequencia->pop()]->toggle();
                timer.restart();
                
                click_pendente = true;
            } else if (resultado->vazia()) {
                gerar_sequencia_e_resultado_esperado(sequencia, resultado, k);

                continue;
            }
        }

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (menu) {
                    if (jogar->clicado(event.mouseButton.x, event.mouseButton.y)) {
                        menu = false;
                        esperar = true;
                        timer.restart();
                    }
                } else if (!derrota && !click_pendente && !esperar && !resultado->vazia()) {
                    auto x = encontrar_clicado(botoes, event.mouseButton.x, event.mouseButton.y);

                    if (x == -1) continue;

                    if (resultado->pop() != x) {
                        derrota = true;
                        continue;
                    }

                    botoes[x]->get_snd().play();
                    timeout = botoes[x]->toggle();
                    timer.restart();
                    
                    click_pendente = true
                } else if (derrota) {
                    menu = true;
                    derrota = false;
                    click_pendente = false;

                    for (auto i = 0; i < 5; ++i)
                        botoes[i]->set_clicavel(true);

                    k = TAMANHO_INICIO;
                    
                    gerar_sequencia_e_resultado_esperado(sequencia, resultado, k);
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
        } else if (derrota) {
            window.draw(fundos_spr[2]);
            sound_gameover.play();
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