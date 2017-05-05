'''
http://www.geeksforgeeks.org/greedy-algorithms-set-1-activity-selection-problem/

You are given n activities with their start and finish times. Select the maximum number of activities that can be performed by a single person, assuming that a person can only work on a single activity at a time.
Example:

Example 1 : Consider the following 3 activities sorted by
by finish time.
     start[]  =  {10, 12, 20};
     finish[] =  {20, 25, 30};
A person can perform at most two activities. The 
maximum set of activities that can be executed 
is {0, 2} [ These are indexes in start[] and 
finish[] ]

Example 2 : Consider the following 6 activities 
sorted by by finish time.
     start[]  =  {1, 3, 0, 5, 8, 5};
     finish[] =  {2, 4, 6, 7, 9, 9};
A person can perform at most four activities. The 
maximum set of activities that can be executed 
is {0, 1, 3, 4} [ These are indexes in start[] and 
finish[] ]
'''
                    
                            # 2   [(10, 20), (12, 25), (20, 30)]
def find_next_activity(begin, sorted_activities):
    ' will find an index of next activity after `begin`'
    next_activity = begin + 1
    while next_activity < len(sorted_activities): # True
        if sorted_activities[next_activity][0] >= sorted_activities[begin][1]:
            return next_activity
        next_activity += 1 # 2

    return len(sorted_activities)

def select_activities(list_begin, list_end):
    activities = list(zip(list_begin, list_end))
    sorted_activities = sorted(activities, key=lambda x: x[1])

    activities_performed = 0
    current_activity = 0
    while current_activity < len(sorted_activities):
        current_activity = find_next_activity(current_activity, sorted_activities)
        activities_performed += 1

    return activities_performed

def test_activities():
    assert select_activities([10, 20, 12], [20, 30, 25]) == 2
    assert select_activities([1, 3, 0, 5, 8, 5], [2, 4, 6, 7, 9, 9]) == 4
    assert select_activities([1], [2]) == 1

