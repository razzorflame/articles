#pragma once

#include "Actor.hpp"

class IPawnController;

/*	Klasa "pionka" jest baz� dla wszystkich
	obiekt�w, kt�re mog� si� porusza� po scenie
	(czy w jakikolwiek inny spos�b maj� by� kontrolowane)
*/
class IPawn
	: public IActor
{
public:
	/*	Konstruktor pionka.
	*/
	explicit IPawn(IPawnController *controller);

	/*	Destruktor pionka. Dba o to, by kontroler zosta� prawid�owo usuni�ty.
	*/
	virtual ~IPawn() override;

	/*	Usuwa stary kontroler i zmienia go na nowy.
	*/
	void ResetController(IPawnController *controller);

	/*	Funkcja uaktualniaj�ca kontroler. Wci�� mo�e by� prze�adowana
		w klasach pochodnych.
	*/
	virtual void Update(const float &deltaTime) override;
protected:
	IPawnController*		m_controller;		// Kontroler pionka.
};

/*	Kontroler dla klasy "pionka".
B�dzie po prostu kontrolowa� go, porusza� itp.
*/
class IPawnController
{
public:
	/* Konstruktor klasy kontrolera pionka */
	IPawnController();

	/* Destruktor klasy kontrolera pionka */
	virtual ~IPawnController();

	/*	Funkcja b�dzie uaktualnia�a wszystko
	co zwi�zane z ruchem pionka. Prezentacje pionka
	zostawiamy dla jego klasy.
	*/
	virtual void Update(const float &deltaTime) = 0;

	/*	Funkcja sprawdza czy kontroler jest u�ywany
	przez jakiego� pionka.
	*/
	inline bool IsPossessed() const { return m_owner != nullptr; }

	/*	Klasa pionka jest zobowi�zana do ustawienia
	siebie jako w�a�ciciela kontrolera (metod� Possess)
	*/
	friend class IPawn;
private:
	/*	Ustawia w�a�ciciela tego kontrolera.
	Kontroler mo�na przypisa� tylko jednorazowo.
	Je�li uda�o si� przypisa� kontroler do pionka to zwraca true.
	*/
	bool Possess(IPawn *owner);
protected:
	IPawn*					m_owner;		// W�a�ciciel kontrolera.
};