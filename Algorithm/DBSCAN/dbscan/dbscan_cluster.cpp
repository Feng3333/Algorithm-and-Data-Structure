/* 
 * Description: DBSCAN cluster 的基本实现
 * Create: 2023-12-12
 * Owner: 
 */

#include <iostream>
#include "dbscan_cluster.h"
#include "geo_algorithm.h"

namespace DbscanCluster {

bool Dbscan::DbscanProcess(const std::vector<Point2D>& oriPoints)
{
    double e = 10.0;
    int minPts = 10;

    std::vector<std::set<int>> points;
    std::vector<std::set<int>> clusterObjects;

    points = GetPointSet(oriPoints, e);
    clusterObjects = GetCorePoint(points, minPts);


    for (int i = 0; i < clusterObjects.size(); ++i) {
        std::cout << "{";
        int count = 0;
        for (auto j = clusterObjects[i].begin(); j != clusterObjects[i].end(); ++j) {
            std::cout << *j + 1;
            if (++count < clusterObjects[i].size()) {
                std::cout << ",";
            }
        }
        std::cout << "}" << std::endl;
    }
}


std::vector<std::set<int>> Dbscan::GetPointSet(const std::vector<Point2D>& data, double e)
{
    std::vector<std::set<int>> pointSet(data.size());

    for (int i = 0; i < data.size(); ++i) {
        // 计算相邻点可以加上该点本身
        for (int j = 0; j < data.size(); ++j) {
            if(GeoAlgorithm::Distance(data[i], data[j]) < e) {
                pointSet[i].insert(j);
            }
        }
    }

    return pointSet;
}

std::vector<std::set<int>> Dbscan::GetCorePoint(std::vector<std::set<int>> points, int minPts)
{
    std::vector<bool> visited(points.size(), false);
    std::vector<std::set<int>> cluster;   // 记录每个聚类簇中的点集
    
    for (int i = 0; i < points.size(); ++i) {
        if (!visited[i]) {
            if (points[i].size() >= minPts) {
                for (std::set<int>::const_iterator j = points[i].begin(); j != points[i].end(); ++j) {
                    visited[*j] = true;
                    // 添加间接可达的点
                    if (points[*j].size() >= minPts) {
                        for (auto k = points[*j].begin(); k != points[*j].end(); ++k) {
                            visited[*k] = true;
                            points[i].insert(*k);
                        }
                    }
                }
                cluster.push_back(points[i]);
            }
        }
    }

    return cluster;
}

} // namespace DbscanCluster