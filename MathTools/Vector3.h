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


#ifndef VECTOR3_H_
#define VECTOR3_H_




class Vector3
{
private :

	double x,y,z;

public:
//-------------------------------------------- Constructeurs

	// Constructeur par defaut
	Vector3 ( );

	// Contructeur par valeur
	Vector3 ( double anX,double anY,double aZ);


	//Constructeur par copie
	Vector3(const Vector3& OtherV);

//--------------------------------------------- Destructeurs
	virtual ~Vector3 ( );

//--------------------------------------------- AffichageDeDebug
	void debugDisplay();


// ---------------------------------------------------------------
// Surcharge d'operateurs
// ---------------------------------------------------------------

// L'Addition
	//Surcharge de +
		friend Vector3 operator+ ( const Vector3& A , const Vector3& B);
	//Surcharge de +=
		friend void operator+= ( Vector3& A, const Vector3& B);



// L'egalite
	//Surcharge de =
		Vector3& operator= ( const Vector3& B);


// La soustraction
	//Surcharge de -
		friend Vector3 operator- ( const Vector3& A, const Vector3& B);

	//Surcharge de -=
		friend void operator-= ( Vector3& A, const Vector3& B);

//  La multiplication
// Par un vector
	//Surcharge de *
		friend double operator *( const Vector3& A, const Vector3& B);

// Par un facteur
	//Surcharge de *
		friend Vector3 operator* ( const Vector3& A, const double k);

	//Surcharge de *
		friend Vector3 operator * (const double k, const Vector3& A);

// La division par un facteur
	//Surcharge de /
		friend Vector3 operator/ (const Vector3& A,const double k);

	//Surcharge de /
		friend Vector3 operator/ (const double k, const Vector3& A);

// L'egalite
	//Surcharge de ==
		friend bool operator== ( const Vector3& A, const Vector3& B);

	//Surcharge de !=
		friend bool operator!= ( const Vector3& A, const Vector3& B);

// L'Oppose
	//Surcharge de -
		friend Vector3 operator- (const Vector3& aVect);

//  Autres Operations
	// Produit Vectoriel
		Vector3 Cross (const Vector3& V) ;

	// Calcul de la norme
		double Norm() const;
	// Calcul de la norme au carre
		double SquaredNorm() const ;

	// Calcul de vecteur unitaire correspondant
		Vector3 Normalize();

	// Copie du vecteur et mise a la norme
		Vector3 CopyAndNormalize();

	//Modification des valeurs
		void Set(double ax, double ay, double az);

	// Recuperation des valeurs
		double GetX();
		double GetY();
		double GetZ();

};

#include "Vector3.ih"
#endif /* VECTOR3_H_ */
