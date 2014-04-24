#include "Level1.h"


Level1::Level1(RenderWindow& window, SFMLDebugDraw& debugDraw, b2World* World,Score* score) 
	:State(window,debugDraw,World),
	 pickupCoin(),
	 levelView(window.getView()),
	 hudView(),
	 score(score) 
{

	//hudView.setCenter(60, 40);//src  rect
	//hudView.setSize(200,200);
	////hudView.zoom(10);
	//hudView.setViewport(FloatRect(0,0,2,2)); // target rect - in ratio
	
	cameraCenter = levelView.getCenter().x;	  //_rWindow = window;
}

Level1::~Level1(void)
{
}

void Level1::LoadContent() 
{	
	
	Texture skull;
	skull.loadFromFile("Art\\Skull.png");
	textureBank.insert( pair<string, Texture>("skull", skull) );

	Texture ground;
	ground.loadFromFile("Art\\GroundBrownExtended.png");
	textureBank.insert( pair<string, Texture>("brownGround", ground) );

	Texture woodSpikes;
	woodSpikes.loadFromFile("Art\\WoodspikeUp2.png");
	textureBank.insert( pair<string, Texture>("woodSpikes", woodSpikes) );

	Texture woodSpikes2;
	woodSpikes2.loadFromFile("Art\\TwoSpikesWood.png");
	textureBank.insert( pair<string, Texture>("twospikes", woodSpikes2) );

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

	Texture SideWalls;
	SideWalls.loadFromFile("Art\\Wall.png");
	textureBank.insert(pair<string,Texture>("wall",SideWalls));


	/******************************************************
	* End loading textures , start initializing game objects
	*******************************************************/

	Ball ball(textureBank["skull"], 200, 40+7 );
	ball.SetWorld(*_pWorld);
	balls.push_back( ball ); //shown in hud

	SpreadPickupCoins();
	
	SpreadBrickPlatforms();

	SpreadTrees(); //Oh yes! we LOVE nature.


	
	//Boundary walls

	StaticPlatform Wall1(textureBank["wall"],0,350,100.0f,0);
	Wall1.SetWorld(*_pWorld);
	platforms.push_back(Wall1);

	StaticPlatform Wall2(textureBank["wall"],2300,350,100.0f,0);
	Wall2.SetWorld(*_pWorld);
	platforms.push_back(Wall2);





	//end wall



	//load the (cruel) spikey ball


	SwingSpikeBall spikeChain(textureBank["chainLink"], textureBank["spikeyBall"], 400, 160, 0);
	spikeChain.IamA( SPIKE_BALL )->ICollideWith( EDWARD );
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

	StaticPlatform spike( textureBank["twospikes"], 250, 100, 400.0f, 0.0f);
	spike.SetWorld( *_pWorld );
	spike.IamA(EntityType::SPIKE)->ICollideWith(EntityType::EDWARD|EntityType::ENEMIES);
	platforms.push_back( spike );
	


	StaticPlatform spike1( textureBank["woodSpikes"], 1000, 700-48-48-40);
	spike1.IamA(SPIKE)->ICollideWith(EDWARD|ENEMIES);
	spike1.SetWorld( *_pWorld );
	platforms.push_back( spike1 );

	StaticPlatform spike2( textureBank["twospikes"], 390, 700-25);//Under ground spikes
	spike2.IamA(SPIKE)->ICollideWith(EDWARD|ENEMIES);
	spike2.SetWorld( *_pWorld );
	platforms.push_back( spike2 );

	StaticPlatform spike3( textureBank["woodSpikes"], 630, 700-48-48-40);
	spike3.IamA(SPIKE)->ICollideWith(EDWARD|ENEMIES);
	spike3.SetWorld( *_pWorld );
	platforms.push_back( spike3 );



	//start second gray ladder
	//origin of next level = origin of lower level + 24 (only x coord)
	StaticPlatform ladder1( textureBank["grayStone"], 1075 + 200, 700-48-48-48, (int)5);
	ladder1.SetWorld( *_pWorld );
	platforms.push_back( ladder1 );

	StaticPlatform ladder2( textureBank["grayStone"], 1075 + 200, 700-48-48-48-48, (int)3);
	ladder2.SetWorld( *_pWorld );
	platforms.push_back( ladder2 );

	StaticPlatform ladder3( textureBank["grayStone"], 1075 + 200, 700-48-48-48-48-48, (int)1,0.35f);
	ladder3.SetWorld( *_pWorld );
	platforms.push_back( ladder3 );

	//end 2nd gray ladder

	//start gray wall
	
	StaticPlatform wall1( textureBank["grayStone"], 800, 24, (int)4);
	wall1.SetWorld( *_pWorld );
	platforms.push_back( wall1 );

	StaticPlatform wall2( textureBank["grayStone"], 800, 48+24, (int)4);
	wall2.SetWorld( *_pWorld );
	platforms.push_back( wall2 );

	StaticPlatform wall3( textureBank["grayStone"], 800, 96+24, (int)4);
	wall3.SetWorld( *_pWorld );
	platforms.push_back( wall3 );

	//end gray wall

	//start grassy ground

	StaticPlatform grassCover1( textureBank["grassGround"], 125, 700-48-48, 450.0f, 0);
	grassCover1.SetWorld( *_pWorld );
	platforms.push_back( grassCover1 );

	StaticPlatform grassCover2( textureBank["grassGround"], 600, 700-48-48, 350.0f, 0);
	grassCover2.SetWorld( *_pWorld );
	platforms.push_back( grassCover2 );

	StaticPlatform grassCover3( textureBank["grassGround"], 1100, 700-48-48);
	grassCover3.SetWorld( *_pWorld );
	platforms.push_back( grassCover3 );

	StaticPlatform grassCover4( textureBank["grassGround"], 1900, 700-48-48);
	grassCover4.SetWorld( *_pWorld );
	platforms.push_back( grassCover4 );


	
	//load ground

	StaticPlatform ground1( textureBank["brownGround"], 125, 700-48, 450.0f, 0); //width 250
	ground1.SetWorld( *_pWorld );
	platforms.push_back( ground1 );

	StaticPlatform ground3( textureBank["brownGround"], 600, 700-48, 350.0f, 0);
	ground3.SetWorld( *_pWorld );
	platforms.push_back( ground3 );

	//continued ground
	StaticPlatform ground2( textureBank["brownGround"], 1100, 700-48);
	ground2.SetWorld( *_pWorld );
	platforms.push_back( ground2 );

	StaticPlatform ground4( textureBank["brownGround"], 1900, 700-48);
	ground4.SetWorld( *_pWorld );
	platforms.push_back( ground4);

	//load characters
	Edward.LoadContent(100,500);
	Edward.IamA( EDWARD )->ICollideWith( HARMFUL_OBSTACLES | HARMFUL_OBSTACLES | ENEMIES );
	Edward.SetWorld(*_pWorld);
	
	//load enemy
	enemy.LoadContent(900,500);
	enemy.SetWorld(*_pWorld);
	

}

