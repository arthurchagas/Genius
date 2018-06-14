#ifndef FILA_H
#define FILA_H

#include "No.h"

class Fila {
public:
    Fila();
    ~Fila();

    unsigned get_tamanho() const;
    static bool cheia();
    bool vazia() const;
    void esvazia_fila();

    void push(int chave);
    int pop();
    int top();

    Fila* clone();
private:
    No* frente;
    No* fim;
    unsigned tamanho;
};

#endif //FILA_H