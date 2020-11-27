#include "List.h"

int main()
{
	try
	{

		List test, test1;
		for (int i = 1; i < 1025; i *= 2) test.addTail(i);
		for (int i = 27; i > 1; i /= 3) test1.addTail(i);

		List test2(6);
		test2 = test2 + test + test1;

		std::cout << test2;

		//test2.outputByHead();
		//test2.outputByTail();
	}
	catch (NodeErrorCode err)
	{
		return err;
	}

	return 0;
}

