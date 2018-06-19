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
    int k = 2;
    int64_t uTimeout = 0;
    bool menu = true, esperar = true, click_pendente = false, derrota = false;

    auto jogar = new Botao(200, 250, BOTAO_INICIO);
    
    sound_buffer_gameover.loadFromFile(GAMEOVER_AUDIO_FILE);
    sound_gameover.setBuffer(sound_buffer_gameover);
    
    sf::Texture fundos[3];
    sf::Sprite fundos_spr[3];

    fundos[0].loadFromFile(FUNDO_INICIO);
    fundos[1].loadFromFile(FUNDO_JOGO);
    fundos[2].loadFromFile(BOTAO_GAMEOVER);
    
    for (auto i = 0; i < 3; ++i)
        fundos_spr[i].setTexture(fundos[i]);

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

                continue;
            } else if (click_pendente && uTimeout < timer.getElapsedTime().asMicroseconds()) {
                click_pendente = false;

                for (auto i = 0; i < 5; ++i)
                    botoes[i]->set_clicavel(true);
                
                continue;
            } else if (!click_pendente && !sequencia->vazia()) {
                botoes[sequencia->top()]->get_snd().play();
                uTimeout = botoes[sequencia->pop()]->toggle();
                timer.restart();
                
                click_pendente = true;
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
                        menu = false;
                        esperar = true;
                        timer.restart();
                    }
                } else if (!derrota && !click_pendente && !esperar && !resultado->vazia()) {
                    auto x = encontrar_clicado(botoes, event.mouseButton.x, event.mouseButton.y);

                    if (x == -1)
                        continue;

                    botoes[x]->get_snd().play();
                    uTimeout = botoes[x]->toggle();
                    timer.restart();
                    
                    click_pendente = true;

                    if (resultado->pop() != x)
                        derrota = true;
                } else if (derrota) {
                    menu = true;
                    derrota = false;
                    click_pendente = false;

                    for (auto i = 0; i < 5; ++i)
                        botoes[i]->set_clicavel(true);

                    delete resultado;
                    delete sequencia;

                    k = 2;
                    
                    resultado = gerar_sequencia(k);
                    sequencia = resultado->clone();
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