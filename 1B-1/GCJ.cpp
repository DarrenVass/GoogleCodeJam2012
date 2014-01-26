/**
* By: Darren Vass
*
*/

#include "GCJ.hpp"

#include <sstream>
#include <algorithm>

using namespace std; //I am lazy

/** ------------ Solving Function ------------- */
string GCJ::ComputeAnswer(TestCaseData &ThisData, uint32_t TCNum)
{
    uint64_t Sum = 0;
    uint64_t Max = 0;
    vector<float> Answers;
    vector<uint32_t>::iterator it;
    for(it = ThisData.Scores.begin(); it!= ThisData.Scores.end(); it++)
    {
        Sum += *it;
        if(*it > Max){ Max = *it; }
    }
    uint32_t MinScore = 0;
    vector<uint32_t>Sorted = ThisData.Scores;
    sort(Sorted.begin(), Sorted.end());
    
    uint64_t PointsLeft = Sum;
    while(PointsLeft > ThisData.Scores)
    {
        for(it = Sorted.begin(); it != Sorted.end(); it++)
        {
            if(*it < MinScore){PointsLeft--;}
        }
        MinScore++
    }
    
    
    MinScore = Max + (float)PointsLeft/ThisData.Scores.size();

  
    // Need to be tied for last.
    for(it = ThisData.Scores.begin(); it!= ThisData.Scores.end(); it++)
    {
        double Answer = (double)(MinScore - *it) / Sum;
        Answers.push_back(Answer);
    }

// For returning answer string (Properly Formatted already)
    stringstream ss;
    ss << "Case #" << TCNum << ":";
    vector<float>::iterator itA;
    for(itA = Answers.begin(); itA != Answers.end(); itA++)
    {
        ss << " " << *itA;
    }
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
        ThisCase.NumOfContestants = atoi(NOC.c_str());
        for(int i = 0; i < ThisCase.NumOfContestants; i++)
        {
            getline(LineStream, NOC, ' ');
            ThisCase.Scores.push_back(atoi(NOC.c_str()));
        }
        
        
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
    
    /*
    // Parse Credit (C)
        getline(FileIn, TempNum);
        ThisCase.Credit = atoi(TempNum.c_str());
        cout << "Credit == " << ThisCase.Credit << endl;
        
    // Parse NumOfitems (I)
        getline(FileIn, TempNum);
        ThisCase.NumOfItems = atoi(TempNum.c_str());
        cout << "NumOfItems == " << ThisCase.NumOfItems << endl;
        
    // Parse I of items
        cout << "Items == ";
        string WholeLine;
        getline(FileIn, WholeLine);
        stringstream LineStream(WholeLine);
        for(int i = 0; i < ThisCase.NumOfItems; i++)
        {
            getline(LineStream, TempNum, ' ');
            cout << " [" << i << "]" << TempNum;
            ThisCase.Items.push_back(atoi(TempNum.c_str()));
        }
        cout << endl;
    */

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
