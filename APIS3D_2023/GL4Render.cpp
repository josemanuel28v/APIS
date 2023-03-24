#include "GL4Render.h"
#include "System.h"

void GL4Render::setupObject(Object* obj)
{
	for (const auto& mesh : obj->getMeshes())
	{
		// Si no existe el id de la mesh en el mapa bufferObjects se añade
		if (bufferObjects.find(mesh->getMeshID()) == bufferObjects.end())
		{
			VBO_t vbo;
			std::vector<vertex_t>* vertices = mesh->getVertices();
			std::vector<glm::uint32>* indices = mesh->getIndices();

			glGenVertexArrays(1, &vbo.id);
			glBindVertexArray(vbo.id);

			// Crear los buffers para los vertices y los indices
			glGenBuffers(1, &vbo.v_id);
			glGenBuffers(1, &vbo.i_id);

			// Vertices
			glBindBuffer(GL_ARRAY_BUFFER, vbo.v_id);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_t) * vertices->size(), vertices->data(), GL_STATIC_DRAW);

			// Indices 
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo.i_id);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices->size(), indices->data(), GL_STATIC_DRAW);

			//
			Material* mat = mesh->getMaterial();
			RenderProgram* program = mat->getProgram();

			glEnableVertexAttribArray(program->varList["vpos"]);
			glVertexAttribPointer(program->varList["vpos"], 4, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, position));

			if (mat->getNormalMode() == Material::PER_VERTEX)
			{
				glEnableVertexAttribArray(program->varList["vnorm"]);
				glVertexAttribPointer(program->varList["vnorm"], 4, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, normal));
			}

			if (mat->getTexturing())
			{
				glEnableVertexAttribArray(program->varList["vtextcoord"]);
				glVertexAttribPointer(program->varList["vtextcoord"], 2, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, textCoord));
			}

			glBindVertexArray(0);

			bufferObjects[mesh->getMeshID()] = vbo;
		}
	}
}

//void setupObjectInstancing(Object* obj, unsigned amount, glm::mat4* mvps)
//{
//	for (const auto& mesh : obj->getMeshes())
//	{
//		// Si no existe el id de la mesh en el mapa bufferObjects se añade
//		if (bufferObjects.find(mesh->getMeshID()) == bufferObjects.end())
//		{
//			VBO_t vbo;
//			std::vector<vertex_t>* vertices = mesh->getVertices();
//			std::vector<glm::uint32>* indices = mesh->getIndices();
//
//			glGenVertexArrays(1, &vbo.id);
//
//			// Crear los buffers para los vertices y los indices
//			glGenBuffers(1, &vbo.v_id);
//			glGenBuffers(1, &vbo.i_id);
//			glGenBuffers(1, &vbo.mvp_id);
//
//			// Vertices
//			glBindBuffer(GL_ARRAY_BUFFER, vbo.v_id);
//			glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_t) * vertices->size(), vertices->data(), GL_STATIC_DRAW);
//
//			// Indices 
//			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo.i_id);
//			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices->size(), indices->data(), GL_STATIC_DRAW);
//
//			// Matrices mvp
//			glBindBuffer(GL_ARRAY_BUFFER, vbo.mvp_id);
//			glBufferData(GL_ARRAY_BUFFER, amount, &mvps[0], GL_STATIC_DRAW);
//
//			glVertexAttribPointer(program->varList["vmvp"], 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
//			glVertexAttribDivisor(3, 1);
//
//			bufferObjects[mesh->getMeshID()] = vbo;
//		}
//	}
//}

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

void GL4Render::drawObject(Object* obj)
{
	obj->computeModelMatrix();
	System::setModelMatrix(obj->getModelMt());

	for (const auto& mesh : obj->getMeshes())
	{
		Material* mat = mesh->getMaterial();

		// Activar buffers antes de usar el programa
		VBO_t buffer = bufferObjects[mesh->getMeshID()];

		// Attributes
		mat->prepare();

		// Dibujado
		glBindVertexArray(buffer.id);
		glDrawElements(GL_TRIANGLES, mesh->getIndices()->size(), GL_UNSIGNED_INT, nullptr); // nullptr porque los datos ya estan copiados
		glBindVertexArray(0);
	}
}

//void GL4Render::drawObjectInstancing(Object* obj)
//{
//	obj->computeModelMatrix();
//	System::setModelMatrix(obj->getModelMt());
//
//	for (const auto& mesh : obj->getMeshes())
//	{
//		Material* mat = mesh->getMaterial();
//
//		// Activar buffers antes de usar el programa
//		VBO_t buffer = bufferObjects[mesh->getMeshID()];
//		glBindVertexArray(buffer.id);
//		glBindBuffer(GL_ARRAY_BUFFER, buffer.v_id);
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.i_id);
//
//		// Attributes
//		mat->prepare();
//
//		// Dibujado
//		glDrawElementsInstanced(GL_TRIANGLES, mesh->getIndices()->size(), GL_UNSIGNED_INT, nullptr, amount); // nullptr porque los datos ya estan copiados
//	}
//}

void GL4Render::drawObjects(std::vector<Object*>* objs) 
{
	for (const auto& obj : *objs) 
	{
		drawObject(obj);
	}
}