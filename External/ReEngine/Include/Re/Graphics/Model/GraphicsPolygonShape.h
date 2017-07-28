#pragma once
#include <Re\Common\utility.h>


namespace Graphics
{

	/// shape which displays many layers of polygons 
	/// which at runtime vibrate
	class PolygonShape:
		public Res::ISerialisable,
		public sf::Drawable,
		public sf::Transformable
	{
	public:
		PolygonShape(size_t layersN = 1, size_t pointN = 1, Color cl = Color::White);
		PolygonShape(const char* path) { deserialise(path); }

		////// Settings 
		__forceinline void setColor(Color cl) ///< setColor of all layers
		{
			m_base[0].color = cl;
			int vertexCount = m_base.getVertexCount();
			for (auto &it : m_layers)
				for (int i = 0; i < vertexCount; ++i)
					it[i].color = cl;
		}
		__forceinline void setPoint(size_t i, const sf::Vector2f s) ///< set position of base vertex with index i. Layers are updated inside draw function
		{
			assert(i < m_base.getVertexCount());
			m_base[i].position = s;
			if (i == 1)
				m_base[m_base.getVertexCount()-1].position = s;
		}
		/// use create function instead
		void setLayersCount(size_t n);  ///< how many layers to use
		__forceinline void setChangeRadius(float r) ///< how far form base points in layers could be
		{
			m_changeRadius = r;
		}
		__forceinline void setCdChange(sf::Time time) ///< set how often to update positions on layers
		{
			m_cdChange = time;
		}
		//__forceinline void setPointCount(size_t n) // use create function instead
		/*{
			m_base.resize(n + 2);
			for (auto &it : m_layers)
				it.resize(n + 2);
		}*/

		////// Gettings

		__forceinline Color getColor() const
		{
			return m_base[0].color;
		}
		__forceinline sf::Vector2f getPoint(size_t i) const
		{
			return m_base[i].position;
		}
		__forceinline size_t getLayersCount() const
		{
			return m_layers.size();
		}
		__forceinline size_t getPointCount() const
		{
			return m_base.getVertexCount();
		}
		__forceinline float getChangeRadius() const
		{
			return m_changeRadius;
		}
		__forceinline sf::Time getCdChange() const
		{
			return m_cdChange;
		}


		void addPoint(int idAfter);
		void delPoint(int idAfter);


	protected:
		void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
		void create(size_t layersN, size_t pointN, Color cl);

	private: /// Members
			 /// general drawing
		sf::VertexArray				m_base;		///< geometry on the basis of which is counted position of each layer
		mutable vector<VertexArray>	m_layers;	///< array of layers drawed onto screan

												/// update data
		float				m_changeRadius;		///< how far away from base can be each point on layer
		sf::Time			m_cdChange{ seconds(0.1f) };	///< how long to wait till update
		mutable sf::Clock	m_changeClock;		///< clock to measure time between layer updates
	protected:
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};


}
