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



#include "Vector3.h"
#include <iostream>
#include "math.h"



const double NILLTHRESHOLD=0.0001f;
Vector3::Vector3 ( ):x(0),y(0),z(0)
{
	// std::cout<<"Appel du constructeur par defaut"<<std::endl;
}
Vector3::Vector3 ( double anX,double anY,double aZ):x(anX),y(anY),z(aZ)
{
	// std::cout<<"Appel du constructeur par valeurs"<<std::endl;
}


Vector3::Vector3 (const Vector3& OtherVector)
{
	x=OtherVector.x;
	y=OtherVector.y;
	z=OtherVector.z;
}
Vector3::~Vector3 ( )
{
	// std::cout<<"Appel du destructeur"<<std::endl;
}

void Vector3::debugDisplay()
{
	std::cout<<"Vector3("<<x<<", "<<y<<", "<<z<<")."<<std::endl;
}



// Surcharge d'operateurs
// ---------------------------------------------------------------

// ------------------------------------------------- L'Addition
//Surcharge de +
Vector3 operator+ (const Vector3& A, const Vector3& B)
{
	return Vector3(A.x+B.x,A.y+B.y,A.z+B.z);
}
		//Surcharge de +=
void operator+= (Vector3& A, const Vector3& B)
{
	A.x += B.x;

	A.y += B.y;

	A.z += B.z;
}


//Surcharge de =
Vector3& Vector3::operator= ( const Vector3& B)
{
(*this).x = B.x;

(*this).y = B.y;

(*this).z = B.z;

return *this;
}

// ------------------------------------------------- La soustraction
//Surcharge de -
Vector3 operator- ( const Vector3& A, const Vector3& B )
{
	return Vector3(A.x-B.x,A.y-B.y,A.z-B.z);
}
void operator-= (Vector3& A, const Vector3& B)
{
	A.x -= B.x;

	A.y -= B.y;

	A.z -= B.z;
}
// ------------------------------------------------- La multiplication
// Par un vector
	//Surcharge de *
double operator* (const Vector3& A, const Vector3& B)
{
	return (A.x*B.x + A.y*B.y + A.z*B.z);
}

// Par un facteur
//Surcharge de *
Vector3 operator* (const Vector3& A, const double k)
{
	return Vector3( A.x*k, A.y*k, A.z*k );
}

//Surcharge de *
Vector3 operator* (const double k, const Vector3& A)
{
	return Vector3(A.x*k,A.y*k,A.z*k);
}

// La division par un facteur


//Surcharge de /
Vector3 operator/ (const Vector3& A, const double k)
{
	return Vector3( A.x/k, A.y/k, A.z/k );
}

//Surcharge de /
Vector3 operator/ (const double k, const Vector3& A)
{
	return Vector3( A.x/k, A.y/k, A.z/k );
}

// L'egalite
//Surcharge de ==
bool operator==(const Vector3& A, const Vector3& B)
{
	if((A.x==B.x) && (A.y==B.y) && (A.z==B.z))
	{
		return true;
	}
	return false;
}
//Surcharge de !=
bool operator!=(const Vector3& A, const Vector3& B)
{
	if( (A.x!=B.x) || (A.y!=B.y) || (A.z!=B.z) )
	{
		return true;
	}
	return false;
}

// ------------------------------------------------- L'Oppose
//Surcharge de -
	Vector3 operator- (const Vector3& aVect)
	{
		return Vector3( -aVect.x, -aVect.y, -aVect.z);
	}
// ------------------------------------------------- Autres Operations
// Produit vectoriel
Vector3 Vector3::Cross ( const Vector3& aVect )
{
	return Vector3( (y*aVect.z) - (z*aVect.y), (z*aVect.x) - (x*aVect.z), (x*aVect.y) - (y*aVect.x)  ) ;
}

// Calcul de la norme
double Vector3::Norm() const
{
	return ( ( double ) sqrt( ( x*x ) + ( y*y )+ ( z*z) ) );
}
// Calcul de la norme au carre
double Vector3::SquaredNorm() const
{
	return ( ( x*x ) + ( y*y )+ ( z*z) );
}

// Calcul de vecteur unitaire correspondant

Vector3 Vector3::Normalize()
{
	double temp = Norm();

	if ( temp <= NILLTHRESHOLD)
	{
		return Vector3(0.0f, 0.0f, 0.0f);
	}

	x /= temp;
	y /= temp;
	z /= temp;

	return Vector3(x,y,z);
}


	// Copie du vecteur et mise a la norme
Vector3 Vector3::CopyAndNormalize()
{
	double tempX = x;
	double tempY = y;
	double tempZ = z;

	double temp = Norm();

	if ( temp <= NILLTHRESHOLD)
	{
		return Vector3(0.0f, 0.0f, 0.0f);
	}

	tempX /= temp;
	tempY /= temp;
	tempZ /= temp;
	return Vector3(tempX,tempY,tempZ);
}

//Modification des valeurs
void Vector3::Set(double aX, double aY, double aZ)
{
	x=aX;
	y=aY;
	z=aZ;
}

// Recuperation des valeurs
double Vector3::GetX()
{
	return x;
}
double Vector3::GetY()
{
	return y;
}
double Vector3::GetZ()
{
	return z;
}




