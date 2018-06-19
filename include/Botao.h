#ifndef BOTAO_H
#define BOTAO_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include <cinttypes>

class Botao {
public:
	Botao(float x, float y, std::string nome_spr, std::string nome_spr2, std::string nome_msc);
	Botao(float x, float y, std::string nome_spr);

	bool clicado(int x, int y) const;

	sf::Sprite get_spr();
    sf::Sound& get_snd();
	int64_t toggle();
	int64_t set_clicavel(bool opt);
	bool e_clicavel();
	void timeout();

private:
	float x, y;
	bool clicavel, timed_out;
	sf::Sprite spr, spr2;
    sf::Texture txt, txt2;
    sf::Sound snd;
    sf::SoundBuffer snd_bffr;
	int64_t get_snd_timeout() const;
};
#endif //BOTAO_H