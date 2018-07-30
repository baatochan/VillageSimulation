//
// Created by black on 05.06.18.
//

#pragma once


#include <Place.hpp>
#include <condition_variable>

class Well
		: public eng::Place
{
protected:
	Rally* rally_;

	std::condition_variable partnerHolder_;

	std::pair<eng::Agent*, eng::Agent*> wellers_;
	int amountOfWellers_{0}; //NOLINT

	const int desiredBuckets_{30};
	int readyBuckets_{0};
	std::chrono::milliseconds pullTime{100};

	std::mutex wellerMutex_;
	std::mutex bucketMutex_;

public:
	Well();

	void useWell(eng::Agent* agent);
	void transport(eng::Agent* agent);

	void registerYourself() override;
	std::string getName() const override;
	void execute(Engine::Agent *agent) override;
};

