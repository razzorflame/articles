#pragma once

#include "Main.hpp"

#include <unordered_map>

/* Klasa do zarz¹dzania teksturami
*/
class CTextureManager final
{
public:
	/* Typedef dla umilenia ¿ycia. */
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

	/*	Statyczna metoda, ktora laduje teksture do pamieci i ustawia j¹ pod kluczem
		podanym w [textureName]. Jeœli textura o tej nazwie ju¿ istnia³a, to zamieniamy j¹.
		Robimy to w taki sposób, by nie "psuæ" spritów, które ju¿ korzystaj¹ z tamtej tekstury.
	*/
	static sf::Texture* Load(const std::string &textureName, const std::string &texturePath);

	/*	Usuwa teksture o podanej nazwie [textureName] z pamiêci.
	*/
	static bool			Unload(const std::string &textureName);
	
	/*	Usuwa wszystkie tekstury z pamiêci.
		Zwraca iloœæ usuniêtych tekstur.
	*/
	static std::size_t	Cleanup();

	/*	Pobiera teksture ze zbioru, jednak gdy jeszcze nie zosta³a ona wczytana
		to zwróci nullptr.
	*/
	static sf::Texture* Get(const std::string &textureName);

	/*	Sprawdza czy tekstura zosta³a wczeœniej wczytana.
	*/
	inline static bool Exists(const std::string &textureName) { return CTextureManager::Get(textureName) != nullptr; }
private:
	/*	Konstruktor menedzera tekstur.
		Jest prywatny ze wzglêdu na to, ¿e ca³a klasa jest singletonem.
	*/
	CTextureManager();

	/*	Tworzy pojedyncz¹ instancjê klasy CTextureManager i j¹ zwraca.
		Ta metoda jest prywatna, ze wzglêdu na to, ¿e zostawiamy zarz¹dzanie
		klas¹ metodom statycznym.
	*/
	inline static CTextureManager& Instance()
	{
		static CTextureManager instance;
		return instance;
	}


	TTexturesUM			m_textures;		// Zbiór tekstur.
};