void Level1::UnloadContent() 
{
	for ( int i = 0; i < coins.size(); ++i)
	{
		delete coins[i];	
	}
}

State::LevelState Level1::Update(Event gameEvent, Event previousGameEvent, Time timeSinceLastUpdateCall ) 
{
	//_miniView.move(1,0);
	
	Time frameTime = frameClock.restart();

	//handles camera movement
		//-- keep edward at center of screen
	/*	
	if( MathHelper::ToPixel(Edward.GetPhysicsBody()->GetPosition().x) > _rWindow.getSize().x/2)
	{
		levelView.setCenter(sf::Vector2f(MathHelper::ToPixel(Edward.GetPhysicsBody()->GetPosition().x),levelView.getCenter().y));
	
		if( MathHelper::ToPixel(Edward.GetPhysicsBody()->GetPosition().x) > (2300-_rWindow.getSize().x/2))
		levelView.setCenter(sf::Vector2f(2300-_rWindow.getSize().x/2.f,_rWindow.getSize().y/2.f));
	}
	else
		levelView.setCenter(sf::Vector2f(_rWindow.getSize().x/2.f,_rWindow.getSize().y/2.f));
	*/
	

		levelView.setCenter(sf::Vector2f(
			//MathHelper::ToPixel(Edward.GetPhysicsBody()->GetPosition().x),
			cameraCenter,
			levelView.getCenter().y
		));

	//end camera movement
	if(MathHelper::ToPixel(Edward.GetPhysicsBody()->GetPosition().y)>750)
		Edward.Respawn(_pWorld,100,300);

	_pWorld->Step( timeStep, 8, 8);

	for ( int i = 0; i < platforms.size(); ++i)
		platforms[i].Update(gameEvent, timeSinceLastUpdateCall );

	for ( int i = 0; i < spikeChains.size(); ++i)
		spikeChains[i].Update( gameEvent, timeSinceLastUpdateCall );

	
	for ( int i = 0; i < coins.size(); ++i)
		coins[i]->Update( gameEvent, timeSinceLastUpdateCall );

	pickupCoin.Update( gameEvent, timeSinceLastUpdateCall );

	//pc2.Update( gameEvent, timeSinceLastUpdateCall );

	
	Edward.Update(gameEvent, previousGameEvent, timeSinceLastUpdateCall, frameTime);

	enemy.Update(gameEvent, Edward, timeSinceLastUpdateCall, frameTime);


	
	return LState;


}

