Operating the program:

// ----------------------------------------------------------- //

cd pathFinding

chosing an algorithm:
algorithm names = DFS, BFS, A*, Greedy, Bi-directional, MBA*

./search.sh <textFile> <algorithm name> <optional param=GUI> 
**Optional gui param available

Optional testing framework (not enough error handling for random maps - may need to close program if not loading)

./search.sh <textFile> <algorithm name> <optional param=TEST> 
**All algorithms except Bi-direcitonal and MBA* used on the tests, just easier 
for the script to have a param added on
** --- See the output.txt file to observe csv results -- **

// ----------------------------------------------------------- //


References:
Russell, S & Norvig, P 2010, Artificial Intelligence A Modern Approach, Pearson Education, Upper Saddle River, New Jersey. 

GUI tutorial:
https://www.sfml-dev.org/tutorials/2.4/graphics-draw.php

MIT License

Copyright (c) 2017 Cormac

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
