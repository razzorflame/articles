#pragma once

#include "Actor.hpp"

class IPawnController;

/*	Klasa "pionka" jest baz¹ dla wszystkich
	obiektów, które mog¹ siê poruszaæ po scenie
	(czy w jakikolwiek inny sposób maj¹ byæ kontrolowane)
*/
class IPawn
	: public IActor
{
public:
	/*	Konstruktor pionka.
	*/
	explicit IPawn(IPawnController *controller);

	/*	Destruktor pionka. Dba o to, by kontroler zosta³ prawid³owo usuniêty.
	*/
	virtual ~IPawn() override;

	/*	Usuwa stary kontroler i zmienia go na nowy.
	*/
	void ResetController(IPawnController *controller);

	/*	Funkcja uaktualniaj¹ca kontroler. Wci¹¿ mo¿e byæ prze³adowana
		w klasach pochodnych.
	*/
	virtual void Update(const float &deltaTime) override;
protected:
	IPawnController*		m_controller;		// Kontroler pionka.
};

/*	Kontroler dla klasy "pionka".
Bêdzie po prostu kontrolowa³ go, porusza³ itp.
*/
class IPawnController
{
public:
	/* Konstruktor klasy kontrolera pionka */
	IPawnController();

	/* Destruktor klasy kontrolera pionka */
	virtual ~IPawnController();

	/*	Funkcja bêdzie uaktualnia³a wszystko
	co zwi¹zane z ruchem pionka. Prezentacje pionka
	zostawiamy dla jego klasy.
	*/
	virtual void Update(const float &deltaTime) = 0;

	/*	Funkcja sprawdza czy kontroler jest u¿ywany
	przez jakiegoœ pionka.
	*/
	inline bool IsPossessed() const { return m_owner != nullptr; }

	/*	Klasa pionka jest zobowi¹zana do ustawienia
	siebie jako w³aœciciela kontrolera (metod¹ Possess)
	*/
	friend class IPawn;
private:
	/*	Ustawia w³aœciciela tego kontrolera.
	Kontroler mo¿na przypisaæ tylko jednorazowo.
	Jeœli uda³o siê przypisaæ kontroler do pionka to zwraca true.
	*/
	bool Possess(IPawn *owner);
protected:
	IPawn*					m_owner;		// W³aœciciel kontrolera.
};