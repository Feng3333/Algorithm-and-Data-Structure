/* 
 * Description: DBSCAN cluster 的基本实现
 * Create: 2023-12-12
 * Owner: 
 */

#include <iostream>
#include <vector>
#include <set>
#include "point2d.h"

#ifndef DBSCAN_CLUSTER
#define DBSCAN_CLUSTER

namespace DbscanCluster {

class Dbscan {
    Dbscan() = delete;

    bool DbscanProcess(const std::vector<Point2D>& oriPoints);

    // 获取相邻的点集数据，其中std::vector<std::set<int>> int表示对应id
    std::vector<std::set<int>> GetPointSet(const std::vector<Point2D>& data, double e);
    // 筛选和获取核心聚类点
    std::vector<std::set<int>> GetCorePoint(std::vector<std::set<int>> points, int minPts);
};


} // namespace DbscanCluster

#endif // DBSCAN_CLUSTER