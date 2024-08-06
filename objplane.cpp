#include "objplane.hpp"
#include <cmath>

qbRT::ObjPlane::ObjPlane()
{

}

qbRT::ObjPlane::~ObjPlane()
{

}

bool qbRT::ObjPlane::TestIntersection(const qbRT::Ray& castRay, qbVector<double>& intPoint,
	qbVector<double>& localNormal, qbVector<double>& localColor)
{
	// Copy the ray and apply the backwards transform. 
	qbRT::Ray bckRay = m_transformMatrix.Apply(castRay, qbRT::BCKTFORM);

	// Copy the m_lab and normalize
	qbVector<double> k = bckRay.m_lab;
	k.Normalize();

	// Check for intersection.
	if (!CloseEnough(k.GetElement(2), 0.0))
	{
		// There is an intersection. 
		double t = bckRay.m_point1.GetElement(2) / -k.GetElement(2);

		// If t is negative, then the intersection point must be behind the camera. 
		if (t > 0.0)
		{
			// Compute the values for u and v. 
			double u = bckRay.m_point1.GetElement(0) + (k.GetElement(0) * t);
			double v = bckRay.m_point1.GetElement(1) + (k.GetElement(1) * t);

			// If the magnitude of both u and v is less than or equal to one
			if ((abs(u) < 1.0) && (abs(v) < 1.0))
			{
				// Compute the point of intersection. 
				qbVector<double> poi = bckRay.m_point1 + t * k;

				// Transform the intersection point back into world coordinates. 
				intPoint = m_transformMatrix.Apply(poi, qbRT::FWDTFORM);

				// Compute the lcoal normal.
				qbVector<double> localOrigin{ std::vector<double> {0.0, 0.0, 0.0} };
				qbVector<double> normalVector{ std::vector<double> {0.0, 0.0, -1.0} };
				qbVector<double> globalOrigin = m_transformMatrix.Apply(localOrigin, qbRT::FWDTFORM);
				localNormal = m_transformMatrix.Apply(normalVector, qbRT::FWDTFORM) - globalOrigin;
				localNormal.Normalize();

				// Return the color.
				localColor = m_baseColor;
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	return false;
}

