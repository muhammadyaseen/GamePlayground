#include "Game.h"

// @see : http://stackoverflow.com/questions/10647448/why-constant-data-member-of-a-class-need-to-be-initialized-at-the-constructor
Game::Game(RenderWindow& window, SFMLDebugDraw& debugDraw) 
	: timeStep( 1.0f / 60.0f ), _rWindow(window), _rSfmlDebugDraw(debugDraw)
{
	  //_rWindow = window;
}

bool Game::Run() 
{
	Initialize();
	LoadContent();
	Clock timeElapsed;
	_rWindow.setKeyRepeatEnabled(true);

	while (_rWindow.isOpen())
	{
		_rWindow.pollEvent(e);

		if (e.type == Event::Closed)
		{
			_rWindow.close();
		}
		
		HandleInput(e);

		//Time lastUpdateCall = timeElapsed.restart();

		if (timeElapsed.getElapsedTime().asMilliseconds() >= 16)
		{
			Update(e, oldEvent, timeElapsed.restart());
		}

		Time lastDrawCall = /*lastUpdateCall +*/ timeElapsed.getElapsedTime(); //.restart();

		Draw(_rWindow, lastDrawCall);

		oldEvent = e;

	}
	
	return true;
}

void Game::Initialize() 
{
	_pWorld = new b2World( b2Vec2(0, 10.f) );
	_pWorld->SetAllowSleeping( true );
	_pWorld->SetDebugDraw( &_rSfmlDebugDraw );
}


void Game::LoadContent() 
{
	//string contentPath = "H:\\Art Assets\\Demo\\";
	
	Texture ground;
	ground.loadFromFile("Art\\Floor.png");
	_textureBank.insert( pair<string, Texture>("floor", ground) );

	Texture boundaryWall;
	boundaryWall.loadFromFile("Art\\BoundaryWall.png");
	_textureBank.insert( pair<string, Texture>("boundaryWall", boundaryWall) );


	Texture ball;
	ball.loadFromFile("Art\\Skull.png");
	_textureBank.insert( pair<string, Texture>("ball", ball) );

	Texture box;
	box.loadFromFile("Art\\Crate.png");
	_textureBank.insert( pair<string, Texture>("box", box) );

	Texture spikePlatform;
	spikePlatform.loadFromFile("Art\\Spikes.png");
	_textureBank.insert( pair<string, Texture>("spikes", spikePlatform) );

	Texture bomb;
	bomb.loadFromFile("Art\\Bomb.png");
	_textureBank.insert( pair<string, Texture>("bomb", bomb) );

	Texture bombParticle;
	bombParticle.loadFromFile("Art\\BombParticle.png");
	_textureBank.insert( pair<string, Texture>("bombParticle", bombParticle) );

	Bomb explosive( _textureBank["bomb"], 400, 550, 200 );
	explosive.SetWorld( *_pWorld );
	bombs.push_back( explosive );

	//load ground

	StaticPlatform road( _textureBank["floor"], 400, 600);
	road.SetWorld( *_pWorld );
	platforms.push_back( road );

	//load roof

	StaticPlatform roof( _textureBank["floor"], 400, 0);
	roof.SetWorld(*_pWorld);
	platforms.push_back(roof);

	//create left and right walls

	//left wall
	StaticPlatform leftWall( _textureBank["boundaryWall"], 0, 200);
	leftWall.SetWorld( *_pWorld );
	platforms.push_back( leftWall );

	//right wall
	StaticPlatform rightWall( _textureBank["boundaryWall"], 780, 200);
	rightWall.SetWorld( *_pWorld );
	platforms.push_back( rightWall );

	//load spike platform
	StaticPlatform spike( _textureBank["spikes"], 350, 200, 45);
	spike.SetWorld( *_pWorld );
	platforms.push_back( spike );


	//load balls
	Ball skullBall( _textureBank["ball"], 650, 0);
	skullBall.SetWorld( *_pWorld );
	balls.push_back( skullBall );

	//load boxes
	Box crate( _textureBank["box"], 300, 0);
	crate.SetWorld( *_pWorld );
	boxes.push_back( crate );

	//load characters
	Edward.LoadContent();
	Edward.SetWorld(*_pWorld);
	
	//load enemy
	enemy.LoadContent();
	enemy.SetWorld(*_pWorld);

}

void Game::UnloadContent() 
{
	delete _pWorld;
}

void Game::Update(Event gameEvent, Event previousGameEvent, Time timeSinceLastUpdateCall)
{
	_pWorld->Step(timeStep, 8, 8);

	Time frameTime = frameClock.restart();

	for (int i = 0; i < balls.size(); ++i)
		balls[i].Update(gameEvent, timeSinceLastUpdateCall);

	for (int i = 0; i < boxes.size(); ++i)
		boxes[i].Update(gameEvent, timeSinceLastUpdateCall);

	for (int i = 0; i < platforms.size(); ++i)
		platforms[i].Update(gameEvent, timeSinceLastUpdateCall);

	for (int i = 0; i < bombs.size(); ++i)
		bombs[i].Update(gameEvent, timeSinceLastUpdateCall);

	Edward.Update(gameEvent, previousGameEvent, timeSinceLastUpdateCall, frameTime);

	enemy.Update(gameEvent, Edward, timeSinceLastUpdateCall, frameTime);
}

void Game::Draw(RenderWindow& window, Time timeSinceLastDrawCall ) 
{
	_rWindow.clear( Color(0,0,0) );

	for ( int i = 0; i < balls.size(); ++i)
		balls[i].Draw(_rWindow, timeSinceLastDrawCall );

	for ( int i = 0; i < boxes.size(); ++i)
		boxes[i].Draw( _rWindow, timeSinceLastDrawCall );

	for ( int i = 0; i < platforms.size(); ++i)
		platforms[i].Draw( _rWindow, timeSinceLastDrawCall );

	for ( int i = 0; i < bombs.size(); ++i)
		bombs[i].Draw( _rWindow, timeSinceLastDrawCall );
	
	Edward.Draw(_rWindow, timeSinceLastDrawCall);
	
	enemy.Draw(_rWindow, timeSinceLastDrawCall);
		
	_pWorld->DrawDebugData();

	_rWindow.display();

}

void Game::HandleInput(Event gameEvent)
{
	if ( gameEvent.type == Event::KeyPressed )
	{
	
		if ( gameEvent.key.code == Keyboard::C ) //spawn box
		{
			Vector2i mousePos = Mouse::getPosition( _rWindow );

			Box crate( _textureBank["box"], mousePos.x, mousePos.y);
			crate.SetWorld( *_pWorld );
			boxes.push_back( crate );

		}

		if ( gameEvent.key.code == Keyboard::B ) //spawn ball
		{
			Vector2i mousePos = Mouse::getPosition( _rWindow );

			Ball ball( _textureBank["ball"], mousePos.x, mousePos.y);
			ball.SetWorld( *_pWorld );
			balls.push_back( ball );

		}

		if ( gameEvent.key.code == Keyboard::C ) //increase ball radius
		{}

		if ( gameEvent.key.code == Keyboard::Q ) //decrease ball radius
		{
			_pWorld->DestroyBody(enemy.GetPhysicsBody());
		}

		if ( gameEvent.key.code == Keyboard::E ) //explode
		{
		
			for ( int i = 0; i < bombs.size(); ++i)
				bombs[i].Explode( _textureBank["bombParticle"], *_pWorld );
		
		}

		if (gameEvent.key.code == Keyboard::Escape)
		{
			_rWindow.close();
		}

		//TODO: implement a BOMB with skull ball
	
	}
}