#include "InstancedEmitter.h"
#include "System.h"

InstancedEmitter::~InstancedEmitter()
{
	if (mvps) delete mvps;
	if (colors) delete colors;
}

void InstancedEmitter::setMaxParticles(unsigned maxNumParticles)
{
	if (mvps) delete mvps;
	if (colors) delete colors;
	this->maxNumParticles = maxNumParticles;
	mvps = new glm::mat4[maxNumParticles];
	colors = new glm::vec4[maxNumParticles];
}

void InstancedEmitter::step(double deltaTime)
{
	// Generar partículas si se está emitiendo
	if (emitting)
	{
		float emissionRate = glm::linearRand(minRate, maxRate);
		float newParticleCount = particleAccum + emissionRate * deltaTime;
		int particlesToCreate = (int)newParticleCount;
		particleAccum = newParticleCount - particlesToCreate;

		for (int i = 0; i < particlesToCreate; ++i)
		{
			float randSpin = glm::linearRand(minSpin, maxSpin);
			double randLifeTime = glm::linearRand(minLifeTime, maxLifeTime);
			float randScale = glm::linearRand(minScale, maxScale);
			glm::vec3 randVelocity = glm::vec3(glm::linearRand(minVel.x, maxVel.x),
											   glm::linearRand(minVel.y, maxVel.y),
											   glm::linearRand(minVel.z, maxVel.z));
			// Falta el color
			Particle* p = new Particle(mshFile, randVelocity, randSpin, randLifeTime, randScale, autoFade);
			p->setPosition(this->getPosition());
			particles->push_back(p);
		}
	}

	// Ordenar partículas por distancia a la cámara
	std::map<float, Particle*> distMap;
	for (Particle* p : *particles)
	{
		p->step(deltaTime);
		if (p->getRemainingLifeTime() > 0)
		{
			float dist = glm::distance(glm::vec3(p->getPosition()), glm::vec3(System::getCamera()->getPosition()));
			distMap[dist] = p;
		}
		else
		{
			delete p;
		}
	}

	particles->clear();

	currentNumParticles = glm::min((unsigned)distMap.size(), maxNumParticles);
	auto it = distMap.begin();
	for (unsigned i = 0; i < currentNumParticles; ++it, ++i) // si no se recorre entero el distMap se pierden particulas, esto pasa cuando el numero de particulas es mayor a maxNumParticles se podrían seguir introduciendo en particles y solo actualizar las matrices mvp que sea posible
	{
		it->second->updateAlpha();
		particles->push_back(it->second);

		it->second->computeModelMatrix();
		mvps[i] = System::getCamera()->getProjection() * System::getCamera()->getView() * it->second->getModelMt();
		colors[i] = it->second->getMeshes()[0]->getMaterial()->getColor(); // Importante hacer el updateAlpha de la particula justo antes de setear el color debido a que la mesh se comparte
	}

	// Si no se han podido enviar todas las particulas porque superan el maximo seteado se borran las que han sobrado
	for (; it != distMap.end(); ++it)
	{
		delete it->second;
	}
}
