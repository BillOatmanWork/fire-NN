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
- uses a unique NNUE (halfkp_256x2-32-32) evaluation
- fast alpha-beta search
- or optional experimental MCTS-UCT search
 (Monte Carlo Tree Search w/ Upper Confidence Bounds Applied to Trees) pure/no minmax

**fire-NN-08272022-004408 is now available**

| strength estimate                     |      |                    |      |      |   |       |
| ------------------------------------- | ---- | ------------------ | ---- | ---- | - |------ |       
|                                       | games|(+win, =draw, -loss)|  (%) |  Diff| SD|CFS (%)|
|    fire-NN-08272022-004408 (3438 Elo) |  7218|(+2315,=2395,-2508)| 48.7 %|
|    vs.                                |      |                   |       |       |    |       |
|    stockfish-15                       |   380| (  7,   58,  315)|   9.5 |   -397|  22|    0.0|
|    komodo-dragon-3.1                  |   380| (  3,   66,  311)|   9.5 |   -397|  21|    0.0|
|    berserk-9                          |   380| ( 20,   83,  277)|  16.2 |   -289|  17|    0.0|
|    koivisto_8.0                       |   380| ( 24,  113,  243)|  21.2 |   -231|  17|    0.0|
|    rubiChess-20220813                 |   380| ( 50,  149,  181)|  32.8 |   -126|  15|    0.0|
|    seer-v2.5                          |   380| ( 84,  137,  159)|  40.1 |    -70|  12|    0.0|
|    rofChade-3.0                       |   380| ( 78,  172,  130)|  43.2 |    -48|  13|    0.0|
|    rebel-15.1                         |   380| ( 96,  177,  107)|  48.6 |    -10|  14|   23.0|
|    slow64-2.9                         |   380| (110,  163,  107)|  50.4 |     +3|  12|   59.2|
|    fire-8242022                       |   380| (128,  144,  108)|  52.6 |    +19|  12|   93.4|
|    nemorino-6.00                      |   380| (149,  155,   76)|  59.6 |    +68|  12|  100.0|
|    wasp-6.00                          |   380| (155,  144,   81)|  59.7 |    +69|  14|  100.0|
|    ethereal-12.75                     |   380| (172,  124,   84)|  61.6 |    +83|  13|  100.0|
|    igel-3.1.0                         |   380| (172,  149,   59)|  64.9 |   +108|  13|  100.0|
|    tucano-10.00                       |   380| (196,  129,   55)|  68.6 |   +137|  13|  100.0|
|    clover-3.1                         |   380| (194,  134,   52)|  68.7 |   +138|  13|  100.0|
|    minic-3.24                         |   380| (201,  122,   57)|  68.9 |   +140|  14|  100.0|
|    xiphos-0.6                         |   379| (234,   91,   54)|  73.7 |   +182|  14|  100.0|
|    marvin-6.0.0                       |   379| (242,   85,   52)|  75.1 |   +194|  15|  100.0|
  
## monte-carlo search mode:  

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
