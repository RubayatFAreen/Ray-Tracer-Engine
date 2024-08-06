#include "pointlight.hpp"

qbRT::PointLight::PointLight()
{
	m_color = qbVector<double>{ std::vector<double> {1.0, 1.0, 1.0} };
	m_intensity = 1.0;
}

qbRT::PointLight::~PointLight()
{

}

bool qbRT::PointLight::ComputeIllumination(const qbVector<double>& intPoint, const qbVector<double>& localNormal,
	const std::vector<std::shared_ptr<qbRT::ObjectBase>>& objectList,
	const std::shared_ptr<qbRT::ObjectBase>& currentObject,
	qbVector<double>& color, double& intensity)
{
	// Construct a vector pointing from the intersection point to the light.
	qbVector<double> lightDir = (m_location - intPoint).Normalized();

	// Compute a starting point. 
	qbVector<double> startPoint = intPoint;
	
	// Construct a ray from the point of intersection to the light. 
	qbRT::Ray lightRay(startPoint, startPoint + lightDir);
	qbVector<double> poi		{ 3 };
	qbVector<double> poiNormal	{ 3 };
	qbVector<double> poiColor	{ 3 };
	bool validInt = false;
	for (auto sceneObject : objectList)
	{
		if (sceneObject != currentObject)
		{
			validInt = sceneObject->TestIntersection(lightRay, poi, poiNormal, poiColor);
		}

		if (validInt)
			break;
	}

	if (!validInt)
	{
		// Compute the angle between the local normal and light ray
		// Note that we assume that localNormal is a unit vector. 
		double angle = acos(qbVector<double>::dot(localNormal, lightDir));
		if (angle > 1.5708)
		{
			// No illumination
			color = m_color;
			intensity = 0.0;
			return false;
		}
		else 
		{
			color = m_color;
			intensity = m_intensity * (1.0 - (angle / 1.5708));
			return true;
		}
	}
	else
	{
		// Shadow Condition
		color = m_color;
		intensity = 0.0;
		return false;
	}
}