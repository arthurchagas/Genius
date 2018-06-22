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

    bool menu = true, esperar = true, clique_pendente = false, derrota = false;

    int k = TAMANHO_INICIO;
    int64_t timeout = 0;
    
    carregar_sons_gameover(sound_buffer_gameover, sound_gameover);
    carregar_sprites_background(fundos, fundos_spr);
    carregar_botoes(jogar, botoes);

    gerar_sequencia_e_resultado_esperado(sequencia, resultado, k);

    while (window.isOpen()) {
        if (!menu && !derrota) {
            // Um novo jogo foi iniciado
            if (esperar) {
                // Esperar TEMPO_INICIO segundos antes de qualquer coisa
                if (timer.getElapsedTime().asSeconds() < TEMPO_INICIO) continue;
                
                // TEMPO_INICIO segundos já se passaram, liberar inicio do jogo
                esperar = false;
                timer.restart();

                continue;
            } 
            // Algum botão foi clicado
            else if (clique_pendente) {
                // Esperar um timeout definido pelo botão clicado
                if (timer.getElapsedTime().asMicroseconds() < timeout) continue;

                // Timeout já expirou, liberar todos os botões para clique
                clique_pendente = false;
                timer.restart();

                for (auto i = 0; i < 5; ++i)
                    botoes[i]->set_clicavel(true);
                
                continue;
            }
            // Mostrar o próximo botão da sequência
            else if (!sequencia->vazia())
                executar_clique(botoes[sequencia->pop()],  timeout, timer, clique_pendente);
            // Usuário clicou corretamente em toda a sequência
            // Gerar nova sequência
            else if (resultado->vazia()) {
                gerar_sequencia_e_resultado_esperado(sequencia, resultado, k);

                continue;
            }
        }

        while (window.pollEvent(event)) {
            // Janela foi fechada
            if (event.type == sf::Event::Closed)
                window.close();
            // Botão esquerdo do mouse foi clicado
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (menu) {
                    // Botão para iniciar o jogo foi clicado
                    if (jogar->clicado(event.mouseButton.x, event.mouseButton.y)) {
                        menu = false;
                        esperar = true;
                        timer.restart();
                    }
                } else if (!derrota) {
                    // Ignorar clique se já está a processar outro clique 
                    // ou se o jogo ainda não começou
                    // ou se a rodada já terminou
                    if (clique_pendente || esperar || resultado->vazia()) continue;
                    
                    // Descobrir se algum botão foi clicado
                    auto x = encontrar_clicado(botoes, event.mouseButton.x, event.mouseButton.y);

                    // Nenhum botão foi clicado
                    if (x == -1) continue;

                    // Fim de jogo, o botão clicado não era o próximo na sequência
                    if (resultado->pop() != x) {
                        sound_gameover.play();
                        derrota = true;
                        continue;
                    }

                    // Efetuar clique
                    executar_clique(botoes[x], timeout, timer, clique_pendente);
                } 
                // Clique em qualquer lugar após o fim de jogo: reiniciar
                else {
                    // Voltar ao estado inicial
                    menu = true;
                    derrota = false;
                    clique_pendente = false;

                    // Resetar botoes
                    for (auto i = 0; i < 5; ++i)
                        botoes[i]->set_clicavel(true);

                    // Resetar tamanho da sequencia
                    k = TAMANHO_INICIO;
                    
                    // Gerar sequencia do novo jogo
                    gerar_sequencia_e_resultado_esperado(sequencia, resultado, k);
                }
            }
        }

        window.clear();
        
        // Desenhar menu
        if (menu) {
            window.draw(fundos_spr[0]);
            window.draw(jogar->get_spr());
        }
        // Desenhar jogo principal
        else if (!derrota) {
            window.draw(fundos_spr[1]);
			
            for (auto i = 0; i < 5; ++i)
				window.draw(botoes[i]->get_spr());
        }
        // Desenhar fim de jogo
        else {
            window.draw(fundos_spr[2]);
        }

        window.display();
    }

    // Liberar toda memória alocada
    for (auto i = 0; i < 5; ++i)
        delete botoes[i];
    delete resultado;
    delete sequencia;
    delete jogar;

    return 0;
}