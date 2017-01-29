#include "../Include/TextureManager.hpp"

//////////////////////////////////////////////////////////////////////
CTextureManager::CTextureManager()
{
}

//////////////////////////////////////////////////////////////////////
CTextureManager::~CTextureManager()
{
	/* Usuwamy ka�d� tekstur�. */
	for (auto textureData : m_textures)
	{
		delete (textureData.second);
	}
}

//////////////////////////////////////////////////////////////////////
sf::Texture* CTextureManager::Load(const std::string &textureName, const std::string &texturePath)
{
	/* Spr�bujmy popra� teksture z mened�era */
	sf::Texture *result = CTextureManager::Get(textureName);
	
	/* Jezeli istnieje juz tekstura o takiej nazwie */
	if (result)
	{
		/*	Wczytujemy j� ponownie, by nie zamienia�
			niepotrzebnie wska�nik�w w zbiorze tekstur.
		*/
		result->loadFromFile(texturePath);
	}
	else
	{
		/*	Je�li jednak tekstura jeszcze nie istania�a
			to musimy j� utworzy� od podstaw.
			Tworzymy now� teksture.
		*/
		result = new sf::Texture();
		/* Wczytujemy j� z pliku. */
		result->loadFromFile(texturePath);
		/* Nast�pnie zapisujemy j� w kontenerze.*/
		Instance().m_textures[textureName] = result;
	}

	/* Tekstura wynikowa jest wskazywana wlasnie przez result. Zwracamy j� */
	return result;
}

//////////////////////////////////////////////////////////////////////
bool CTextureManager::Unload(const std::string &textureName)
{
	/*	By unikn�� kilkukrotniego wywo�ania funkcji Instance()
		tworzymy referencje na t� instancj�.
	*/
	auto &instance = Instance();

	/* Szukamy tekstury w kontenerze. Funkcja find zwraca iterator. */
	auto textureIt = instance.m_textures.find(textureName);

	/* Je�li iterator wskazuje na koniec kontenera to nie znaleziono tekstury.*/
	if (textureIt == instance.m_textures.end())
	{
		return false;
	}
	else
	{
		/*	Tekstura zosta�a znaleziona. Nale�y usun�� jej wska�nik. */
		delete (textureIt->second);
		/*	Iterator wskazuje dok�adnie na tekstur�, kt�r� chcemy usun�� z kontenera.
			Robimy to za pomoc� metody erase.
		*/
		instance.m_textures.erase(textureIt);

		/* Tekstura zosta�a zwolniona, zwracamy prawd�. */
		return true;
	}
}

//////////////////////////////////////////////////////////////////////
std::size_t CTextureManager::Cleanup()
{
	/*	By unikn�� kilkukrotniego wywo�ania funkcji Instance()
		tworzymy referencje na t� instancj�.
	*/
	auto &instance = Instance();

	/*	Pobieramy ilo�� tekstur do usuni�cia. */
	std::size_t textureCount = instance.m_textures.size();

	/*	Usuwamy ka�d� teksture. */
	for (auto textureData : instance.m_textures)
	{
		delete (textureData.second);
	}

	/*	Zwracamy ilo�� tekstur */
	return textureCount;
}

//////////////////////////////////////////////////////////////////////
sf::Texture * CTextureManager::Get(const std::string &textureName)
{
	/*	By unikn�� kilkukrotniego wywo�ania funkcji Instance()
		tworzymy referencje na t� instancj�.
	*/
	auto &instance = Instance();

	/* Szukamy tekstury w kontenerze. Funkcja find zwraca iterator. */
	auto textureIt = instance.m_textures.find(textureName);

	/* Je�li iterator wskazuje na koniec kontenera to nie znaleziono tekstury.*/
	if (textureIt == instance.m_textures.end())
	{
		return nullptr;
	}

	/* Tekstura zosta�a znaleziona. Zwracamy j�. */
	return textureIt->second;
}

