// Grass_Geometry.shader
#version 330 core
layout(points) in;
layout(triangles, max_vertices = 3) out;

in vec3 Frag
uniform sampler2D grassDistribution;

void generate_grass_obj(vec4 position, float size)
{
  // generates a plane that holds the grass texture
  vec3 center = vec3(position.x, position.z, position.y);
  float deltaX = size / 2;
  float deltaY = size;

  gl_Position = position + vec4(-deltaX, 0.0, -deltaX, 0.0);    // 1:bottom-left
  EmitVertex();
  gl_Position = position + vec4(deltaX, 0.0, -deltaX, 0.0);    // 2:bottom-right
  EmitVertex();
  gl_Position = position + vec4(-deltaX, 0.0, deltaY, 0.0);    // 3:top-left
  EmitVertex();
  gl_Position = position + vec4(deltaX, 0.0, deltaY, 0.0);    // 4:top-right
  EmitVertex();

  EndPrimitive();
}

void main()
{
  /*
  for(int i = 0; i < grassDistribution; i++)
  
  */

  /*
  Calculate the centroid of each triangle and sample the distribution texture at that point.
  Using the sampled color value, decide if a plane should be placed or not.
  */
  generate_grass_obj(position, 10);
}