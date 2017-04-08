#include "../Include/AISense.hpp"

#include "../Include/Game.hpp" // Potrzebne do dostania sie do klasy poziomu

#include "../Include/SFMLShapes.hpp" // Potrzebne do generowania ksztaltu wycinka kola

// Domyslnie debugowanie jest wlaczone.
bool IAISense::DebugMode = true;

////////////////////////////////////////////////
IAISense::IAISense(IPawn &owner)
	: m_owner(owner)
{
}

////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////

////////////////////////////////////////////////
CSightSense::CSightSense(IPawn &owner, const float &sightDistance, const float &sightAngle)
	: IAISense(owner)
{
	/* Konstruktor po prostu ustawia poczatkowe wartosci. */
	SetSightDistance(sightDistance);
	SetSightAngle(sightAngle);
}

////////////////////////////////////////////////
bool CSightSense::SetSightDistance(const float & sightDistance)
{
	/* Musimy zapobiedz ustawieniu ujemnego zasiegu wzroku. */
	if (sightDistance > 0)
	{
		m_sightDistance = sightDistance;
		return true;
	}
	return false;
}

////////////////////////////////////////////////
bool CSightSense::SetSightAngle(const float & sightAngle)
{
	/*	Musimy zapobiedz ustawieniu ujemnego kata widzenia lub kata > 180.
		Przy kacie 180 stopni postac widzi 180 st. w lewo i 180st w prawo,
		wiec obejmuje to caly obszar naokolo niego.
	*/
	if (sightAngle > 0 && sightAngle <= 180)
	{
		m_sightAngle = sightAngle;
		return true;
	}
	return false;
}

////////////////////////////////////////////////
void CSightSense::DrawDebug()
{
	/*	Musimy sprawdzic czy w ogole debugging jest wlaczony.
	*/
	if (IAISense::DebugMode)
	{
		/*	Musimy utworzyc sobie ksztalt wycinka kola.
			Potem ustawimy sobie jego kolor, grubosc i kolor obramowania.
			Na koncu jeszcze tylko ustawiamy pozycje i obrot.
		*/
		auto shape = SFMLShapes::GeneratePie(m_sightDistance, m_sightAngle, 50);
		shape.setFillColor(sf::Color(255, 255, 255, 30));
		shape.setOutlineThickness(2);
		shape.setOutlineColor(sf::Color::White);
		shape.setRotation(m_owner.GetRotation());
		shape.setPosition(m_owner.GetLocation().x, m_owner.GetLocation().y);

		// Wyswietlamy wycinek kola na oknie.
		CGame::Instance().GetWindow().draw(shape);
	
		/*	Teraz trzeba wyswietlic postrzeganych aktorow.
			Nie warto tworzyc oddzielnego ksztaltu kola dla kazdego aktora,
			wiec zrobimy to w ten sposob, ze przygotujemy sobie kolo przed petla
			a nastepnie bedziemy je wyswietlac po prostu ze zmieniona pozycja.
		*/
		// Tworzymy kolo o promieniu np. 30px.
		sf::CircleShape sensedActorShape(30);
		// Wyrownujemy je do srodka (punkt 30px,30px)
		sensedActorShape.setOrigin(30, 30);
		// Ustawiamy kolor itp.
		sensedActorShape.setFillColor(sf::Color(255, 0, 0, 30));
		sensedActorShape.setOutlineColor(sf::Color::Red);
		sensedActorShape.setOutlineThickness(1);
		// Dla kazdego postrzeganego aktora...
		for (auto actor : m_sensedActors)
		{
			// ustaw pozycje kola na pozycje aktora...
			sensedActorShape.setPosition(actor->GetLocation().x, actor->GetLocation().y);
			// i wyswietl kolo na ekranie.
			CGame::Instance().GetWindow().draw(sensedActorShape);
		}
	}
}

////////////////////////////////////////////////
IAISense::TQueryActors CSightSense::QueryActors(bool(*filterFunc)(IActor * const))
{
	//	W tej funkcji wykonujemy od nowa sprawdzenie jacy aktorzy sa w polu widzenia.
	
	// Na poczatku musimy porzucic stare wyniki.
	m_sensedActors.clear();

	// Bierzemy liste aktorow ze sceny.
	auto actors = CGame::Instance().GetLevel()->GetActors();
	// Zapisujemy sobie pozycje wlasciciela do pomocniczej zmiennej
	auto parentLocation = m_owner.GetLocation();
	
	// Sprawdzamy kazdego aktora ze sceny
	for (auto actor : actors)
	{
		/*	Wykluczamy ze sprawdzenia wlasciciela zmyslu.
			(!filterFunc || filterFunc(actor)) "przepusci" aktora dalej jesli:
			a) niezdefiniowano funkcji filtra (filterFunc == nullptr)
			b) funkcja filtra zostala zdefiniowana i zwrocila true
		*/
		if (actor != &m_owner && (!filterFunc || filterFunc(actor)))
		{
			// Zapisujemy pozycje aktualnie sprawdzanego aktora do pomocniczej zmiennej
			auto actorLocation = actor->GetLocation();
			// Sprawdzamy czy aktor jest w zasiegu
			if (actorLocation.Distance(parentLocation) <= m_sightDistance)
			{
				/*	Musimy sobie policzyc kat, w ktorym musialby patrzec wlasciciel, zeby patrzec dokladnie w kierunku sprawdzanego aktora.
					Robi sie to w ten sposob. A = pozycja wlasciciela, B = pozycja sprawdzanego
					kat = atan2(B.y - A.y, B.x - A.x). Nastepnie kat konwertujemy z radianow na stopnie (kat = kat / Pi * 180st)
				*/
				float angle = atan2(actorLocation.y - parentLocation.y, actorLocation.x - parentLocation.x) / grim::Math::Pi * 180.f;

				/* Sprawdzamy |kat| < kat widzenia. Jesli tak to gracz jest w polu widzenia. */
				if (grim::Math::Absolute(angle) < m_sightAngle)
				{
					// Dodajemy sprawdzanego gracza jako poprawny wynik.
					m_sensedActors.push_back(actor);
				}
			}
		}	
	}

	return m_sensedActors;
}
