#pragma once

#include "Main.hpp"
#include "Math.hpp"

class CGame;

/*	Aktor - podstawowa klasa dla jakiegokolwiek
	wy�wietlanego elementu na scenie. Jest ona w ca�o�ci
	zdefiniowana w tym pliku.
*/
class IActor
{
public:
	/*	Konstruktor aktora.
	*/
	inline IActor()
		: m_rotation(0)
	{
	}

	/*	Destruktor aktora.
	*/
	inline virtual ~IActor() {}

	/*	Ustawia pozycje aktora na podan� w [location]
	*/
	inline virtual void SetLocation(const grim::Vector2 &location) { m_location = location; }

	/*	Ustawia rotacj� aktora na podan� w [rotation]
	*/
	inline virtual void SetRotation(const float &rotation) { m_rotation = rotation; }

	/*	Porusza obiekt wzgl�dem aktualnej pozycji o [delta] jednostek.
	*/
	inline void Move(const grim::Vector2 &delta)		{ this->SetLocation(m_location + delta); }

	/* Obraca obiekt wzgl�dem aktualnego obrotu o [delta] stopni
	*/
	inline void Rotate(const float &delta)				{ this->SetRotation(m_rotation + delta); }

	/*	Metoda s�u��ca do uaktualniania obiektu. Sam aktor nie jest jeszcze kompletnym obiektem
		dlatego ta metoda jest tutaj pusta.
	*/
	inline virtual void Update(const float &deltaTime) {}

	/*	Metoda s�u��ca do wyswietlania aktora. Pocz�tkowo aktor nie posiada nic do wy�wietlenia,
		klasy pochodne maj� tutaj dowolno��, jednak musz� mie� zdefiniowan� t� funkcj�, gdy� jest
		ona czysto wirtualna.
	*/
	virtual void Draw() = 0;

	/* Pobiera aktualn� pozycj� aktora. */
	inline grim::Vector2	GetLocation() const { return m_location; }

	/* Pobiera aktualny obr�t aktora. */
	inline float			GetRotation() const { return m_rotation; }

protected:
	grim::Vector2		m_location;			// Zawiera informacj�, gdzie aktor aktualnie si� znajduje.
	float				m_rotation;			// Zawiera informacj� o obrocie aktora.
};
