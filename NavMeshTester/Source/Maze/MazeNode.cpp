#include "Maze\MazeNode.h"

MazeNode::MazeNode()
	: m_Position(0.f, 0.f), m_Type(mNodeType::Default), m_Spawns(mSpawnType::None)
{

}

void MazeNode::Position(const Vector2& a_Position)
{
	m_Position = a_Position;
}

void MazeNode::Type(mNodeType a_Type)
{
	m_Type = a_Type;

	if (m_Type != mNodeType::Spawn)
	{
		m_Spawns = mSpawnType::None;
	}
}

void MazeNode::Spawns(mSpawnType a_Spawns)
{
	m_Spawns = a_Spawns;
}

const Vector2& MazeNode::Position() const
{
	return m_Position;
}

mNodeType MazeNode::Type() const
{
	return m_Type;
}

mSpawnType MazeNode::Spawns() const
{
	return m_Spawns;
}

bool MazeNode::operator==(const MazeNode& rhs) const
{
	return (m_Position == rhs.m_Position);
}

bool MazeNode::operator==(const Vector2& rhs) const
{
	return (m_Position == rhs);
}

bool MazeNode::operator==(const mNodeType& rhs) const
{
	return (m_Type == rhs);
}