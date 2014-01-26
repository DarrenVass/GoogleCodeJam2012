/**
* Google Code Jam Framework Definitions for 2012
* By: Darren Vass
*
*/

#include "GCJ.hpp"

#include <sstream>
#include <algorithm>
#include <set>

using namespace std; //I am lazy

/** ------------ Solving Function ------------- */
string GCJ::ComputeAnswer(TestCaseData &ThisData, uint32_t TCNum)
{
    cout << "Min " << ThisData.Min << " and Max " << ThisData.Max << endl;
    uint64_t RecycledNumbers = 0;
    stringstream ss;
    
    if(ThisData.Max > 10)
    {
	for(int i = ThisData.Min; i <= ThisData.Max; i++)
	{
	    ss << i;
	    /**
	    * Start at Y = (1 to Len - 1). Move Y end digits to the front.
	    */
	    set<uint32_t>Values;
	    for(int j = 1; j < ThisData.NumOfDigits; j++)
	    { // Possible forg NumOfDigits - 1 Permutations.
		string NewString = ss.str();
		if(MoveToStart(NewString, j))
		{
		    uint32_t CurNum = atoi(NewString.c_str());
		    if(CurNum > i and CurNum <= ThisData.Max)
		    {
			pair<set<uint32_t>::iterator, bool> ret;
			ret = Values.insert(CurNum);
			if(ret.second)
			{
			    RecycledNumbers++;
			}
		    }
		}
	    }
	    ss.str("");
	}
    }
    // Else it's 0 recycled numbers
    

// For returning answer string (Properly Formatted already)
    ss << "Case #" << TCNum << ": " << RecycledNumbers;
    return ss.str();
}

bool GCJ::MoveToStart(std::string &StringIn, int Num)
{
    string Temp = StringIn.substr(Num);
    if(Temp.c_str()[0] == '0'){ return false; }
    Temp += StringIn.substr(0, Num);
    StringIn = Temp;
    return true;
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
	memset(ThisCase.MinChar, 0, 8);
	memset(ThisCase.MaxChar, 0, 8);
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
       
    // Parse I of items
        string WholeLine;
        getline(FileIn, WholeLine);
        stringstream LineStream(WholeLine);
        for(int i = 0; i < 2; i++)
        {
            getline(LineStream, TempNum, ' ');
	    switch(i)
	    {
		case 0:
		    ThisCase.Min = atoi(TempNum.c_str());
		    for(int i = 0; i < TempNum.length(); i++)
		    {
			ThisCase.MinChar[i] = TempNum.c_str()[i];
		    }
		break;
		case 1:
		    ThisCase.Max = atoi(TempNum.c_str());
		    ThisCase.NumOfDigits = TempNum.length();
		    for(int i = 0; i < TempNum.length(); i++)
		    {
			ThisCase.MaxChar[i] = TempNum.c_str()[i];
		    }
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
