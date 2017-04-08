#pragma once

#include "Pawn.hpp" // Klasa przeciwnika dziedziczy po pionku. Dodajemy go.

#include "AISense.hpp"

/*	Tworzymy klase pionka podobnie jak klase gracza 
	z ta roznica, ze jej kontroler poki co nic nie bedzie robil.
	Zachowaniem wroga zajmiemy sie pozniej.
*/
class CEnemy
	: public IPawn
{
	sf::Sprite m_sprite; // Tworzymy sprajta do wyswietlania wroga

	CSightSense m_sightSense; // Zmysl wzroku wroga
public:
	CEnemy(); // Konstruktor, w ktorym stworzymy wstepne ustawienie wroga

	// Metoda do ustawiania pozycji.
	virtual void SetLocation(const grim::Vector2 &location) override;

	// Metoda, ktorej uzyjemy do update-owania zmyslow
	virtual void Update(const float &deltaTime) override;

	// Metoda do wyswietlania wroga.
	virtual void Draw() override;
};

/*	Kontroler sztucznej inteligencji dla wroga.
	Poki co zostawimy go pustego.
*/
class CEnemyAIController
	: public IPawnController
{
public:
	CEnemyAIController(); // Konstruktor

	// Metoda ciagle aktualizujaca AI wroga.
	virtual void Update(const float &deltaTime) override;
};
