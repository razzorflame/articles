#include "..\Include\Player.hpp"

#include "..\Include\Game.hpp"				// Potrzebujemy klasy gry bo w niej znajduje sie okno, na ktorym bedziemy wyswietlac gracza.
#include "..\Include\TextureManager.hpp"	// Potrzebujemy texture menedzera by dostac teksture

////////////////////////////////////////////////////////
CPlayer::CPlayer() // Konstruktor klasy
	: IPawn(new CPlayerController) // klasa bazowa IPawn pobiera wskaznik na kontroler, ktory sami musimy sobie utworzyc.
{
	/*	Tutaj przeprowadzimy sobie konfiguracje naszego gracza.
		Na pewno musimy ustawic teksture sprajta i ja wysrodkowac (pozycja bedzie ustalana od srodka tekstury)
	*/


	/*	Bierzemy teksture i zapisujemy do "texture" (auto odpowiada teraz za sf::Texture*).
		Przypominam, ze metoda CTextureManager::Get nie wczytuje tekstury z dysku tylko daje nam juz wczesniej
		wczytana teksture, ktora sobie tak nazwalismy. Wczytamy ja przy uruchomieniu gry.
	*/
	auto texture = CTextureManager::Get("Player_Stand_01");		
	m_sprite.setTexture(*texture);								// Ustawiamy teksture sprajtowi
	m_sprite.setOrigin(36, 36);									// Tekstura ma rozmiar 73x73 wiec ustawiam origin na srodek
}

////////////////////////////////////////////////////////
void CPlayer::SetLocation(const grim::Vector2 & location)
{
	/*	Tutaj mamy za zadanie ustawienie pozycji kazdemu wyswietlanemu elementowi.
		Poki co mamy tylko glownego sprajta.
		Musimy tez wywolac implementacje tej metody dla klasy bazowej.
	*/
	IPawn::SetLocation(location);								// wywolujemy implementacje klasy bazowej
	m_sprite.setPosition(location.x, location.y);				// ustawiamy pozycje sprajta
}

////////////////////////////////////////////////////////
void CPlayer::Draw()
{
	/*	Ta metoda odpowiada za wyswietlenie kazdego elementu graficznego, ktory mamy w naszej klasie.
		Na razie jest to tylko glowny sprajt (m_sprite). Musimy wiec sie dostac do okna SFMLa i wyswietlic na nim
		naszego sprajta.
	*/
	CGame::Instance().GetWindow().draw(m_sprite);
}

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
CPlayerController::CPlayerController() // Konstruktor kontrolera gracza
	: m_moveSpeed(200.f) // niech postac porusza sie przykladowo z predkoscia 200px/s
{
}

////////////////////////////////////////////////////////
void CPlayerController::Update(const float & deltaTime)
{
	/*	Ta metoda odpowiada za ciagla obsluge klawiszy i ruchu */

	/*	Pobieram sobie pozycje gracza do zmiennej by ulatwic operacje na niej.
		Na koncu po wykonaniu wszelkich operacji na kopii ustawimy sobie naszego gracza
		na ta pozycje.
	*/
	auto location = m_owner->GetLocation();

	/*	Tutaj sprawdzam czy gracz naciska przyciski zwiazane z ruchem.
		Jesli tak to odpowiednio zmieniam pozycje gracza
	*/
	if (sf::Keyboard::isKeyPressed(K_MoveUp))
		location += grim::Vector2f(0, -m_moveSpeed * deltaTime);
	if (sf::Keyboard::isKeyPressed(K_MoveDown))
		location += grim::Vector2f(0, m_moveSpeed * deltaTime);
	if (sf::Keyboard::isKeyPressed(K_MoveLeft))
		location += grim::Vector2f(-m_moveSpeed * deltaTime, 0);
	if (sf::Keyboard::isKeyPressed(K_MoveRight))
		location += grim::Vector2f(m_moveSpeed * deltaTime, 0);

	// Po zmianach trzeba ustawic nowa pozycje naszemu graczowi.
	// Przypominam: m_owner to wskaznik typu IPawn* na kontrolowan¹ postaæ.
	m_owner->SetLocation(location);
}
