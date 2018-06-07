//
// Created by black on 06.06.18.
//

#pragma once


#include <Place.hpp>
#include <condition_variable>
#include <list>

class Rally
		: public eng::Place
{
	std::list<eng::Envelope> offerList_;
protected:
	std::condition_variable offerSubscription_;
	std::mutex offerMutex_;

public:
	Rally();

	void printOffers();
	void addOffer(eng::Envelope envelope);

	std::list<Engine::Envelope> const& getOfferList() const;

	void execute(Engine::Agent *agent) override;
	std::string getName() const override;
};

