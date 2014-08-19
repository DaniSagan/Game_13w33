/*
 * Utils.cpp
 *
 *  Created on: Aug 13, 2013
 *      Author: daniel
 */

#include "Utils.h"

namespace dfv
{

IntRect::IntRect()
{
	this->Left = 0;
	this->Right = 0;
	this->Top = 0;
	this->Bottom = 0;
}

IntRect::IntRect(int left, int top, int right, int bottom)
{
	this->Left = left;
	this->Right = right;
	this->Top = top;
	this->Bottom = bottom;
}

RealRect::RealRect():
		xmin(0.0), xmax(0.0), ymin(0.0), ymax(0.0)
{
}

RealRect::RealRect(float xmin_, float xmax_, float ymin_, float ymax_):
		xmin(xmin_), xmax(xmax_), ymin(ymin_), ymax(ymax_)
{
}

bool RealRect::contains(sf::Vector2f pos)
{
	return pos.x >= this->xmin && pos.x < this->xmax &&
		   pos.y >= this->ymin && pos.y < this->ymax;
}

void RealRect::trim(float xmin, float xmax, float ymin, float ymax)
{
	if(this->xmin < xmin) this->xmin = xmin;
	if(this->xmax > xmax) this->xmax = xmax;
	if(this->ymin < ymin) this->ymin = ymin;
	if(this->ymax > ymax) this->ymax = ymax;
}

void RealRect::trim(RealRect rect)
{
	return this->trim(rect.xmin, rect.xmax, rect.ymin, rect.ymax);
}

void RealRect::setFromCenterRadius(sf::Vector2f center_pos, float radius)
{
	this->xmin = center_pos.x - radius;
	this->xmax = center_pos.x + radius;
	this->ymin = center_pos.y - radius;
	this->ymax = center_pos.y + radius;
}

std::string RealRect::toString() const
{
	std::stringstream ss;
	ss << "xmin=" << this->xmin << ", xmax=" << this->xmax << ", ymin=" << this->ymin << ", ymax=" << this->ymax;
	return ss.str();
}

RealIntRect::RealIntRect():
		xmin(0.0), xmax(0.0), ymin(0.0), ymax(0.0)
{
}

RealIntRect::RealIntRect(int xmin_, int xmax_, int ymin_, int ymax_):
		xmin(xmin_), xmax(xmax_), ymin(ymin_), ymax(ymax_)
{
}

bool RealIntRect::contains(sf::Vector2i pos)
{
	return pos.x >= this->xmin && pos.x < this->xmax &&
		   pos.y >= this->ymin && pos.y < this->ymax;
}

void RealIntRect::trim(int xmin, int xmax, int ymin, int ymax)
{
	if(this->xmin < xmin) this->xmin = xmin;
	if(this->xmax > xmax) this->xmax = xmax;
	if(this->ymin < ymin) this->ymin = ymin;
	if(this->ymax > ymax) this->ymax = ymax;
}

void RealIntRect::trim(RealIntRect rect)
{
	return this->trim(rect.xmin, rect.xmax, rect.ymin, rect.ymax);
}

void RealIntRect::setFromCenterRadius(sf::Vector2i center_pos, int radius)
{
	this->xmin = center_pos.x - radius;
	this->xmax = center_pos.x + radius;
	this->ymin = center_pos.y - radius;
	this->ymax = center_pos.y + radius;
}

std::string RealIntRect::toString() const
{
	std::stringstream ss;
	ss << "xmin=" << this->xmin << ", xmax=" << this->xmax << ", ymin=" << this->ymin << ", ymax=" << this->ymax;
	return ss.str();
}

GuiRect::GuiRect():
		left(0.0), top(0.0), right(0.0), bottom(0.0)
{
}

GuiRect::GuiRect(float left_, float top_, float right_, float bottom_):
		left(left_), top(top_), right(right_), bottom(bottom_)
{
}

bool GuiRect::contains(sf::Vector2f pos)
{
	return pos.x >= this->left && pos.x < this->right &&
			pos.y >= this->top && pos.y < this->bottom;
}

OpenGLImage::OpenGLImage():
		handle(0)
{

}

void OpenGLImage::loadFromFile(std::string filename)
{
	this->image.loadFromFile(filename);
	glGenTextures(1, &this->handle);
	glBindTexture(GL_TEXTURE_2D, this->handle);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(
		GL_TEXTURE_2D, 0, GL_RGBA,
		this->image.getSize().x, this->image.getSize().y,
		0,
		GL_RGBA, GL_UNSIGNED_BYTE, this->image.getPixelsPtr()
	);
	this->tex_coords.resize(4);
	this->tex_coords[0] = sf::Vector2f(0.f, 1.f);
	this->tex_coords[1] = sf::Vector2f(1.f, 1.f);
	this->tex_coords[2] = sf::Vector2f(1.f, 0.f);
	this->tex_coords[3] = sf::Vector2f(0.f, 0.f);
}

GLuint OpenGLImage::getHandle() const
{
	return this->handle;
}

sf::Vector2f OpenGLImage::getTexCoords(const unsigned int index) const
{
	return this->tex_coords[index];
}

Quad::Quad()
{

}

void Quad::create(const std::vector<sf::Vector3f>& vertices)
{
	if(vertices.size() != 4)
	{
		throw std::invalid_argument("parameter vertices must have 4 elements");
	}
	this->vertices.resize(4);
	for(unsigned int i = 0; i < 4; i++)
	{
		this->vertices[i] = vertices[i];
	}
	this->normals.resize(4);
	this->normals[0] = Utils::cross(this->vertices[1] - this->vertices[0],
			                        this->vertices[3] - this->vertices[0]);
	//this->normals[0] = this->normals[0] / Utils::Length(this->normals[0]);
	this->normals[1] = Utils::cross(this->vertices[2] - this->vertices[1],
				                    this->vertices[0] - this->vertices[1]);
	//this->normals[1] = this->normals[1] / Utils::Length(this->normals[1]);
	this->normals[2] = Utils::cross(this->vertices[3] - this->vertices[2],
									this->vertices[1] - this->vertices[2]);
	//this->normals[2] = this->normals[0] / Utils::Length(this->normals[2]);
	this->normals[3] = Utils::cross(this->vertices[0] - this->vertices[3],
									this->vertices[2] - this->vertices[3]);
	//this->normals[3] = this->normals[3] / Utils::Length(this->normals[3]);
}

sf::Vector3f Quad::getVertex(const unsigned int index) const
{
	return this->vertices[index];
}

sf::Vector3f Quad::getNormal(const unsigned int vertex_index) const
{
	return this->normals[vertex_index];
}

Utils::Utils()
{
	// TODO Auto-generated constructor stub

}

Utils::~Utils()
{
	// TODO Auto-generated destructor stub
}

float Utils::dot(const sf::Vector3f& v1, const sf::Vector3f& v2)
{
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

sf::Vector3f Utils::cross(const sf::Vector3f& v1, const sf::Vector3f& v2)
{
	return sf::Vector3f(v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x);
}

sf::Vector3f Utils::diff(const sf::Vector3f& v1, const sf::Vector3f& v2)
{
	return sf::Vector3f(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

sf::Vector2f Utils::diff(const sf::Vector2f& v1, const sf::Vector2f& v2)
{
	return sf::Vector2f(v1.x - v2.x, v1.y - v2.y);
}

void Utils::drawRectangle(sf::Image& img, const sf::Vector2i& top_left,
		const sf::Vector2i& bottom_right, const sf::Color& color)
{
	unsigned int width = bottom_right.x - top_left.x + 1;
	unsigned int height = bottom_right.y - top_left.y + 1;
	//const sf::Uint8* lp_pixels = img.GetPixelsPtr();
	for(unsigned int i = 0; i < width; i++)
	{
		for(unsigned j = 0; j < height; j++)
		{
			img.setPixel(top_left.y + j, top_left.x + i, color);
		}
	}
}

float Utils::length(const sf::Vector3f v)
{
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

float Utils::length(const sf::Vector2f v)
{
	return sqrt(v.x*v.x + v.y*v.y);
}

void Utils::trimRect(IntRect& rect, const IntRect& limits)
{
	if(rect.Left < limits.Left) rect.Left = limits.Left;
	if(rect.Right > limits.Right) rect.Right = limits.Right;
	if(rect.Top > limits.Top) rect.Top = limits.Top;
	if(rect.Bottom < limits.Bottom) rect.Bottom = limits.Bottom;
}

void Utils::trimRect(IntRect& rect, int left, int right, int top,
		int bottom)
{
	if(rect.Left < left) rect.Left = left;
	if(rect.Right > right) rect.Right = right;
	if(rect.Top > top) rect.Top = top;
	if(rect.Bottom < bottom) rect.Bottom = bottom;
}

IntRect Utils::createRect(const sf::Vector2i& position, int radius)
{
	IntRect rect;
	rect.Left = position.x - radius;
	rect.Right = position.x + radius;
	rect.Bottom = position.y - radius;
	rect.Top = position.y + radius;

	return rect;
}

sf::Vector2i Utils::toVector2i(const sf::Vector2f& v)
{
	return sf::Vector2i(floor(v.x), floor(v.y));
}

sf::Vector2f Utils::toVector2f(const sf::Vector2i& v)
{
	return sf::Vector2f(v.x, v.y);
}

sf::Vector2f Utils::getVector2d(const sf::Vector3f& v)
{
	return sf::Vector2f(v.x, v.y);
}

std::vector<std::string> Utils::stringTokenize(const std::string& str,
		const std::string& delimiters)
{
	std::vector<std::string> tokens;

	// skip delimiters at beginning.
	std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);

	// find first "non-delimiter".
	std::string::size_type pos = str.find_first_of(delimiters, lastPos);

	while (std::string::npos != pos || std::string::npos != lastPos)
	{
		// found a token, add it to the vector.
		tokens.push_back(str.substr(lastPos, pos - lastPos));

		// skip delimiters.  Note the "not_of"
		lastPos = str.find_first_not_of(delimiters, pos);

		// find next "non-delimiter"
		pos = str.find_first_of(delimiters, lastPos);
	}

	return tokens;
}

std::string Utils::toString(const IntRect& rect)
{
	std::stringstream ss;
	ss << "L:" << rect.Left << ", ";
	ss << "R:" << rect.Right << ", ";
	ss << "B:" << rect.Bottom << ", ";
	ss << "T:" << rect.Top;
	return ss.str();
}

bool Utils::rectContains(const IntRect& rect, const sf::Vector2i& pos)
{
	return pos.x >= rect.Left && pos.x <= rect.Right &&
			pos.y <= rect.Bottom && pos.y >= rect.Top;
}



} /* namespace dfv */


