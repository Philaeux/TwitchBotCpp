#include "TwitchBotCpp.h"

#include <boost/program_options.hpp>
using namespace boost::program_options;

using namespace std;

int main(int argc, char* argv[])
{
	// Parse parameters
	string cfg = "default.cfg";
	options_description desc("Allowed options");
	desc.add_options()
		("help,h", "print usage message")
		("cfg", value<string>()->default_value(cfg), "configuration file to use");

	variables_map vm;
	store(parse_command_line(argc, argv, desc), vm);
	

	cout << cfg << endl;

	if (vm.count("help")) {  
		cout << desc << "\n";
		return 0;
	}

	return 0;
}
