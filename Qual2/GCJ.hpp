/**
* Google Code Jam Framework Declarations 2012 by Darren Vass
*/

#ifndef GOOGLE_CODE_JAM_HPP
#define GOOGLE_CODE_JAM_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <inttypes.h>
#include <cstdlib>

/** MODIFY  */
struct TestCaseData
{
    uint32_t NumOfGooglers; //N
    uint32_t Surprises;     //S
    uint32_t AtLeastThis;   //P
    std::vector<uint32_t>Points; //t^N
    
};

class GCJ{
private:
    uint32_t NumOfTestCases;

    std::string InputFileName;
    std::ifstream FileIn;
    
    std::string OutputFileName;
    std::ofstream FileOut;
    
    /** 
    * This is where the logic for solving a test case will go.
    * Will likely include other Functions.
    * @param TestCase The Data structure for this problem
    * @param TestCaseNumber unsigned int to know which case this is (For return)
    * @return String to be output to file. Should be already formatted.
    */
    std::string ComputeAnswer(TestCaseData &TestCase, uint32_t TestCaseNumber);
    
/** For parse debugging */
    void PrintTestCase(TestCaseData &TestCase, uint32_t TestCaseNumber)
    {
        std::cout << "== Test Case " << TestCaseNumber << " ==" << std::endl;
        
    }

public:
// Constructor/Destructors
    GCJ();
    ~GCJ(void){};

// Member Functions
    /**
    * Will Read in the InFile, Compute the Answer (Hopefully) and output 
    * the results to a file.
    * 
    * Open InFile and OutFile
    * While(InFile Not Finished (For 0 till # of test cases)
    *   Parse Next Test Case
    *   String Answer = ComputeAnswer(TestCase, TestCaseNumber)
    *   OutputFile << Answer
    *   
    */
    void Computationalize();
    
// Setters
    void SetInputFileName(std::string InFile); // Sets Outfile name to "Out_'InFile'"
    void SetOutputFileName(std::string OutFile);
    
// Getters
    std::string GetInputFileName(){ return InputFileName; }
    std::string GetOuptutFileName(){ return OutputFileName; }
};


#endif  /* GOOGLE_CODE_JAM_HPP */

