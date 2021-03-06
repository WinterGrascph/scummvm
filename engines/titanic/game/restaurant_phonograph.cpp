/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#include "titanic/game/restaurant_phonograph.h"

namespace Titanic {

CRestaurantPhonograph::CRestaurantPhonograph() : CPhonograph(),
	_fieldF8(1), _field114(0) {}

void CRestaurantPhonograph::save(SimpleFile *file, int indent) {
	file->writeNumberLine(1, indent);
	file->writeNumberLine(_fieldF8, indent);
	file->writeQuotedLine(_string2, indent);
	file->writeQuotedLine(_string3, indent);

	file->writeNumberLine(_field114, indent);

	CPhonograph::save(file, indent);
}

void CRestaurantPhonograph::load(SimpleFile *file) {
	file->readNumber();
	_fieldF8 = file->readNumber();
	_string2 = file->readString();
	_string3 = file->readString();
	_field114 = file->readNumber();

	CPhonograph::load(file);
}

} // End of namespace Titanic
