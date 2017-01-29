#include "../Include/Level.hpp"

#include "../Include/Game.hpp"

////////////////////////////////////////////////////////////////
CLevel::CLevel()
{
}

////////////////////////////////////////////////////////////////
CLevel::~CLevel()
{
	/* Przy niszczeniu sceny niszczymy tak�e aktor�w. */
	this->Cleanup();
}

////////////////////////////////////////////////////////////////
bool CLevel::Add(IActor *actor)
{
	/* Nie marnujmy czasu gdy podano wska�nik zerowy. */
	if (actor)
	{
		/*	Sprawdzamy czy przypadkiem podany aktor
			nie znajduje si� ju� na scenie.
		*/
		if (!this->Exists(actor))
		{
			m_actors.push_back(actor);
			return true;
		}
	}
	return false;
}

////////////////////////////////////////////////////////////////
bool CLevel::Remove(IActor *actor)
{
	/* Nie marnujmy czasu gdy podano wska�nik zerowy. */
	if (actor)
	{
		/*	Sprawdzamy czy aktor jest na scenie.
			Je�li tak to go usuwamy.
		*/
		auto actorIt = std::find(m_actors.begin(), m_actors.end(), actor);
		if (actorIt != m_actors.end())
		{
			m_actors.erase(actorIt);
			return true;
		}
	}
	return false;
}

////////////////////////////////////////////////////////////////
bool CLevel::Exists(IActor *actor) const
{
	return std::find(m_actors.begin(), m_actors.end(), actor) != m_actors.end();
}

////////////////////////////////////////////////////////////////
std::size_t CLevel::Cleanup()
{
	/* Usu� wszystkich aktor�w (z pami�ci, nie tylko z kontenera)*/
	std::size_t actorsCount = m_actors.size();
	for (auto *actor : m_actors)
		delete actor;
	return actorsCount;
}

////////////////////////////////////////////////////////////////
void CLevel::Update(const float &deltaTime)
{
	/* Wszyscy aktorzy zostaj� uaktualnieni. */
	for (auto *actor : m_actors)
	{
		actor->Update(deltaTime);
	}
}

////////////////////////////////////////////////////////////////
void CLevel::Draw()
{
	/* Wy�wietlamy ka�dego aktora. */
	for (auto *actor : m_actors)
	{
		actor->Draw();
	}
}
