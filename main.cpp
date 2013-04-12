#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include "HedeHodoShell.h"

using namespace std;

int main(int argc, char ** argv){
    
 HedeHodoShell *shell = new HedeHodoShell();
    shell->executeCommand("makeDir photos");
    shell->executeCommand("makeDir videos");
    shell->executeCommand("makeDir Videos");
    shell->executeCommand("makeDir videos");
    
    
    shell->executeCommand("makeDoc photos");
    shell->executeCommand("makeDoc photos.txt");
    shell->executeCommand("makeDoc plainText");
    shell->executeCommand("makeDoc plainText");
    shell->executeCommand("makeDir plainText");
    
    
    shell->executeCommand("printWorkingDir");
    shell->executeCommand("changeWorkingDir videos");
    shell->executeCommand("printWorkingDir");
    shell->executeCommand("changeWorkingDir ..");
    shell->executeCommand("changeWorkingDir photos");
    shell->executeCommand("printWorkingDir");

    shell->executeCommand("makeDir lastYear");
    shell->executeCommand("changeWorkingDir thisYear");
    shell->executeCommand("makeDir thisYear");
    shell->executeCommand("changeWorkingDir thisYear");
    shell->executeCommand("printWorkingDir");
    shell->executeCommand("list"); // no children = no output
    
    shell->executeCommand("lineCount example.txt");
    shell->executeCommand("makeDoc example.txt");
    shell->executeCommand("lineCount example.txt");
    shell->executeCommand("appendLine example.txt 'data structures course is the best course ever'"); // APPEND: Document example.txt has 1 lines).
    shell->executeCommand("appendLine example.txt 'this is line two hell yes'"); // APPEND: Document example.txt has 2 lines.
    shell->executeCommand("appendLine example.txt 'this is the last line of the document happy coding'"); // APPEND: Document example.txt has 3 lines.
    shell->executeCommand("appendLine example.txt ''"); // APPEND: Document example.txt has 4 lines.
    shell->executeCommand("appendLine example.txt 'oh there is a new line'"); // APPEND: Document example.txt has 5 lines.
    shell->executeCommand("lineCount example.txt");
    
    shell->executeCommand("makeDoc anotherExample.txt");
    
    shell->executeCommand("printWorkingDir");
    shell->executeCommand("changeWorkingDir ..");
    shell->executeCommand("changeWorkingDir ..");
    
    shell->executeCommand("list");
    
    shell->executeCommand("remove Videos");
    shell->executeCommand("remove -r Videos");
    
    shell->executeCommand("makeDir anotherDir");
    shell->executeCommand("list");
    
    shell->executeCommand("changeWorkingDir photos");
    shell->executeCommand("changeWorkingDir thisYear");
    shell->executeCommand("list");
    
    shell->executeCommand("appendLine anotherExample.txt 'CS two zero two'");
    shell->executeCommand("appendLine anotherExample.txt 'programming assignment three'");
    shell->executeCommand("appendLine anotherExample.txt 'bilkent university'");
    
    shell->executeCommand("makeDir testDir");    
    shell->executeCommand("list");

    shell->executeCommand("head 2 example.txt");
    shell->executeCommand("head 10 anotherExample.txt");
    shell->executeCommand("head 1 testDir");
    
    shell->executeCommand("tail 2 anotherExample.txt");
    shell->executeCommand("tail 10 example.txt");
    shell->executeCommand("tail 1 testDir");
    
    shell->executeCommand("lineCount example.txt");
    shell->executeCommand("lineCount anotherExample.txt");
    shell->executeCommand("lineCount testDir");
    
    shell->executeCommand("uniqueWordCount example.txt");
    shell->executeCommand("uniqueWordCount anotherExample.txt");
    shell->executeCommand("uniqueWordCount testDir");
    
    
    shell->executeCommand("list");
    shell->executeCommand("remove -r example.txt");
    shell->executeCommand("remove example.txt");
    shell->executeCommand("list");

	delete shell;
    return 0;
}
