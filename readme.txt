
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
