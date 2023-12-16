/* 
 * Description: 二维几何算法
 * Create: 2023-12-12
 * Owner: 
 */

#ifndef GEO_ALGORITHM 
#define GEO_ALGORITHM

#include <cmath>

namespace GeoAlgorithm{

/**
 * 计算两点的平方距离
 * @tparam PointT
 * @param p1
 * @param p2
 * @return double
*/
template <typename PointT>
inline double SquareDistance(const PointT& p1, const PointT& p2)
{
    return static_cast<double>(p1.x() - p2.x()) * static_cast<double>(p1.x() - p2.x()) +
           static_cast<double>(p1.y() - p2.y()) * static_cast<double>(p1.y() - p2.y());
}

/**
 * 计算两点的距离
 * @tparam PointT
 * @param p1
 * @param p2
 * @return double
*/
template <typename PointT>
inline double Distance(const PointT& p1, const PointT& p2)
{
    return std::sqrt(SquareDistance(p1, p2));
}

}

#endif // GEO_ALGORITHM