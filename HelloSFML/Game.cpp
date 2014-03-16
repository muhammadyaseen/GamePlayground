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
	
	while ( _rWindow.isOpen() )
	{
		Event e;

		_rWindow.pollEvent(e);

		if ( e.type == Event::Closed )
		{
			_rWindow.close();
		}
		
		HandleInput( e );

		//Time lastUpdateCall = timeElapsed.restart();

		if ( timeElapsed.getElapsedTime().asMilliseconds() >= 16 )
		{
			Update( e, timeElapsed.restart() );
		}
	
		Time lastDrawCall = /*lastUpdateCall +*/ timeElapsed.getElapsedTime(); //.restart();

		Draw( _rWindow, lastDrawCall );
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

	//set up joined platform
	
	Texture jointPlatformTexture;
	jointPlatformTexture.loadFromFile("Art\\Wood.png");
	textureBank.insert( pair<string, Texture>("jointWood", jointPlatformTexture) );

	Texture screw;
	screw.loadFromFile("Art\\Screw.png");
	textureBank.insert( pair<string, Texture>("screw", screw) );

	Texture wheelTexture;
	wheelTexture.loadFromFile("Art\\Wheel.png");
	textureBank.insert( pair<string, Texture>("wheel", wheelTexture) );

	for (int i = 0; i <= 3; i++) //5 wheels 
	{
		Wheel wheel( textureBank["wheel"], 250 + i*85, 600 );
		wheel.SetWorld( *_pWorld );
		wheels.push_back( wheel );
	}

	JointPlatform jointPlatform( textureBank["jointWood"], textureBank["screw"], 300,350,0 );
	jointPlatform.SetWorld( *_pWorld );
	jointPlatforms.push_back( jointPlatform );
	
	//load bomb! (not the one that KILLs people)
	Bomb explosive( textureBank["bomb"], 200, 550, 1000 );
	explosive.SetWorld( *_pWorld );
	bombs.push_back( explosive );

	//load ground

	StaticPlatform road( textureBank["floor"], 400, 750);
	road.SetWorld( *_pWorld );
	platforms.push_back( road );

	//create left and right walls

	//left wall
	StaticPlatform leftWall( textureBank["boundaryWall"], 0, 300);
	leftWall.SetWorld( *_pWorld );
	platforms.push_back( leftWall );

	//right wall
	StaticPlatform rightWall( textureBank["boundaryWall"], 780, 300);
	rightWall.SetWorld( *_pWorld );
	platforms.push_back( rightWall );

	//load spike platform
	StaticPlatform spike( textureBank["spikes"], 150, 150, 45);
	spike.SetWorld( *_pWorld );
	platforms.push_back( spike );


	//load balls
	Ball skullBall( textureBank["ball"], 250, 0);
	skullBall.SetWorld( *_pWorld );
	balls.push_back( skullBall );

	//load boxes
	Box crate( textureBank["box"], 100, 0);
	crate.SetWorld( *_pWorld );
	boxes.push_back( crate );


}

void Game::UnloadContent() 
{
	delete _pWorld;
}

void Game::Update(Event gameEvent, Time timeSinceLastUpdateCall ) 
{

	_pWorld->Step( timeStep, 8, 8);

	for ( int i = 0; i < balls.size(); ++i)
		balls[i].Update(gameEvent, timeSinceLastUpdateCall );

	for ( int i = 0; i < boxes.size(); ++i)
		boxes[i].Update(gameEvent, timeSinceLastUpdateCall );

	for ( int i = 0; i < platforms.size(); ++i)
		platforms[i].Update(gameEvent, timeSinceLastUpdateCall );

	for ( int i = 0; i < bombs.size(); ++i)
		bombs[i].Update( gameEvent, timeSinceLastUpdateCall );

	for ( int i = 0; i < jointPlatforms.size(); ++i)
		jointPlatforms[i].Update( gameEvent, timeSinceLastUpdateCall );

	for ( int i = 0; i < wheels.size(); ++i)
		wheels[i].Update( gameEvent, timeSinceLastUpdateCall );
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

	for ( int i = 0; i < jointPlatforms.size(); ++i)
		jointPlatforms[i].Draw( _rWindow, timeSinceLastDrawCall );

	for ( int i = 0; i < wheels.size(); ++i)
		wheels[i].Draw( _rWindow, timeSinceLastDrawCall );
	
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

			Box crate( textureBank["box"], mousePos.x, mousePos.y);
			crate.SetWorld( *_pWorld );
			boxes.push_back( crate );

		}

		if ( gameEvent.key.code == Keyboard::B ) //spawn ball
		{
			Vector2i mousePos = Mouse::getPosition( _rWindow );

			Ball ball( textureBank["ball"], mousePos.x, mousePos.y);
			ball.SetWorld( *_pWorld );
			balls.push_back( ball );

		}

		if ( gameEvent.key.code == Keyboard::C ) //increase ball radius
		{}

		if ( gameEvent.key.code == Keyboard::Q ) //decrease ball radius
		{}

		if ( gameEvent.key.code == Keyboard::E ) //explode
		{
		
			for ( int i = 0; i < bombs.size(); ++i)
				bombs[i].Explode( textureBank["bombParticle"], *_pWorld );
		
		}

		//TODO: implement a BOMB with skull ball
	
	}
}