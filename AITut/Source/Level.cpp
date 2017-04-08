#include "../Include/Level.hpp"

#include "../Include/Game.hpp"

////////////////////////////////////////////////////////////////
CLevel::CLevel()
{
}

////////////////////////////////////////////////////////////////
CLevel::~CLevel()
{
	/* Przy niszczeniu sceny niszczymy tak¿e aktorów. */
	this->Cleanup();
}

////////////////////////////////////////////////////////////////
bool CLevel::Add(IActor *actor)
{
	/* Nie marnujmy czasu gdy podano wskaŸnik zerowy. */
	if (actor)
	{
		/*	Sprawdzamy czy przypadkiem podany aktor
			nie znajduje siê ju¿ na scenie.
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
	/* Nie marnujmy czasu gdy podano wskaŸnik zerowy. */
	if (actor)
	{
		/*	Sprawdzamy czy aktor jest na scenie.
			Jeœli tak to go usuwamy.
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
	/* Usuñ wszystkich aktorów (z pamiêci, nie tylko z kontenera)*/
	std::size_t actorsCount = m_actors.size();
	for (auto *actor : m_actors)
		delete actor;
	return actorsCount;
}

////////////////////////////////////////////////////////////////
void CLevel::Update(const float &deltaTime)
{
	/* Wszyscy aktorzy zostaj¹ uaktualnieni. */
	for (auto *actor : m_actors)
	{
		actor->Update(deltaTime);
	}
}

////////////////////////////////////////////////////////////////
void CLevel::Draw()
{
	/* Wyœwietlamy ka¿dego aktora. */
	for (auto *actor : m_actors)
	{
		actor->Draw();
	}
}
