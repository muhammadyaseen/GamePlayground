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

	curScr=new View(_rWindow.getDefaultView());
	
	while ( _rWindow.isOpen() )
	{
		_rWindow.pollEvent(e);

		if ( e.type == Event::Closed )
		{
			_rWindow.close();
		}
		
		HandleInput( e );

		//Time lastUpdateCall = timeElapsed.restart();

		if ( timeElapsed.getElapsedTime().asMilliseconds() >= 1 )
		{
			Update( e, oldEvent ,timeElapsed.restart() );
		}
	
		Time lastDrawCall = /*lastUpdateCall +*/ timeElapsed.getElapsedTime(); //.restart();

		Draw( _rWindow, lastDrawCall );
		
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
	textureBank.insert( pair<string, Texture>("floor", ground) );

	Texture boundaryWall;
	boundaryWall.loadFromFile("Art\\BoundaryWall.png");
	textureBank.insert( pair<string, Texture>("boundaryWall", boundaryWall) );


	Texture ball;
	ball.loadFromFile("Art\\Skull.png");
	textureBank.insert( pair<string, Texture>("ball", ball) );

	Texture box;
	box.loadFromFile("Art\\Crate.png");
	textureBank.insert( pair<string, Texture>("box", box) );

	Texture spikePlatform;
	spikePlatform.loadFromFile("Art\\Spikes.png");
	textureBank.insert( pair<string, Texture>("spikes", spikePlatform) );

	Texture bomb;
	bomb.loadFromFile("Art\\Bomb.png");
	textureBank.insert( pair<string, Texture>("bomb", bomb) );

	Texture bombParticle;
	bombParticle.loadFromFile("Art\\BombParticle.png");
	textureBank.insert( pair<string, Texture>("bombParticle", bombParticle) );

	Bomb explosive( textureBank["bomb"], 400, 550, 200 );
	explosive.SetWorld( *_pWorld );
	bombs.push_back( explosive );

	//load ground

	StaticPlatform road(textureBank["floor"], 400, 600,2);
	road.SetWorld( *_pWorld );
	platforms.push_back( road );

	//load roof

	StaticPlatform roof( textureBank["floor"], 400, 0,2);
	roof.SetWorld(*_pWorld);
	platforms.push_back(roof);

	//create left and right walls

	//left wall
	StaticPlatform leftWall( textureBank["boundaryWall"], 0, 200);
	leftWall.SetWorld( *_pWorld );
	platforms.push_back( leftWall );

	////right wall
	//StaticPlatform rightWall( textureBank["boundaryWall"], 780, 200);
	//rightWall.SetWorld( *_pWorld );
	//platforms.push_back( rightWall );

	//load spike platform
	StaticPlatform spike( textureBank["spikes"], 350, 200, 1, 1, 45);
	spike.SetWorld( *_pWorld );
	platforms.push_back( spike );


	//load balls
	Ball skullBall( textureBank["ball"], 650, 0);
	skullBall.SetWorld( *_pWorld );
	balls.push_back( skullBall );

	//load boxes
	Box crate( textureBank["box"], 300, 0);
	crate.SetWorld( *_pWorld );
	boxes.push_back( crate );

	//load characters
	Edward.LoadContent();
	Edward.SetWorld(*_pWorld);
	
}

void Game::UnloadContent() 
{
	delete _pWorld;
}

void Game::Update(Event gameEvent, Event previousGameEvent, Time timeSinceLastUpdateCall ) 
{

	_pWorld->Step(timeStep, 8, 8);

	Time frameTime = frameClock.restart();

	for ( int i = 0; i < balls.size(); ++i)
		balls[i].Update(gameEvent, timeSinceLastUpdateCall );

	for ( int i = 0; i < boxes.size(); ++i)
		boxes[i].Update(gameEvent, timeSinceLastUpdateCall );

	for ( int i = 0; i < platforms.size(); ++i)
		platforms[i].Update(gameEvent, timeSinceLastUpdateCall );

	for ( int i = 0; i < bombs.size(); ++i)
		bombs[i].Update( gameEvent, timeSinceLastUpdateCall );
	
	Edward.Update(gameEvent, previousGameEvent, timeSinceLastUpdateCall, frameTime);
}

void Game::Draw(RenderWindow& window, Time timeSinceLastDrawCall ) 
{
	_rWindow.clear( Color(255,255,255) );

	for ( int i = 0; i < balls.size(); ++i)
		balls[i].Draw(_rWindow, timeSinceLastDrawCall );


	for ( int i = 0; i < boxes.size(); ++i)
		boxes[i].Draw( _rWindow, timeSinceLastDrawCall );


	for ( int i = 0; i < platforms.size(); ++i)
		platforms[i].Draw( _rWindow, timeSinceLastDrawCall );

	for ( int i = 0; i < bombs.size(); ++i)
		bombs[i].Draw( _rWindow, timeSinceLastDrawCall );
	
	Edward.Draw(_rWindow, timeSinceLastDrawCall);
		
	//_pWorld->DrawDebugData();

	_rWindow.display();

}

void Game::HandleInput(Event gameEvent)
{
	if ( gameEvent.type == Event::KeyPressed )
	{
	
		
		if ( gameEvent.key.code == Keyboard::Right ) //spawn box
		{
			/*Vector2i mousePos = Mouse::getPosition( _rWindow );

			Box crate( textureBank["box"], mousePos.x, mousePos.y);
			crate.SetWorld( *_pWorld );
			boxes.push_back( crate );*/
			curScr->move(1,0);
			_rWindow.setView(*curScr);

		}

		if ( gameEvent.key.code == Keyboard::B ) //spawn ball
		{
			Vector2i mousePos = Mouse::getPosition( _rWindow );

			Ball ball( textureBank["ball"], mousePos.x, mousePos.y);
			ball.SetWorld( *_pWorld );
			balls.push_back( ball );

		}

		if ( gameEvent.key.code == Keyboard::X ) //increase ball radius
		{
			Bomb explosive( textureBank["bomb"], 400, 550, 200 );
			explosive.SetWorld( *_pWorld );
			bombs.push_back( explosive );
		}

		if ( gameEvent.key.code == Keyboard::Q ) //decrease ball radius
		{}

		if ( gameEvent.key.code == Keyboard::E ) //explode
		{
		
			for ( int i = 0; i < bombs.size(); ++i)
				bombs[i].Explode( textureBank["bombParticle"], *_pWorld );
		
		}

		if (gameEvent.key.code == Keyboard::Escape)
		{
			_rWindow.close();
		}

		//TODO: implement a BOMB with skull ball
	
	}
}