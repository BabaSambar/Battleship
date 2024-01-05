#pragma once
#include <stack>
#include <memory>

#include "GameState.h"
#include "MainMenuState.h"
#include "GameOngoingState.h"
#include "GameOverState.h"

class StateManager
{
public:
	StateManager();
	// Add state to state stack
	static void AddState(std::unique_ptr<GameState> NewState, bool ReplaceState = true);
	// Remove state from top of state stack
	static void RemoveState();
	// Process all changes of statemanager
	static void ProcessChanges();
	// Return top state
	static std::unique_ptr<GameState> &GetTopState();

	// Return if statestack is empty
	static bool Empty();
	// Return size of statestack
	static int GetSize();

private:
	static std::stack<std::unique_ptr<GameState>> m_StateStack;
	static std::unique_ptr<GameState> m_NewState;
	static bool m_add, m_replace, m_remove;
};

