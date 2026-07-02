#include "stdafx.h"
#include "Game.h"

Game::Game()
{
	Reset();
}

void Game::Reset()
{
	Console::SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	Console::CursorVisible(false);
	paddle.width = 12;
	paddle.height = 2;
	paddle.x_position = 32;
	paddle.y_position = 30;

	ball.visage = 'O';
	ball.color = ConsoleColor::Cyan;
	ResetBall();

	// TODO #2 - Add this brick and 4 more bricks to the vector

	// Create 5 bricks
	bricks.clear(); // Make sure the vector is cleared when resetted
	bricks.reserve(5); // Reserve 5 slots for 5 bricks

	const int brickCount = 5;

	// Brick dimension
	const int brickH = 2;
	const int brickW = 10;

	// Single row
	const int rowY = 5;

	int windowWidth = Console::WindowWidth();

	// Bricks' width
	int totalBricksWidth = brickCount * brickW;

	// Window's remaining space
	int remainingSpace = windowWidth - totalBricksWidth;

	// Even spacing - divide remainin space by the count of bricks
	float spacing = static_cast<float>(remainingSpace) / (brickCount +1);

	for (int i = 0; i < brickCount; i++) {
		Box brick;
		brick.width = 10;
		brick.height = 2;

		// evenly space the bricks' x position
		brick.x_position = static_cast<int>(spacing + i * (brickW + spacing));

		// All bricks has the same y position
		brick.y_position = rowY;

		brick.doubleThick = true;
		brick.color = ConsoleColor::DarkGreen;	

		// Add current brick to vector
		bricks.push_back(brick);
	}
	
}

void Game::ResetBall()
{
	ball.x_position = paddle.x_position + paddle.width / 2;
	ball.y_position = paddle.y_position - 1;
	ball.x_velocity = rand() % 2 ? 1 : -1;
	ball.y_velocity = -1;
	ball.moving = false;
}

bool Game::Update()
{
	if (GetAsyncKeyState(VK_ESCAPE) & 0x1)
		return false;

	if (GetAsyncKeyState(VK_RIGHT) && paddle.x_position < WINDOW_WIDTH - paddle.width)
		paddle.x_position += 2;

	if (GetAsyncKeyState(VK_LEFT) && paddle.x_position > 0)
		paddle.x_position -= 2;

	if (GetAsyncKeyState(VK_SPACE) & 0x1)
		ball.moving = !ball.moving;

	if (GetAsyncKeyState('R') & 0x1)
		Reset();

	ball.Update();
	CheckCollision();
	return true;
}

//  All rendering, including text, should occur in the Render function
void Game::Render() const
{
	Console::Lock(true);
	Console::Clear();
	
	paddle.Draw();
	ball.Draw();

	// TODO #3 - Update render to render all bricks
	// Render all the bricks in the vector
	for (const Box& brick : bricks) {
		brick.Draw();
	}
	
	Console::Lock(false);
}

void Game::CheckCollision()
{
	// TODO #4 - Update collision to check all bricks
	if (brick.Contains(ball.x_position + ball.x_velocity, ball.y_position + ball.y_velocity))
	{
		brick.color = ConsoleColor(brick.color - 1);
		ball.y_velocity *= -1;

		// TODO #5 - If the ball hits the same brick 3 times (color == black), remove it from the vector

	}

	// TODO #6 - If no bricks remain, pause ball and display (render) victory text with R to reset


	if (paddle.Contains(ball.x_position + ball.x_velocity, ball.y_velocity + ball.y_position))
	{
		ball.y_velocity *= -1;
	}

	// TODO #7 - If ball touches bottom of window, pause ball and display (render) defeat text with R to reset
}
