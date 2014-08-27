/*
 *  Hyperopolis: Megacities building game.
    Copyright (C) 2014  Daniel Fernández Villanueva

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

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
	assert(vertices.size() == 4);
	this->vertices.resize(4);
	for(unsigned int i = 0; i < 4; i++)
	{
		this->vertices.at(i) = vertices.at(i);
	}
	this->normals.resize(4);
	this->normals[0] = Utils::cross(this->vertices[1] - this->vertices[0],
			                        this->vertices[3] - this->vertices[0]);
	this->normals[1] = Utils::cross(this->vertices[2] - this->vertices[1],
				                    this->vertices[0] - this->vertices[1]);
	this->normals[2] = Utils::cross(this->vertices[3] - this->vertices[2],
									this->vertices[1] - this->vertices[2]);
	this->normals[3] = Utils::cross(this->vertices[0] - this->vertices[3],
									this->vertices[2] - this->vertices[3]);
	this->normals.at(0) = this->normals.at(0) / Utils::length(this->normals.at(0));
	this->normals.at(1) = this->normals.at(1) / Utils::length(this->normals.at(1));
	this->normals.at(2) = this->normals.at(2) / Utils::length(this->normals.at(2));
	this->normals.at(3) = this->normals.at(3) / Utils::length(this->normals.at(3));
}

void Quad::create(const sf::Vector3f & v0,
				  const sf::Vector3f & v1,
				  const sf::Vector3f & v2,
				  const sf::Vector3f & v3)
{
	this->vertices.resize(4);
	this->vertices[0] = v0;
	this->vertices[1] = v1;
	this->vertices[2] = v2;
	this->vertices[3] = v3;

	this->normals.resize(4);
	this->normals[0] = Utils::cross(this->vertices[1] - this->vertices[0],
									this->vertices[3] - this->vertices[0]);
	this->normals[1] = Utils::cross(this->vertices[2] - this->vertices[1],
									this->vertices[0] - this->vertices[1]);
	this->normals[2] = Utils::cross(this->vertices[3] - this->vertices[2],
									this->vertices[1] - this->vertices[2]);
	this->normals[3] = Utils::cross(this->vertices[0] - this->vertices[3],
									this->vertices[2] - this->vertices[3]);
	this->normals.at(0) = this->normals.at(0) / Utils::length(this->normals.at(0));
	this->normals.at(1) = this->normals.at(1) / Utils::length(this->normals.at(1));
	this->normals.at(2) = this->normals.at(2) / Utils::length(this->normals.at(2));
	this->normals.at(3) = this->normals.at(3) / Utils::length(this->normals.at(3));
}

sf::Vector3f Quad::getVertex(const unsigned int index) const
{
	return this->vertices.at(index);
}

sf::Vector3f Quad::getNormal(const unsigned int vertex_index) const
{
	return this->normals.at(vertex_index);
}

sf::Vector3f Quad::getNormal() const
{
	assert(this->vertices.size() == 4);
	sf::Vector3f v =  Utils::cross(Utils::diff(this->vertices[1], this->vertices[0]),
								   Utils::diff(this->vertices[3], this->vertices[0]));
	return v / Utils::length(v);
}

void Quad::draw() const
{
	assert(this->vertices.size() == 4);
	sf::Vector3f normal = this->getNormal();
	glNormal3f(normal.x, normal.y, normal.z);
	std::vector<sf::Vector3f>::const_iterator it;
	for(it = this->vertices.begin(); it != this->vertices.end(); it++)
	{
		glVertex3f(it->x, it->y, it->z);
	}

}

float Quad::getAvgHeight() const
{
	return 0.25 * (this->vertices.at(0).z + this->vertices.at(1).z + this->vertices.at(2).z + this->vertices.at(3).z);
}

float Quad::getMaxInclination() const
{
	std::vector<float> inc(4);
	inc.at(0) = Utils::pitch(this->vertices[0]-this->vertices[1]);
	inc.at(1) = Utils::pitch(this->vertices[1]-this->vertices[2]);
	inc.at(2) = Utils::pitch(this->vertices[2]-this->vertices[3]);
	inc.at(3) = Utils::pitch(this->vertices[3]-this->vertices[0]);
	return *(std::max_element(inc.begin(), inc.end()));
}

float Quad::getMinHeight() const
{
	std::vector<float> heights;
	for(auto vertex: this->vertices)
	{
		heights.push_back(vertex.z);
	}
	return *(std::min_element(heights.begin(), heights.end()));
}

float Quad::getMaxheight() const
{
	std::vector<float> heights;
	for(auto vertex: this->vertices)
	{
		heights.push_back(vertex.z);
	}
	return *(std::max_element(heights.begin(), heights.end()));
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

float Utils::interpolate2d(float x0, float x1, float y0, float y1, float z00,
		float z01, float z10, float z11, float x, float y)
{
	const float a = (x1-x0)*(y1-y0);
	const float a00 = (x-x0)*(y-y0);
	const float a01 = (x-x0)*(y1-y);
	const float a10 = (x1-x)*(y-y0);
	const float a11 = (x1-x)*(y1-y);
	return (a11*z00 + a10*z01 + a01*z10 + a00*z11) / a;
}

float Utils::pitch(sf::Vector3f v)
{
	return std::abs(atan(v.z/(sqrt(v.x*v.x+v.y*v.y))));
}

float Utils::floatRandom(const float min, const float max)
{
	return min + (max-min)*(float(rand()) / float(RAND_MAX));
}

float Utils::rFunction(const float x, const float n)
{
	float e = 2.7182818284;
	return (pow(e, n*(1.f-x)) - 1.f) / (pow(e, n) - 1.f);
}

bool Utils::test()
{
	bool everything_ok = true;
	bool test_interpolate2d =
			interpolate2d(0.0, 1.0, 0.0, 1.0,
				  1.0, 2.0, 3.0, 4.0,
				  0.0, 0.0) == 1.0;

	bool test_rFunction = std::abs(rFunction(0.f, 10.f) - 1.0) < 1e-10 &&
					      std::abs(rFunction(1.f, 10.f)) < 1e-10;

	std::cout << rFunction(0.f, 10.f) << std::endl;
	std::cout << rFunction(1.f, 10.f) << std::endl;

	if(test_interpolate2d)
	{
		std::cout << "test_interpolate2d passed" << std::endl;
	}
	else
	{
		std::cout << "test_interpolate2d NOT passed" << std::endl;
		everything_ok = false;
	}

	if(test_rFunction)
	{
		std::cout << "test_rFunction passed" << std::endl;
	}
	else
	{
		std::cout << "test_rFunction NOT passed" << std::endl;
		everything_ok = false;
	}

	return everything_ok;
}



} /* namespace dfv */


