/*
  Fire is a freeware UCI chess playing engine authored by Norman Schmidt.

  Fire utilizes many state-of-the-art chess programming ideas and techniques
  which have been documented in detail at https://www.chessprogramming.org/
  and demonstrated via the very strong open-source chess engine Stockfish...
  https://github.com/official-stockfish/Stockfish.
  
  Fire is free software: you can redistribute it and/or modify it under the
  terms of the GNU General Public License as published by the Free Software
  Foundation, either version 3 of the License, or any later version.

  You should have received a copy of the GNU General Public License with
  this program: copying.txt.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "cpuid.h"
#include "options.h"
#include "util/util.h"
#include "uci.h"

std::unique_ptr<options> params;

int main(const int argc, char* argv[])
{
	// display engine name, version, platform, and bmis
	acout() << util::engine_info() << std::endl;

	// display cpu info
	cpuid();
	acout() << std::endl;

	// read parameters from disk (engine.conf)
	params = std::make_unique<options>(argc, argv);
	auto p = params->value<std::string>("param");
	params->read_param_file(p);

	// initialize system using default hash (64 MB)
	init(default_hash);
	
	// enter infinite loop and parse for input
	uci_loop(argc, argv);
	return 0;
}
