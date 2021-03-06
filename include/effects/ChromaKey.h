/**
 * @file
 * @brief Header file for ChromaKey class
 * @author Jonathan Thomas <jonathan@openshot.org>
 *
 * @section LICENSE
 *
 * Copyright (c) 2008-2014 OpenShot Studios, LLC
 * <http://www.openshotstudios.com/>. This file is part of
 * OpenShot Library (libopenshot), an open-source project dedicated to
 * delivering high quality video editing and animation solutions to the
 * world. For more information visit <http://www.openshot.org/>.
 *
 * OpenShot Library (libopenshot) is free software: you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * OpenShot Library (libopenshot) is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with OpenShot Library. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef OPENSHOT_CHROMAKEY_EFFECT_H
#define OPENSHOT_CHROMAKEY_EFFECT_H

#include "../EffectBase.h"

#include <cmath>
#include <ctime>
#include <iostream>
#include <omp.h>
#include <stdio.h>
#include <memory>
#include "../Color.h"
#include "../Exceptions.h"
#include "../KeyFrame.h"

using namespace std;

namespace openshot
{

	/**
	 * @brief This class uses the ImageMagick++ libraries, to remove (i.e. key out) a color (i.e. greenscreen)
	 *
	 * The greenscreen / bluescreen effect replaces matching colors in the video image with
	 * transparent pixels, revealing lower layers in the timeline.
	 */
	class ChromaKey : public EffectBase
	{
	private:
		Color color;
		Keyframe fuzz;

		/// Init effect settings
		void init_effect_details();

	public:

		/// Blank constructor, useful when using Json to load the effect properties
		ChromaKey();

		/// Default constructor, which takes an openshot::Color object and a 'fuzz' factor, which
		/// is used to determine how similar colored pixels are matched. The higher the fuzz, the
		/// more colors are matched.
		///
		/// @param color The color to match
		/// @param fuzz The fuzz factor (or threshhold)
		ChromaKey(Color color, Keyframe fuzz);

		/// @brief This method is required for all derived classes of EffectBase, and returns a
		/// modified openshot::Frame object
		///
		/// The frame object is passed into this method, and a frame_number is passed in which
		/// tells the effect which settings to use from it's keyframes (starting at 1).
		///
		/// @returns The modified openshot::Frame object
		/// @param frame The frame object that needs the effect applied to it
		/// @param frame_number The frame number (starting at 1) of the effect on the timeline.
		std::shared_ptr<Frame> GetFrame(std::shared_ptr<Frame> frame, long int frame_number);

		/// Get and Set JSON methods
		string Json(); ///< Generate JSON string of this object
		void SetJson(string value) throw(InvalidJSON); ///< Load JSON string into this object
		Json::Value JsonValue(); ///< Generate Json::JsonValue for this object
		void SetJsonValue(Json::Value root); ///< Load Json::JsonValue into this object

		// Get all properties for a specific frame
		string PropertiesJSON(long int requested_frame);
	};

}

#endif
