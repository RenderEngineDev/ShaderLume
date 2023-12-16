#include "Objects/Primitives.h"

Primitives::Plane::Plane(glm::vec3 position = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f)) : Object(position, scale) {
	setupMesh();
}

void Primitives::Plane::setupMesh() {

	std::vector<Vertex> vertices = std::vector<Vertex>({
		{ glm::vec3( 1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f) },
		{ glm::vec3( 1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f) },
		{ glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f) },
		{ glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f) }
		});
	std::vector<unsigned int> indices = std::vector<unsigned int>({
			0, 1, 2,
			1, 2, 3,
		});
	std::vector<Texture> textures = std::vector<Texture>();

	this->mesh = new Mesh(vertices, indices, textures);
}

/*
	TODO: 
	przenie�� projection i view do jakiego� zewn�trznego renderera, kt�ry b�dzie ich referencje wykorzystywa� przy rysowaniu wszystkich obiekt�w
*/
void Primitives::Plane::Draw(Shader& shader, glm::mat4& projection, glm::mat4& view) {
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	model = glm::scale(model, scale);
	shader.setMat4("projection", projection);
	shader.setMat4("view", view);
	shader.setMat4("model", model);

	mesh->Draw();
}

Primitives::Cube::Cube(glm::vec3 position = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f)) : Object(position, scale) {
	setupMesh();
}

void Primitives::Cube::setupMesh() {

	std::vector<Vertex> vertices = std::vector<Vertex>({
		{ glm::vec3(1.0f, -1.0f,  1.0f), glm::vec3(1.0f, -1.0f,  1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.0f) },
		{ glm::vec3(1.0f,  1.0f,  1.0f), glm::vec3(1.0f,  1.0f,  1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f), glm::vec3(0.0f) },
		{ glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f), glm::vec3(0.0f) },
		{ glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.0f) },
		{ glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.0f) },
		{ glm::vec3(1.0f,  1.0f, -1.0f), glm::vec3(1.0f,  1.0f, -1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f), glm::vec3(0.0f) },
		{ glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f), glm::vec3(0.0f) },
		{ glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.0f) }
		});
	std::vector<unsigned int> indices = std::vector<unsigned int>({
		// front
		0, 1, 2,
		0, 2, 3,
		// right
		0, 1, 5,
		0, 4, 5,
		// left
		2, 3, 6,
		3, 6, 7,
		// top
		1, 2, 5,
		2, 5, 6,
		// bottom
		0, 3, 4,
		3, 4, 7,
		// back
		4, 5, 6,
		4, 6, 7
		});
	std::vector<Texture> textures = std::vector<Texture>();

	this->mesh = new Mesh(vertices, indices, textures);
}

/*
	TODO:
	przenie�� projection i view do jakiego� zewn�trznego renderera, kt�ry b�dzie ich referencje wykorzystywa� przy rysowaniu wszystkich obiekt�w
*/
void Primitives::Cube::Draw(Shader& shader, glm::mat4 &projection, glm::mat4 &view) {
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	model = glm::scale(model, scale);
	shader.setMat4("projection", projection);
	shader.setMat4("view", view);
	shader.setMat4("model", model);

	mesh->Draw();
}

Primitives::RMSphere::RMSphere(glm::vec3 position, glm::vec3 scale, const char* fShaderPath) : RMObject(position, scale, fShaderPath)
{

}

void Primitives::RMSphere::Draw(Camera::Camera &camera)
{
	shader.use();
	/*
		definicje view przeniesc do kamery, aby mogla zwrocic sama rotacje bez przesuniecia
	*/
	glm::mat4 view = glm::mat4{glm::vec4(camera.right,0),
					 glm::vec4(camera.up,   0),
					 glm::vec4(camera.front,0), 
					 glm::vec4(camera.right,1)};

	shader.setMat4("View", view);
	shader.setVec3("CameraPos", camera.position);
	shader.setVec3("SpherePos", position);
	shader.setFloat("Zoom", camera.zoom);

	mesh->Draw();
}
