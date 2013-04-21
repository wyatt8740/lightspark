/**************************************************************************
    Lightspark, a free flash player implementation

    Copyright (C) 2013  Antti Ajanki (antti.ajanki@iki.fi)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************************/

#include "scripting/flash/display/GraphicsBitmapFill.h"
#include "scripting/flash/display/BitmapData.h"
#include "scripting/flash/geom/flashgeom.h"
#include "scripting/class.h"
#include "scripting/argconv.h"

using namespace lightspark;

GraphicsBitmapFill::GraphicsBitmapFill(Class_base* c):
	ASObject(c), repeat(true), smooth(false)
{
}

void GraphicsBitmapFill::sinit(Class_base* c)
{
	c->setConstructor(Class<IFunction>::getFunction(_constructor));
	c->setSuper(Class<ASObject>::getRef());

	REGISTER_GETTER_SETTER(c, bitmapData);
	REGISTER_GETTER_SETTER(c, matrix);
	REGISTER_GETTER_SETTER(c, repeat);
	REGISTER_GETTER_SETTER(c, smooth);

	c->addImplementedInterface(InterfaceClass<IGraphicsFill>::getClass());
	IGraphicsFill::linkTraits(c);
	c->addImplementedInterface(InterfaceClass<IGraphicsData>::getClass());
	IGraphicsData::linkTraits(c);
}

ASFUNCTIONBODY(GraphicsBitmapFill, _constructor)
{
	GraphicsBitmapFill* th = obj->as<GraphicsBitmapFill>();
	ASObject::_constructor(obj,NULL,0);
	ARG_UNPACK (th->bitmapData, NullRef) (th->matrix, NullRef) (th->repeat, true) (th->smooth, false);
	return NULL;
}

ASFUNCTIONBODY_GETTER_SETTER(GraphicsBitmapFill, bitmapData);
ASFUNCTIONBODY_GETTER_SETTER(GraphicsBitmapFill, matrix);
ASFUNCTIONBODY_GETTER_SETTER(GraphicsBitmapFill, repeat);
ASFUNCTIONBODY_GETTER_SETTER(GraphicsBitmapFill, smooth);

FILLSTYLE GraphicsBitmapFill::toFillStyle()
{
	return Graphics::createBitmapFill(bitmapData, matrix, repeat, smooth);
}

void GraphicsBitmapFill::appendToTokens(std::vector<GeomToken>& tokens)
{

	tokens.emplace_back(GeomToken(SET_FILL, toFillStyle()));
}