#include <Re\Graphics\Model\GraphicsPolygonShape.h>


namespace Graphics
{

	PolygonShape::PolygonShape(size_t layersN, size_t pointN, Color cl)
	{
		create(layersN, pointN, cl);
	}

	void PolygonShape::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		/// for testing, draw base shape
		//target.draw(m_base, states);

		/// draw and update layers
		if (m_changeClock.getElapsedTime() > m_cdChange)
		{
			float angle;
			float radius;
			int vertexCount = m_base.getVertexCount() -1;
			for (auto& itLayer : m_layers)
			{
				for (int i = 0; i < vertexCount; ++i)
				{
					angle = randRange(0, M_PI * 2);
					radius = randRange(0, m_changeRadius);

					itLayer[i].position.x = m_base[i].position.x + radius * cos(angle);
					itLayer[i].position.y = m_base[i].position.y + radius * sin(angle);
				}
				itLayer[vertexCount] = itLayer[1];

				target.draw(itLayer, states);
			}

			m_changeClock.restart();
		}
		else
		{
			/// only draw
			for (auto& itLayer : m_layers)
				target.draw(itLayer, states);
		}
	}

	void PolygonShape::create(size_t layersN, size_t pointN, Color cl)
	{
		m_layers.resize(layersN);

		m_base.resize(pointN);
		for (auto &it : m_layers)
		{
			it.setPrimitiveType(sf::TriangleFan);
			it.resize(pointN);
			for (int i = 0; i < pointN; ++i)
			{
				it[i].color = cl;
			}
		}
	}

	void PolygonShape::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
#ifdef RE_EDITOR
		/// TODO
		Color cl = getColor();
		saver.save("clR", cl.r);
		saver.save("clG", cl.g);
		saver.save("clB", cl.b);
		saver.save("clA", cl.a);

		saver.save("layersN", getLayersCount());
		saver.save("cdChange", getLayersCount());
		saver.save("changeRadius", getLayersCount());
		
		int i = 1;
		saver.nextLine(file);
		do
		{
			saver.save("posX", m_base[i].position.x);
			saver.save("posY", m_base[i].position.y);
			++i;
		}
		DATA_SCRIPT_MULTILINE_SAVE(file, saver, i < getPointCount() - 2);
#endif
	}

	void PolygonShape::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		m_base.clear();
		m_base.append(Vector2f());
		Color cl( loader.load("clR", 255u), 
			loader.load("clG", 255u), 
			loader.load("clB", 255u),
			loader.load("clA", 255u)
			);
		m_base[0].color = cl;

		size_t layersN = loader.load("layersN", 1);

		m_changeRadius = loader.load("changeRadius", 0.f);
		m_cdChange = sf::seconds(loader.load("cdChange", 0.1f));

		DATA_SCRIPT_MULTILINE(file, loader)
		{
			float posX = loader.load("posX", 0.f);
			float posY = loader.load("posY", 0.f);
			m_base.append(Vertex(sf::Vector2f(posX, posY), cl));
		}
		m_base.	append(m_base[1]);

		size_t vertexCount = m_base.getVertexCount();
		m_layers.resize(layersN);
		for (auto &it : m_layers)
		{
			it.setPrimitiveType(sf::TriangleFan);
			it.resize(vertexCount);
			for (int i = 0; i < vertexCount; ++i)
				it[i].color = cl;
		}
	}

	void PolygonShape::setLayersCount(size_t n)
	{
		size_t vertexCount = getPointCount();
		Color cl = getColor();

		m_layers.resize(n);
		for (auto &it : m_layers)
		{
			it.setPrimitiveType(sf::TriangleFan);
			it.resize(vertexCount);
			for (int i = 0; i < vertexCount; ++i)
				it[i].color = cl;
		}
	}

	void PolygonShape::addPoint(int idAfter)
	{
		m_base.resize(m_base.getVertexCount() + 1);
		for (auto &itLayer : m_layers)
			itLayer.resize(m_base.getVertexCount());
		
		for (int i = m_base.getVertexCount()-1; i > idAfter; --i)
		{
			m_base[i] = m_base[i - 1];
		}
		//m_base[m_base.getVertexCount() - 1] = m_base[1];

		setColor(getColor());
	}
	void PolygonShape::delPoint(int id)
	{
		for (int i = id+1; i < m_base.getVertexCount(); ++i)
		{
			m_base[i-1] = m_base[i];
		}

		m_base.resize(m_base.getVertexCount() -1);
		for (auto &itLayer : m_layers)
			itLayer.resize(m_base.getVertexCount());
	}


}