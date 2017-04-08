#pragma once

#include "Actor.hpp" // Klasa bedzie operowala na aktorach ze sceny.

#include "Pawn.hpp" // Potrzebna bedzie tez klasa pionka

// Klasa bazowa dla wszelkich zmyslow.
class IAISense
{
protected:
	IPawn		&m_owner; // Wlasciciel tego konkretnego zmyslu.
public:
	/* Jest to konstruktor klasy zmyslu.
	*/
	explicit IAISense(IPawn &owner);

	/* Pomocniczy typ do skrocenia zapisu. */
	typedef std::vector<IActor*> TQueryActors;

	/*	Ta metoda bedzie odpowiadala za wykonanie odpowiedniego dzialania
		sprawdzajacego wyniki dzialania zmyslu. Bedzie ona zwracala liste pasujacych aktorow ze sceny,
		ktorzy spelniaj¹ odpowiednie warunki.
		Warunki, ktore ma spelnic dany aktor by nie zostal usuniety z wynikow sprawdza funkcja filterFunc.
		Parametr filterFunc to wskaznik na funkcje, ktora zwraca prawde gdy aktor ma byc dodany do wynikow lub falsz gdy ma byc usuniety z wynikow.
		Domyslnie filterFunc akceptuje kazdy wynik.

		Przykladowo gdy chcemy sprawdzic czy zmysl wykryl jakichs aktorow, ktorzy sa graczami, bedziemy chcieli usunac z wynikow
		wszystkich aktorow, ktorzy nie sa klasy CPlayer. Zrobimy to w ten sposob:

		aiSense->QueryActors([](IActor *const actor){ return dynamic_cast<CPlayer*>(actor) != nullptr; }

		dynamic_cast daje pusty wskaznik, gdy wykonano niepoprawne rzutowanie, dlatego bedzie skutecznym filtrem przeciwko niechcianym wynikom.
	*/
	virtual TQueryActors QueryActors(bool(*filterFunc)(IActor* const actor) = [](IActor *const actor) { return true; }) = 0; // Funkcja domyslnie jest niezdefiniowana.

	/*	Ta metoda bêdzie wyswietlala informacje dla debugowania.
		Przykladowo bedzie pokazywala dzialanie zmyslu wzroku (obszar widzenia, postrzeganych aktorow itp.)
		Nie jest to metoda czysto wirtualna (=0) gdyz nie wymagamy, by klasy potomne musialy miec implementacje
		tej metody. Zostawiamy ja domyslnie po prostu pusta.
	*/
	inline virtual void DrawDebug() { }
	
	/*	Ta metoda zwraca KOPIE tablicy, w ktorej znajduja sie wszyscy wykryci aktorzy przez zmysl.
	*/
	inline TQueryActors GetSensedActors() const { return m_sensedActors; }

protected:
	TQueryActors m_sensedActors; // Tablica aktorow, ktora byla wynikiem ostatniego wywolania QueryActors.
public:
	/*	Informuje czy jestesmy w trybie debuggingu czy nie.
		Jesli debugujemy to debugujemy wszystko, dlatego jest to zmienna statyczna.
	*/
	static bool DebugMode;
};

// Klasa zmyslu wzroku.
class CSightSense
	: public IAISense
{
	/*	Musimy ponizsze zmienne zrobic prywatne ze wzgledu na koniecznosc walidacji danych.
		Nie chcemy przeciez, zeby zasieg wzroku byl ujemny albo by pole widzenia bylo wieksze niz 180 stopni.
	*/
	float m_sightDistance;	// Zasieg wzroku w pikselach.

	/*	Pole widzenia w stopniach.	
		Kat ten to rozpietosc widzenia / 2 (gdyz rozpietosc widzenia siega od [twoj_obrot - m_sightAngle] do [twoj_obrot + m_sightAngle],
		czyli po prostu widzisz maksymalnie do m_sightAngle stopni w lewo i maksymalnie do m_sightAngle stopni w prawo.)
	*/
	float m_sightAngle;
public:

	/* Konstruktor zmyslu wzroku.
	*/
	CSightSense(IPawn &owner, const float &sightDistance = 300, const float &sightAngle = 45);

	/*	Metoda, ktora ustawia zasieg widzenia.
	*/
	bool SetSightDistance(const float &sightDistance);

	/*	Metoda, ktora ustawia max. kat widzenia.
	*/
	bool SetSightAngle(const float &sightAngle);

	/* Metody zwracajace wlasciwosci tego zmyslu. */
	inline float GetSightDistance() const { return m_sightDistance; }
	inline float GetSightAngle() const { return m_sightAngle; }

	/* Metoda ta bedzie zwracala wszystkich aktorow, ktorzy sa w zasiegu wzroku, w polu widzenia i ktorzy nie zostana usunieci przez filtr jednoczesnie. */
	virtual TQueryActors QueryActors(bool(*filterFunc)(IActor* const actor) = [](IActor *const actor) { return true; }) override;

	/* Ta metoda bedzie wyswietlala pole widzenia i postrzeganych aktorow. */
	virtual void DrawDebug() override;
};
