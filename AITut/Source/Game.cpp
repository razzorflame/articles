#include "../Include/Game.hpp"
#include "../Include/TextureManager.hpp"

#include "../Include/Player.hpp"
#include "../Include/Enemy.hpp"

/////////////////////////////////////////////////////////
CGame::CGame()							// Konstruktor klasy.
	:									// Korzystamy z listy inicjalizacyjnej.
m_status(Status::Initializing),			// Status w konstruktorze ustawiamy na Initializing.
										// Tworzymy okno SFMLa. Typowe okienko 800x600.
m_window(sf::VideoMode(800, 600, 32), "Sztuczna inteligencja #01", sf::Style::Close),	
m_currentLevel(new CLevel())			// Tworzymy domy�ln� scene.
{
	CTextureManager::Load("Player_Stand_01", "Data/Textures/BlueMage/Mage_Stand_01.png");
	CTextureManager::Load("Enemy_Stand_01", "Data/Textures/OrangeMage/Mage_Stand_01.png");
}

/////////////////////////////////////////////////////////
CGame::~CGame()							// Destruktor klasy.
{
	// Zamknijmy okno gry je�eli zosta�o otwarte.
	if(m_window.isOpen())
	{
		m_window.close();
	}

	if (m_currentLevel)
		delete m_currentLevel;
}

/////////////////////////////////////////////////////////
void CGame::Run()						// Glowny kod gry.
{
	/* Pami�tamy �eby ustawi� odpowiedni status aplikacji. */
	m_status = Status::Running;

	auto player = new CPlayer();
	player->SetLocation({ 400, 300 });
	m_currentLevel->Add(player);


	auto enemy = new CEnemy();
	enemy->SetLocation({400, 300});
	m_currentLevel->Add(enemy);

	/* Ciemnoszary kolor. */
	sf::Color bgColor(30, 30, 30);

	/* By prawid�owo uaktualnia� scen� potrzebujemy czasu klatki. */
	sf::Clock GameClock;
	/* W DeltaTime przechowujemy czas klatki. */
	float DeltaTime = 1 / 60.f;

	/*	Wykonujemy p�tl� gl�wn�.
		Przerywamy kiedy status zmienimy na CleaningUp
		czyli po prostu gdy chcemy zamkn�� aplikacj�.
	*/
	while (m_status != Status::CleaningUp)
	{
		/*	Aby zmierzy� czas klatki potrzebujemy pobra� czas przy jej rozpocz�ciu i przy ko�cu */
		float frameStartTime = GameClock.getElapsedTime().asSeconds();

		/* P�tla zdarze� */
		sf::Event windowEvent;
		while (m_window.pollEvent(windowEvent))
		{
			if (windowEvent.type == sf::Event::Closed)
				m_status = Status::CleaningUp; // Reszta czyszczenia zostanie wykonana w destruktorze.
		}

		m_window.clear(bgColor);

		/*	Uaktualnij wszystkie elementy sceny
			A nast�pnie j� wy�wietl.
		*/
		m_currentLevel->Update(DeltaTime);
		m_currentLevel->Draw();
		
		/* Ca�o�� przenosimy na ekran. */
		m_window.display();

		/*	Aby zmierzy� czas klatki potrzebujemy pobra� czas przy jej rozpocz�ciu i przy ko�cu
			Dodatkowo liczymy tutaj ile czasu zaj�o obs�u�enie logiki i wy�wietlenie klatki.
		*/
		DeltaTime = GameClock.getElapsedTime().asSeconds() - frameStartTime;
	}
}


