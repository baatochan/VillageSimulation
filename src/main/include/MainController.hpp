//
// Created by black on 28.05.18.
//

#pragma once


#include <ScreenManager.hpp>

class MainController
{
protected:
	std::shared_ptr<msm::WindowStorage> windowStoragePtr_;

	void allocateStorage();
	void loadPlaces();
	void initialiseLogger();

public:
	void init();
	void close();

	const std::shared_ptr<MainScreenManager::WindowStorage>& getWindowStorage() const;
};

