#include "Geometry.h"
#include "Consts.h"

Sphere::Sphere(Vec3 center, double radius) : center(center), radius(radius){}

bool Sphere::intersect(const Ray& ray, ObjectIntersection* info) const
	//comentei tudo para eu entender heheheheh
{
	/*esse algoritmo � uma resolu��o geom�trica para achar o parametro da equa��o parametrica(t)
	que representa onde o vetor fez a interse��o com a esfera*/
	/*envolve achar o t que faz que chega mais perto do centro da esfera (tca) fazendo o produto
	escalar de L(vetor entre a origem do raio e o centro da esfera) e o vetor de dire��o, retornando
	a o tamanho do vetor L projetado no vetor de dire��o(tca)*/
	Vec3 L = this->center - ray.getOrigin();
	double tca = L.dotProduct(ray.getDirection());
	if (tca < 0.0f) {									//a interse��o � atr�s da camera
		return false;
	}
	/*sabendo o tca, temos que achar o thc que � onde o o parametro que corresponde ao meio caminho
	do vetor dentro da esfera, para ent�o subitrair com o tca e achar o ponto de interse��o do vetor 
	com a esfera mais pr�ximo*/
	//triangulo: d(distancia do centro da esfera ao ponto mais proximo do vetor), raio e thc
	double dSquared = L.dotProduct(L) - tca * tca;		//pitagoras
	double rSquared = this->radius * this->radius;
	if (dSquared > rSquared)		//o vetor n�o passa pela esfera
		return false;
	double thc = sqrt(rSquared - dSquared);
	
	//pontos de interse��o do vetor com a "casca" da esfera
	double t0 = tca - thc;
	double t1 = tca + thc;
	if (t0 < 0.0f && t1 < 0.0f) //ambas interse��es atr�s da camera 
		return false;
	
	//atribui os valores � estrutura de dados da interse��o
	if (t0 > t1 && t1 > 0.0f)
		info->t = t1;
	if (t0 < t1 && t0 > 0.0f)
		info->t = t0;
	info->p = ray.getOrigin() + (ray.getDirection() * info->t);
	info->n = (info->p - center).normalize();
	return true;
}