void Level1::Draw(RenderWindow& window, Time timeSinceLastDrawCall ) 
{
	_rWindow.clear( Color(255,255,255) );

	_rWindow.setView( hudView );

	pickupCoin.Draw(_rWindow, timeSinceLastDrawCall );

	balls[0].Draw( _rWindow, timeSinceLastDrawCall );

	///draw HUD elements
		//todo: add code
	//end


	//draw the level

	_rWindow.setView( levelView );

	pickupCoin.Draw(_rWindow, timeSinceLastDrawCall );

	balls[0].Draw( _rWindow, timeSinceLastDrawCall );

	//_rWindow.draw(testSprite);

	for ( int i = 0; i < platforms.size(); ++i)
		platforms[i].Draw( _rWindow, timeSinceLastDrawCall );

	for ( int i = 0; i < spikeChains.size(); ++i)
		spikeChains[i].Draw( _rWindow, timeSinceLastDrawCall );

	for ( int i = 0; i < coins.size(); ++i)
		coins[i]->Draw( _rWindow, timeSinceLastDrawCall );

	pickupCoin.Draw(_rWindow, timeSinceLastDrawCall );
	
	//pc2.Draw(_rWindow, timeSinceLastDrawCall );

	Edward.Draw(_rWindow, timeSinceLastDrawCall);
	
	enemy.Draw(_rWindow, timeSinceLastDrawCall);
	
	//_pWorld->DrawDebugData();

	_rWindow.display();

}

void Level1::HandleInput(Event gameEvent)
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

void Level1::SpreadPickupCoins()
{
	vector<b2Vec2> locations;

	locations.push_back( b2Vec2(510, 700-48-48-48-48-50) );
	locations.push_back( b2Vec2(670, 700-48-48-48-48-48-48-50) );
	locations.push_back( b2Vec2(515, 700-48-48-48-48-48-48-48-48-50-15) );
	locations.push_back( b2Vec2(645, 700-48-48-48-48-48-48-48-48-48-48-50-40) );
	locations.push_back( b2Vec2(910, 700-48-48-48-48-48-48-48-48-50) );
	locations.push_back( b2Vec2(990, 700-48-48-48-48-48-48-48-48-50) );
	locations.push_back( b2Vec2(1105, 700-48-48-48-48-48-48-48-50-10) );
	locations.push_back( b2Vec2(1195, 700-48-48-48-48-48-48-48-50-10) );
	//locations.push_back( b2Vec2(810, 190) );
	//locations.push_back( b2Vec2(170, 280) );

	for ( int i = 0; i < locations.size(); ++i)
	{
		Coin* c = new Coin;
		c->Create(textureBank["coin"], locations[i].x, locations[i].y);
		c->IamA( COIN )->ICollideWith( EDWARD );
		coins.push_back(c);
	
	}
}

void Level1::SpreadBrickPlatforms()
{
	vector<b2Vec2> locations;
	locations.push_back( b2Vec2(550 , 700-48-48-48-40) );
	locations.push_back( b2Vec2(630, 700-48-48-48-48-48-40) );
	locations.push_back( b2Vec2(560, 700-48-48-48-48-48-48-48-48-15) );
	locations.push_back( b2Vec2(700 , 700-48-48-48-48-48-48-48-48-48-48-40) );
	
	locations.push_back( b2Vec2(950, 700-48-48-48-48-48-48-48-48) );
	
	locations.push_back( b2Vec2(1145, 700-48-48-48-48-48-48-48-10) );
	//locations.push_back( b2Vec2(1075 + 450, 700-48-48-48-48-48-48-48-48) );

	for ( int i = 0; i < locations.size(); ++i)
	{
		StaticPlatform brickPlatform(textureBank["brickStone"], locations[i].x, locations[i].y, (int)4, 0.35f);
		
		brickPlatform.IamA( BRICK_PLATFORM )->ICollideWith( RANGER | EDWARD );
		brickPlatform.SetWorld(*_pWorld);
		
		platforms.push_back( brickPlatform );
	
	}
}

void Level1::SpreadTrees()
{
	vector<b2Vec2> locations;

	locations.push_back( b2Vec2(875 , 700-48-48-48) );
	locations.push_back( b2Vec2(1075 , 700-48-48-48) );
	locations.push_back( b2Vec2(850, 700-48-48-48) );
	locations.push_back( b2Vec2(650+150, 700-48-48-48) );
	locations.push_back( b2Vec2(600+150+120, 700-48-48-48) );
	locations.push_back( b2Vec2(1300, 700-48-48-48) );
	locations.push_back( b2Vec2(1300, 700-48-48-48) );
	locations.push_back( b2Vec2(1400, 700-48-48-48) );
	locations.push_back( b2Vec2(1600, 700-48-48-48) );
	locations.push_back( b2Vec2(2000, 700-48-48-48) );
	locations.push_back( b2Vec2(100, 700-48-48-48) );
	locations.push_back( b2Vec2(1350, 700-48-48-48) );
	//locations.push_back( b2Vec2(805, 70) );
	//locations.push_back( b2Vec2(805, 70) );


	for ( int i = 0; i < locations.size(); ++i)
	{
		StaticPlatform tree(textureBank["treeTexture"], locations[i].x, locations[i].y, 1);
		tree.IamA( TREE )->ICollideWith( UNKNOWN );
		tree.SetWorld(*_pWorld);
		
		platforms.push_back( tree );
	}

	
}