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

#ifndef MAP_H_
#define MAP_H_

#include "../../MathTools/Matrix.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "../../Types.h"

class Map {
public:
	Map(std::string aFile);
	virtual ~Map();
	void rafiner();
	T_Matrix<double> * getMap(){ return mInitialMap ;}
	TALColor getColor(int h);
	double scale;
protected :
	void parseMyFile();

protected :

	std::string mFile;
	T_Matrix<double> * mInitialMap;
	std::map<HRange, TALColor > colorMap;
};

#endif /* MAP_H_ */
