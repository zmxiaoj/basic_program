#include <bits/stdc++.h>


struct Point {
    double x, y;
    int cluster;
    bool visited;

    Point(double _x, double _y) : x(_x), y(_y), cluster(-1), visited(false) {}


    bool operator==(const Point& other) const {
        // return (x == other.x && y == other.y);
        return (this->x == other.x && this->y == other.y);
    }

    bool operator!=(const Point& other) const {
        return !(*this == other);
    }
};



int main()
{
    auto distanceEuclid = [&](Point a, Point b) -> double {
        return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
    };
    auto getNeighbours = [&](std::vector<Point>& points, int pointIdx, double eps) 
        -> std::pair<std::vector<Point>, std::vector<int>> {
            std::vector<Point> neighbours;
            std::vector<int> neighboursIdx;
            std::pair<std::vector<Point>, std::vector<int>> result;
            // for (auto& p : points) {
            //     if (p != point && distanceEuclid(point, p) <= eps) {
            //         neighbours.push_back(p);
            //     }
            // }
            for (int i = 0; i < points.size(); i++) {
                if (i != pointIdx && distanceEuclid(points[pointIdx], points[i]) <= eps) {
                    neighbours.push_back(points[i]);
                    neighboursIdx.push_back(i);
                }
            }
            result = std::make_pair(neighbours, neighboursIdx);
            return result;
        };

    auto dbscan = [&](std::vector<Point>& points, double eps, int minPts) -> void {
        // clusterIdx = -1 - noise
        int currClusterIdx = 0;
        std::vector<std::vector<Point>> clusterPoint;
        std::vector<std::vector<int>> clusterPointIdx;

        while (true) {
            auto unvisitedPoints = std::find_if(points.begin(), points.end(), [](Point p){return p.visited == false;});
            if (unvisitedPoints == points.end()) {
                break;
            }
            unvisitedPoints->visited = true;
            int unvisitedPointsIdx = unvisitedPoints - points.begin();

            auto neighbours = getNeighbours(points, unvisitedPointsIdx, eps);
            std::vector<Point> neighboursPoints = neighbours.first;
            std::vector<int> neighboursPointsIdx = neighbours.second;
            
            if (neighboursPoints.size() < minPts) {
                unvisitedPoints->cluster = -1;
            }
            else {
                unvisitedPoints->cluster = currClusterIdx;
                std::vector<Point> cluster;
                std::vector<int> clusterIdx;

                std::vector<Point> todoPoints = neighboursPoints;
                std::vector<int> todoPointsIdx = neighboursPointsIdx;

                for (int i = 0; i< todoPoints.size(); i++) {
                    Point currentPoint = todoPoints[i];
                    int currentPointIdx = todoPointsIdx[i];

                    if (!currentPoint.visited) {
                        currentPoint.visited = true;
                        auto currentNeighbours = getNeighbours(points, currentPointIdx, eps);
                        std::vector<Point> currentNeighboursPoints = currentNeighbours.first;
                        std::vector<int> currentNeighboursPointsIdx = currentNeighbours.second;

                        if (currentNeighboursPoints.size() >= minPts) {
                            todoPoints.insert(todoPoints.end(), currentNeighboursPoints.begin(), currentNeighboursPoints.end());
                            todoPointsIdx.insert(todoPointsIdx.end(), currentNeighboursPointsIdx.begin(), currentNeighboursPointsIdx.end());
                        }
                    }
                    if (currentPoint.cluster == -1) {
                        currentPoint.cluster = currClusterIdx;
                        cluster.push_back(currentPoint);
                        clusterIdx.push_back(currClusterIdx);
                    }
                }
                clusterPoint.push_back(cluster);
                clusterPointIdx.push_back(clusterIdx);
                currClusterIdx += 1;
            }
        }
    };

    return 0;
}
