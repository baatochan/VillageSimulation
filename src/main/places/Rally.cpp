//
// Created by black on 06.06.18.
//

#include <spdlog/spdlog.h>
#include "Rally.hpp"

std::string Rally::getName() const
{
	return {"Rally Point"};
}

Rally::Rally()
		: Place( { 35, 35 }, { 400,200 } )
{
	getShape()->setFillColor(sf::Color::Blue);
}

void Rally::execute(Engine::Agent *agent)
{
	std::unique_lock<std::mutex> uniqueLock(offerMutex_);

	if ( offerList_.empty() )
	{
		spdlog::get("main")->debug(
				"There was no work offers for {}."
				, agent->getName()
		);
		offerSubscription_.wait_for(uniqueLock, std::chrono::seconds(10) , [&](){
			return !offerList_.empty();
		});
		if ( offerList_.empty() )
			return;
	}

	spdlog::get("main")->debug(
			"There was work for {}."
			, agent->getName()
	);

	eng::Envelope envelope = eng::Envelope{ offerList_.front().target, offerList_.front().message };
	agent->setOrder(envelope);

	spdlog::get("main")->debug(
			"{} moved to work at {}."
			, agent->getName()
			, envelope.target->getName()
	);

	offerList_.front().amount--;
	if ( offerList_.front().amount == 0 )
		offerList_.pop_front();

	offerSubscription_.notify_one();
}

void Rally::addOffer(eng::Envelope envelope)
{
	std::unique_lock<std::mutex> uniqueLock(offerMutex_);

	offerList_.push_back(envelope);
	offerSubscription_.notify_all();
}
