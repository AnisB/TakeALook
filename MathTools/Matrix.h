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




#ifndef __MATRIX_H__
#define __MATRIX_H__

//------------------------------------------------ Includes
#include <iostream>
#include <math.h>
#include "Vector3.h"



namespace Inertia
{
using namespace std;



template <class T> class T_Matrix
 {
     public:
	   //------------------------------------------------ Attributs
       // Coeffs de la matrice
       T **P;
       // Nombre de lignes
       int dimRows;
       // Number of Columns
       int dimColumns;

       //------------------------------------------------ Constructeurs
       // Constructeur pour une matrice carrée
       T_Matrix(int aDimension);
       // Constructeur d'une matrice rectangulaire
       T_Matrix(int nbRows,int nbColumns);
       // Constructeur de copie
       T_Matrix(const T_Matrix<T>& aMatrix);
       //------------------------------------------------ Destructeurs
       ~T_Matrix();



       //------------------------------------------------ Autres méthodes

       // Remise à zero
       void Reinitiate();

       // Libération de la mémoire
       void Free();

       // Changement dynamique de taille pour une matrice rectangulaire
       void Resize(int newRows,int newColumns);

       // Changement dynamique de taille pour une matrice carrée
       void Resize(int newDimension);

       // Remplissage par flux
       void in(T*);

       // Surcharge sortie standard
       ostream& out(ostream&) const;

      //------------------------------------------------- Proprietes intéressantes d'une matrice
       // Calcul de la matrice cofacteur
       T_Matrix Cofactor();

       // Calcul du cofacteur correspondant a l'element (i,j) de la matrice
       T Cofactor(int i, int j);


       T minor(int, int);

       // Calcul du determinant
       T Determinant();

       // Transposition
       void Transpose();


       // Inverse d'une matrice
       void Reverse();


       // Transposition et cofacteur
       void CofactorAndTranspose();


       //------------------------------------------------- Surcharge d'operateurs

       // Surcharge de l'attribution
       T_Matrix<T>& operator=(const T_Matrix<T>&);


       // Surcharge de la matrice de signe opposé
       T_Matrix<T> operator-();

       //Surcharge de l'addition
       T_Matrix<T> operator+(const T_Matrix<T>&) ;

       //Surcharge de la soustraction
       T_Matrix<T> operator-(const T_Matrix<T>&);

       //Surcharge du produit matriciel
       T_Matrix<T> operator*(const T_Matrix<T>&);

       //Surcharge du produit Matrice/Vecteur
	   Vector3	  operator*(const Vector3&);

       //Surcharge du produit scalaire Matrice/scalaire
       T_Matrix<T> operator*(const T);


       //Surcharge du produit scalaire Matrice/scalaire
       T_Matrix<T> operator*=(const T);

     private:
       // Méthode de calcul de determinant pour une matrice 3x3
       T Determinant3x3();

       // Méthode de calcul de determinant pour une matrice 2x2
       T Determinant2x2();

       T_Matrix<T> matrix4minor(int,int);
       T_Matrix<T> mul(const T_Matrix<T>&);
 };
}
#include "Matrix.ih"

 //---------------------------------------------------------------------------
  #endif
