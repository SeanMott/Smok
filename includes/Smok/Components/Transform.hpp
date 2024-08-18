#pragma once

//defines a transform component

#include <glm/vec3.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include <cstdint>

namespace Smok::ECS::Comp
{
	//defines a transform
	struct Transform
	{
		uint64_t ID = 0; //the ID associated with this component
		bool isDirty = true; //data has changed

		bool rotationDataIsInRadians = false; //is internal data in radians

		glm::vec3 position = { 0.0f, 0.0f, 0.0f }, eularRotation = { 0.0f, 0.0f, 0.0f },
			scale = { 1.0f, 1.0f, 1.0f };

		glm::quat rotation;

		glm::mat4 modelMatrix = glm::mat4(1.0f);

		//generates the model matrix regardless of dirty flag, does not reset dirty flag
		inline glm::mat4 GenerateModelMatrix_Forced()
		{
			modelMatrix = glm::toMat4(rotation);
			return modelMatrix;
		}

		//gets the model matrix, if dirty flag is true, will generate one and reset flag
		inline glm::mat4 ModelMatrix()
		{
			if (isDirty)
			{
				modelMatrix = GenerateModelMatrix_Forced();
				isDirty = false;
			}

			return modelMatrix;
		}

		//gets the eular rotation in radians
		inline glm::vec3 GetEularRotation_Radians() const {(rotationDataIsInRadians == true ? eularRotation : glm::radians(eularRotation));}

		//gets the eular rotation in degrees
		inline glm::vec3 GetEularRotation_Degrees() const { (rotationDataIsInRadians == false ? eularRotation : glm::degrees(eularRotation)); }

		//gets eular rotation from quaterion rotation || returned eular WILL BE in radians
		inline glm::vec3 GetEularRotationFromQuaterion() const { return glm::eulerAngles(rotation); }

		//sets the roation || assumes passed in data IS in radians || this is desired over setting directly so the dirty flag is set
		inline void SetEularRotation_Radians(const glm::vec3 rot)
		{
			eularRotation = rot;
			rotation = glm::rotate(glm::mat4(1.0f), rot.x, glm::vec3(1.0f, 0.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), rot.y, glm::vec3(0.0f, 1.0f, 0.0f)) *
				glm::rotate(glm::mat4(1.0f), rot.z, glm::vec3(0.0f, 0.0f, 1.0f));
			rotationDataIsInRadians = true;
			isDirty = true;
		}

		//sets the roation || assumes passed in data is NOT in radians || this is desired over setting directly so the dirty flag is set
		inline void SetEularRotation(const glm::vec3 rot) { SetEularRotation_Radians(rot); }
	};
}