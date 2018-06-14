#include "No.h"

No::No(int chave) : chave(chave) {
    proximo = nullptr;
    anterior = nullptr;
}

void No::set_proximo(No* prox) {
    proximo = prox;
}

void No::set_anterior(No* ant) {
    anterior = ant;
}

int No::get_item() const {
    return chave;
}

No* No::get_proximo() const {
    return proximo;
}

No* No::get_anterior() const {
    return anterior;
}