//
// Created by black on 28.05.18.
//

#pragma once


#include <ScreenManager.hpp>

class MainController
{
	static MainController* instance_;
protected:
	std::condition_variable      var;
	std::mutex                   mutex;
	std::unique_lock<std::mutex> scopedLock{mutex};

	std::vector<std::shared_ptr<eng::Place>> places_;
	std::vector<std::shared_ptr<eng::Agent>> agents_;
	std::shared_ptr<msm::WindowStorage>      windowStoragePtr_;

	void allocateStorage();
	void loadPlaces();
	void initialiseLogger();

public:
	void init();
	void stop();
	void close();

	static MainController& getInstance();

	const std::shared_ptr<MainScreenManager::WindowStorage>& getWindowStorage() const;
};

