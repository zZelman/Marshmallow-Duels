#include "CGame.h"
#include "Headers/include_sfml.h"
#include <iostream>
#include <assert.h>

CGame::CGame()
{
	// * m_pWindow new'ed here
	initWindow();

	m_pTexture = new CTexture("res/Players/arrow debug(32x32, 2x2).png",
	                          sf::Vector2<int>(32, 32),
	                          sf::Vector2<int>(2, 2));
	m_pPlayer = new CPlayer(m_pTexture, sf::Vector2<int>(1, 1));

	m_pTile_Container = new CTile_Container("simple map.tmx");

	m_pRenderEngine = new CRenderEngine(m_pWindow, m_pTile_Container, m_pPlayer);

	m_pUI = new CUI(m_pPlayer);

	m_pPhysicsEngine = new CPhysicsEngine(m_pPlayer, m_pTile_Container);



	// re-work the window to be dependent on the amount of tiles in the world
	// work toward finding the whole world width/height
//	sf::Vector2<int> gridSize = m_pTile_Container->getGridSize();
//	sf::Vector2<int> gridSubSize = m_pTile_Container->getGridSubSize();
//	int width = gridSize.x * gridSubSize.x;
//	int height = gridSize.y * gridSubSize.y;
//	m_pWindow->create(sf::VideoMode(width, height), "Placeholder-RTS");


	isRunning = false;
	isPaused = false;
}


CGame::~CGame()
{
	delete m_pWindow;
	m_pWindow = NULL;

	delete m_pTexture;
	m_pTexture = NULL;

	delete m_pPlayer;
	m_pPlayer = NULL;

	delete m_pRenderEngine;
	m_pRenderEngine = NULL;

	delete m_pUI;
	m_pUI = NULL;

	delete m_pPhysicsEngine;
	m_pPhysicsEngine = NULL;

}


sf::RenderWindow* CGame::getGameWindow()
{
	return m_pWindow;
}


bool CGame::getIsRunning()
{
	return isRunning;
}


bool CGame::getIsPaused()
{
	return isPaused;
}


void CGame::startGame()
{
	gameLoop();
}


void CGame::stopGame()
{
	isRunning = false;
}


void CGame::initWindow()
{
	int numTiles = 25;
	int sizeTile = 32;
	int size = sizeTile * numTiles;
	m_pWindow 	= new sf::RenderWindow(sf::VideoMode(size, size), "Independent Study");

	// NOTE: do not use Virtual Sync and fixed frame rate at once
//	m_pGameWindow->setVerticalSyncEnabled(true);
	m_pWindow->setFramerateLimit(60);

	sf::FloatRect viewRect(0, 0, size, size);
	sf::View view;
	view.reset(viewRect);
	m_pWindow->setView(view);

	m_pWindow->setVisible(true);
}


void CGame::gameLoop()
{
	isRunning = true;

	while (m_pWindow->isOpen() && isRunning)
	{

		// NOTE: events must be polled within the main window thread (API thing)
		sf::Event event;
		bool isSystemEvent = false;
		while (m_pWindow->pollEvent(event))
		{
			// window was closed by user
			if (event.type == sf::Event::Closed)
			{
				m_pWindow->close();
				return;
			}

			// update game system information (size, focus, etc)
			isSystemEvent = input_gameSystem(&event);

			// only allow the user to supply input to the game when not paused
			//		and the input was not a system call
			if (!isPaused && !isSystemEvent)
			{
				input_user(&event);
			}
		}

		if (!isPaused) // only update states if game is actively running
		{
			update(); // update all game states
		}

		render(); // render all game things based on their states
	}

	// if the program flow gets here, its because isRunning was requested as being false
	//		therefore, you still need to close the window
	m_pWindow->close();
}


bool CGame::input_user(sf::Event* pEvent)
{

	// keyboard
	if (pEvent->type == sf::Event::KeyPressed) // press
	{
		if (pEvent->key.code == sf::Keyboard::Escape)
		{
			isRunning = false;
			return true;
		}
		else if (m_pUI->userInput_keyPress(pEvent))
		{
			return true;
		}

	}
	else if (pEvent->type == sf::Event::KeyReleased) // release
	{
		if (m_pUI->userInput_keyRelease(pEvent))
		{
			return true;
		}

	}

	// mouse
	if (pEvent->type == sf::Event::MouseButtonPressed) // press
	{
		if (m_pUI->userInput_mousePress(pEvent))
		{
			return true;
		}
	}
	else if (pEvent->type == sf::Event::MouseButtonReleased) // release
	{
		if (m_pUI->userInput_mouseRelease(pEvent))
		{
			return true;
		}
	}

	return false;
}


bool CGame::input_gameSystem(sf::Event* pEvent)
{
	// user is not looking at game
	if (pEvent->type == sf::Event::LostFocus)
	{
		isPaused = true;
		return true;
	}

	// user is looking at the game now
	if (pEvent->type == sf::Event::GainedFocus)
	{
		isPaused = false;
		return true;
	}

	// user changed the window size
	if (pEvent->type == sf::Event::Resized)
	{
		sf::FloatRect visibleArea(0, 0, pEvent->size.width, pEvent->size.height);
		m_pWindow->setView(sf::View(visibleArea));

		return true;
	}

	return false;
}


void CGame::update()
{
	m_pPhysicsEngine->update();

	m_pPlayer->update();

}


void CGame::render()
{
	m_pWindow->clear(sf::Color::White); // clear screen with a black background

	m_pRenderEngine->render();

	m_pWindow->display(); // displays what has been rendered since last clear
}
