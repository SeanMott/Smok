#pragma once

//defines a camera

#include <glm/gtx/transform.hpp>

namespace Smok::ECS::Comp
{
	//defines a camera
	struct Camera
	{
		uint64_t ID = 0; //the ID associated with this component
		bool isDirty = true; //data has changed

		glm::mat4 projection = glm::mat4(1.0f), view = glm::mat4(1.0f),
			PV = glm::mat4(1.0f);

		//generates perspective
		inline glm::mat4 GeneratePerspective()
		{
			projection = glm::perspective(glm::radians(70.f), 1700.f / 900.f, 0.1f, 200.0f);
			projection[1][1] *= -1;
			return projection;
		}

		//generates view
		inline glm::mat4 GenerateView(const glm::vec3& position)
		{
			view = glm::translate(glm::mat4(1.f), position);
			return view;
		}

		//generates perspective * view
	};
}