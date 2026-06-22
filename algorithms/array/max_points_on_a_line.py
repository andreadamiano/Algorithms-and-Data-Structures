from collections import defaultdict

def max_points(ponits):
    points_len = len(points)
    max_points = 0

    if points_len <= 2:
        return points_len

    for i in range(points_len):
        points_on_a_line = defaultdict(lambda : 1)
        duplicate_points = 0
        for j in range(points_len):
            if i == j:
                continue
                
            if points[i][0] == points[j][0]:
                if points[i][1] == points[j][1]:
                    duplicate_points += 1
                else:
                    points_on_a_line[float("inf")] += 1
            else:
                slope = (points[i][1] - points[j][1]) / (points[i][0] - points[j][0])
                points_on_a_line[slope] += 1

        max_points = max(max_points, max(points_on_a_line.values()) + duplicate_points)

    return max_points
            

if __name__ == "__main__":
    points = [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
    print(max_points(points))