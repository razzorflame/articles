#pragma once

#include "Main.hpp"

#include <unordered_map>

/* Klasa do zarz�dzania teksturami
*/
class CTextureManager final
{
public:
	/* Typedef dla umilenia �ycia. */
	typedef std::unordered_map<std::string, sf::Texture *> TTexturesUM;

	/*	Destruktor - zwalnia cala pamiec, wszystkie pozostale tekstury
	*/
	~CTextureManager();

	/*	Menedzer tekstur to singleton, zabraniamy kopiowania tego obiektu.
	*/
	CTextureManager(const CTextureManager &Other)	= delete;
	/*	Menedzer tekstur to singleton, zabraniamy kopiowania tego obiektu.
	*/
	void operator=(const CTextureManager &Other)	= delete;

	/*	Statyczna metoda, ktora laduje teksture do pamieci i ustawia j� pod kluczem
		podanym w [textureName]. Je�li textura o tej nazwie ju� istnia�a, to zamieniamy j�.
		Robimy to w taki spos�b, by nie "psu�" sprit�w, kt�re ju� korzystaj� z tamtej tekstury.
	*/
	static sf::Texture* Load(const std::string &textureName, const std::string &texturePath);

	/*	Usuwa teksture o podanej nazwie [textureName] z pami�ci.
	*/
	static bool			Unload(const std::string &textureName);
	
	/*	Usuwa wszystkie tekstury z pami�ci.
		Zwraca ilo�� usuni�tych tekstur.
	*/
	static std::size_t	Cleanup();

	/*	Pobiera teksture ze zbioru, jednak gdy jeszcze nie zosta�a ona wczytana
		to zwr�ci nullptr.
	*/
	static sf::Texture* Get(const std::string &textureName);

	/*	Sprawdza czy tekstura zosta�a wcze�niej wczytana.
	*/
	inline static bool Exists(const std::string &textureName) { return CTextureManager::Get(textureName) != nullptr; }
private:
	/*	Konstruktor menedzera tekstur.
		Jest prywatny ze wzgl�du na to, �e ca�a klasa jest singletonem.
	*/
	CTextureManager();

	/*	Tworzy pojedyncz� instancj� klasy CTextureManager i j� zwraca.
		Ta metoda jest prywatna, ze wzgl�du na to, �e zostawiamy zarz�dzanie
		klas� metodom statycznym.
	*/
	inline static CTextureManager& Instance()
	{
		static CTextureManager instance;
		return instance;
	}


	TTexturesUM			m_textures;		// Zbi�r tekstur.
};