#pragma once

#include "Main.hpp"

#include "Level.hpp"

/*	Glowna klasa gry przeznaczona do zarzadzania
	wszelkimi zasobami i kontrolujaca rozgrywke.
*/
class CGame final
{
public:
	enum Status
	{
		Initializing	= 0,			// Ten status zostanie ustawiony gdy wejdziemy do konstruktora klasy gry.
		Running			= 1,			// Ten status zostanie ustawiony gdy rozpoczniemy gre.
		Paused			= 2,			// Ten status zostanie ustawiony gdy uzytkownik zapauzuje gre.
		CleaningUp		= 3				// Ten status zostanie ustawiony gdy wejdziemy do destruktora klasy gry.
	};

	/*	Destruktor klasy gry.
		Wykonuje wszelkie niezbedne operacje
		do prawidlowego zwolnienia zasobow gry.
	*/
	~CGame();

	/*	Uruchamia glowny kod gry. */
	void Run();

	/* Zwraca status gry. */
	inline Status GetStatus() const { return m_status; }

	/* Zwraca okno gry. */
	inline sf::RenderWindow& GetWindow() { return m_window; }

	/* Zwraca aktualny poziom gry. */
	inline CLevel *GetLevel() { return m_currentLevel; }


	/*	Funkcja tworz¹ca jedyn¹ instancjê
		klasy gry.
	*/
	inline static CGame& Instance()
	{
		static CGame instance;
		return instance;
	}

private:
	/*	Konstruktor glowny klasy gry.
		Odpowiada za przygotowanie zasobow gry,
		by ta nastepnie mogla zostac poprawnie rozpoczêta.
	*/
	CGame();

	/*	Nasza gra nie moze zostac skopiowana
		dlatego ten destruktor jest zablokowany
	*/
	CGame(const CGame &) = delete;

	/*	Pamietamy tak¿e o usunieciu operatora przypisania */
	void operator=(const CGame &) = delete;

	Status				m_status;			// Aktualny status gry.
	sf::RenderWindow	m_window;			// Okno gry.
	CLevel*				m_currentLevel;		// Aktualna scena gry.
};