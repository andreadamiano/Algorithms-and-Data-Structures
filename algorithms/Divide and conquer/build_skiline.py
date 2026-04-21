from sortedcontainers import SortedList

def build_skiline(buildings: list):
    result = []
    points = []
    heights = SortedList([0])
    ongoing_height = 0
    for build in buildings:
        points.append([build[0], -build[2]]) #mark the starting of the building by marking the height as negative 
        points.append([build[1], build[2]])
    
    print(sorted(points, key=lambda x: x[0]))

    for x, height in sorted(points, key=lambda x:x[0]):
        if height < 0:
            heights.add(-height) #O(nlogn)
        else:
            heights.remove(height) #O(nlogn)

        max_height = heights[-1]
        if ongoing_height != max_height:
            ongoing_height = max_height
            result.append((x, ongoing_height))

    return result
        

if __name__ == "__main__":
    buldings = [[2,9,10],[3,7,15],[5,12,12],[15,20,10],[19,24,8]]
    print(build_skiline(buldings))