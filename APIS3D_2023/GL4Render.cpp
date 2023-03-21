#include "GL4Render.h"
#include "System.h"

void GL4Render::setupObject(Object* obj)
{
	for (const auto& mesh : obj->getMeshes())
	{
		VBO_t vbo;
		std::vector<vertex_t>* vertices = mesh->getVertList();
		std::vector<glm::uint32>* indices = mesh->getTriangleIdxList();

		glGenVertexArrays(1, &vbo.id);

		// Crear los buffers para los vertices y los indices
		glGenBuffers(1, &vbo.v_id);
		glGenBuffers(1, &vbo.i_id);

		// Vertices
		glBindBuffer(GL_ARRAY_BUFFER, vbo.v_id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_t) * vertices->size(), vertices->data(), GL_STATIC_DRAW);

		// Indices 
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo.i_id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices->size(), indices->data(), GL_STATIC_DRAW);

		bufferObjects[mesh->getMeshID()] = vbo;
	}
}

void GL4Render::removeObject(Object* obj)
{
	for (const auto& mesh : obj->getMeshes())
	{
		unsigned int meshID = mesh->getMeshID();

		// Si el vbo asociado al meshID existe en bufferObjects se libera la memoria de sus buffers
		if (bufferObjects.find(meshID) != bufferObjects.end())
		{
			const VBO_t& vbo = bufferObjects[meshID];
			glDeleteVertexArrays(1, &vbo.id);
			glDeleteBuffers(1, &vbo.v_id);
			glDeleteBuffers(1, &vbo.i_id);
		}
	}
}

// COMPLETAR ESTA CLASE CORRECTAMENTE CUANDO EST� LO QUE FALTE
// Cuidado: De momento no se utilizan texturas ni indices, ni hay camara
void GL4Render::drawObjects(std::vector<Object*>* objs) 
{
	// Limpiar buffer de color y profundidad
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (const auto& obj : *objs) {

		obj->computeModelMatrix();
		System::setModelMatrix(obj->getModelMt());

		for (const auto& mesh : obj->getMeshes())
		{
			Material* mat = mesh->getMaterial();

			// Activar buffers antes de usar el programa
			VBO_t buffer = bufferObjects[mesh->getMeshID()];
			glBindVertexArray(buffer.id);
			glBindBuffer(GL_ARRAY_BUFFER, buffer.v_id);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.i_id);
		
			// Attributes
			mat->prepare();

			mesh->getDepthTestEnabled() ? glDepthMask(GL_TRUE) : glDepthMask(GL_FALSE);

			// Dibujado
			glDrawElements(GL_TRIANGLES, mesh->getTriangleIdxList()->size(), GL_UNSIGNED_INT, nullptr); // nullptr porque los datos ya estan copiados
		}
	}

	glfwSwapBuffers(window);
}