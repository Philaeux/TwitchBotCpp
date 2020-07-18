#include <memory>

#include "TwitchBotCpp.h"
#include "Configuration.h"

using namespace std;

int main(int argc, char** argv)
{
	shared_ptr<Configuration> cfg = make_shared<Configuration>();
	cfg->parse_config(argc, argv);	

	return 0;
}
