#include <string>
#include <fstream>
#include <stdexcept>

using namespace std;

class firefoxcontrol
{
	public:
		int createprofile(string name);
		int deleteprofile(string name);

	
	
	    string getprofilepath(string name);
};
