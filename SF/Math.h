#include <SFML/Graphics.hpp>

#include <cmath>

namespace SF::Math{

    template<typename T>
    inline float vecDist(const sf::Vector2<T>&  vec1, const sf::Vector2<T>& vec2) {
		return sqrt((vec2.x - vec1.x) * (vec2.x - vec1.x) +
			(vec2.y - vec1.y) * (vec2.y - vec1.y));
	};

};