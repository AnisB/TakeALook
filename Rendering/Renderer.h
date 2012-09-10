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


#ifndef RENDERER_H_
#define RENDERER_H_


#include <list>
#include "../Objects/MovableObjects/Light.h"
#include "../Objects/MovableObjects/Camera.h"
#include <string>
class Renderer {
public:
	Renderer();
	virtual ~Renderer();
	void loadMap(std::string aFile );

protected :
	std::list<Light *> mLights;
	std::list<Camera *> mCameras;

};

#endif /* RENDERER_H_ */
