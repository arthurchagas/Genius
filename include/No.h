#ifndef NO_H
#define NO_H

class No {
public:
    No(int chave);

    void set_proximo(No* prox);
    void set_anterior(No* ant);
    int get_item() const;
    No* get_proximo() const;
    No* get_anterior() const;
private:
    int chave;
    No* proximo;
    No* anterior;
};

#endif //NO_h