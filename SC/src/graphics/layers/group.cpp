#include "group.h"

namespace sparky { namespace graphics {

	Group::Group(const maths::mat4& transformMatrix)
		: m_TransformationMatrix(transformMatrix)
	{
	}

	Group::~Group()
	{
		for (int i = 0; i < m_Renderables.size(); i++)
			delete m_Renderables[i];
	}

	void Group::add(Renderable2D* renderable)
	{
		m_Renderables.push_back(renderable);
	}

	void Group::remove(Renderable2D* renderable)
	{
		for (int i = 0; i < m_Renderables.size(); i++)
			if (m_Renderables[i]->getTexture()->getName() == renderable->getTexture()->getName())
				m_Renderables.erase(m_Renderables.begin() + i);
	}

	void Group::submit(Renderer2D* renderer) const
	{
		renderer->push(m_TransformationMatrix);

		for (const Renderable2D* renderable : m_Renderables)
			renderable->submit(renderer);

		renderer->pop();
	}



} }