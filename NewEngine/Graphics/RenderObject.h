#pragma once

class RenderObject{
	public:
		RenderObject();

		//Make rendering happen in subclass
		virtual void Render() = 0;
};