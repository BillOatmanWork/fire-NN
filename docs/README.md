# Fire NN

![alt tag](https://raw.githubusercontent.com/FireFather/fire-NN/master/docs/fire.png)

A strong UCI chess engine including a unique NNUE evaluation created from SF & LC0 shared data

- fire without NNUE can be found here: https://github.com/FireFather/fire
- fire w/ NNUE from self-play can be found here: https://github.com/FireFather/fire-zero

## features
- c++17
- windows & linux
- uci
- 64-bit
- smp (to 256 threads)
- configurable hash (to 1024 GB)
- ponder
- multiPV
- analysis (infinite) mode
- chess960 (Fischer Random)
- syzygy tablebases
- adjustable contempt setting
- fast perft & divide
- bench (includes ttd time-to-depth calculation)
- timestamped bench, perft/divide, and tuner logs
- asychronous cout (acout) class using std::unique_lock<std::mutex>
- uci option searchtype random w/ uniform_real_distribution & mesenne_twister_engine
- reads engine.conf on startup for search, eval, pawn, and material parameters
- uses a NNUE evaluation
- fast alpha-beta search
- or optional experimental MCTS-UCT search
 (Monte Carlo Tree Search w/ Upper Confidence Bounds Applied to Trees) pure/no minmax

**fire-NN-08272022-004408 is now available**

![alt tag](https://raw.githubusercontent.com/FireFather/fire-NN/master/docs/Fire_8.NN.MCx64.png)

Fire-NN has undergone months of meticulous analysis and refactoring using many of the most modern C++ tools available today, including Clang, ReSharper C++, and Visual Studio Code Analysis, ensuring the production of extremely fast highly optimized and stable executables.


## available Windows binaries
- **x64 bmi2** = fast pgo binary (for modern 64-bit systems w/ BMI2 instruction set) if you own a Intel Haswell or newer cpu, this compile should be faster.
- **x64 avx2** = fast pgo binary (for modern 64-bit systems w/ AVX2 instruction set) if you own a modern AMD cpu, this compile should be the fastest.

- **windows** : fire-NN_x64_x64_bmi2.exe or fire-NN_x64_avx2.exe


run 'bench' at command line to determine which binary runs best/fastest on your system. for greater accuracy, run it twice and calculate the average of both results.

please see **http://chesslogik.wix.com/fire** for more info

## compile it yourself
- **windows** (visual studio) use included project files: Fire.vcxproj or Fire.sln
- **minGW** run one of the included bash shell scripts: make_bmi2.sh, make_avx2.sh, or make_all.sh 
- **ubuntu** type 'make profile-build ARCH=x86-64-bmi2', 'make profile-build ARCH=x86-64-avx2', etc.

## uci options
- **Hash** size of the hash table. default is 64 MB.
- **Threads** number of processor threads to use. default is 1, max = 128.
- **MultiPV** number of pv's/principal variations (lines of play) to be output. default is 1.
- **Contempt** higher contempt resists draws.
- **MoveOverhead** Adjust this to compensate for network and GUI latency. This is useful to avoid losses on time.
- **MinimumTime** Absolute minimum time (in ms) to spend on a single move. Also useful to avoid losses on time.
- **Ponder** also think during opponent's time. default is false.
- **UCI_Chess960** play chess960 (often called FRC or Fischer Random Chess). default is false.
- **Clear Hash** clear the hash table. delete allocated memory and re-initialize.
- **SyzygyProbeDepth** engine begins probing at specified depth. increasing this option makes the engine probe less.
- **EngineMode** choose NNUE (default), or random.
- **MCTS** enable Monte Carlo Tree Search w/UCT (Upper Confidence Bounds Applied to Trees)
- **SyzygyProbeLimit** number of pieces that have to be on the board in the endgame before the table-bases are probed.
- **Syzygy50MoveRule** set to false, tablebase positions that are drawn by the 50-move rule will count as a win or loss.
- **SyzygyPath** path to the syzygy tablebase files.
- **NnueEvalFile** path to the NNUE evaluation file.

## acknowledgements
many of the ideas & techiques incorporated into Fire are documented in detail here
- [Chess Programming Wiki](https://www.chessprogramming.org)

and some have been adapted from the super strong open-source chess engine
- [Stockfish](https://github.com/official-stockfish/Stockfish)

and others
- [Ippolit](https://github.com/FireFather/ippolit)
- [Robbolito](https://github.com/FireFather/robbolito)
- [Firebird](https://github.com/FireFather/firebird)
- [Ivanhoe](https://www.chessprogramming.org/IvanHoe)
- [Houdini](https://www.cruxis.com/chess/houdini.htm)
- [Gull](https://github.com/FireFather/seagull)

the endgame table bases are implemented using code adapted from Ronald de Man's
- [Syzygy EGTBs & probing code](https://github.com/syzygy1/tb)

The NNUE implementation utilizes a modified version of Daniel Shaw's/Cfish excellent nnue probe code:
- [nnue-probe](https://github.com/dshawul/nnue-probe/)

the MCTS implementation is derived from Stephane Nicolet's work
- https://github.com/snicolet/Stockfish/commits/montecarlo

if you are interested in learning about my particular testing methodology, I've explained it in some detail here:
http://www.chessdom.com/fire-the-chess-engine-releases-a-new-version/

## license
Fire is distributed under the GNU General Public License. Please read LICENSE for more information.

please see **http://chesslogik.wix.com/fire** for more info

## Does Fire-NN play like Stockfish? 
No. Here are the results of Don Daily's SIM program (default values) today to measure Fire 8.NN move selection vs the last 4 versions of Stockfish:

![alt tag](https://raw.githubusercontent.com/FireFather/fire-NN/master/docs/matrix.png)

As you can see Stockfish 14.1 and Stockfish 15 make the same moves ~64% of the time (see row 4, column 5)

Fire 8.NN has an excellent score of ~43.34 % (see row 1), making different moves than SF almost 60% of the time.

The Sim tool can be downloaded here:
https://komodochess.com/downloads.htm
(bottom of page)


best regards-

firefather@telenet.be
