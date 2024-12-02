Beginning of Repo. Creating this to cover thought processes when solving these problems. 


Day 1 part 1: 
    Problem: 
        List of possible locations is Empty. 
        A series of notes and lists of locations has been found. 
            Locations have a Location ID, no names. 
            The lists aren't very similar. Need to reconcile the lists. 
            Need to determine the differences in locations by comparing smallest number in list A to smallest in list B. 
                NOTE: Will need to sort the list to be in order for us to do this. 
            Need to get the difference between the two numbers and add to the total. 

    Plan: 
        My plan is to read in the input line by line and organize into a vector or queue. 
            As I'm reading the items in, I will try to perform the sort at that time to save on multiple passes. 
            Once the lists are individually sorted I will run through both of them and get the difference per elements of the lists, adding to a running total. 

    Solution: 
        I read in each list using fstream and sorted as we went, I'm not sure if this is the best approach as each sort has to occur every time we add an element. Need to see if it'd be better to just wait til all elements are entered before running the sort. After that I just looped through both new vectors and added the total based on the absolute value of first minus second. This worked just fine and was a fairly quick operation.

Day 1 part 2: 
    Problem: 
        The lists are incorrect, or there was bad handwriting. 
        We need to look for how often each number in the first list appears in the second list, then add up each number that appears in both multiplied by the number of times it appears in the second list. 

    Plan: 
        Since the list is already sorted, we can just do a nested loop and create a count for each number. Once we hit the first value that is greater than the current number, we can exit early. When that occurs, we simply take the count and multiply it by the number and add it to our total. 

    Solution:
        Planned solution worked like a charm. Seemed very quick, and I think the early exit definitely helped the runtime. Not sure if this is the best solution, but it seems pretty good to me. 


