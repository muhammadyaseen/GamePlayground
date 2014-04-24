#include "Game.h"

// @see : http://stackoverflow.com/questions/10647448/why-constant-data-member-of-a-class-need-to-be-initialized-at-the-constructor
Game::Game(RenderWindow& window, SFMLDebugDraw& debugDraw)//, CollisionListener& listener) 
	: timeStep( 1.0f / 60.0f ),
	 _rWindow(window), 
	 _rSfmlDebugDraw(debugDraw),
	 pickupCoin(),
	 levelView(window.getDefaultView()),
	 hudView(),
	 gameEventListener()
{

	hudView.setCenter(38, 38);//src  rect
	hudView.setSize( 70,64);
	//hudView.zoom(10);
	hudView.setViewport(FloatRect(0,0,.075,.1)); // target rect - in ratio

	cameraCenter = levelView.getCenter().x;	  //_rWindow = window;
}

bool Game::Run() 
{
	Initialize();
	
	LoadContent();

	Clock timeElapsed;
	
	while ( _rWindow.isOpen() )
	{

		_rWindow.pollEvent(e);

		if ( e.type == Event::Closed )
		{
			_rWindow.close();
			UnloadContent();
			break;
		}
		
		HandleInput( e );

		//Time lastUpdateCall = timeElapsed.restart();

		if ( timeElapsed.getElapsedTime().asMilliseconds() >= 16 )
		{
			Update( e, oldEvent, timeElapsed.restart() );
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

	//set this objekt as Listener of box2d's collision events
	_pWorld->SetContactListener( &gameEventListener );


}


void Game::LoadContent() 
{	
	Texture skull;
	skull.loadFromFile("Art\\Skull.png");
	textureBank.insert( pair<string, Texture>("skull", skull) );

	Texture ground;
	ground.loadFromFile("Art\\GroundBrownExtended.png");
	textureBank.insert( pair<string, Texture>("brownGround", ground) );

	Texture woodSpikes;
	woodSpikes.loadFromFile("Art\\TwoSpikesWood.png");
	textureBank.insert( pair<string, Texture>("woodSpikes", woodSpikes) );

	Texture grassGround;
	grassGround.loadFromFile("Art\\GrassGroundExtended.png");
	textureBank.insert( pair<string, Texture>("grassGround", grassGround) );

	Texture boundaryWall;
	boundaryWall.loadFromFile("Art\\BoundaryWall.png");
	textureBank.insert( pair<string, Texture>("boundaryWall", boundaryWall) );

	Texture grayStone;
	grayStone.loadFromFile("Art\\PlatformStone.png");
	grayStone.setRepeated(true);
	textureBank.insert( pair<string, Texture>("grayStone", grayStone) );

	Texture treeTexture;
	treeTexture.loadFromFile("Art\\Tree.png");
	treeTexture.setRepeated(true); //if we want to have a 'bunch' of trees
	textureBank.insert( pair<string, Texture>("treeTexture", treeTexture) );

	Texture brickStone;
	brickStone.loadFromFile("Art\\BrickSmall.png");
	brickStone.setRepeated(true);
	textureBank.insert( pair<string, Texture>("brickStone", brickStone) );

	//textures for spike ball chains
	Texture chainTexture;
	chainTexture.loadFromFile("Art\\ChainLinkShortGrey.png");
	textureBank.insert( pair<string, Texture>("chainLink", chainTexture) );

	Texture spikeyBallTexture;
	spikeyBallTexture.loadFromFile("Art\\SpikeBallResized.png");
	textureBank.insert( pair<string, Texture>("spikeyBall", spikeyBallTexture) );

	Texture coinTexture;
	coinTexture.loadFromFile("Art\\coin.png");
	textureBank.insert( pair<string, Texture>("coin", coinTexture) );

	pickupCoin.Create(textureBank["coin"], 20, 40 ); //shown in HUD

	//StaticPlatform ball(textureBank["skull"], 50, 40+30 );
	//ball.SetWorld(*_pWorld);
	//platforms.push_back( ball ); //shown in hud

	SpreadPickupCoins();
	
	SpreadBrickPlatforms();

	SpreadTrees(); //Oh yes! we LOVE nature.

	//load the (cruel) spikey ball

	SwingSpikeBall spikeChain(textureBank["chainLink"], textureBank["spikeyBall"], 400, 150, 0);
	spikeChain.SetWorld( *_pWorld );
	spikeChains.push_back(spikeChain);

	//start first gray ladder
	//origin of next level = origin of lower level + 24 (only x coord)
	StaticPlatform platform( textureBank["grayStone"], 200, 700-48-48-48, (int)4);
	platform.SetWorld( *_pWorld );
	platforms.push_back( platform );

	StaticPlatform l2( textureBank["grayStone"], 200+24, 700-48-48-48-48, (int)3);
	l2.SetWorld( *_pWorld );
	platforms.push_back( l2 );

	StaticPlatform l3( textureBank["grayStone"], 200+24+24, 700-48-48-48-48-48, (int)2);
	l3.SetWorld( *_pWorld );
	platforms.push_back( l3 );

	//end gray ladder

	StaticPlatform spike( textureBank["woodSpikes"], 250, 100, 400, 0.0f);
	spike.SetWorld( *_pWorld );
	platforms.push_back( spike );

	//start second gray ladder
	//origin of next level = origin of lower level + 24 (only x coord)
	StaticPlatform ladder1( textureBank["grayStone"], 1075 + 200, 700-48-48-48, (int)4);
	ladder1.SetWorld( *_pWorld );
	platforms.push_back( ladder1 );

	StaticPlatform ladder2( textureBank["grayStone"], 1075 + 200, 700-48-48-48-48, (int)3);
	ladder2.SetWorld( *_pWorld );
	platforms.push_back( ladder2 );

	StaticPlatform ladder3( textureBank["grayStone"], 1075 + 200, 700-48-48-48-48-48, (int)2);
	ladder3.SetWorld( *_pWorld );
	platforms.push_back( ladder3 );

	//end 2nd gray ladder

	//start gray wall
	
	StaticPlatform wall1( textureBank["grayStone"], 700, 24, (int)4);
	wall1.SetWorld( *_pWorld );
	platforms.push_back( wall1 );

	StaticPlatform wall2( textureBank["grayStone"], 700, 48+24, (int)4);
	wall2.SetWorld( *_pWorld );
	platforms.push_back( wall2 );

	StaticPlatform wall3( textureBank["grayStone"], 700, 96+24, (int)4);
	wall3.SetWorld( *_pWorld );
	platforms.push_back( wall3 );

	//end gray wall

	//start grassy ground
	/*StaticPlatform grassCover( textureBank["grassGround"], 400, 700-48-48);
	grassCover.SetWorld( *_pWorld );
	platforms.push_back( grassCover );*/

	StaticPlatform grassCover( textureBank["grassGround"], 125, 700-48-48, 450, 0);
	grassCover.SetWorld( *_pWorld );
	platforms.push_back( grassCover );

	StaticPlatform grassCover2( textureBank["grassGround"], 625, 700-48-48, 350, 0);
	grassCover2.SetWorld( *_pWorld );
	platforms.push_back( grassCover2 );

	StaticPlatform grassCoverCtd( textureBank["grassGround"], 1200, 700-48-48);
	grassCoverCtd.SetWorld( *_pWorld );
	platforms.push_back( grassCoverCtd );

	
	//load ground

	/*StaticPlatform ground1( textureBank["brownGround"], 400, 700-48);
	ground1.SetWorld( *_pWorld );
	platforms.push_back( ground1 );
*/

	StaticPlatform ground1( textureBank["brownGround"], 125, 700-48, 450, 0); //width 250
	ground1.SetWorld( *_pWorld );
	platforms.push_back( ground1 );

	StaticPlatform ground3( textureBank["brownGround"], 625, 700-48, 350, 0);
	ground3.SetWorld( *_pWorld );
	platforms.push_back( ground3 );

	//continued ground
	StaticPlatform ground2( textureBank["brownGround"], 1200, 700-48);
	ground2.SetWorld( *_pWorld );
	platforms.push_back( ground2 );

	//create left and right walls

	//left wall
	//StaticPlatform leftWall( textureBank["boundaryWall"], 0, 300);
	//leftWall.SetWorld( *_pWorld );
	//platforms.push_back( leftWall );


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

	for ( int i = 0; i < coins.size(); ++i)
	{
		delete coins[i];	
	}
}

void Game::Update(Event gameEvent, Event previousGameEvent, Time timeSinceLastUpdateCall ) 
{
	//_miniView.move(1,0);
	Time frameTime = frameClock.restart();

	//handles camera movement
		//-- keep edward at center of screen
		
	//if( MathHelper::ToPixel(Edward.GetPhysicsBody()->GetPosition().x) < _rWindow.getSize().x/2)
	//	levelView.setCenter(sf::Vector2f(_rWindow.getSize().x/2,levelView.getCenter().y));
	//else
		levelView.setCenter(sf::Vector2f(
			//MathHelper::ToPixel(Edward.GetPhysicsBody()->GetPosition().x),
			cameraCenter,
			levelView.getCenter().y
		));

	//end camera movement

	_pWorld->Step( timeStep, 8, 8);

	for ( int i = 0; i < platforms.size(); ++i)
		platforms[i].Update(gameEvent, timeSinceLastUpdateCall );

	for ( int i = 0; i < spikeChains.size(); ++i)
		spikeChains[i].Update( gameEvent, timeSinceLastUpdateCall );

	
	for ( int i = 0; i < coins.size(); ++i)
		coins[i]->Update( gameEvent, timeSinceLastUpdateCall );

	pickupCoin.Update( gameEvent, timeSinceLastUpdateCall );
	//balls[0].Update( gameEvent, timeSinceLastUpdateCall );

	//pc2.Update( gameEvent, timeSinceLastUpdateCall );

	
	Edward.Update(gameEvent, previousGameEvent, timeSinceLastUpdateCall, frameTime);

	enemy.Update(gameEvent, Edward, timeSinceLastUpdateCall, frameTime);


}

void Game::Draw(RenderWindow& window, Time timeSinceLastDrawCall ) 
{
	_rWindow.clear( Color(255,255,255) );

	_rWindow.setView( hudView );

	pickupCoin.Draw(_rWindow, timeSinceLastDrawCall );

	//balls[0].Draw( _rWindow, timeSinceLastDrawCall );

	///draw HUD elements
		//todo: add code
	//end


	//draw the level

	_rWindow.setView( levelView );

	//pickupCoin.Draw(_rWindow, timeSinceLastDrawCall );

	//_rWindow.draw(testSprite);

	for ( int i = 0; i < platforms.size(); ++i)
		platforms[i].Draw( _rWindow, timeSinceLastDrawCall );

	for ( int i = 0; i < spikeChains.size(); ++i)
		spikeChains[i].Draw( _rWindow, timeSinceLastDrawCall );

	for ( int i = 0; i < coins.size(); ++i)
		coins[i]->Draw( _rWindow, timeSinceLastDrawCall );

	//pickupCoin.Draw(_rWindow, timeSinceLastDrawCall );
	
	//pc2.Draw(_rWindow, timeSinceLastDrawCall );

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


		}

		if ( gameEvent.key.code == Keyboard::A ) //spawn box
		{
			cameraCenter -= 10;
		}

		if ( gameEvent.key.code == Keyboard::S ) //spawn box
		{
			cameraCenter += 10;
		}

		if ( gameEvent.key.code == Keyboard::B ) //spawn ball
		{
			Vector2i mousePos = Mouse::getPosition( _rWindow );


		}

		if ( gameEvent.key.code == Keyboard::C ) //increase ball radius
		{}

		if ( gameEvent.key.code == Keyboard::Q ) //decrease ball radius
		{}

		if ( gameEvent.key.code == Keyboard::E ) //explode
		{
		
		}
	
	}
}

