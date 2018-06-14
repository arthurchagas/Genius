#include "Botao.h"

Botao::Botao(const float x, const float y, std::string nome_spr, std::string nome_spr2, std::string nome_msc)
	: x(x), y(y), clicavel(true), timed_out(false) {
	this->txt.loadFromFile(nome_spr);
	this->spr.setTexture(this->txt);
	this->spr.setPosition(this->x, this->y);

	this->txt2.loadFromFile(nome_spr2);
	this->spr2.setTexture(this->txt2);
	this->spr2.setPosition(this->x, this->y);

    this->snd_bffr.loadFromFile(nome_msc);
    this->snd.setBuffer(this->snd_bffr);
}

Botao::Botao(const float x, const float y, std::string nome_spr): x(x), y(y), clicavel(true), timed_out(false) {
	this->txt.loadFromFile(nome_spr);
	this->spr.setTexture(this->txt);
	this->spr.setPosition(this->x, this->y);
}

bool Botao::clicado(const int x, const int y) const {
	return clicavel && !timed_out && x > this->spr.getPosition().x &&
		x < this->spr.getPosition().x + this->spr.getGlobalBounds().width &&
		y > this->spr.getPosition().y &&
		y < this->spr.getPosition().y + this->spr.getGlobalBounds().height;
}

int64_t Botao::get_snd_timeout() const {
	return this->snd_bffr.getDuration().asMicroseconds();
}

int64_t Botao::toggle() {
	clicavel = !clicavel;

	if (clicavel)
		return 0;
	
	return this->get_snd_timeout();
}

void Botao::timeout() {
	timed_out = !timed_out;
}

sf::Sprite Botao::get_spr() {
	if (clicavel)
		return spr;
	
	return spr2;
}

sf::Sound& Botao::get_snd() {
    return snd;
}

bool Botao::e_clicavel() {
	return clicavel;
}