// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "Component.h"
#include <unordered_map>
#include <string>

class AIComponent : public Component
{
public:
	AIComponent(class Actor* owner);
	
	void Update(float deltaTime) override;
	void ChangeState(const std::string& name);
	
	// �� ���¸� �ʿ� �߰��Ѵ�.
	void RegisterState(class AIState* state);
private:
	// ������ �̸��� AIState �ν��Ͻ��� �����Ѵ�
	std::unordered_map<std::string, class AIState*> mStateMap;
	// AI�� ���� ����
	class AIState* mCurrentState;
};
