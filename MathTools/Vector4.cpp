/**
  * This file belongs to the TakeALook project
  *
  * @see https://github.com/AnisB/Inertia
  * @author 2012-2013 Anis Benyoub <benyoub.anis@gmail.com>
  * @see The GNU Public License (GPL)
  */

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */


#include "Vector4.h"
#include <iostream>
#include "math.h"


using namespace std;
using namespace TakeALook;

const double NILLTHRESHOLD=0.0001f;
Vector4::Vector4 ( ):x(0),y(0),z(0),w(0)
{
	// std::cout<<"Appel du constructeur par defaut"<<std::endl;
}
Vector4::Vector4 (const Vector4 & OtherVector )
{
	x=OtherVector.x;
	y=OtherVector.y;
	z=OtherVector.z;
	w=OtherVector.w;
}
Vector4::Vector4 ( double anX,double anY,double aZ,double aW):x(anX),y(anY),z(aZ),w(aW)
{
	// std::cout<<"Appel du constructeur par valeurs"<<std::endl;
}
Vector4::~Vector4 ( )
{
	// std::cout<<"Appel du destructeur"<<std::endl;
}

void Vector4::debugDisplay() const
{
	cout<<"Vector4("<<x<<", "<<y<<", "<<z<<", "<<w<<")."<<endl;
}

// Surcharge d'operateurs
// ---------------------------------------------------------------

// ------------------------------------------------- L'Addition
//Surcharge de +
Vector4 operator+ (const Vector4& A, const Vector4& B)
{
	return Vector4(A.x+B.x,A.y+B.y,A.z+B.z,A.w+B.w);
}
		//Surcharge de +=
void operator+= (Vector4& A, const Vector4& B)
{
	A.x += B.x;

	A.y += B.y;

	A.z += B.z;

	A.w += B.w;
}


// ------------------------------------------------- La soustraction
//Surcharge de -
Vector4 operator- ( const Vector4& A, const Vector4& B )
{
	return Vector4(A.x-B.x,A.y-B.y,A.z-B.z,A.w-B.w);
}
void operator-= (Vector4& A, const Vector4& B)
{
	A.x -= B.x;

	A.y -= B.y;

	A.z -= B.z;

	A.w -= B.w;
}
// ------------------------------------------------- La multiplication
// Par un vector
	//Surcharge de *
double operator* (const Vector4& A, const Vector4& B)
{
	return (A.x*B.x + A.y*B.y + A.z*B.z + A.w*B.w );
}

// Par un facteur
//Surcharge de *
Vector4 operator* (const Vector4& A, const double k)
{
	return Vector4( A.x*k, A.y*k, A.z*k , A.w*k);
}

//Surcharge de *
Vector4 operator* (const double k, const Vector4& A)
{
	return Vector4(A.x*k,A.y*k,A.z*k,A.w*k);
}

// La division par un facteur


//Surcharge de /
Vector4 operator/ (const Vector4& A, const double k)
{
	return Vector4( A.x/k, A.y/k, A.z/k , A.w/k );
}

//Surcharge de /
Vector4 operator/ (const double k, const Vector4& A)
{
	return Vector4( A.x/k, A.y/k, A.z/k, A.w/k );
}

// L'egalite
//Surcharge de ==
bool operator==(const Vector4& A, const Vector4& B)
{
	if((A.x==B.x) && (A.y==B.y) && (A.z==B.z)&& (A.w==B.w))
	{
		return true;
	}
	return false;
}


// L'egalite
//Surcharge de =
void Vector4::operator=(const Vector4& B)
{
	x = B.x;

	y = B.y;

	z = B.z;

	w = B.w;
}
//Surcharge de !=
bool operator!=(const Vector4& A, const Vector4& B)
{
	if( (A.x!=B.x) || (A.y!=B.y) || (A.z!=B.z) || (A.w!=B.w))
	{
		return true;
	}
	return false;
}

// ------------------------------------------------- L'Oppose
//Surcharge de -
	Vector4 operator- (const Vector4& aVect)
	{
		return Vector4( -aVect.x, -aVect.y, -aVect.z, -aVect.w);
	}

// ------------------------------------------------- Autres Operations

// Calcul de la norme
double Vector4::Norm() const
{
	return ( ( double ) sqrt( ( x*x ) + ( y*y )+ ( z*z)+ ( w*w) ) );
}
// Calcul de la norme au carre
double Vector4::SquaredNorm() const
{
	return ( ( x*x ) + ( y*y ) + ( z*z) + ( w*w)  );
}

// Calcul de vecteur unitaire correspondant

Vector4 Vector4::Normalize()
{
	double temp = Norm();

	if ( temp <= NILLTHRESHOLD)
	{
		return Vector4(0.0f, 0.0f, 0.0f,0.0f);
	}

	x /= temp;
	y /= temp;
	z /= temp;
	w /= temp;

	return Vector4(x,y,z,w);
}


	// Copie du vecteur et mise a la norme
Vector4 Vector4::CopyAndNormalize()
{
	double tempX = x;
	double tempY = y;
	double tempZ = z;
	double tempW = w;

	double temp = Norm();

	if ( temp <= NILLTHRESHOLD)
	{
		return Vector4(0.0f, 0.0f, 0.0f, 0.0f);
	}

	tempX /= temp;
	tempY /= temp;
	tempZ /= temp;
	tempW /= temp;


	return Vector4(tempX,tempY,tempZ,tempW);
}

//Modification des valeurs
void Vector4::Set(double aX, double aY, double aZ, double aW)
{
	x=aX;
	y=aY;
	z=aZ;
	w=aW;
}

// Recuperation des valeurs
double Vector4::GetX()
{
	return x;
}
double Vector4::GetY()
{
	return y;
}
double Vector4::GetZ()
{
	return z;
}
double Vector4::GetW()
{
	return w;
}


