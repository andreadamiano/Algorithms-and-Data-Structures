def video_stiching(clips: list, time):
    coverage = [0] * (time+1)

    for clip in clips:
        start, end = clip[0], clip[1]
        if start <= time:
            coverage[start] = max(coverage[start], end)

    print(coverage)

    end = furthest = n_clips = 0
    i = 0

    while end < time:
        n_clips += 1
        while i <= end and i <= time:
            furthest = max(furthest, coverage[i])
            i += 1

        if furthest <= end:
            return -1
        
        end = furthest


    return n_clips






if __name__ == "__main__":
    # clips = [[0,2],[4,6],[8,10],[1,9],[1,5],[5,9]]
    # time = 10
    # clips = [[0,1],[1,2]]
    # time = 5
    clips = [[5,7],[1,8],[0,0],[2,3],[4,5],[0,6],[5,10],[7,10]]
    time = 5
    print(video_stiching(clips, time))