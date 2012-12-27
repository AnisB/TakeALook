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


#include "Rendering/Renderer.h"
int main()
{
	Renderer aRenderer;
	aRenderer.loadMap("../Maps/sea.map");
	//aRenderer.setCamera(Vector3(2000,-1000,900),Vector3(0,1000,920));
	//aRenderer.setCamera(Vector3(3110,-900,4000),Vector3(-2100,270,920));

	aRenderer.setCamera(Vector3(60,-50,40),Vector3(-100,20,10));
	//aRenderer.addLight(Vector3(100.0,100.0,100.0));
	aRenderer.render();
}
