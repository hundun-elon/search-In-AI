#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

const string GOAL = "ABCDEFGHIJKLMNO#";

// Moves and their effects on index position
const int dRow[] = {-1, 1, 0, 0}; // UP, DOWN, LEFT, RIGHT
const int dCol[] = {0, 0, -1, 1};

// A* Node Structure
struct State
{
      string board;
      int blankPos;
      int g; // Cost so far
      int h; // Misplaced Tiles heuristic

      State(string b, int pos, int cost) : board(b), blankPos(pos), g(cost)
      {
            h = misplacedTiles(b);
      }

      int f() const
      {
            return g + h;
      }

      // Custom comparison for priority queue (min-heap)
      bool operator>(const State &other) const
      {
            return this->f() > other.f();
      }

      // Misplaced Tiles heuristic function
      static int misplacedTiles(const string &b)
      {
            int count = 0;
            for (int i = 0; i < 16; i++)
            {
                  if (b[i] != GOAL[i] && b[i] != '#')
                  {
                        count++;
                  }
            }
            return count;
      }
};

// Swap function to move tiles
string swapTiles(const string &board, int pos1, int pos2)
{
      string newBoard = board;
      swap(newBoard[pos1], newBoard[pos2]);
      return newBoard;
}

// A* Search Algorithm
int aStarSearch(string start)
{
      priority_queue<State, vector<State>, greater<State>> pq;
      unordered_set<string> visited;

      int blankPos = start.find('#');
      pq.push(State(start, blankPos, 0));
      visited.insert(start);

      while (!pq.empty())
      {
            State current = pq.top();
            pq.pop();

            // If goal state is reached, return the cost
            if (current.board == GOAL)
                  return current.g;

            int row = current.blankPos / 4;
            int col = current.blankPos % 4;

            // Try all 4 moves
            for (int i = 0; i < 4; i++)
            {
                  int newRow = row + dRow[i];
                  int newCol = col + dCol[i];

                  if (newRow >= 0 && newRow < 4 && newCol >= 0 && newCol < 4)
                  {
                        int newPos = newRow * 4 + newCol;
                        string newBoard = swapTiles(current.board, current.blankPos, newPos);

                        // If new state is not visited, add to priority queue
                        if (visited.find(newBoard) == visited.end())
                        {
                              pq.push(State(newBoard, newPos, current.g + 1));
                              visited.insert(newBoard);
                        }
                  }
            }
      }
      return -1;
}

int main()
{
      string start;
      cin >> start;

      int result = aStarSearch(start);
      cout << result << endl;

      return 0;
}
