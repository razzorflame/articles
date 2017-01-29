#pragma once

#include "Main.hpp"
#include "Math.hpp"

class CGame;

/*	Aktor - podstawowa klasa dla jakiegokolwiek
	wyœwietlanego elementu na scenie. Jest ona w ca³oœci
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

	/*	Ustawia pozycje aktora na podan¹ w [location]
	*/
	inline virtual void SetLocation(const grim::Vector2 &location) { m_location = location; }

	/*	Ustawia rotacjê aktora na podan¹ w [rotation]
	*/
	inline virtual void SetRotation(const float &rotation) { m_rotation = rotation; }

	/*	Porusza obiekt wzglêdem aktualnej pozycji o [delta] jednostek.
	*/
	inline void Move(const grim::Vector2 &delta)		{ this->SetLocation(m_location + delta); }

	/* Obraca obiekt wzglêdem aktualnego obrotu o [delta] stopni
	*/
	inline void Rotate(const float &delta)				{ this->SetRotation(m_rotation + delta); }

	/*	Metoda s³u¿¹ca do uaktualniania obiektu. Sam aktor nie jest jeszcze kompletnym obiektem
		dlatego ta metoda jest tutaj pusta.
	*/
	inline virtual void Update(const float &deltaTime) {}

	/*	Metoda s³u¿¹ca do wyswietlania aktora. Pocz¹tkowo aktor nie posiada nic do wyœwietlenia,
		klasy pochodne maj¹ tutaj dowolnoœæ, jednak musz¹ mieæ zdefiniowan¹ t¹ funkcjê, gdy¿ jest
		ona czysto wirtualna.
	*/
	virtual void Draw() = 0;

	/* Pobiera aktualn¹ pozycjê aktora. */
	inline grim::Vector2	GetLocation() const { return m_location; }

	/* Pobiera aktualny obrót aktora. */
	inline float			GetRotation() const { return m_rotation; }

protected:
	grim::Vector2		m_location;			// Zawiera informacjê, gdzie aktor aktualnie siê znajduje.
	float				m_rotation;			// Zawiera informacjê o obrocie aktora.
};
