#pragma once

#include "Actor.hpp"

class CGame;

/*	Klasa do zarz¹dzania poziomem
	sk³adaj¹cym siê z wielu aktorów.
*/
class CLevel final
{
public:
	/*	U³atwmy sobie ¿ycie typedefem. */
	typedef std::vector<IActor *> TActorsV;

	/*	Konstruktor klasy poziomu.
	*/
	CLevel();

	/*	Destruktor klasy poziomu.
		Dba o poprawne zwolnienie pozosta³ych zasobów
	*/
	~CLevel();

	/*	Dodaje aktora do poziomu. 
		Jeœli aktor pozostanie do czasu destrukcji obiektu poziomu
		to automatycznie zostanie zniszczony przez jego destruktor.
		Zwraca prawdê jeœli aktora jeszcze nie by³o w tym poziomie.
	*/
	bool Add(IActor *actor);

	/*	Usuwa aktora ze poziomu.
		Nie zwalnia pamiêci.
		Zwraca prawdê jeœli aktor by³ w tym poziomie.
	*/
	bool Remove(IActor *actor);

	/*	Zwraca prawdê jeœli podany aktor jest juz w tym poziomie.
	*/
	bool Exists(IActor *actor) const;

	/*	Sprz¹ta ca³y poziom. Robi to samo co destruktor,
		ale obiekt poziomu zostaje.
	*/
	std::size_t Cleanup();

	/*	Uaktualnia wszystkich aktorów z poziomu.
	*/
	void Update(const float &deltaTime);

	/*	Wyœwietla wszystkich aktorów w tym poziomie.
	*/
	void Draw();

	/* Zwraca iloœæ aktorów znajduj¹cych siê na tym levelu. */
	inline std::size_t Count() const { return m_actors.size(); }

	/* Zwraca kopie tablicy z wszystkimi aktorami w poziomie. */
	inline TActorsV GetActors() const { return m_actors; }
private:
	TActorsV		m_actors;		// Aktorzy na scenie.
};
