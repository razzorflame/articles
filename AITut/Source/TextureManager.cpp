#include "../Include/TextureManager.hpp"

//////////////////////////////////////////////////////////////////////
CTextureManager::CTextureManager()
{
}

//////////////////////////////////////////////////////////////////////
CTextureManager::~CTextureManager()
{
	/* Usuwamy ka¿d¹ teksturê. */
	for (auto textureData : m_textures)
	{
		delete (textureData.second);
	}
}

//////////////////////////////////////////////////////////////////////
sf::Texture* CTextureManager::Load(const std::string &textureName, const std::string &texturePath)
{
	/* Spróbujmy popraæ teksture z mened¿era */
	sf::Texture *result = CTextureManager::Get(textureName);
	
	/* Jezeli istnieje juz tekstura o takiej nazwie */
	if (result)
	{
		/*	Wczytujemy j¹ ponownie, by nie zamieniaæ
			niepotrzebnie wskaŸników w zbiorze tekstur.
		*/
		result->loadFromFile(texturePath);
	}
	else
	{
		/*	Jeœli jednak tekstura jeszcze nie istania³a
			to musimy j¹ utworzyæ od podstaw.
			Tworzymy now¹ teksture.
		*/
		result = new sf::Texture();
		/* Wczytujemy j¹ z pliku. */
		result->loadFromFile(texturePath);
		/* Nastêpnie zapisujemy j¹ w kontenerze.*/
		Instance().m_textures[textureName] = result;
	}

	/* Tekstura wynikowa jest wskazywana wlasnie przez result. Zwracamy j¹ */
	return result;
}

//////////////////////////////////////////////////////////////////////
bool CTextureManager::Unload(const std::string &textureName)
{
	/*	By unikn¹æ kilkukrotniego wywo³ania funkcji Instance()
		tworzymy referencje na t¹ instancjê.
	*/
	auto &instance = Instance();

	/* Szukamy tekstury w kontenerze. Funkcja find zwraca iterator. */
	auto textureIt = instance.m_textures.find(textureName);

	/* Jeœli iterator wskazuje na koniec kontenera to nie znaleziono tekstury.*/
	if (textureIt == instance.m_textures.end())
	{
		return false;
	}
	else
	{
		/*	Tekstura zosta³a znaleziona. Nale¿y usun¹æ jej wskaŸnik. */
		delete (textureIt->second);
		/*	Iterator wskazuje dok³adnie na teksturê, któr¹ chcemy usun¹æ z kontenera.
			Robimy to za pomoc¹ metody erase.
		*/
		instance.m_textures.erase(textureIt);

		/* Tekstura zosta³a zwolniona, zwracamy prawdê. */
		return true;
	}
}

//////////////////////////////////////////////////////////////////////
std::size_t CTextureManager::Cleanup()
{
	/*	By unikn¹æ kilkukrotniego wywo³ania funkcji Instance()
		tworzymy referencje na t¹ instancjê.
	*/
	auto &instance = Instance();

	/*	Pobieramy iloœæ tekstur do usuniêcia. */
	std::size_t textureCount = instance.m_textures.size();

	/*	Usuwamy ka¿d¹ teksture. */
	for (auto textureData : instance.m_textures)
	{
		delete (textureData.second);
	}

	/*	Zwracamy iloœæ tekstur */
	return textureCount;
}

//////////////////////////////////////////////////////////////////////
sf::Texture * CTextureManager::Get(const std::string &textureName)
{
	/*	By unikn¹æ kilkukrotniego wywo³ania funkcji Instance()
		tworzymy referencje na t¹ instancjê.
	*/
	auto &instance = Instance();

	/* Szukamy tekstury w kontenerze. Funkcja find zwraca iterator. */
	auto textureIt = instance.m_textures.find(textureName);

	/* Jeœli iterator wskazuje na koniec kontenera to nie znaleziono tekstury.*/
	if (textureIt == instance.m_textures.end())
	{
		return nullptr;
	}

	/* Tekstura zosta³a znaleziona. Zwracamy j¹. */
	return textureIt->second;
}

