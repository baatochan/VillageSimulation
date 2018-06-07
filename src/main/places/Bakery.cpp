//
// Created by black on 05.06.18.
//

#include "Bakery.hpp"

void Bakery::execute(Engine::Agent *agent)
{

}

void Bakery::registerYourself()
{
	Place::registerYourself();
}

Bakery::Bakery()
	: Place( { 100, 100 }, { 75, 85 } )
{
	getShape()->setFillColor(sf::Color( 160, 82, 45 ));
}
