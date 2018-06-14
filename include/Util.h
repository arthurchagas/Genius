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

#define BACKGROUND RSC_DIR "Menu" IMG_EXTENSION
#define JOGAR RSC_DIR "Jogar" IMG_EXTENSION

#define TEMPO_INICIO 2.0d

Fila* gerar_sequencia(int tamanho);
void travar_todos(Botao *botoes[5]);
void liberar_todos(Botao *botoes[5]);
int encontrar_clicado(Botao *botoes[5], int x, int y, int64_t &uTimeout, sf::Clock &timer, bool &click_pendente);

#endif //UTIL_H