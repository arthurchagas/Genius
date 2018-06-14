#include "Fila.h"

Fila::Fila() : tamanho(0) {
    this->frente = new No(-1);
    this->fim = new No(-1);

    this->frente->set_proximo(this->fim);
    this->frente->set_anterior(nullptr);

    this->fim->set_proximo(nullptr);
    this->fim->set_anterior(this->frente);
}

Fila* Fila::clone() {
    auto rtrn = new Fila();

    auto aux = this->frente->get_proximo();

    while(aux != this->fim) {
        rtrn->push(aux->get_item());
        aux = aux->get_proximo();
    }

    return rtrn;
}

Fila::~Fila() {
    esvazia_fila();

    delete this->frente;
    delete this->fim;
}

unsigned Fila::get_tamanho() const {
    return tamanho;
}

bool Fila::cheia() {
    return false;
}

bool Fila::vazia() const {
    return tamanho == 0;
}

void Fila::push(int chave) {
    auto aux = new No(chave);

    aux->set_proximo(this->fim);
    aux->set_anterior(this->fim->get_anterior());
    this->fim->get_anterior()->set_proximo(aux);
    this->fim->set_anterior(aux);

    ++this->tamanho;
}

int Fila::pop() {
    auto aux = this->frente->get_proximo();
    auto aux2 = this->top();

    aux->get_proximo()->set_anterior(this->frente);
    this->frente->set_proximo(aux->get_proximo());

    delete aux;

    --this->tamanho;

    return aux2;
}

int Fila::top() { 
    return this->frente->get_proximo()->get_item();
}

void Fila::esvazia_fila() {
    while (!vazia())
        pop();
}