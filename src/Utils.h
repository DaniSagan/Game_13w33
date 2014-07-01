/*
 * Utils.h
 *
 *  Created on: Aug 13, 2013
 *      Author: daniel
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <cmath>
#include <string>
#include <sstream>
#include <stdexcept>

namespace dfv
{

struct IntRect
{
	IntRect();
	IntRect(int left, int top, int right, int bottom);
	int Left;
	int Right;
	int Top;
	int Bottom;
};

struct RealRect
{
	RealRect();
	RealRect(float xmin_, float xmax_, float ymin_, float ymax_);
	float xmin, xmax, ymin, ymax;
	bool contains(sf::Vector2f pos);
	void trim(float xmin, float xmax, float ymin, float ymax);
	void trim(RealRect rect);
	void setFromCenterRadius(sf::Vector2f center_pos, float radius);
	std::string toString() const;
};

struct RealIntRect
{
	RealIntRect();
	RealIntRect(int xmin_, int xmax_, int ymin_, int ymax_);
	int xmin, xmax, ymin, ymax;
	bool contains(sf::Vector2i pos);
	void trim(int xmin, int xmax, int ymin, int ymax);
	void trim(RealIntRect rect);
	void setFromCenterRadius(sf::Vector2i center_pos, int radius);
	std::string toString() const;
};

struct GuiRect
{
	GuiRect();
	GuiRect(float left_, float top_, float right_, float bottom_);
	float left, top, right, bottom;
	bool contains(sf::Vector2f pos);
};

class OpenGLImage
{
public:
	OpenGLImage();
	void loadFromFile(std::string filename);
	GLuint getHandle() const;
	sf::Vector2f getTexCoords(const unsigned int index) const;
protected:
	sf::Image image;
	GLuint handle;
	std::vector<sf::Vector2f> tex_coords;
};

class Quad
{
public:
	Quad();
	void create(const std::vector<sf::Vector3f>& vertices);
	sf::Vector3f getVertex(const unsigned int index) const;
	sf::Vector3f getNormal(const unsigned int vertex_index) const;
protected:
	std::vector<sf::Vector3f> vertices;
	std::vector<sf::Vector3f> normals;
};

class Utils
{
public:
	Utils();
	virtual ~Utils();

	static float Dot(const sf::Vector3f& v1, const sf::Vector3f& v2);
	static sf::Vector3f Cross(const sf::Vector3f& v1, const sf::Vector3f& v2);
	static sf::Vector3f Diff(const sf::Vector3f& v1, const sf::Vector3f& v2);
	static sf::Vector2f Diff(const sf::Vector2f& v1, const sf::Vector2f& v2);
	static void DrawRectangle(
			sf::Image& img,
			const sf::Vector2i& top_left,
			const sf::Vector2i& bottom_right,
			const sf::Color& color);
	static float Length(const sf::Vector3f v);
	static float Length(const sf::Vector2f v);
	static void TrimRect(IntRect& rect, int left, int right, int top, int bottom);
	static void TrimRect(IntRect& rect, const dfv::IntRect& limits);
	static IntRect CreateRect(const sf::Vector2i& position, int radius);
	static sf::Vector2i ToVector2i(const sf::Vector2f& v);
	static sf::Vector2f ToVector2f(const sf::Vector2i& v);
	static sf::Vector2f GetVector2d(const sf::Vector3f& v);
	static std::vector<std::string> StringTokenize(
			const std::string& str,
			const std::string& delimiters);
	static std::string ToString(const IntRect& rect);
	static bool RectContains(const IntRect& rect, const sf::Vector2i& pos);
};

} /* namespace dfv */
#endif /* UTILS_H_ */
