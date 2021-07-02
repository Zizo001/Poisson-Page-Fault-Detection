/***************************************************************************
* File: program3.cpp
* Author: Zeyad Elhabbab
* Date: 4/25/2021
* Procedures:
* main          
- Performs 1000 experiments. Each experiment generates a new set of  random Poisson numbers
  and calls the 3 algorithms. Working set sizes range from 2-20, with each set size having
  1000 runs. After 1000 runs, the results are printed out

* FifoCounting  
- Generates set sizes ranging from 2-20 and applies the FIFO algorithm to the Poisson Numbers 

* LruCounting
- Generates set sizes ranging from 2-20 and applies the LRU algorithm to the Poisson Numbers 

* ClockCounting
- Generates set sizes ranging from 2-20 and applies the Clock algorithm to the Poisson Numbers 
***************************************************************************/

#include <iostream>     //used for input/output
#include <random>       //used for random number engine and poisson distribution functions
#include <time.h>       //used for time() functions in order to increase seed randomness 

using namespace std;    //using standard C++ library

/***************************************************************************
* int FifoCounting( int pArr[])
* Author: Zeyad Elhabbab
* Date: 4/25/2021
* Description:         Uses the FIFO algorithm to calculate the number of faults
                       given an array of integers. It performs this for working
                       set sizes 2-20.
*
* Parameters:
    pArr[]  I/P int    The array of random Poisson integers that will be run through
                       the FIFO algorithm.
    
**************************************************************************/
int FifoCounting( int pArr[])
{
    int faults = 0;											//total number of faults
    int fFaults = 0;										//used to subtract the value from faults to obtain faults per set size
	
    for(int setSize = 2; setSize <= 20; setSize++) //runs set sizes from 2 - 20. Note that the <= does mean k goes up to 21, but the 
                                                   //results are consistent for working set sizes 2-20. It is simply the way the 
                                                   //algorithm's iterations are coded
    {
        int fifo[setSize] = {0};                   //array for length of working set size
        int fifoIndex = 0;                         //serves as an index for our number array 
        bool fifoHitCheck = false;                 //determines whether we have a hit

        for (int i = 0; i < 1000; i++)             //runs through each working set size 1000 times
        {
            
            for(int j = 0; j < setSize; j++)       //index to be used in comparison of values 
            {
                if((fifo[j] == pArr[i]))           //compares value of fifo array to poisson number array
                {
                    fifoHitCheck = true;           //if equal, set fifoHitCheck to true and exit loop
                    break;                         //break to immedietly exit loop since we don't need to check the rest of the loop
                }
            }
            if(fifoHitCheck == false)              //checks to see if we got a hit. If not, then increment fault and index
            {
                fifo[fifoIndex] = pArr[i];         //set the value of our number equal to the given poisson number from pArr
                faults++;                          //increment the number of faults
                fifoIndex++;                       //increment the index for the next run

                if(fifoIndex >= setSize)           //if the fifoIndex is greater than the capacity, then we have reached capacity
                                                   //and so we will reset
                {
                    fifoIndex = 0;                 //reset our index to beginning of the array 
                }
            }

            else                                   //if not, then set out fifohitCheck to false
            {
                fifoHitCheck = false;              //set fifohitCheck to false
            }
        }

        //output the current amount of tallied faults for each working set size. Used 
        //for both debugging and to export the values into an external program to graph results
        
        cout << "FIFO: " << setSize << " " << faults - fFaults << endl;     //print out algorithm name, working set size, and the faults over 1000 iterations on that set size
        fFaults = faults;                                                   //updates faults
        
    }
    return faults;
}

