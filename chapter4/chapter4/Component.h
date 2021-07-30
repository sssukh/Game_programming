// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include <cstdint>

class Component
{
public:
	
	Component(class Actor* owner, int updateOrder = 100);

	virtual ~Component();
	
	virtual void Update(float deltaTime);
	
	virtual void ProcessInput(const uint8_t* keyState) {}

	int GetUpdateOrder() const { return mUpdateOrder; }
protected:
	
	class Actor* mOwner;

	int mUpdateOrder;
};
