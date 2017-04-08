#include "../Include/SFMLShapes.hpp"

#include "../Include/Math.hpp"

namespace SFMLShapes
{
	sf::ConvexShape GeneratePie(const float & radius, const float & angle, unsigned int vertexCount)
	{
		/*	Nie mozemy utworzyc wycinka kola z mniej niz 3 punktow.
			Zabezpieczamy przed nierozsadnym uzytkownikiem
		*/
		if (vertexCount < 3)
			vertexCount = 3;

		/*	Tworzymy sobie pomocnicza zmienna, ktora zawiera kat "angle" tylko ze w radianach.
			Potrzebujemy kata w radianach bo wymagaja tego funkcje trygonometryczne cos() i sin()
		*/
		const float angleRad = angle * grim::Math::Pi / 180.f;

		// Tworzymy nowy ksztalt.
		auto shape = sf::ConvexShape();
		// Ilosc punktow to vertexCount. Tym samym wiemy, ze ich indeksy to od 0 do vertexCount-1
		shape.setPointCount(vertexCount);

		// Dodajemy punkt startowy (punkt 0px,0px). Punkt ten lezy w centrum kola
		shape.setPoint(0, { 0, 0 });

		/*	Teraz zaczynamy dodawac punkty od indeksu 1 (indeks 0 wypelnilismy na gorze)
			Lecimy az do ostatniego
		*/
		for (auto i = 1u; i < vertexCount; i++)
		{
			/*	Liczymy sobie kat pod ktorym lezy aktualny punkt.
				Caly wycinek rozposciera sie od -angle do +angle, lecz my od razu bedziemy pracowac na radianach.
				Wynikowy kat to po prostu -angleRad + 2*angleRad*(i-1)*(vertexCount-1)
			*/
			const float targetAngle = -angleRad + (i - 1) / float(vertexCount - 1)*angleRad * 2;
			// liczymy pozycje tego punktu: (x, y). Robimy to tak: (cos(kat)*radius, sin(kat)*radius)
			shape.setPoint(i, { cos(targetAngle)*radius, sin(targetAngle)*radius });
		}
		return shape;
	}
}
