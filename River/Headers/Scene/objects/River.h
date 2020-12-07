#pragma once
#include "Scene/utils/Surface.h"
#include "utils/view/Image.h"
#include "view/Shader.h"

class River
{
public:
	River() :
		image("./Resources/Images/WaterDiffuse.png"),
		texture("./Resources/Images/WaterDiffuse.png"),
		surface(3, 3, 10),
		shader("./Resources/Shaders/Water/Water_Vertex.shader", "",
			   "./Resources/Shaders/Water/Water_Fragment.shader")
	{
		
	}

	void update_shaders(const std::string& name, const glm::mat4& mat)
	{
		shader.bind();

		shader.SetMat4(name, mat);

		shader.unbind();
	}


private:
	Image image;
	const std::string image_path;
	Texture texture;
	Surface surface;

	Shader shader;
	const std::string fragment_shader;
	const std::string vertex_shader;
};

//class temp: public Shader
//{
//	/** Shaders initialization */
//	std::string vertexSource = ParseShader("./uni_shaders/uniform_vertex.shader");
//	std::string fragmentSource = ParseShader("./uni_shaders/uniform_fragment.shader");
//
//	unsigned int program = CreateShader(vertexSource, fragmentSource);
//
//	glUseProgram(program); // shader.bind()
//
//	/** Matrices creation */
//	glm::mat4 model = glm::mat4(1.0f);
//	glm::mat4 view = glm::lookAt(glm::vec3(0, 2, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));	//center, lookat, up
//	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
//	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)(1), 0.1f, 100.0f);		//perspective view
//	glm::mat4 projection = glm::ortho(0.0f, 500.0f, 0.0f, 500.0f, -0.1f, 100.0f);				//orthogonal view
//	 final Model View Projection matrix creation
//	glm::mat4 mvp = glm::mat4(1.0f);
//
//	 mvp ID setup for shader use
//	unsigned int mvp_id = glGetUniformLocation(program, "mvp");
//	if(mvp_id >= 0) // if we get negative -1 then it didn't find our uniform
//	{
//		/*GLint location,GLsizei count,GLboolean transpose,const GLfloat *value)*/
//		glUniformMatrix4fv(mvp_id, 1, GL_FALSE, &mvp[0][0]);
//	}
//	 model ID setup for shader use
//	unsigned int model_id = glGetUniformLocation(program, "model");
//	if(model_id >= 0) // if we get negative -1 then it didn't find our uniform
//	{
//		glUniformMatrix4fv(model_id, 1, GL_FALSE, &model[0][0]);
//	}
//
//	 mvp update and sending to shader
//	mvp = projection * view * model;
//	glUniformMatrix4fv(mvp_id, 1, GL_FALSE, &mvp[0][0]);
//
//}