/***************************************************************************
* int LRUCounting( int pArr[])
* Author: Zeyad Elhabbab
* Date: 4/25/2021
* Description:          Uses the LRU algorithm to calculate the number of faults
                        given an array of integers. It performs this for working
                        set sizes 2-20. In addition to that, it employs a weight
                        system in order to determine how recently did a page trace
                        get used.
*
* Parameters:
    pArr[]  I/P int     The array of random Poisson integers that will be run through
                        the LRU algorithm.
    
**************************************************************************/
int LruCounting( int pArr[])
{
    int faults = 0;											//total number of faults
    int fFaults = 0;										//used to subtract the value from faults to obtain faults per set size
	
    for(int setSize = 2; setSize <= 20; setSize++)          //runs set sizes from 2 - 20. Note that the <= does mean k goes up to 21, but the 
                                                            //results are consistent for working set sizes 2-20. It is simply the way the
                                                            //algorithm's iterations are coded                                                        
    {
        int lru[setSize] = {0};                             //array for length of working set size
        int lruWeight[setSize] = {0};                       //array for weight at each index
        int weightIndex = 0;                                //initializing a variable for weight
        bool lruHitCheck = false;                           //determines whether we have a hit

        for (int i = 0; i < 1000; i++)                      //runs through each working set size 1000 times         
        {
            for(int j = 0; j < setSize; j++)                //index to be used in comparison of values
            {
                if((lru[j] == pArr[i]))                     //compares value of lru array to poisson number array
                {
                    weightIndex++;                          //increments the weight index
                    lruWeight[j] = weightIndex;             //sets the element's weight to the weight index
                    lruHitCheck = true;                     //if equal, set lruHitCheck to true and exit loop
                    break;                                  //break to immedietly exit loop since we don't need to check the rest of the loop
                }
            }

            if(lruHitCheck == false)                        //checks to see if we got a hit. If not, then increment fault and index
            {
                int lruIndex = 0;                           //initialize our index to beginning of the array

                for(int w = 0; w < setSize ;w++)            //make a counter to help iterate weight assignment
                {
                    if(lruWeight[w] < lruWeight[lruIndex])  //if weight at index w is less than our current number's weight
                    {
                        lruIndex = w;                       //set our elements weight to w
                    }
                }

                lru[lruIndex] = pArr[i];                    //set the value of our number equal to the given poisson number from pArr  
                weightIndex++;                              //increment the weight index
                lruWeight[lruIndex] = weightIndex;          //update the weight to the new weight index value
                faults++;                                   //increment the number of faults
            }

            
            else                                            //if not, set the lruHitCheck to false
            {
                lruHitCheck = false;                        //set lruHitCheck to false
            }
            
        }
        
        //output the current amount of tallied faults for each working set size. Used 
        //for both debugging and to export the values into an external program to graph results

        cout << "LRU: " << setSize << " " << faults - fFaults << endl;      //print out algorithm name, working set size, and the faults over 1000 iterations on that set size
        fFaults = faults;                                                   //updates faults

    }
    return faults;
}

