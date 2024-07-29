#include<bits/stdc++.h>


struct Point {
    std::vector<float> coordinates;

    Point(std::initializer_list<float> init) : coordinates(init) {}
};

struct Node {
    Point point;
    Node *left, *right;

    Node(const Point& pt) : point(pt), left(nullptr), right(nullptr) {}
};

class KDTree {
public:
    KDTree(std::vector<Point>& points) {
        root = build(points, 0);
    }

    ~KDTree() {
        clear(root);
    }

private:
    Node* root;

    Node* build(std::vector<Point>& points, int depth) {
        if (points.empty()) return nullptr;

        int axis = depth % points[0].coordinates.size();
        std::sort(points.begin(), points.end(), [axis](const Point& a, const Point& b) {
            return a.coordinates[axis] < b.coordinates[axis];
        });

        int median = points.size() / 2;
        Node* node = new Node(points[median]);

        std::vector<Point> left_points(points.begin(), points.begin() + median);
        std::vector<Point> right_points(points.begin() + median + 1, points.end());

        node->left = build(left_points, depth + 1);
        node->right = build(right_points, depth + 1);

        return node;
    }

    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }
};

int main()
{
    // construct KD tree

    return 0;
}