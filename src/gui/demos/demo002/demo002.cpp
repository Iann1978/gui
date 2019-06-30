#include "prebuild.h"


#include <list>


#include <common/common_shader.hpp>
#include <common/texture.hpp>
#include <common/text2D.hpp>

#include <Engine/Renderable.h>
#include <Engine/Time.h>
#include <Engine/Input.h>
#include <Engine/Screen.h>
#include <Engine/Shader.h>
#include <Engine/Image.h>
#include <Engine/Text.h>
#include <Engine/Cube.h>
#include <Engine/Curve.h>
#include <Engine/Point.h>
#include <Engine/Engine.h>


#include <StatusBar.h>


#pragma warning (disable: 4996)


int main(void)
{
	Engine engine;

	//CreateGeo(engine.geolist);
	//CreateUI(engine.uilist);
	//CreateTechFeel001(engine.uilist);

	engine.Run();

	//DestroyGeo(engine.geolist);
	//DestroyUI(engine.uilist);


	return 0;
}

