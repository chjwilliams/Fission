#pragma once

#define STATE_NULL	0
#define STATE_MENU	1
#define STATE_HELP	2
#define STATE_GAME	3
#define GAME_OVER	4

class GameState
{
private:
	static unsigned int m_Current;
	static bool m_GameOver;
public:
	inline static void setGameState(unsigned int state) { m_Current = state; }
	inline static unsigned int getGameState() { return m_Current; }

	inline static bool isGame() { return m_Current == STATE_GAME; }
	inline static bool isHelp() { return m_Current == STATE_HELP; }
	inline static bool isMenu() { return m_Current == STATE_MENU; }

	inline static void setGameOver(bool gameover) { m_GameOver = gameover; }
	inline static bool isGameOver() { return m_GameOver; }
};