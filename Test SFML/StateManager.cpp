#include "StateManager.h"

StateManager::StateManager()
{

}

bool StateManager::m_add = false;
bool StateManager::m_remove = false;
bool StateManager::m_replace = false;
std::stack<std::unique_ptr<GameState>> StateManager::m_StateStack;
std::unique_ptr<GameState> StateManager::m_NewState;

void StateManager::AddState(std::unique_ptr<GameState> NewState, bool ReplaceState)
{
	m_add = true;
	m_NewState = std::move(NewState);

	m_replace = ReplaceState;
}

void StateManager::RemoveState()
{
	m_remove = true;
}

void StateManager::ProcessChanges()
{
	// Remove state
	if (m_remove && !m_StateStack.empty())
	{
		m_StateStack.pop();
		if (!m_StateStack.empty())
		{
			m_StateStack.top()->Start();
		}
	}
	m_remove = false;
	// Add state
	if (m_add)
	{
		if (m_replace && !m_StateStack.empty())
		{
			m_StateStack.pop();
		}
		if (!m_StateStack.empty())
		{
			m_StateStack.top()->Pause();
		}
		m_StateStack.push(std::move(m_NewState));
	}
	m_add = false;
}

std::unique_ptr<GameState> &StateManager::GetTopState()
{
	return m_StateStack.top();
}

bool StateManager::Empty()
{
	if (m_StateStack.empty())
	{
		return true;
	}
	else
	{
		return false;
	}
}

int StateManager::GetSize()
{
	return StateManager::m_StateStack.size();
}