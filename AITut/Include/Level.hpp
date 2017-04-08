#pragma once

#include "Actor.hpp"

class CGame;

/*	Klasa do zarz�dzania poziomem
	sk�adaj�cym si� z wielu aktor�w.
*/
class CLevel final
{
public:
	/*	U�atwmy sobie �ycie typedefem. */
	typedef std::vector<IActor *> TActorsV;

	/*	Konstruktor klasy poziomu.
	*/
	CLevel();

	/*	Destruktor klasy poziomu.
		Dba o poprawne zwolnienie pozosta�ych zasob�w
	*/
	~CLevel();

	/*	Dodaje aktora do poziomu. 
		Je�li aktor pozostanie do czasu destrukcji obiektu poziomu
		to automatycznie zostanie zniszczony przez jego destruktor.
		Zwraca prawd� je�li aktora jeszcze nie by�o w tym poziomie.
	*/
	bool Add(IActor *actor);

	/*	Usuwa aktora ze poziomu.
		Nie zwalnia pami�ci.
		Zwraca prawd� je�li aktor by� w tym poziomie.
	*/
	bool Remove(IActor *actor);

	/*	Zwraca prawd� je�li podany aktor jest juz w tym poziomie.
	*/
	bool Exists(IActor *actor) const;

	/*	Sprz�ta ca�y poziom. Robi to samo co destruktor,
		ale obiekt poziomu zostaje.
	*/
	std::size_t Cleanup();

	/*	Uaktualnia wszystkich aktor�w z poziomu.
	*/
	void Update(const float &deltaTime);

	/*	Wy�wietla wszystkich aktor�w w tym poziomie.
	*/
	void Draw();

	/* Zwraca ilo�� aktor�w znajduj�cych si� na tym levelu. */
	inline std::size_t Count() const { return m_actors.size(); }

	/* Zwraca kopie tablicy z wszystkimi aktorami w poziomie. */
	inline TActorsV GetActors() const { return m_actors; }
private:
	TActorsV		m_actors;		// Aktorzy na scenie.
};