void Game::SpreadPickupCoins()
{
	vector<b2Vec2> locations;

	locations.push_back( b2Vec2(10, 400) );
	locations.push_back( b2Vec2(600, 300) );
	locations.push_back( b2Vec2(340, 220) );
	locations.push_back( b2Vec2(910, 120) );
	locations.push_back( b2Vec2(610, 70) );
	locations.push_back( b2Vec2(510, 40) );
	locations.push_back( b2Vec2(810, 190) );
	locations.push_back( b2Vec2(170, 280) );

	for ( int i = 0; i < locations.size(); ++i)
	{
		Coin* c = new Coin;
		c->Create(textureBank["coin"], locations[i].x, locations[i].y);
		coins.push_back(c);
	
	}
}

void Game::SpreadBrickPlatforms()
{
	vector<b2Vec2> locations;

	locations.push_back( b2Vec2(875 , 270) );
	locations.push_back( b2Vec2(1075 , 220) );
	locations.push_back( b2Vec2(850, 400) );
	locations.push_back( b2Vec2(650, 500) );
	locations.push_back( b2Vec2(600, 300) );
	//after 2nd ladder
	locations.push_back( b2Vec2(1075 + 650, 700-48-48-48-48-48-48-48) );
	locations.push_back( b2Vec2(1075 + 450, 700-48-48-48-48-48-48-48-48) );

	for ( int i = 0; i < locations.size(); ++i)
	{
		StaticPlatform brickPlatform(textureBank["brickStone"], locations[i].x, locations[i].y, (int)4);
		brickPlatform.SetWorld(*_pWorld);
		brickPlatform.setEntityType(BRICK_PLATFORM);
		platforms.push_back( brickPlatform );
	
	}
}

void Game::SpreadTrees()
{
	vector<b2Vec2> locations;

	locations.push_back( b2Vec2(875 , 270-40) );
	locations.push_back( b2Vec2(1075 , 220-40) );
	locations.push_back( b2Vec2(850, 400-40) );
	locations.push_back( b2Vec2(650+150, 700-48-48-48-24) );
	locations.push_back( b2Vec2(600+150+120, 700-48-48-48-24) );
	//locations.push_back( b2Vec2(805, 70) );
	//locations.push_back( b2Vec2(805, 70) );


	for ( int i = 0; i < locations.size() - 4; ++i)
	{
		StaticPlatform tree(textureBank["treeTexture"], locations[i].x, locations[i].y, 2);
		tree.SetWorld(*_pWorld);
		tree.setEntityType(TREE);
		platforms.push_back( tree );

	}

	for ( int i = locations.size() - 4; i < locations.size(); ++i)
	{
		StaticPlatform tree(textureBank["treeTexture"], locations[i].x, locations[i].y, 1);
		tree.SetWorld(*_pWorld);
		tree.setEntityType(TREE);
		platforms.push_back( tree );
	}
}