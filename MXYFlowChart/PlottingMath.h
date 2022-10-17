#ifndef PLOTTINGMATH_H
#define PLOTTINGMATH_H

#include <math.h>
#include <vector>
#include <list>

#ifdef PI
#undef PI
#undef PI_2
#undef PI_4
#endif
const double PI = 3.14159265358979323846;
const double PI_2 = 1.57079632679489661923;
const double PI_4 = 0.78539816339744830962;
const double LN_2 = 0.69314718055994530942;
const double INVLN_2 = 1.0 / LN_2;

namespace Math {
/**
 * 计算和基准向量v夹角为a、长度为d的目标向量（理论上有两个，一左一右）
 * @param v 基准向量
 * @param a 目标向量和基准向量的夹角，默认为90度，这里的单位使用弧度
 * @param d 目标向量的长度，即模，默认为1，即单位向量
 * @return 返回目标向量数组（就两个向量，一左一右）
 */
	std::vector<std::pair<double,double>> calculateVector(std::pair<double,double> v, float a = PI_2, float d = 1.0);
/**
 * 计算两条直线的交点
 * 通过向量的思想进行计算，需要提供两个向量以及两条直线上各自一个点
 * @param v_1   直线1的向量
 * @param v_2   直线2的向量
 * @param points1   直线1上的任意一点
 * @param points2   直线2上的任意一点
 * @return 返回交点
 */
	std::pair<double,double> calculateIntersection(std::pair<double,double> v_1, std::pair<double,double> v_2, std::pair<double,double> point1, std::pair<double,double> point2);

/**
 * 计算两个向量的角平分线向量
 * @param v1 向量1
 * @param v2 向量2
 * @return 返回角平分线向量
 */
	std::pair<double,double> calculateAngularBisector(std::pair<double,double> v1, std::pair<double,double> v2);

/**
* 通过三角形的底边两端点坐标以及底边两夹角，计算第三个点坐标
* @param pointS 底边第一个点
* @param pointE 底边第二个点
* @param a_S 底边和第一个点所在的另一条边的夹角
* @param a_E 底边和第二个点所在的另一条边的夹角
* @return 返回顶点（理论上存在两个值）
*/
	std::vector<std::pair<double,double>> calculateIntersectionFromTwoCorner(std::pair<double,double> pointS, std::pair<double,double> pointE, float a_S, float a_E);
/**
 * @brief inciseBezier
 * @param pSrcPt
 * @param j
 * @param pDstPt
 */
	void inciseBezier(const std::vector<std::pair<double,double>>& pSrcPt, int j, std::vector<std::pair<double,double>>& pDstPt);
/**
 * @brief getBezierGap
 * @param pSrcPt
 * @param j
 * @return
 */
	float getBezierGap(std::vector<std::pair<double,double>>& pSrcPt, int j);
/**
 * @brief createBezier
 * @param points
 * @param precision
 * @param part
 * @return
 */
	std::vector<std::pair<double,double>> createBezier(const std::vector<std::pair<double,double>>& points, float precision = 0, int part = 20);
/**
 * @brief createBezier2
 * @param points
 * @param part
 * @return
 */
	std::vector<std::pair<double,double>> createBezier2(std::vector<std::pair<double,double>>& points, int part = 20);
/**
 * @brief createBezier3
 * @param points
 * @param part
 * @return
 */
	std::vector<std::pair<double,double>> createBezier3(const std::vector<std::pair<double,double>>& points, int part = 20);

/**
 * Method: createCloseCardinal
 * 创建闭合Cardinal的控制点。
 * 利用输入的点数组计算出相应的Cardinal控制点，再使用贝塞尔曲线3创建经过所有Cardinal控制点的圆滑闭合曲线。
 *
 * Parameters:
 * points -{Array(<SuperMap.Geometry.Point>)} 传入的待计算的初始点串。
 * Returns:
 * {Array(<SuperMap.Geometry.Point>)} 计算出相应的Cardinal控制点。
 *
 * (code)
 * var points = [];
 * points.push(new SuperMap.Geometry.Point(-50,30));
 * points.push(new SuperMap.Geometry.Point(-30,50));
 * points.push(new SuperMap.Geometry.Point(2,60));
 * points.push(new SuperMap.Geometry.Point(8,20));
 *
 * var cardinal = SuperMap.Geometry.LineString.createCloseCardinal(points);
 * (end)
 */

std::vector<std::pair<double,double>> createCloseCardinal(std::vector<std::pair<double,double>>& points);

/**
* Method: calculateMidpoint
* 计算两个点所连成的线段的的中点
*
* Parameters:
* pointA - {<SuperMap.Geometry.Point>} 第一个点
* pointB -  {<SuperMap.Geometry.Point>} 第二个点
*
* Returns:
* {<SuperMap.Geometry.Point>} 返回中点
*/

std::pair<double,double> calculateMidpoint(const std::pair<double,double>& pointA, const std::pair<double,double>& pointB);

/**
* Method: calculateDistance
* 计算两点间的距离
*
* Parameters:
* pointA - {<SuperMap.Geometry.Point>} 第一个点
* pointB -  {<SuperMap.Geometry.Point>} 第二个点
*
* Returns:
* {<SuperMap.Geometry.Point>} 返回两点间的距离值
*/
float calculateDistance(const std::pair<double,double>& pointA, const std::pair<double,double>& pointB);

/**
* Method: calculateArc
* 根据圆心、半径，与X轴的起点角和终点角计算圆弧。
*
* Parameters:
* center - {<SuperMap.Geometry.Point>} 圆心
* radius - {Number}半径
* startAngle - {Number}起点角,范围为0到2π。
* endAngle - {Number}终点角,范围为0到2π。
* direction - {Number}从起点到终点的方向，其值为1：逆时针，其值为-1：顺时针。默认为1，即逆时针。
* sides - {Number}圆弧所在圆的点数，默认为360个，即每1°一个点。
*
* Returns:
* {Array(<SuperMap.Geometry.Point>)} 圆弧上的点数组
*/

std::vector<std::pair<double,double>> calculateArc(const std::pair<double,double>& center, float radius, float startAngle, float endAngle, float direction, float sides=360);

/**
* Method: calculateAngle
* 计算圆上一点所在半径的直线与X轴的夹角，结果以弧度形式表示，范围是+π到 +2π。
*/
float calculateAngle(const std::pair<double,double>& pointA, const std::pair<double,double>& centerPoint);

typedef std::vector<std::pair<double,double>> LineString;
typedef std::vector<LineString> MultiLineString;

/**
* Method: calculateArrowLines
* 根据两点计算其所在向量的箭头（即两条直线）
*
* Parameters:
* startP - {<SuperMap.Geometry.Point>} 向量的起点
* endP -  {<SuperMap.Geometry.Point>} 向量的终点
* ratio -  {Number} 直线长度与箭头长度的比值，默认为10倍
* angle - {Number} 箭头所在直线与直线的夹角，范围为0到π，默认为Math.PI/6。
*
* Returns:
* {Array(<SuperMap.Geometry.LineString>)} 返回中点
*/

MultiLineString calculateArrowLines(const std::pair<double,double>& startP, const std::pair<double,double>& endP, float ratio = 10, float angle = PI/6);

} // namespace Math


#endif