/***************************************************************************
* int ClockCounting( int pArr[])
* Author: Zeyad Elhabbab
* Date: 4/25/2021
* Description:          Uses the Clock algorithm to calculate the number of faults
                        given an array of integers. It performs this for working
                        set sizes 2-20. In addition to that, it employs a use bit
                        in order to determine whether to give a page trace a 'second'
                        chance
*
* Parameters:
    pArr[]  I/P int     The array of random Poisson integers that will be run through
                        the Clock algorithm.
    
**************************************************************************/
int ClockCounting( int pArr[])
{
    int faults = 0;											//total number of faults
    int fFaults = 0;										//used to subtract the value from faults to obtain faults per set size
	
    for(int setSize = 2; setSize <= 20; setSize++)          //runs set sizes from 2 - 20. Note that the <= does mean k goes up to 21, but the 
                                                            //results are consistent for working set sizes 2-20. It is simply the way the
                                                            //algorithm's iterations are coded 
    {
        int clock[setSize] = {0};                           //array for length of working set size
        bool clockUseBit[setSize] = {false};                //array for use bit at each index in boolean form
        bool clockHitCheck = false;                         //determines whether we have a hit

        for (int i = 0; i < 1000; i++)                      //runs through each working set size 1000 times         
        {
            for(int j = 0; j < setSize; j++)                //index to be used in comparison of values
            {
                if((clock[j] == pArr[i]))                   //compares value of clock array to poisson number array
                {
                    clockUseBit[j] = true;                  //sets the element's use bit to true, or 1
                    clockHitCheck = true;                   //if equal, set clockHitCheck to true and exit loop
                    break;                                  //break to immedietly exit loop since we don't need to check the rest of the loop
                }
            }

            if(clockHitCheck == false)                      //checks to see if we got a hit. If not, then increment fault and index
            {
                int clockIndex = 0;                         //initialize our index to beginning of the array

                for(int w = 0; w < setSize ;w++)            //make a counter to help iterate weight assignment
                {
                    if(clockUseBit[w] == false)             //if use bit at index w is false, or 0
                    {
                        clockIndex = w;                     //set our clock index to w
                        break;                              //break to immedietly exit loop since we don't need to check the rest of the loop
                    }
                    if( w == setSize-1)                     //comparing the loop index "w" to the setSize
                                                            //subtract one from the setSize, if not then we would be
                                                            //comparing the size of the array to the length of the array
                    {
                        for(int r = 0; r < setSize ;r++)    
                        {
                            clockUseBit[r] = false;
                        }
                        w = -1;                             //setting w to be -1 because if  set it to 0, when the loop
                                                            //looks around it will add one to w and it would become 1 when we are needing it to be 0
                    }
                }

                clock[clockIndex] = pArr[i];                //set the value of our number equal to the given poisson number from pArr  
                clockUseBit[clockIndex] = true;             //set the use bit to true
                faults++;                                   //increment the number of faults
            }

            
            else                                            //if not, set the clockHitCheck to false
            {
                clockHitCheck = false;                      //set clockHitCheck to false
            }
            
        }
        
        //output the current amount of tallied faults for each working set size. Used 
        //for both debugging and to export the values into an external program to graph results

        cout << "Clock: " << setSize << " " << faults - fFaults << endl;    //print out algorithm name, working set size, and the faults over 1000 iterations on that set size
        fFaults = faults;                                                   //updates faults
    }
    return faults;
}

/***************************************************************************
* int main( int argc, char *argv [])
* Author: Zeyad Elhabbab
* Date: 4/25/2021
* Description: Performs 1000 experiments to calculate the number of faults
               detected by FIFO, LRU, and Clock algorithms. Every expriment,
               a new set of random page traces is generated
*
* Parameters:
    argc    I/P int        The # of arguements on the command line
    argv    I/P char* []   The arguements on said command line

**************************************************************************/

int main(int argc, char *argv []) { 

    int fifoFaults = 0;                                              //variable for FIFO faults
    int lruFaults = 0;                                               //variable for LRU faults
    int clockFaults = 0;                                             //variable for clock faults
    
    for(int expirment = 0; expirment < 1000; expirment++)            //perform 1000 expriments in total
    {
        default_random_engine generator;                             //initialize our random engine
        poisson_distribution<int> distribution(10);                  //call our poisson_distribution functions and pass lambda = 10

        unsigned randomSeed = time(0);                               //generate a random seed using time() function
        srand(randomSeed);                                           //use srand to further randomize the seed
        generator.seed(randomSeed);                                  //insert the random seed into the random engine. Ensures every iteration is significantly random

        int poissonArr[1000];                                        //create an array to store 1000 random page traces

        for (int i = 0; i < 1000; i++)                               //loop to iterate generating and storing random numbers
            {
                int poissonN = distribution(generator);              //set our Poisson number into the randomly generated value using the function calls above
                poissonArr[i] = poissonN;                            //place current poisson number into array                
            }
            fifoFaults += FifoCounting(poissonArr);                  //call the FIFO algorithm and pass the Poisson number array
            lruFaults += LruCounting(poissonArr);                    //call the LRU algorithm and pass the Poisson number array
            clockFaults += ClockCounting(poissonArr);                //call the Clock algorithm and pass the Poisson number array
    }

    cout << "The total amount of faults calculated by the FIFO algorithm: "  << fifoFaults << endl;       //print out the total number of faults calculated from FIFO algorithm
    cout << "The total amount of faults calculated by the LRU algorithm: "   << lruFaults << endl;        //print out the total number of faults calculated from LRU algorithm
    cout << "The total amount of faults calculated by the Clock algorithm: " << clockFaults << endl;     //print out the total number of faults calculated from LRU algorithm

    return 0;
}

/********************************************************************/