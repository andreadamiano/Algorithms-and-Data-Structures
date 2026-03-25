import heapq

def get_order(tasks: list):
    available_tasks = []
    response = []

    #sort tasks 
    tasks = sorted([(task[0], task[1], index) for index, task in enumerate(tasks)])
    print(tasks)

    time = tasks[0][0]
    index = 0

    while len(response) < len(tasks):
        #append new tasks as the other task gets processed
        while (index < len(tasks)) and (tasks[index][0] <= time):
            heapq.heappush(available_tasks, (tasks[index][1], tasks[index][2]))  #min heap ordered based on processing time
            index += 1

        #pop new task
        if available_tasks:
            current_task = heapq.heappop(available_tasks)
            time += current_task[0]  
            response.append(current_task[1])

        elif index < len(tasks):
            #spin wait 
            time = tasks[index][0]  #the next time available to start a task is the immediately next task in the sorted list of tasks 
    
    return response
            

        
        



if __name__ == "__main__":
    # tasks = [[1,2],[2,4],[3,2],[4,1]]
    tasks = [[7,10],[7,12],[7,5],[7,4],[7,2]]
    tasks = [[9,10],[9,12],[9,5],[7,1]]
    print(get_order(tasks))