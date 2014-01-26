/**
* Google Code Jam Framework main for 2012
* By: Darren Vass
*
*/

#include "GCJ.hpp"      // Google Code Jam 'Framework'

#include <string>

using namespace std;    //I am lazy

/**
* Forward Declarations
*/
static int ParseArgs (int argc, char *argv[]);

GCJ GCJHandle;

int main (int argc, char *argv[])
{
    if (ParseArgs (argc, argv))
    { 
        cout << "Problem parsing command line arguments" << endl;
        return 1; 
    }
    
    // OutputFileName is set by default to OUT_<InputFileName>
    //GCJHandle.SetOutputFileName("NAMEGOESHERE");
    
    /** Handles parsing input, computing answer & output of answer. */    
    GCJHandle.Computationalize();
    
    return 0;    
}


/**
* Usage Instructions
*/
static void Usage (FILE *f, char *s)
{
    fprintf (f,
        "\n"
        "Usage: %s -f [Input File]\n\n"
        "Options:\n"
        "  -h?            This help\n"
        "  -f <File>      The input data file\n"
        "  -o <File>      The output data file\n", s
    );
}

/**
* Parse the command line arguments.
*/
static int ParseArgs (int argc, char *argv[])
{
    int c;
    while ((c = getopt (argc, argv, "f:o:")) != -1) {

        switch (c) {
            case  -1:
                continue;
            case 'f':
                GCJHandle.SetInputFileName(optarg);
                //Auto Set OutputFileName to "Out_'optarg'"
            break;
            case 'o':
                GCJHandle.SetOutputFileName(optarg);
            break;
            default:
                Usage (stderr, argv[0]);
                return -1;
        }
    }

    return 0;
}
