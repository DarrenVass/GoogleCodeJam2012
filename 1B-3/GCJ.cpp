/**
* By: Darren Vass
*
*/

#include "GCJ.hpp"

#include <sstream>

using namespace std; //I am lazy

/** ------------ Solving Function ------------- */
string GCJ::ComputeAnswer(TestCaseData &ThisData, uint32_t TCNum)
{
    vector<uint32_t>::iterator it;
    for(it = ThisData.Numbers.begin(); it != ThisData.Numbers.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
    
    bool Possible = false;
    vector<uint32_t> Nums1, Nums2;
    vector<uint32_t>::iterator it1, it2;
    
    for(int Num = 2; Num <= 19; Num++)
    { // Num of Elements to compare 
        for(int Num2 = 1; Num2 <= 20-Num; Num2++)
        {
            for(int i = 0; i < 20; i ++)
            {
                for(int j = 0; j < 20; j++)
                {
                    
                }
            }
        }
    }
      
    stringstream ss;
    if(Possible)
    {
        ss << "Case #" << TCNum << ":\n";
        for(it1 = Nums1.begin(); it1 != Nums1.end(); it1++)
        {
            ss << *it1 << " ";
        }
        ss << "\n";
        for(it2 = Nums1.begin(); it2 != Nums1.end(); it2++)
        {
            ss << *it2 << " ";
        }
    }
    else
    {
        ss << "Case #" << TCNum << ": Impossible";
    }

// For returning answer string (Properly Formatted already)
    
    cout << "Return " << ss.str() << endl;
    return ss.str();
}

void GCJ::Computationalize()
{
    FileIn.open(InputFileName.c_str(), ifstream::in);
    if(FileIn.good()){ cout << "FileIn Opened and good" << endl; }
    else { 
        cout << "Problem opening FileIn" << endl; 
        exit(1);
    }
    FileOut.open(OutputFileName.c_str(), ofstream::out);
    if(FileOut.good()){ cout << "FileOut Opened and good" << endl; }
    else { 
        cout << "Problem opening FileOut" << endl; 
        exit(1);
    }
    
// Parse Number of Test Cases
    string TempNum;
    getline(FileIn, TempNum);
    cout << "Number of testcases == " << TempNum << endl;
    NumOfTestCases = atoi(TempNum.c_str());
    uint32_t CurrentTestCaseNum = 0;
    
// Parse rest of file.
    while(FileIn.good() and !FileIn.eof())
    {
        CurrentTestCaseNum++;
        if(CurrentTestCaseNum > NumOfTestCases)
        {
            cout << CurrentTestCaseNum << " > NumOfTestCases (" << NumOfTestCases << ")" << endl;
            exit(1);
        }
        
    // Parsing of each test case.
    /** MODIFY */
        TestCaseData ThisCase;
        string LINE;
        getline(FileIn, LINE);
        stringstream LineStream(LINE);
        string NOC;
        getline(LineStream, NOC, ' ');
        uint32_t NUM = atoi(NOC.c_str());
        for(int i = 0; i < NUM; i++)
        {
            getline(LineStream, NOC, ' ');
            ThisCase.Numbers.push_back(atoi(NOC.c_str()));
        }
        
    
    // Call solver function
        string TestCaseAnswer = ComputeAnswer(ThisCase, CurrentTestCaseNum);
        
    // Output the Answer
        cout << "Answer = " <<  TestCaseAnswer << endl;
        if(FileOut.good()){ FileOut << TestCaseAnswer << endl; }
        cout << "========================" << endl;
    }
    
// Check for early exit
    if(FileIn.eof()){ cout << "File Input EOF" << endl; }
    else 
    { 
        cout << "File Input while loop exited but not EOF. Good = " << FileIn.good() << endl; 
    }
    
    FileIn.close();
    FileOut.close();
}

/** --------------- Constructor --------------- */
GCJ::GCJ()
{
    OutputFileName = "";
    InputFileName = "";
}

/** --------------- SETTERS ------------------- */

void GCJ::SetInputFileName(string InFile)
{
    InputFileName = InFile;
    cout << "InputFileName to " << InputFileName << endl;
    if(OutputFileName.length() == 0)
    {
        OutputFileName = "Out_" + InFile; //Lazy naming convention.
        cout << "OutputFileName to " << OutputFileName << endl;
    }
}

void GCJ::SetOutputFileName(string OutFile)
{
    OutputFileName = OutFile;
    cout << "OutputFileName to " << OutputFileName << endl;
}
