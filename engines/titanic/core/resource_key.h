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

#ifndef TITANIC_RESOURCE_KEY_H
#define TITANIC_RESOURCE_KEY_H

#include "titanic/support/string.h"
#include "titanic/core/saveable_object.h"

namespace Titanic {

class CResourceKey: public CSaveableObject {
private:
	CString _key;
	CString _value;

	void setValue(const CString &name);
public:
	CLASSDEF;
	CResourceKey() {}
	CResourceKey(const CString &name) { setValue(name); }

	/**
	 * Save the data for the class to file
	 */
	virtual void save(SimpleFile *file, int indent);

	/**
	 * Load the data for the class from file
	 */
	virtual void load(SimpleFile *file);

	/**
	 * Return the key
	 */
	const CString &getString() const { return _key; }

	/**
	 * Checks whether a file for the given key exists,
	 * and returns it's filename if it does
	 */
	CString exists() const;

	/**
	 * Scans for a file with a matching name
	 */
	bool scanForFile() const;

	/**
	 * Returns the type of the resource based on it's extension
	 */
	FileType fileTypeSuffix() const;

	/**
	 * Returns the type of the resource based on it's extension
	 */
	ImageType imageTypeSuffix() const;
};

} // End of namespace Titanic

#endif /* TITANIC_RESOURCE_KEY_H */
