/*#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

int main()
{
	b2Vec2 gravity(0.0f, 10.0f);

	b2World myWorld(gravity);

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
*/
/*
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <cstdio>
 
#define PPM 30 // Pixel Per Meters
 
using namespace sf;
 
int main()
{
    bool running = true;
 
    RenderWindow app(VideoMode(800,600,32),"First Test",Style::Close);
 
    sf::CircleShape box(100.f);
	//,sf::Color::White);
    //Shape ground = sf::LineShape(50,550,750,200,1);//,sf::Color::Red);
 
 
    // set up the world
    b2Vec2 gravity(0.0f,-9.8f);
    b2World *myWorld = new b2World(gravity);
 
    // box body definition
    b2BodyDef boxBodyDef;
    b2Vec2 boxVelocity;
    boxVelocity.Set(0.0f,10.0f);
    boxBodyDef.type = b2_dynamicBody;
    boxBodyDef.position.Set(500,20);
    boxBodyDef.linearVelocity = boxVelocity;
 
    // line body definition
    b2BodyDef lineBodyDef;
    lineBodyDef.type = b2_staticBody;
    lineBodyDef.position.Set(50,550);
 
    // create the bodies
    b2Body *boxBody = myWorld->CreateBody(&boxBodyDef);
    b2Body *lineBody = myWorld->CreateBody(&lineBodyDef);
 
    // create the shapes
    b2PolygonShape boxShape,lineShape;
    boxShape.SetAsBox(50.0f/PPM,25.0f/PPM);
    //lineShape.SetAsEdge(b2Vec2(50/PPM,550/PPM),b2Vec2(750/PPM,200/PPM));
 
    // add fixtures
    b2FixtureDef boxFixtureDef,lineFixtureDef;
    boxFixtureDef.shape = &boxShape;
    lineFixtureDef.shape = &lineShape;
    boxFixtureDef.density = 1;
 
    boxBody->CreateFixture(&boxFixtureDef);
    lineBody->CreateFixture(&lineFixtureDef);
 
    float timeStep = 1.0f / 20.0f; // 20fps
 
    int velIter = 8;
    int posIter = 3;
 
    while(running)
    {
        Event event;
        while(app.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            running = false;
        }
 
        myWorld->Step(timeStep, velIter, posIter);
 
 
        b2Vec2 pos = boxBody->GetPosition();
        printf("%f %f\n",pos.x, pos.y);
 
 
        //box.SetPointPosition(0,pos.x, pos.y);
        //box.SetPointPosition(1,pos.x+100,pos.y);
        //box.SetPointPosition(2,pos.x+100,pos.y+50);
        //box.SetPointPosition(3,pos.x,pos.y+50);
 
 
        app.clear();
 
        app.draw(box);
        //app.draw(ground);
        app.display();
    }
 
    app.close();
    delete myWorld;
 
    return EXIT_SUCCESS;
}*/