/**
 * Pure abstract class representing actions a game player is able to perform
 * @author: Dennis Zinzi (130301136)
 */
#pragma once

class InputPlayer{
	public:
		virtual void MoveLeft() = 0;
		virtual void MoveForward() = 0;
		virtual void MoveRight() = 0;
		virtual void MoveBackward() = 0;
		virtual void Jump() = 0;
		virtual void Shoot() = 0;
		virtual void NoMovement() = 0;
		virtual void ShowControls(bool show) = 0;
};