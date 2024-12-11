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

Day 2 part 1:
    Problem: 
        There is some unusual data. 
        The data is separated into 1 report per line(a series of numbers per line)
        Each number is a "Level" separated by spaces. 
        Reports are considered safe if the numbers in a line are all either decreasing or increasing, and any 2 adjacent numbers must change by at least 1 number but no more than 3. 
        Need to determine how many reports are safe. 
        ADDED PROBLEM STATEMENT: The number of levels isn't always consistent. 

    Plan: 
        Read in each line. At time of read in, look at each number and make sure that:
            1. Each number is either increasing or decreasing, but not both.
                Can probably do this by just determining it from the first two numbers and ensuring that the pattern continues.  
            2. Each change between numbers is between 1 and 3 inclusive.
                Easy enough, just check the diff and if it is above 3 or less than 1 exit early. 
        If both conditions are met, add 1 to total number of safe reports. 
        Need to read in all numbers per line into a temp container and then loop through that container. 

    Solution: 
        Ended up pretty similar to my expectation, but needed to look some things up. On my first attempt I didn't realize that the puzzle input may have more than 5 elements per line, which caused me to be off by quite a bit. Once I updated to be more dynamic I had to check that it was always increasing or decreasing(Turns out this is called monotonic), and while checking I went ahead and checked that it was also within our range of 1 >= x <= 3. Then I just needed to make sure that we didn't try to access/perform math on an element beyond the range of our vector. 

Day 2 Part 2: 
    Problem:
        The solution to Day 1 seems low. 1 violation per line is actually acceptable.
        If greater than 2 violations occur, then it is an invalid level. 
        Everything else remains the same. 
    Plan: 
        I think if we hit a violation we can simply remove that element and re-run, maybe add to a violation count. If violation count is ever greater than 1 we return false. Basically in the loop:
                    If we find violation check the violation count
                    if greater than 1 return false
                    else increase violation count, remove this element, decrease iterator by 1, and continue the check. 
    Solution: 
        Yeah, this one gave me massive issues and I had to rework a bit. 
        I kept the ismonotonicwithinrange and instead of doing any targeted removal I just retry it removing 1 element at a time and seeing if it works that way. 

Day 3 Part 1: 
    Problem: 
        Computer memory is corrupted. All instructions have been jumbled up. 
        Goal of program is to multiply numbers. Has instructions with a function format and two 1-3 digit numbers as input. 
        Characters that should be ignored are also part of the instructions, such as spaces and special characters.
    Plan: 
        Probably do a regex to find just mul(Numbers). Seems like we don't need to strip out excess characters from within a valid mul function call, guessing that will be part 2. 
        So format we are looking for is simply mul(X,Y) no special characters, no spaces. The call for mul CAN have things leading into it though, such as _mul(x,y) being valid. 
        Could probably skip regex and simply do a bunch of char scanning logic, but that will be a last resort. 
    Solution: 
        Basically what I said and Regex sucks. 
    
Day 3 Part 2: 
    Problem: 
        There are Do and Don't instructions that enable and disable the mul functions. 
        When Do is the last one read we continue adding the values. When Don't is the last one read we stop adding them. 
        It starts enabled. 
    Plan: 
        I'm thinking this time we read each line and look for the instances of do / don't. Basically create substrings that exist between these values and then run the regex against those. 
    Solution: 
        This one was harder than I wanted it to be for me. Had to make a function to extract the strings between do's and don't's into a new string, then ran the previous mul(x,y) parsing logic against the new string. Because it needed to be enable by default I "cheated" and added the word do to the very beginning of the input string before reading in the lines. Seems like it is O(n*m*r) which I think is sufficient. 

Day 4 Part 1: 
    Problem: 
        It's a word search. Ugh....2D array stuff again. Need to find all instances of the word XMAS forward, backward, Up, Down, and Diagnols. 
    Plan: 
        Tedious 2D Array logic. Gonna go 1 character at a time, check to see if it's an X, then check all valid directions for M, then have to continue checking solely in that direction for the A and S. Should be simple, but gonna be time consuming I think. 
    Solution: 
        Used Vectors of vectors and had no real problem with this. Solution worked on first attempt. 

