/**
* By: Darren Vass
*
*/

#include "GCJ.hpp"

#include <sstream>
#include <map>

using namespace std; //I am lazy

/** ------------ Solving Function ------------- */
string GCJ::ComputeAnswer(TestCaseData &ThisData, uint32_t TCNum)
{
    multimap<uint32_t, uint32_t>Mappings;
    
    std::vector<std::pair<uint32_t, uint32_t> >::iterator it;
    for(it = ThisData.Pairs.begin(); it != ThisData.Pairs.end(); it++)
    {
        Mappings.insert(*it);
        cout << "O: " << it->first << "->" << it->second << endl;
    }
    
    bool Duplicate = false;
    multimap<uint32_t, uint32_t>::iterator it2, it3, it4;
    for(it2 = Mappings.begin(); it2 != Mappings.end(); it2++)
    {
        for(it3 = Mappings.begin(); it3 != Mappings.end(); it3++)
        {
            if(it2->second == it3->first)
            {
                for(it4 = Mappings.begin(); it4 != Mappings.end(); it4++)
                {
                    if(it4->first == it2->first and it4->second == it3->second)
                    {
                        Duplicate = true;
                        cout << "Duplicate " << it4->first << "->" << it4->second << endl;
                        goto CONTINUE;
                    }
                }
                cout << "A: " << it2->first << "->" << it3->second << " from " << it3->first << "->" << it3->second << endl;;
                Mappings.insert(make_pair(it2->first, it3->second));
            }
        }
    }
    
CONTINUE:

// For returning answer string (Properly Formatted already)
    stringstream ss;
    ss << "Case #" << TCNum << ": ";
    
    if(Duplicate){ ss << "Yes"; }
    else { ss << "No"; }
    
    
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
        
        getline(FileIn, TempNum);
        ThisCase.NumOfClasses = atoi(TempNum.c_str());
        
        for(int i = 1; i <= ThisCase.NumOfClasses; i++)
        {
            string TempNum2;
            getline(FileIn, TempNum);
            stringstream LineStream(TempNum);
            getline(LineStream, TempNum2, ' ');
            int Number = atoi(TempNum2.c_str());
            for(int j = 0; j < Number; j ++)
            {
                getline(LineStream, TempNum2, ' ');
                ThisCase.Pairs.push_back(make_pair(i, atoi(TempNum2.c_str())));
            }
        }       
        
        
        
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
