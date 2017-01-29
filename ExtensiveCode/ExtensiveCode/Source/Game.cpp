#include "../Include/Game.hpp"

/////////////////////////////////////////////////////////
CGame::CGame()							// Konstruktor klasy.
	:									// Korzystamy z listy inicjalizacyjnej.
m_status(Status::Initializing),			// Status w konstruktorze ustawiamy na Initializing.
										// Tworzymy okno SFMLa. Typowe okienko 800x600.
m_window(sf::VideoMode(800, 600, 32), "Tworzenie gier - podstawowa budowa gry wzorowana na Unreal Engine 4", sf::Style::Close),	
m_currentLevel(new CLevel())			// Tworzymy domyœln¹ scene.
{
}

/////////////////////////////////////////////////////////
CGame::~CGame()							// Destruktor klasy.
{
	// Zamknijmy okno gry je¿eli zosta³o otwarte.
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
	/* Pamiêtamy ¿eby ustawiæ odpowiedni status aplikacji. */
	m_status = Status::Running;

	/* Ciemnoszary kolor. */
	sf::Color bgColor(30, 30, 30);

	/* By prawid³owo uaktualniaæ scenê potrzebujemy czasu klatki. */
	sf::Clock GameClock;
	/* W DeltaTime przechowujemy czas klatki. */
	float DeltaTime = 1 / 60.f;

	/*	Wykonujemy pêtlê glówn¹.
		Przerywamy kiedy status zmienimy na CleaningUp
		czyli po prostu gdy chcemy zamkn¹æ aplikacjê.
	*/
	while (m_status != Status::CleaningUp)
	{
		/*	Aby zmierzyæ czas klatki potrzebujemy pobraæ czas przy jej rozpoczêciu i przy koñcu */
		float frameStartTime = GameClock.getElapsedTime().asSeconds();

		/* Pêtla zdarzeñ */
		sf::Event windowEvent;
		while (m_window.pollEvent(windowEvent))
		{
			if (windowEvent.type == sf::Event::Closed)
				m_status = Status::CleaningUp; // Reszta czyszczenia zostanie wykonana w destruktorze.
		}

		m_window.clear(bgColor);

		/*	Uaktualnij wszystkie elementy sceny
			A nastêpnie j¹ wyœwietl.
		*/
		m_currentLevel->Update(DeltaTime);
		m_currentLevel->Draw();
		
		/* Ca³oœæ przenosimy na ekran. */
		m_window.display();

		/*	Aby zmierzyæ czas klatki potrzebujemy pobraæ czas przy jej rozpoczêciu i przy koñcu
			Dodatkowo liczymy tutaj ile czasu zajê³o obs³u¿enie logiki i wyœwietlenie klatki.
		*/
		DeltaTime = GameClock.getElapsedTime().asSeconds() - frameStartTime;
	}
}


