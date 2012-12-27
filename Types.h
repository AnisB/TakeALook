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

#pragma once
#include <map>

class HRange
{
	public:
	int l;
	int h;

	HRange(int al,int ah)
	{
		this->l=al;
		this->h=ah;
	}
	HRange(const HRange & aRange)
	{
		this->l=aRange.l;
		this->h=aRange.h;
	}
	void operator=(const HRange & aRange)
	{
		this->l=aRange.l;
		this->h=aRange.h;
	}
	bool operator<( HRange  aRange)
	{
		return(this->h<=aRange.l);

	}
};
class TALColor
{
	public:
	int r;
	int g;
	int b;
	int a;
	TALColor()
	{
		this->r=255;
		this->g=255;
		this->b=255;
		this->a=255;
	}
	TALColor(const TALColor & aColor)
	{
		this->r=aColor.r;
		this->g=aColor.g;
		this->b=aColor.b;
		this->a=aColor.a;
	}
	void operator=(const TALColor & aColor)
	{
		this->r=aColor.r;
		this->g=aColor.g;
		this->b=aColor.b;
		this->a=aColor.a;
	}
};
typedef struct t_Point
{
	double x;
	double y;
} Point;

typedef struct t_Triangle
{
	Point mP1;
	Point mP2;
	Point mP3;
	double r;
	double g;
	double b;
	double a;
} Triangle;

 struct Line
{
	Point mP1;
	Point mP2;
	Point mP3;
	double r;
	double g;
	double b;
	double a;
} ;





