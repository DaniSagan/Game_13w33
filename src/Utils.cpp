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
	this->normals[0] = Utils::Cross(this->vertices[1] - this->vertices[0],
			                        this->vertices[3] - this->vertices[0]);
	//this->normals[0] = this->normals[0] / Utils::Length(this->normals[0]);
	this->normals[1] = Utils::Cross(this->vertices[2] - this->vertices[1],
				                    this->vertices[0] - this->vertices[1]);
	//this->normals[1] = this->normals[1] / Utils::Length(this->normals[1]);
	this->normals[2] = Utils::Cross(this->vertices[3] - this->vertices[2],
									this->vertices[1] - this->vertices[2]);
	//this->normals[2] = this->normals[0] / Utils::Length(this->normals[2]);
	this->normals[3] = Utils::Cross(this->vertices[0] - this->vertices[3],
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

sf::Vector3f Utils::Cross(const sf::Vector3f& v1, const sf::Vector3f& v2)
{
	return sf::Vector3f(v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x);
}

sf::Vector3f Utils::Diff(const sf::Vector3f& v1, const sf::Vector3f& v2)
{
	return sf::Vector3f(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

sf::Vector2f Utils::Diff(const sf::Vector2f& v1, const sf::Vector2f& v2)
{
	return sf::Vector2f(v1.x - v2.x, v1.y - v2.y);
}

void Utils::DrawRectangle(sf::Image& img, const sf::Vector2i& top_left,
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

float Utils::Length(const sf::Vector3f v)
{
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

float Utils::Length(const sf::Vector2f v)
{
	return sqrt(v.x*v.x + v.y*v.y);
}

void Utils::TrimRect(IntRect& rect, const IntRect& limits)
{
	if(rect.Left < limits.Left) rect.Left = limits.Left;
	if(rect.Right > limits.Right) rect.Right = limits.Right;
	if(rect.Top > limits.Top) rect.Top = limits.Top;
	if(rect.Bottom < limits.Bottom) rect.Bottom = limits.Bottom;
}

void Utils::TrimRect(IntRect& rect, int left, int right, int top,
		int bottom)
{
	if(rect.Left < left) rect.Left = left;
	if(rect.Right > right) rect.Right = right;
	if(rect.Top > top) rect.Top = top;
	if(rect.Bottom < bottom) rect.Bottom = bottom;
}

IntRect Utils::CreateRect(const sf::Vector2i& position, int radius)
{
	IntRect rect;
	rect.Left = position.x - radius;
	rect.Right = position.x + radius;
	rect.Bottom = position.y - radius;
	rect.Top = position.y + radius;

	return rect;
}

sf::Vector2i Utils::ToVector2i(const sf::Vector2f& v)
{
	return sf::Vector2i(floor(v.x), floor(v.y));
}

sf::Vector2f Utils::ToVector2f(const sf::Vector2i& v)
{
	return sf::Vector2f(v.x, v.y);
}

sf::Vector2f Utils::GetVector2d(const sf::Vector3f& v)
{
	return sf::Vector2f(v.x, v.y);
}

std::vector<std::string> Utils::StringTokenize(const std::string& str,
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

std::string Utils::ToString(const IntRect& rect)
{
	std::stringstream ss;
	ss << "L:" << rect.Left << ", ";
	ss << "R:" << rect.Right << ", ";
	ss << "B:" << rect.Bottom << ", ";
	ss << "T:" << rect.Top;
	return ss.str();
}

bool Utils::RectContains(const IntRect& rect, const sf::Vector2i& pos)
{
	return pos.x >= rect.Left && pos.x <= rect.Right &&
			pos.y <= rect.Bottom && pos.y >= rect.Top;
}



} /* namespace dfv */
