
#pragma once

class  IRenderable
{
public:
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual ~IRenderable() { }
};