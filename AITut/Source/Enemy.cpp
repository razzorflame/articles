#include "..\Include\Enemy.hpp"

#include "..\Include\Game.hpp" // Klasa gry potrzebna do wyswietlenia wroga.
#include "..\Include\TextureManager.hpp" // Klasa menedzera tekstur do ich pobrania.

////////////////////////////////////////////////////////
CEnemy::CEnemy()
	: IPawn(new CEnemyAIController), // Tak jak w klasie gracza wywolujemy konstruktor klasy bazowej z wlasnym kontrolerem AI.
	m_sightSense(*this, 400, 30) // Tworzymy sobie zmysl wzroku. Musimy podac referencje na wlasciciela (*this), dystans i kat widzenia
{
	/*	Aby zobaczyc pelne wytlumaczenie ponizszego kodu przejdz do kontruktora klasy CPlayer
		w pliku Player.cpp
	*/
	auto texture = CTextureManager::Get("Enemy_Stand_01"); // Tym razem ustawimy sobie inna teksturke. 
	m_sprite.setTexture(*texture); // Ustawiamy teksturke
	m_sprite.setOrigin(36, 36);	// Ustawiamy srodek wyswietlania.
}

////////////////////////////////////////////////////////
void CEnemy::SetLocation(const grim::Vector2 & location)
{
	// To samo co w CPlayer::SetLocation
	IPawn::SetLocation(location);
	m_sprite.setPosition(location.x, location.y);
}

////////////////////////////////////////////////////////
void CEnemy::Update(const float & deltaTime)
{
	// Bardzo wazne! Wykonujemy tez to co wykonuje klasa bazowa!
	IPawn::Update(deltaTime);

	// Uaktualniamy nasz zmysl wzroku.
	m_sightSense.QueryActors();
}

////////////////////////////////////////////////////////
void CEnemy::Draw()
{
	// To samo co w CPlayer::Draw
	CGame::Instance().GetWindow().draw(m_sprite);
	// Wyswietlamy informacje debugowania.
	m_sightSense.DrawDebug();
}


////////////////////////////////////////////////////////
CEnemyAIController::CEnemyAIController()
{
	// Poki co kontroler zostawiamy pusty.
}

////////////////////////////////////////////////////////
void CEnemyAIController::Update(const float & deltaTime)
{
	// Poki co kontroler zostawiamy pusty.
}
