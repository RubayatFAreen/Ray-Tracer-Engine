#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>
#include <SDL.h>
#include "qbImage.hpp"
#include "camera.hpp"
#include "objsphere.hpp"
#include "objplane.hpp"
#include "pointlight.hpp"

namespace qbRT
{
	class Scene
	{
	public:
		// The default constructor.
		Scene();

		// Function to perform the rendering.
		bool Render(qbImage& outputImage);

		// Private functions.
	private:

		// Private members.
	private:
		// The camera that we will use.
		qbRT::Camera m_camera;

		// The list of objects in the scene.
		std::vector<std::shared_ptr<qbRT::ObjectBase>> m_objectList;

		// The list of lights in the scene.
		std::vector<std::shared_ptr<qbRT::LightBase>> m_lightList;
	};
}

#endif