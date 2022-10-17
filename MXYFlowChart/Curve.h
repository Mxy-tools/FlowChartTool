#pragma once

#include "utils.h"

/*!
 * \class	Curve
 *
 * \brief	曲线.
 *
 * \author	xllin
 * \date	2021/2/23
 */

class Curve
{
public:
	vector<Q_PointF>Generate(const vector<Q_PointF>& _points)
	{
		if (_points.size() < 2)
			return vector<Q_PointF>();
		else if (_points.size() == 2)
			return _points;
		else
			return getCurvePoints(t, _points);
	}

private:
	double t = 0.3;
};