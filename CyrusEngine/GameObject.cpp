#include "GameObject.h"

GameObject::GameObject() : m_position(0, 0), m_velocity(0, 0), m_acceleration(0, 0)
, m_width(0), m_height(0), m_currentRow(0), m_currentFrame(0), m_numFrames(0)
, m_bUpdating(false), m_bDead(false), m_bDying(false), m_angle(0), m_alpha(255)
{
}

GameObject::~GameObject()
{
}
