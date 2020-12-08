#include <iostream>

#include "Scene/Scene.h"

int main()
{
	Scene scene;
	scene.render();
	return 0;
};


// TODO: list
/*
	3. Create a shader to render the object, the shader consists of a vertex and a
		fragment program.
			a. Vertex shader: Applies MVP transformation on the vertex and passes it
				with the texture coordinates to the fragment shader.
			b. Fragment shader: To illuminate the scene you are going to use a
				directional light source. A directional light is used to simulate the sun and
				has only a direction vector. Using this light source implement the phong
				illumination model. The shader should receive the vertex position and
				texture coordinates from the vertex shader. It should also get the
				lighting parameters and a sampler for the water diffuse texture via
				uniform variables. This texture should be used in the diffuse term to
				specify the color of the fragment.
*/