/**
 * Abstract Base class for any object to be rendered on screen
 * @author: Dennis Zinzi (130301136)
 */
#pragma once

class RenderObject{
	public:
		RenderObject();

		//Make rendering happen in subclass
		virtual void Render() = 0;
};