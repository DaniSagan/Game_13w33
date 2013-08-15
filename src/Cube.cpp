/*
 * Cube.cpp
 *
 *  Created on: Aug 11, 2013
 *      Author: daniel
 */

#include "Cube.h"

namespace dfv
{

Cube::Cube()
{
	// TODO Auto-generated constructor stub

}

Cube::~Cube()
{
	// TODO Auto-generated destructor stub
}

sf::Color Cube::GetColor() const
{
	return this->color;
}

void Cube::SetColor(sf::Color color)
{
	this->color = color;
	this->gl_color_top = sf::Vector3f((float)color.r / 255.f, (float)color.g / 255.f, (float)color.b / 255.f);
	this->gl_color_side_b = sf::Vector3f(gl_color_top.x * 0.8, gl_color_top.y * 0.8, gl_color_top.z * 0.8);
	this->gl_color_side_d = sf::Vector3f(gl_color_top.x * 0.6, gl_color_top.y * 0.6, gl_color_top.z * 0.6);
	this->gl_color_bottom = sf::Vector3f(gl_color_top.x * 0.4, gl_color_top.y * 0.4, gl_color_top.z * 0.4);
}

const sf::Vector3f& Cube::GetPosition() const
{
	return this->position;
}

void Cube::SetPosition(const sf::Vector3f& position)
{
	this->position = position;
}

void Cube::Draw(sf::Window& window, const dfv::Camera& camera, bool top_only)
{
	//glLoadIdentity();
	//glTranslatef(this->position.x - camera.GetPosition().x,
	//		this->position.y - camera.GetPosition().y,
	//		this->position.z - camera.GetPosition().z);
	//glRotatef(camera.GetRpy().x, 1.f, 0.f, 0.f);
	//glRotatef(camera.GetRpy().y, 0.f, 1.f, 0.f);
	//glRotatef(camera.GetRpy().z, 0.f, 0.f, 1.f);


	glBegin(GL_QUADS);

		//glColor3f(this->gl_color_top.x, this->gl_color_top.y, this->gl_color_top.z);
		glTexCoord2d(0.0,0.0);
		glVertex3f(this->position.x - 0.5f, this->position.y - 0.5f, this->position.z + 0.5f);
		glTexCoord2d(1.0,0.0);
		glVertex3f(this->position.x + 0.5f, this->position.y - 0.5f, this->position.z + 0.5f);
		glTexCoord2d(1.0,1.0);
		glVertex3f(this->position.x + 0.5f, this->position.y + 0.5f, this->position.z + 0.5f);
		glTexCoord2d(0.0,1.0);
		glVertex3f(this->position.x - 0.5f, this->position.y + 0.5f, this->position.z + 0.5f);

		if(top_only == false)
		{
			glColor3f(this->gl_color_bottom.x, this->gl_color_top.y, this->gl_color_top.z);
			glVertex3f(-0.5f, -0.5f, -0.5f);
			glVertex3f(-0.5f,  0.5f, -0.5f);
			glVertex3f( 0.5f,  0.5f, -0.5f);
			glVertex3f( 0.5f, -0.5f, -0.5f);

			glColor3f(this->gl_color_side_b.x, this->gl_color_side_b.y, this->gl_color_side_b.z);
			glVertex3f(-0.5f, -0.5f, -0.5f);
			glVertex3f(-0.5f,  0.5f, -0.5f);
			glVertex3f(-0.5f,  0.5f,  0.5f);
			glVertex3f(-0.5f, -0.5f,  0.5f);

			glColor3f(this->gl_color_side_d.x, this->gl_color_side_d.y, this->gl_color_side_d.z);
			glVertex3f(0.5f, -0.5f, -0.5f);
			glVertex3f(0.5f,  0.5f, -0.5f);
			glVertex3f(0.5f,  0.5f,  0.5f);
			glVertex3f(0.5f, -0.5f,  0.5f);

			glColor3f(this->gl_color_side_b.x, this->gl_color_side_b.y, this->gl_color_side_b.z);
			glVertex3f(-0.5f, -0.5f,  0.5f);
			glVertex3f(-0.5f, -0.5f, -0.5f);
			glVertex3f( 0.5f, -0.5f, -0.5f);
			glVertex3f( 0.5f, -0.5f,  0.5f);

			glColor3f(this->gl_color_side_d.x, this->gl_color_side_d.y, this->gl_color_side_d.z);
			glVertex3f(-0.5f, 0.5f,  0.5f);
			glVertex3f(-0.5f, 0.5f, -0.5f);
			glVertex3f( 0.5f, 0.5f, -0.5f);
			glVertex3f( 0.5f, 0.5f,  0.5f);
		}

	glEnd();
}

} /* namespace dfv */
