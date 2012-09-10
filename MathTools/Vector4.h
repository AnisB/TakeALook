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


#ifndef Vector4_H_
#define Vector4_H_



namespace Inertia
{
class Vector4
{
public :

	double x,y,z,w;

public:
//-------------------------------------------- Constructeurs

	// Constructeur par defaut
	Vector4 ( );
	// Contructeur par valeur
	Vector4 ( double anX,double anY,double aZ, double anW);
	//Constructeur par copie
	Vector4(const Vector4& OtherV);

//--------------------------------------------- Destructeurs
	virtual ~Vector4 ( );

//--------------------------------------------- AffichageDeDebug
	void debugDisplay();


// ---------------------------------------------------------------
// Surcharge d'operateurs
// ---------------------------------------------------------------

// ------------------------------------------------- L'Addition
	//Surcharge de +
		friend Vector4 operator+ ( const Vector4& A , const Vector4& B);
		//Surcharge de +=
			friend void operator+= ( Vector4& A, const Vector4& B);

// ------------------------------------------------- La soustraction
		//Surcharge de -
		friend Vector4 operator- ( const Vector4& A, const Vector4& B);

		//Surcharge de -=
		friend void operator-= ( Vector4& A, const Vector4& B);

// ------------------------------------------------- La multiplication
		// Par un vector
			//Surcharge de *
			friend double operator *( const Vector4& A, const Vector4& B);

		// Par un facteur
		//Surcharge de *
			friend Vector4 operator* ( const Vector4& A, const double k);

		//Surcharge de *
			friend Vector4 operator * (const double k, const Vector4& A);

// -------------------------------------------------- La division par un facteur
		//Surcharge de /
			friend Vector4 operator/ (const Vector4& A,const double k);

		//Surcharge de /
			friend Vector4 operator/ (const double k, const Vector4& A);

		// L'egalite
		//Surcharge de ==
			friend bool operator== ( const Vector4& A, const Vector4& B);

		//Surcharge de !=
			friend bool operator!= ( const Vector4& A, const Vector4& B);

// ------------------------------------------------- L'Oppose
		//Surcharge de -
			friend Vector4 operator- (const Vector4& aVect);

// ------------------------------------------------- Autres Operations

	// Calcul de la norme
	double Norm() const;
	// Calcul de la norme au carre
	double SquaredNorm() const ;

	// Calcul de vecteur unitaire correspondant
	Vector4 Normalize();

	// Copie du vecteur et mise a la norme
	Vector4 CopyAndNormalize();

	//Modification des valeurs
	void Set(double aX, double aY, double aZ, double aW);

	// Recuperation des valeurs
	double GetX();
	double GetY();
	double GetZ();
	double GetW();
};
}
#endif /* Vector4_H_ */
