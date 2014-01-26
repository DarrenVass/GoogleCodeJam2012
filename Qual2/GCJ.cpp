/**
* Google Code Jam Framework Definitions for 2012
* By: Darren Vass
*
*/

#include "GCJ.hpp"

#include <sstream>

using namespace std; //I am lazy

/** ------------ Solving Function ------------- */
string GCJ::ComputeAnswer(TestCaseData &ThisData, uint32_t TCNum)
{
    uint32_t Answers = 0, RemainingSurprises = ThisData.Surprises;
    vector<uint32_t>::iterator it;
    for(it = ThisData.Points.begin(); it != ThisData.Points.end(); it++)
    {
        if(ThisData.AtLeastThis == 0){ Answers++; continue; }
        else if(ThisData.AtLeastThis == 1 and *it >= 1){ Answers++; continue; }
        // X surprises, 8 At least.
        if(*it >= ((ThisData.AtLeastThis * 3) - 2))
        {// 7 7 8 22+ auto include.
            Answers++;
        }
        else if(RemainingSurprises > 0 and (*it >=  (ThisData.AtLeastThis * 3) - 4))
        { // 20-21 possible.
            if((*it == (ThisData.AtLeastThis * 3) - 3) and *it >= 3)
            {// 21 6 7 8
                RemainingSurprises--;
                Answers++;
            }
            else if((*it == (ThisData.AtLeastThis * 3) - 4) and *it >= 2)
            {//20 6 6 8
                RemainingSurprises--;
                Answers++;
            }
        }
        // Else Impossible to be an answer. (19-)
    }
    cout << endl;

// For returning answer string (Properly Formatted already)
    stringstream ss;
    ss << "Case #" << TCNum << ": " << Answers;
    cout << "Return " << ss.str() << endl;
    return ss.str();
}

/** ----------- FILE Manipulation ------------- */

void GCJ::Computationalize()
{
// Open Files
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
    // Full line == getline(FileIn, STRING)
    /* Read in numbered space seperated line
    for(int i = 0; i < NUMOFVALUES; i++)
    {
        string Value;
        if(FileIn.good())
        {
            getline(FileIn, Value, " ");
        }
        else
        {
            cout << "Problem getting Value # " << i << " of " << NUMOFVALUES << endl;
            exit(1);
        }
    }    
    */
       
        cout << "Items == ";
        string WholeLine;
        getline(FileIn, WholeLine);
        cout << "WHOLE LINE = " << WholeLine << endl;
        stringstream LineStream(WholeLine);
        for(int i = 0; i < (3 + ThisCase.NumOfGooglers); i++)
        {
            getline(LineStream, TempNum, ' ');
            switch(i)
            {
                case 0: //N
                    ThisCase.NumOfGooglers = atoi(TempNum.c_str());
                break;
                case 1: //S
                    ThisCase.Surprises = atoi(TempNum.c_str());
                break;
                case 2: //P
                    ThisCase.AtLeastThis = atoi(TempNum.c_str());
                break;
                default:
                    ThisCase.Points.push_back(atoi(TempNum.c_str()));
                break;
            }
        }
        cout << endl;


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
    if(OutputFileName.length() == 0) //TODO len("") ?= 0
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
