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
    cout << "Line = " << ThisData.Line << endl;
    string NewString = "";

    for(int i = 0; i < ThisData.Line.length(); i++)
    {
        char NextChar;
        
        switch(ThisData.Line.c_str()[i])
        {
            case 'a': NextChar = 'y'; break;
            case 'b': NextChar = 'h'; break;
            case 'c': NextChar = 'e'; break;
            case 'd': NextChar = 's'; break;
            case 'e': NextChar = 'o'; break;
            case 'f': NextChar = 'c'; break;
            case 'g': NextChar = 'v'; break;
            case 'h': NextChar = 'x'; break;
            case 'i': NextChar = 'd'; break;
            case 'j': NextChar = 'u'; break;
            case 'k': NextChar = 'i'; break;
            case 'l': NextChar = 'g'; break;
            case 'm': NextChar = 'l'; break;
            case 'n': NextChar = 'b'; break;
            case 'o': NextChar = 'k'; break;
            case 'p': NextChar = 'r'; break;
            case 'q': NextChar = 'z'; break;
            case 'r': NextChar = 't'; break;
            case 's': NextChar = 'n'; break;
            case 't': NextChar = 'w'; break;
            case 'u': NextChar = 'j'; break;
            case 'v': NextChar = 'p'; break;
            case 'w': NextChar = 'f'; break;
            case 'x': NextChar = 'm'; break;
            case 'y': NextChar = 'a'; break;
            case 'z': NextChar = 'q'; break;
            case ' ': NextChar = ' '; break;
        }
        NewString += NextChar;
    }


// For returning answer string (Properly Formatted already)
    stringstream ss;
    ss << "Case #" << TCNum << ": " << NewString;
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
	string TempLine;
    	getline(FileIn, TempLine);
	ThisCase.Line = TempLine;
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