Day 4 Part 2: 
    Problem: 
        It wasn't supposed to be XMAS it was suppossed to be MAS in X form as in M A S and M A S must cross. Can be forward or backwards but has to be a cross. 
    Plan: 
        This is a little more complicated, but I'm thinking about starting by looking for A's then checking the (upLeft, downRight) and (upRight, downLeft) positions for word completion. The tricky part is making sure both are true, but I think I can only check for the other if the first is correct. Can probably re-use a good portion of what I have already. 
    Solution: 
        Removed the match function and changed it to a much simpler xpattern match that was just a few conditions, also simplified the count function as it didn't need all of the direction callouts since the word find was actually simpler. Not sure if this is the most efficient, but it was the quickest to develop. 

Day 5 Part 1: 
    Problem: 
        We have two sets of inputs. 1 is rules for page updates, the other is a list of page updates to be done. We need to filter out all of the updates to be done that are invalid according to the rules, and then get the middle number for each valid update and add it to a running total. 
        Rules stipulate 2 numbers, the first is a page number, the second is what pages MUST come after it. 
        The Update list is a list of pages in the order of their updates. 
        The list of pages must adhere to all rules if it is to be considered valid. 
    Plan: 
        First we need to read in the instructions into a series of pairs and the page updates into a 2D container. 
        Then we need to look at each line of updates and make sure that they are in the correct order based on the rules.
            I think the best way to do this would actually be to loop through each line backwards and ensure that each page from right to left is ONLY behind pages that are valid. 
            If a line is valid we add it to a new vector and return that at the end of the function. 
            Once we have the valid lines, we should loop through each and determine the middle value(probably as simple as vec size / 2?) and add that to the current total. 
    Solution:
        Followed my plan nearly exactly and it worked. I think it's very inefficient because of all of the looping, but it still works so *shrug*

Day 5 Part 2: 
    Problem: 
        Need to take all of the incorrect lines and correct them according to the rules, then add up their middle numbers. 
    Plan: 
        oof. I already have the instances where a rule is broken, so I can add that to a separate vector of updates. 
        Then I'll need to pass that along to another function that will go through and re-order that based on the rules, then I'll need to perform another pass to see if any rules have now been broken. Once it passes through completely without a rule violation we can add the line to a vector and continue to the next line. Once all lines are done we can run the middle number grab and add and it should be fine. Definitely do not want to update in place though, so this will be a bit challenging for me. 
    Solution:
        Proposed solution worked once I figured out that j = line[i].size() is in fact different than j = line[i].size() -1.....

Day 6 Part 1: 
    Problem: 
        Need to watch the guards patrol. They are represented by a character ^, and the valid paths are represented by a ., with Blocking locations represented as character #. 
        They always move straight forward til they hit a block, then turn 90 degrees to the right and continue straight forward. 
        We need to find out how many spaces they move into before they exit out of the grid on one of the four sides. 
    Plan: 
        Probably create a node class with an enum that is "Guard", "ValidMove", "InvalidMove". Then just check the next direction and see if it's valid or invalid. Do this until we hit an edge(-1 on top or left or > size for the right and bottom.)
    Solution: 
        Basically exactly as I planned, used a set to ensure we only track any given position 1 time and then count the size of the set at the end. 

Day 6 Part 2: 
    Problem: 
        Need to see how many positions we can add an obstruction to to create an infinite loop. 
    Plan: 
        Basically run it with updating each position to have an obstruction and see if that would cause an inf loop. We know if it's an infinite loop if we hit the same location going the same direction.
    Solution: 
        Exactly as planned, but it took longer than I expected so I thought I was in an infinite loop and kept killing it early....should have thought about how long that would take instead of assuming I was wrong. 

        




