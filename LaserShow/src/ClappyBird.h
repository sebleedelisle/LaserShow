//
//  ClappyBird.h
//  LaserShow
//
//  Created by Seb Lee-Delisle on 18/03/2014.
//
//

#pragma once

#include "LaserManager.h"

class ClappyBird {

	public:
	
	ClappyBird() : laserManager(*LaserManager::instance()) {};

	LaserManager& laserManager;



};