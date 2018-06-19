#ifndef UTIL_H
#define UTIL_H

#include "Fila.h"
#include "Botao.h"

#define ADORE 0
#define ALYSSA 1
#define DETOX 2
#define JINKX 3
#define VANJIE 4

#define RSC_DIR "rsc/"

#define SELECTED_SUFIX "_Selected"

#define AUDIO_EXTENSION ".ogg"
#define IMG_EXTENSION ".png"

#define ADORE_FILE RSC_DIR "Adore" IMG_EXTENSION
#define ALYSSA_FILE RSC_DIR "Alyssa" IMG_EXTENSION
#define DETOX_FILE RSC_DIR "Detox" IMG_EXTENSION
#define JINKX_FILE RSC_DIR "Jinkx" IMG_EXTENSION
#define VANJIE_FILE RSC_DIR "Vanjie" IMG_EXTENSION

#define ADORE_SELECTED_FILE RSC_DIR "Adore" SELECTED_SUFIX IMG_EXTENSION
#define ALYSSA_SELECTED_FILE RSC_DIR "Alyssa" SELECTED_SUFIX IMG_EXTENSION
#define DETOX_SELECTED_FILE RSC_DIR "Detox" SELECTED_SUFIX IMG_EXTENSION
#define JINKX_SELECTED_FILE RSC_DIR "Jinkx" SELECTED_SUFIX IMG_EXTENSION
#define VANJIE_SELECTED_FILE RSC_DIR "Vanjie" SELECTED_SUFIX IMG_EXTENSION

#define ADORE_AUDIO_FILE RSC_DIR "Adore" AUDIO_EXTENSION
#define ALYSSA_AUDIO_FILE RSC_DIR "Alyssa" AUDIO_EXTENSION
#define DETOX_AUDIO_FILE RSC_DIR "Detox" AUDIO_EXTENSION
#define JINKX_AUDIO_FILE RSC_DIR "Jinkx" AUDIO_EXTENSION
#define VANJIE_AUDIO_FILE RSC_DIR "Vanjie" AUDIO_EXTENSION

#define FUNDO_INICIO RSC_DIR "Menu" IMG_EXTENSION
#define BOTAO_INICIO RSC_DIR "Jogar" IMG_EXTENSION

#define FUNDO_JOGO RSC_DIR "Fundo" IMG_EXTENSION

#define BOTAO_GAMEOVER RSC_DIR "GameOver" IMG_EXTENSION
#define GAMEOVER_AUDIO_FILE RSC_DIR "GameOver" AUDIO_EXTENSION

#define TEMPO_INICIO 2.0d
#define TAMANHO_INICIO 2

Fila* gerar_sequencia(int tamanho);
int encontrar_clicado(Botao *botoes[5], int x, int y);
void carregar_botoes(Botao *&jogar, Botao *botoes[5]);
void carregar_sprites_background(sf::Texture *fundos, sf::Sprite *fundos_spr);
void carregar_sons_gameover(sf::SoundBuffer &sound_buffer_gameover, sf::Sound &sound_gameover);
void gerar_sequencia_e_resultado_esperado(Fila *&sequencia, Fila *&resultado, int &k);

#endif //UTIL_H