#include "ProgramManager.h"


int main(void) {
	{
		ProgramManager program;

		if (!program.Initialise())
		{
			return -1;
		}
		program.Run();
		program.ShutDown();
	}

	_CrtDumpMemoryLeaks();
    return 0;
}