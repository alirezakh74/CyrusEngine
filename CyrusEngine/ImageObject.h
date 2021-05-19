#pragma once

#include "ShooterObject.h"
#include "GameObjectFactory.h"

class ImageObject : public ShooterObject
{
public:
	ImageObject();
	~ImageObject();

	virtual void load(std::unique_ptr<LoaderParams> const &pParams) override;
	virtual void update() override;
	virtual void draw() override;
	virtual void clean() override;

private:
	static const int m_speed = 5;
	bool m_bRightMoving;
	int m_r;
	int m_g;
	int m_b;
	int m_a;
};

class ImageCreator : public BaseCreator
{
	virtual GameObject* createGameObject() const override
	{
		return new ImageObject();
	}
};

