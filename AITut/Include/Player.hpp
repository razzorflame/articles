#pragma once

#include "Pawn.hpp" // Klasa dziedziczy po pionku, wiec pamietamy by dodac plik naglowkowy

// Klasa gracza
class CPlayer
	: public IPawn
{
	sf::Sprite m_sprite; // Potrzebujemy sprita by wyswietlac naszego gracza
public:
	CPlayer(); // Konstruktor

	/*	Przeladowujemy wirtualna metode z IActor (klasa bazowa od IPawn)
		Ustawiamy w niej pozycje sprita.
	*/
	virtual void SetLocation(const grim::Vector2 &location) override;
	/*	Domyslnie metoda IActor::Draw nic nie wyswietla i daje nam dowolnosc
		w klasach potomnych. Gracz musi byc wyswietlany wiec w tej metodzie
		wyswietlimy sobie naszego sprita w oknie.
	*/
	virtual void Draw() override;
};

// Klasa kontrolera gracza
// Sluzy do poruszania graczem.
class CPlayerController
	: public IPawnController
{
protected:
	float m_moveSpeed; // Stworzmy sobie zmienna, ktora przechowuje predkosc naszego gracza (pix/s)
public:
	CPlayerController(); // Konstruktor

	/*	Przeladowana metoda z IPawnController, to tutaj odbywa sie
		ca³a logika kontrolera - poruszanie postacia.
	*/
	virtual void Update(const float &deltaTime) override;

	/*	A tutaj pomocniczo definiujemy sobie klawisze, ktorymi bedziemy poruszali
		naszego gracza.
	*/
	static const sf::Keyboard::Key K_MoveUp = sf::Keyboard::W;
	static const sf::Keyboard::Key K_MoveDown = sf::Keyboard::S;
	static const sf::Keyboard::Key K_MoveLeft = sf::Keyboard::A;
	static const sf::Keyboard::Key K_MoveRight = sf::Keyboard::D;
};
