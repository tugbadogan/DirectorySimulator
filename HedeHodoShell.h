#ifndef _HEDEHODOSHELL_H
#define _HEDEHODOSHELL_H

#include <string>

using namespace std;

class HedeHodoShell {
    public:
		~HedeHodoShell();
        /*
         * This method implements the simplified version of the shell
         * for HedeHodo Operating System.
         * 
         * Read the details from HW3 pdf.
         */
        void executeCommand(string command);
};

#endif
