#include "Shape.h"

Shape::Shape():num_verts(0),num_inds(0)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}

Shape::~Shape()
{
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
}

void Shape::Update(VERTEX* vert, int nv, unsigned short* ind, int ni)
{
	vertices = vert;
	indices = ind;
	num_verts = nv;
	num_inds = ni;
}


void Shape::render()
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, num_inds, GL_UNSIGNED_SHORT, nullptr);
}

void Shape::send()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, num_verts * sizeof(VERTEX), vertices, GL_STATIC_DRAW);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_inds * sizeof(unsigned short), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX), (void*)offsetof(VERTEX, POS));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX), (void*)offsetof(VERTEX, COLOR));
	glEnableVertexAttribArray(1);
}
