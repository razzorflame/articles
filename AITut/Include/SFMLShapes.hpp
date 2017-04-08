#pragma once

#include "Main.hpp"

namespace SFMLShapes
{
	/*	Funkcja, ktora tworzy wycinek kola o promieniu radius, kacie 2*angle (wartosc angle w lewo i wartosc angle w prawo).
		vertexCount to ilosc punktow, z ktorych bedzie skladal sie ksztalt. Minimalnie sa to 3 punkty (bardzo slaba dokladnosc, trojkat)
	*/
	sf::ConvexShape GeneratePie(const float &radius, const float &angle, unsigned int vertexCount = 20);
}
