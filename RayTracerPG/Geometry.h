#pragma once

#include "ObjectIntersection.h"
#include "Vec3.h"
#include "Ray.h"
#include "cmath"

#define TINYOBJLOADER_USE_DOUBLE
#include "Include/tiny_obj_loader.h"

#include <vector>

class Geometry {
public:
	/*Retorna true se r intersecta a geometria e falso caso contr�rio.
	Guarda poss�veis informa��es sobre a intersec��o em info, caso seja provido.*/
	virtual bool intersect(const Ray& ray, ObjectIntersection* info = nullptr) const = 0;
};

class Sphere : public Geometry {
private:
	Vec3 center;
	double radius;
public:
	Sphere(Vec3 center, double radius);
	bool intersect(const Ray& ray, ObjectIntersection* info = nullptr) const override;
};

class Mesh : public Geometry {
private:
	std::vector<double> vertices;
	std::vector<tinyobj::index_t> vertexIndexes;
	std::vector<double> normals;
	std::vector<unsigned char> faceVertex;


public:
	Mesh(std::vector<double>& vertices, std::vector<tinyobj::shape_t>& shapes,
		std::vector<double>& normal);
	
	//interse��o com o mesh
	bool intersect(const Ray& r, ObjectIntersection* info = nullptr) const override;
	//interse��o com um triangulo individual
	static bool intersectTriangle(const Ray& ray, const Vec3* vertex0, const Vec3* vertex1, 
		const Vec3* vertex2, ObjectIntersection* info, double& u, double& v);

	//retorna a normal dada pela interpola��o dos vertices
	Vec3 interpolateNormal(int& index, double& u, double& v) const;
	//Retorna a normal da face (usada caso n�o se tenha as normais no mesh)
	Vec3 faceNormal(Vec3* vertex0, Vec3* vertex1, Vec3* vertex2) const;
};