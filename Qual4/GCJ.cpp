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


// For returning answer string (Properly Formatted already)
    stringstream ss;
    ss << "Case #" << TCNum << ": " << 123;
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

    // Parse I of items
        string WholeLine;
        getline(FileIn, WholeLine);
        stringstream LineStream(WholeLine);
        for(int i = 0; i < 3; i++)
        {
            getline(LineStream, TempNum, ' ');
            switch(i)
            {
		case 0:
		    ThisCase.Height = atoi(TempNum.c_str());
		break;
		case 1:
		    ThisCase.Width = atoi(TempNum.c_str());
		break;
		case 2:
		    ThisCase.MaxDistance = atoi(TempNum.c_str());
		break;
	    }
        }
        
        cout << ThisCase.Width << "*" << ThisCase.Height << endl;
	
	for(int y = 0; y < ThisCase.Height; y++)
	{
	    getline(FileIn, TempNum);
	    for(int x = 0; x < ThisCase.Width; x++)
	    {
		ThisCase.Room[x][y] = TempNum.c_str()[x];
		cout << ThisCase.Room[x][y];
		if(ThisCase.Room[x][y] == 'X')
		{
		    ThisCase.PosX = x;
		    ThisCase.PosY = y;
		}
	    }
	    cout << endl;
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
